#include "cfe.h"
#include "amc_test_utils.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_tbl_hooks.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"
#include "ut_osapi_stubs.h"
#include "ut_osfileapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_evs_stubs.h"

#include <time.h>

/*
 * PWM Config table for testing
 */
AMC_PwmConfigTbl_t PwmConfigTbl = {
        1000,
        2000,
        3000
};

/*
 * Mixer Config table for testing
 */
MultirotorMixer_ConfigTable_t MixerConfigTbl = {
   1.0,          // RollScale
   1.0,          // PitchScale
   1.0,          // YawScale
   1.0,          // IdleSpeed
   1.0,          // DeltaOutMax
   8,            // RotorCount
   MIXER_OCTA_X, // Geometry
   {  // RollScale, PitchScale, YawScale, OutScale
       { 1.0,       1.0,        1.0,      1.0     },
       { 1.0,       1.0,        1.0,      1.0     },
       { 1.0,       1.0,        1.0,      1.0     },
       { 1.0,       1.0,        1.0,      1.0     },
       { 1.0,       1.0,        1.0,      1.0     },
       { 1.0,       1.0,        1.0,      1.0     },
       { 1.0,       1.0,        1.0,      1.0     },
       { 1.0,       1.0,        1.0,      1.0     }
   }
};

/*
 * Function Definitions
 */

void AMC_Test_Setup(void)
{
    /* initialize test environment to default state for every test */

    Ut_CFE_EVS_Reset();
    Ut_CFE_FS_Reset();
    Ut_CFE_TIME_Reset();
    Ut_CFE_TBL_Reset();
    Ut_CFE_SB_Reset();
    Ut_CFE_ES_Reset();
    Ut_OSAPI_Reset();
    Ut_OSFILEAPI_Reset();

    Ut_CFE_TBL_AddTable(AMC_PWM_CONFIG_TABLE_FILENAME, (void *) &PwmConfigTbl);
    Ut_CFE_TBL_AddTable(AMC_MIXER_CONFIG_TABLE_FILENAME, (void *) &MixerConfigTbl);
}

void AMC_Test_TearDown(void) {

}
