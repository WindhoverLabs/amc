
#ifndef AMC_TEST_UTILS_H
#define AMC_TEST_UTILS_H

/*
 * Includes
 */

#include "amc_app.h"

extern AMC_AppData_t  AMC_AppData;

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Definitions
 */

void AMC_Test_Setup(void);
void AMC_Test_TearDown(void);


#ifdef __cplusplus
}
#endif

#endif /* AMC_TEST_UTILS_H */

