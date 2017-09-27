
#include "uttest.h"

#include "amc_app_test.h"
#include "amc_cmds_test.h"
#include "amc_config_tbl_test.h"
#include "amc_cds_tbl_test.h"

int main(void)
{   
    AMC_App_Test_AddTestCases();
    AMC_Cmds_Test_AddTestCases();
    AMC_Config_Tbl_Test_AddTestCases();
    AMC_CDS_Tbl_Test_AddTestCases();

    return(UtTest_Run());

}

