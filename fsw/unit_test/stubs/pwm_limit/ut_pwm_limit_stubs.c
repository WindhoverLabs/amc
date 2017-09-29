/****************************************************************************
*
*   Copyright (c) 2017 Windhover Labs, L.L.C. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
* 3. Neither the name Windhover Labs, L.L.C. nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
* OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
* AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

#include "cfe.h"
#include "utassert.h"
#include "ut_pwm_limit_stubs.h"
#include "ut_pwm_limit_hooks.h"
#include <string.h>

Ut_PwmLimit_HookTable_t           Ut_PwmLimit_HookTable;
Ut_PwmLimit_ReturnCodeTable_t     Ut_PwmLimit_ReturnCodeTable[UT_PWMLIMIT_MAX_INDEX];

void Ut_PwmLimit_Reset(void)
{
    memset(&Ut_PwmLimit_HookTable, 0, sizeof(Ut_PwmLimit_HookTable));
    memset(&Ut_PwmLimit_ReturnCodeTable, 0, sizeof(Ut_PwmLimit_ReturnCodeTable));
}

void Ut_PwmLimit_SetFunctionHook(uint32 Index, void *FunPtr)
{
    if      (Index == UT_PWMLIMIT_INIT_INDEX)     { Ut_PwmLimit_HookTable.PwmLimit_Init = FunPtr; }
    else if (Index == UT_PWMLIMIT_CALC_INDEX)     { Ut_PwmLimit_HookTable.PwmLimit_Calc = FunPtr; }
    else if (Index == UT_HRT_ELAPSED_TIME_INDEX)  { Ut_PwmLimit_HookTable.hrt_elapsed_time = FunPtr; }
    else
    {
        printf("Unsupported PwmLimit Index In SetFunctionHook Call %lu\n", Index);
        UtAssert_True(FALSE, "Unsupported PwmLimit Index In SetFunctionHook Call");
    }
}

void Ut_PwmLimit_SetReturnCode(uint32 Index, int32 RtnVal, uint32 CallCnt)
{
    if (Index < UT_PWMLIMIT_MAX_INDEX)
    {
        Ut_PwmLimit_ReturnCodeTable[Index].Value = RtnVal;
        Ut_PwmLimit_ReturnCodeTable[Index].Count = CallCnt;
    }
    else
    {
        printf("Unsupported PwmLimit Index In SetReturnCode Call %lu\n", Index);
        UtAssert_True(FALSE, "Unsupported PwmLimit Index In SetReturnCode Call");
    }
}

boolean Ut_PwmLimit_UseReturnCode(uint32 Index)
{
    if (Ut_PwmLimit_ReturnCodeTable[Index].Count > 0)
    {
        Ut_PwmLimit_ReturnCodeTable[Index].Count--;
        if (Ut_PwmLimit_ReturnCodeTable[Index].Count == 0)
            return(TRUE);
    }
    else if (Ut_PwmLimit_ReturnCodeTable[Index].ContinueReturnCodeAfterCountZero == TRUE)
    {
        return(TRUE);
    }

    return(FALSE);
}

void Ut_PwmLimit_ContinueReturnCodeAfterCountZero(uint32 Index)
{
    Ut_PwmLimit_ReturnCodeTable[Index].ContinueReturnCodeAfterCountZero = TRUE;
}

void PwmLimit_Init(PwmLimit_Data_t *limit)
{
    /* Check for specified return */
    if (Ut_PwmLimit_UseReturnCode(UT_PWMLIMIT_INIT_INDEX))
        Ut_PwmLimit_ReturnCodeTable[UT_PWMLIMIT_INIT_INDEX].Value;

    /* Check for Function Hook */
    if (Ut_PwmLimit_HookTable.PwmLimit_Init)
        Ut_PwmLimit_HookTable.PwmLimit_Init(limit);
}

void PwmLimit_Calc(const boolean armed, const boolean pre_armed, const unsigned num_channels, const uint16 reverse_mask,
            const uint16 *disarmed_pwm, const uint16 *min_pwm, const uint16 *max_pwm,
            const float *output, uint16 *effective_pwm, PwmLimit_Data_t *limit)
{
    /* Check for specified return */
    if (Ut_PwmLimit_UseReturnCode(UT_PWMLIMIT_CALC_INDEX))
        Ut_PwmLimit_ReturnCodeTable[UT_PWMLIMIT_CALC_INDEX].Value;

    /* Check for Function Hook */
    if (Ut_PwmLimit_HookTable.PwmLimit_Calc)
        Ut_PwmLimit_HookTable.PwmLimit_Calc(armed, pre_armed, num_channels, reverse_mask,
                disarmed_pwm, min_pwm, max_pwm,
                output, effective_pwm, limit);
}

uint64 hrt_elapsed_time(uint64 *input)
{
    /* Check for specified return */
    if (Ut_PwmLimit_UseReturnCode(UT_HRT_ELAPSED_TIME_INDEX))
        return Ut_PwmLimit_ReturnCodeTable[UT_HRT_ELAPSED_TIME_INDEX].Value;

    /* Check for Function Hook */
    if (Ut_PwmLimit_HookTable.hrt_elapsed_time)
        return Ut_PwmLimit_HookTable.hrt_elapsed_time(input);

    return 0;
}
