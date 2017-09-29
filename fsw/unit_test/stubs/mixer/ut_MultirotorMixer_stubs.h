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
#ifndef UT_MULTIROTORMIXER_STUBS_H
#define UT_MULTIROTORMIXER_STUBS_H

#include "cfe.h"
#include "utassert.h"
#include "mixer/MultirotorMixer.h"
#include <string.h>
#include "mixer/MixerTables.h"
//#include "UT_MultirotorMixer.h"

typedef enum
{
    UT_MULTIROTORMIXER_SETCONFIGTABLEPTR_INDEX,
    UT_MULTIROTORMIXER_MIX_INDEX,
    UT_MULTIROTORMIXER_GET_SATURATION_STATUS_INDEX,
    UT_MULTIROTORMIXER_GROUPS_REQUIRED_INDEX,
    UT_MULTIROTORMIXER_SET_TRIM_INDEX,
    UT_MULTIROTORMIXER_SET_THRUST_FACTOR_INDEX,
    UT_MULTIROTORMIXER_MAX_INDEX
} Ut_MultirotorMixer_INDEX_t;

typedef struct
{
    int32  (*SetConfigTablePtr)(MultirotorMixer_ConfigTablePtr_t &);
    uint32 (*mix)(float *, uint32, uint16 *);
    uint16 (*get_saturation_status)(void);
    void   (*groups_required)(uint32 &);
    uint32 (*set_trim)(float);
    void   (*set_thrust_factor)(float);
} Ut_MultirotorMixer_HookTable_t;

typedef struct
{
    int32 SetConfigTablePtr_Return;
    int32 mix_Return;
    int32 get_saturation_status_Return;
    int32 groups_required_Return;
    int32 set_trim_Return;
    int32 set_thrust_factor_Return;
} Ut_MultirotorMixer_Returns_t;

typedef struct
{
    int32   Value;
    uint32  Count;
    boolean ContinueReturnCodeAfterCountZero;
} Ut_MultirotorMixer_ReturnCodeTable_t;

int32 Ut_MultirotorMixer_Init(void);
void  Ut_MultirotorMixer_Reset(void);
void  Ut_MultirotorMixer_SetFunctionHook(uint32 Index, void *FunPtr);
void  Ut_MultirotorMixer_SetReturnCode(uint32 Index, int32 RtnVal, uint32 CallCnt);
void  Ut_MultirotorMixer_ContinueReturnCodeAfterCountZero(uint32 Index);

#endif
