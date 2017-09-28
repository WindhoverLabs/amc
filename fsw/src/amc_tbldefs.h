#ifndef AMC_TBLDEFS_H
#define AMC_TBLDEFS_H

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "cfe.h"
#include "amc_platform_cfg.h"

/************************************************************************
** Local Defines
*************************************************************************/

/**
 * \brief Defines the table identification name used for the PWM
 * configuration table registration.
 */
#define AMC_PWM_CONFIG_TABLENAME ("PWMCFG_TBL")

/**
 * \brief Defines the table identification name used for the Mixer
 * configuration table registration.
 */
#define AMC_MIXER_CONFIG_TABLENAME ("MIXERCFG_TBL")

/** \brief Definition for a single config table entry */
typedef struct
{
    /** \brief Motor disarmed value for this device. */
    uint32  PwmDisarmed;

    /** \brief Motor minimum value for this device.  Keep this high enough to overcome stiction but low enough not to cause lift.*/
    uint32  PwmMin;

    /** \brief Motor maximum value for this device. */
    uint32  PwmMax;
} AMC_PwmConfigTbl_t;


#ifdef __cplusplus
}
#endif

#endif /* AMC_TBLDEFS_H */

/************************/
/*  End of File Comment */
/************************/
