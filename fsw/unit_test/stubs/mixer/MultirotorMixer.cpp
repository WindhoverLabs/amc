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
#include "mixer/MultirotorMixer.h"
#include <string.h>
#include "mixer/MixerTables.h"
#include "UT_MultirotorMixer.h"



MultirotorMixer::MultirotorMixer(
    ControlCallback control_cb,
    cpuaddr cb_handle) :
        Mixer(control_cb, cb_handle),
        m_ThrustFactor(0.0f)
{
//    memset(&m_SaturationStatus, 0, sizeof(m_SaturationStatus));
}

MultirotorMixer::~MultirotorMixer()
{
}

int32 MultirotorMixer::SetConfigTablePtr(
    MultirotorMixer_ConfigTablePtr_t &ConfigTablePtr)
{
    return 0;
};

uint32
MultirotorMixer::mix(float *outputs, uint32 space, uint16 *status_reg)
{
    return 0;
};

void
MultirotorMixer::update_saturation_status(uint32 index, bool clipping_high, bool clipping_low)
{
}

uint16 MultirotorMixer::get_saturation_status()
{
    return 0;
};

void
MultirotorMixer::groups_required(uint32 &groups)
{

};

uint32 MultirotorMixer::set_trim(float trim)
{
    return 0;
}

int32  UT_MultirotorMixer::Init(void)
{
    return 0;

};

void   UT_MultirotorMixer::Reset(void)
{

};

void   UT_MultirotorMixer::SetFunctionHook(uint32 Index, void *FunPtr)
{

};

void   UT_MultirotorMixer::SetReturnCode(uint32 Index, int32 RtnVal, uint32 CallCnt)
{

};

void   UT_MultirotorMixer::ContinueReturnCodeAfterCountZero(uint32 Index)
{

};

int32  UT_MultirotorMixer::SetConfigTablePtr(MultirotorMixer_ConfigTablePtr_t &ConfigTablePtr)
{
    return 0;
};

uint32 UT_MultirotorMixer::mix(float *outputs, uint32 space, uint16 *status_reg)
{
    return 0;
};

uint16 UT_MultirotorMixer::get_saturation_status(void)
{
    return 0;
};

void   UT_MultirotorMixer::groups_required(uint32 &groups)
{

};



