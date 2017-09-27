    
#ifndef AMC_MSG_H
#define AMC_MSG_H

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


/************************************************************************
** Local Defines
*************************************************************************/

/************************************************************************
** AMC Command Codes
*************************************************************************/

/** \amccmd Noop 
**  
**  \par Description
**       Implements the Noop command that demonstrates the AMC task is alive
**
**  \amccmdmnemonic \AMC_NOOP
**
**  \par Command Structure
**       #AMC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \AMC_CMDACPTCNT - command counter will increment
**       - The #AMC_CMD_INF_EID informational event message will be 
**         generated when the command is received
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \AMC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #AMC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #AMC_RESET_CC
*/
#define AMC_NOOP_CC                 (0)

/** \amccmd Reset Counters
**  
**  \par Description
**       Resets the amc housekeeping counters
**
**  \amccmdmnemonic \AMC_TLMRST
**
**  \par Command Structure
**       #AMC_NoArgCmd_t
**
**  \par Command Verification
**       Successful execution of this command may be verified with
**       the following telemetry:
**       - \b \c \AMC_CMDACTPCNT       - command counter will be cleared
**       - \b \c \AMC_CMDRJCTCNT       - command error counter will be cleared
**       - The #AMC_CMD_INF_EID debug event message will be 
**         generated when the command is executed
** 
**  \par Error Conditions
**       This command may fail for the following reason(s):
**       - Command packet length not as expected
** 
**  \par Evidence of failure may be found in the following telemetry: 
**       - \b \c \AMC_CMDRJCTCNT - command error counter will increment
**       - Error specific event message #AMC_MSGID_ERR_EID
**
**  \par Criticality
**       None
**
**  \sa #AMC_NOOP_CC
*/
#define AMC_RESET_CC                (1)

/************************************************************************
** Local Structure Declarations
*************************************************************************/

/** 
**  \brief No Arguments Command
**  For command details see #AMC_NOOP_CC, #AMC_RESET_CC
**  Also see #AMC_SEND_HK_MID
*/
typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} AMC_NoArgCmd_t;

/** 
**  \brief AMC application housekeeping data
*/
typedef struct
{
    /** \brief cFE SB Tlm Msg Hdr */
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];

    /** \amctlmmnemonic \AMC_CMDACPTCNT
        \brief Count of accepted commands */
    uint8              usCmdCnt;   

    /** \amctlmmnemonic \AMC_CMDRJCTCNT
        \brief Count of failed commands */
    uint8              usCmdErrCnt; 

} AMC_HkTlm_t;


#ifdef __cplusplus
}
#endif

#endif /* AMC_MSG_H */

/************************/
/*  End of File Comment */
/************************/
