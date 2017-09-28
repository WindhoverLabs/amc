#include "amc_msg.h"
#include "amc_cds_tbl_test.h"
#include "amc_test_utils.h"
#include "uttest.h"
#include "ut_osapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_es_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"

void AMC_CDS_Tbl_Test_Case1(void)
{

}


void AMC_CDS_Tbl_Test_AddTestCases(void)
{
    UtTest_Add(AMC_CDS_Tbl_Test_Case1, AMC_Test_Setup, AMC_Test_TearDown, "AMC_CDS_Tbl_Test_Case1");
}


