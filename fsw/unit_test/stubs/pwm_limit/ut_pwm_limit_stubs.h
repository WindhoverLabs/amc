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

#ifndef UT_PWMLIMIT_STUBS_H_
#define UT_PWMLIMIT_STUBS_H_

#include "pwm_limit/pwm_limit.h"

typedef enum
{
    UT_PWMLIMIT_INIT_INDEX,
    UT_PWMLIMIT_CALC_INDEX,
    UT_HRT_ELAPSED_TIME_INDEX,
    UT_PWMLIMIT_MAX_INDEX
} Ut_PwmLimit_INDEX_t;

typedef struct
{
    void   (*PwmLimit_Init)(PwmLimit_Data_t *limit);
    void   (*PwmLimit_Calc)(const boolean armed, const boolean pre_armed, const unsigned num_channels, const uint16 reverse_mask,
            const uint16 *disarmed_pwm, const uint16 *min_pwm, const uint16 *max_pwm,
            const float *output, uint16 *effective_pwm, PwmLimit_Data_t *limit);
    uint64 (*hrt_elapsed_time)(uint64 *input);
} Ut_PwmLimit_HookTable_t;

typedef struct
{
    int32   Value;
    uint32  Count;
    boolean ContinueReturnCodeAfterCountZero;
} Ut_PwmLimit_ReturnCodeTable_t;

void Ut_PwmLimit_Reset(void);
void Ut_PwmLimit_SetFunctionHook(uint32 Index, void *FunPtr);
void Ut_PwmLimit_SetReturnCode(uint32 Index, int32 RtnVal, uint32 CallCnt);
void Ut_PwmLimit_ContinueReturnCodeAfterCountZero(uint32 Index);

#endif
