#include "cfe.h"
#include "utassert.h"
#include "ut_osapi_stubs.h"
#include <time.h>
#include <string.h>

Ut_PX4Lib_HookTable_t        Ut_PX4Lib_HookTable;
Ut_PX4Lib_ReturnCodeTable_t  Ut_PX4Lib_ReturnCodeTable[UT_PX4LIB_MAX_INDEX];


int32 Ut_PX4Lib_Init(void)
{

}


void Ut_PX4Lib__Clear(void)
{
    Ut_PX4Lib_Init();
}




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
