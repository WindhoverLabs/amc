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
* 3. Neither the name Windhover Labs nor the names of its 
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

/************************************************************************
** Pragmas
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <errno.h>

#include "cfe.h"

#include "amc_app.h"
#include "amc_msg.h"
#include "amc_version.h"
#include <math.h>
#include "params_msg.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AMC oAMC;


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AMC::AMC() :
    MixerObject(AMC::ControlCallback, (cpuaddr)&CVT.ActuatorControls0)
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
AMC::~AMC()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 AMC::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;
    uint32  ind = 0;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("AMC - Failed to register with EVS (0x%08X)\n", (unsigned int)iStatus);
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 AMC::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
                                 AMC_SCH_PIPE_DEPTH,
                                 AMC_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(AMC_UPDATE_MOTORS_MID, SchPipeId, CFE_SB_Default_Qos, AMC_SCH_PIPE_WAKEUP_RESERVED);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(AMC_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                                     "Sch Pipe failed to subscribe to AMC_UPDATE_MOTORS_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto AMC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(AMC_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, AMC_SCH_PIPE_SEND_HK_RESERVED);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(AMC_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to AMC_SEND_HK_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto AMC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_ARMED_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(AMC_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_ACTUATOR_ARMED_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto AMC_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_ACTUATOR_CONTROLS_0_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(AMC_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to PX4_ACTUATOR_CONTROLS_0_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto AMC_InitPipe_Exit_Tag;
        }

    }
    else
    {
        (void) CFE_EVS_SendEvent(AMC_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create SCH pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto AMC_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
                                 AMC_CMD_PIPE_DEPTH,
                                 AMC_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(AMC_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(AMC_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
                                     "CMD Pipe failed to subscribe to AMC_CMD_MID. (0x%08X)",
                                     (unsigned int)iStatus);
            goto AMC_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(AMC_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to create CMD pipe (0x%08X)",
                                 (unsigned int)iStatus);
        goto AMC_InitPipe_Exit_Tag;
    }

AMC_InitPipe_Exit_Tag:
    return (iStatus);
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AMC::InitData()
{
    /* Init actuator outputs message */
    CFE_SB_InitMsg(&ActuatorOutputs,
            PX4_ACTUATOR_OUTPUTS_MID, sizeof(ActuatorOutputs), TRUE);

    /* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
                   AMC_HK_TLM_MID, sizeof(HkTlm), TRUE);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* AMC initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 AMC::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("AMC - Failed to init events (0x%08X)\n", (unsigned int)iStatus);
        goto AMC_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto AMC_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto AMC_InitApp_Exit_Tag;
    }

    iStatus = MixerObject.SetConfigTablePtr(MixerConfigTblPtr);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(AMC_MIXER_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init mixer (0x%08x)",
                                 (unsigned int)iStatus);
        goto AMC_InitApp_Exit_Tag;
    }

    PwmLimit_Init(&PwmLimit);

    iStatus = InitDevice();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(AMC_DEVICE_INIT_ERR_EID, CFE_EVS_ERROR,
                                 "Failed to init device (0x%08x)",
                                 (unsigned int)iStatus);
        goto AMC_InitApp_Exit_Tag;
    }

AMC_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(AMC_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
                                 AMC_MAJOR_VERSION,
                                 AMC_MINOR_VERSION,
                                 AMC_REVISION,
                                 AMC_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("AMC - Application failed to initialize\n");
        }
    }

    return (iStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 AMC::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(AMC_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(AMC_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case AMC_UPDATE_MOTORS_MID:
                UpdateMotors();
                break;

            case AMC_SEND_HK_MID:
                ReportHousekeeping();
                break;

            case PX4_ACTUATOR_ARMED_MID:
                memcpy(&CVT.ActuatorArmed, MsgPtr, sizeof(CVT.ActuatorArmed));
                break;

            case PX4_ACTUATOR_CONTROLS_0_MID:
                memcpy(&CVT.ActuatorControls0, MsgPtr, sizeof(CVT.ActuatorControls0));
                break;

            default:
                (void) CFE_EVS_SendEvent(AMC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid SCH msgId (0x%04X)", (unsigned short)MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* TODO: If there's no incoming message, you can do something here, or 
         * nothing.  Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else if (iStatus == CFE_SB_TIME_OUT)
    {
        /* TODO: If there's no incoming message within a specified time (via the
         * iBlocking arg, you can do something here, or nothing.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        UpdateMotors();
        iStatus = CFE_SUCCESS;
    }
    else
    {
        (void) CFE_EVS_SendEvent(AMC_RCVMSG_ERR_EID, CFE_EVS_ERROR,
			  "SCH pipe read error (0x%08X).", (unsigned int)iStatus);
    }

    return (iStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send Params                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AMC::SendParams()
{
	int32  Status=CFE_SUCCESS;
	PARAMS_SendParamDataCmd_t ParamDataMsg = {0};
	CFE_SB_MsgPtr_t 	CmdMsgPtr;

	/* Iterate over param table and broadcast to SB */
	for(int i = 0; i < AMC_MAX_PARAMS; ++i)
	{
		/* Init Airliner message */
		CFE_SB_InitMsg(&ParamDataMsg, PARAMS_PARAM_MID, sizeof(PARAMS_SendParamDataCmd_t), FALSE);
		CmdMsgPtr = (CFE_SB_MsgPtr_t)&ParamDataMsg;
		CFE_SB_SetCmdCode(CmdMsgPtr, PARAMS_PARAM_DATA_CC);

		//PwmConfigTblPtr
		/* Update parameter message with current table index values */
//		ParamDataMsg.param_data.value = PARAMS_AppData.ParamTblPtr->params[i].param_data.value;
//		memcpy(ParamDataMsg.param_data.name, PARAMS_AppData.ParamTblPtr->params[i].param_data.name,
//				sizeof(PARAMS_AppData.ParamTblPtr->params[i].param_data.name));
//		ParamDataMsg.param_data.type = PARAMS_AppData.ParamTblPtr->params[i].param_data.type;
//		ParamDataMsg.param_count = PARAMS_AppData.ParamCount;
//		ParamDataMsg.param_index = param_index;

		/* Send to SB */
		Status = CFE_SB_SendMsg(CmdMsgPtr);
		if (Status != CFE_SUCCESS)
		{
			OS_printf("Error sending param to SB\n");
			/* TODO: Decide what to do if the send message fails. */
		}
	}
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Params Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void AMC::ProcessNewParamCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
        	/* If params is sending param data route to GCS */
            case PARAMS_PARAM_DATA_CC:
                //HkTlm.CmdCnt++;
//                (void) CFE_EVS_SendEvent(MAVLINK_CMD_INF_EID, CFE_EVS_INFORMATION,
//                                  "Recvd param data to route to GCS");

                /* Encode param into mavlink and send */
                break;

            default:
                break;
        }
    }
}

PARAMS_ParamData_t* AMC::GetParamData(char* name)
{
	PARAMS_ParamData_t* retData = 0;

	/* Iterate over passed table to find param with passed name */
	for(int i = 0; i < AMC_MAX_PARAMS; ++i)
	{
		if (strcmp(PwmConfigTblPtr->param_data[i].name, name) == 0)
		{
			retData = &PwmConfigTblPtr->param_data[i];
			break;
		}
	}

	return retData;
}

float AMC::GetParamValue(char* name)
{
	float retValue = 0; // what would an expected default return be, and could it impact behavior?

	/* Iterate over passed table to find param with passed name */
	for(int i = 0; i < AMC_MAX_PARAMS; ++i)
	{
		if (strcmp(PwmConfigTblPtr->param_data[i].name, name) == 0)
		{
			retValue = PwmConfigTblPtr->param_data[i].value;
			break;
		}
	}

	return retValue;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void AMC::ProcessCmdPipe()
{
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages until the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case AMC_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(AMC_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid CMD msgId (0x%04X)", (unsigned short)CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent(AMC_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08X)", (unsigned int)iStatus);
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process AMC Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void AMC::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case AMC_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(AMC_CMD_NOOP_EID, CFE_EVS_INFORMATION,
                                  "Recvd NOOP. Version %d.%d.%d.%d",
                                  AMC_MAJOR_VERSION,
                                  AMC_MINOR_VERSION,
                                  AMC_REVISION,
                                  AMC_MISSION_REV);
                break;

            case AMC_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(AMC_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send AMC Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void AMC::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void AMC::SendActuatorOutputs()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&ActuatorOutputs);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&ActuatorOutputs);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean AMC::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult  = TRUE;
    uint16  usMsgLen = 0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            bResult = FALSE;
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            (void) CFE_EVS_SendEvent(AMC_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* AMC Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AMC_AppMain()
{
    oAMC.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* AMC Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AMC::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("AMC - Failed to register the app (0x%08X)\n", (unsigned int)iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(AMC_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(AMC_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(AMC_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(AMC_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(AMC_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(AMC_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Command all motors to stop.                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AMC::StopMotors(void)
{
    uint16 disarmed_pwm[AMC_MAX_MOTOR_OUTPUTS];

    for (uint32 i = 0; i < AMC_MAX_MOTOR_OUTPUTS; i++) {
        disarmed_pwm[i] = GetParamValue("PWN_DISARMED");
    }

    SetMotorOutputs(disarmed_pwm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Mix actuator controls and update motor speeds accordingly.      */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void AMC::UpdateMotors(void)
{
    const uint16 reverse_mask = 0;
    uint16 disarmed_pwm[AMC_MAX_MOTOR_OUTPUTS];
    uint16 min_pwm[AMC_MAX_MOTOR_OUTPUTS];
    uint16 max_pwm[AMC_MAX_MOTOR_OUTPUTS];
    uint16 pwm[AMC_MAX_MOTOR_OUTPUTS];
    PX4_ActuatorOutputsMsg_t outputs;

    ActuatorOutputs.timestamp = CVT.ActuatorControls0.timestamp;

    /* Do mixing */
    ActuatorOutputs.Count = MixerObject.mix(ActuatorOutputs.Output, 0, 0);

    /* Disable unused ports by setting their output to NaN */
    for (size_t i = ActuatorOutputs.Count;
         i < sizeof(ActuatorOutputs.Output) / sizeof(ActuatorOutputs.Output[0]);
         i++) {
        ActuatorOutputs.Output[i] = NAN;
    }

    for (uint32 i = 0; i < AMC_MAX_MOTOR_OUTPUTS; i++) {
        disarmed_pwm[i] = GetParamValue("PWN_DISARMED");
        min_pwm[i] = GetParamValue("PWN_MIN");
        max_pwm[i] = GetParamValue("PWN_MAX");
    }

    PwmLimit_Calc(CVT.ActuatorArmed.Armed,
            FALSE/*_armed.prearmed*/,
            ActuatorOutputs.Count,
            reverse_mask,
            disarmed_pwm,
            min_pwm,
            max_pwm,
            ActuatorOutputs.Output,
            pwm,
            &PwmLimit);

    if (CVT.ActuatorArmed.Lockdown)
    {
        SetMotorOutputs(disarmed_pwm);
    }
    else if(!CVT.ActuatorArmed.InEscCalibrationMode)
    {
        SetMotorOutputs(pwm);
    }

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&ActuatorOutputs);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&ActuatorOutputs);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Mixer callback to get the actual control value.                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 AMC::ControlCallback(
        cpuaddr Handle,
        uint8 ControlGroup,
        uint8 ControlIndex,
        float &Control)
{
    int32 iStatus = 0;

    const PX4_ActuatorControlsMsg_t *controls = (PX4_ActuatorControlsMsg_t*)Handle;

    if(ControlGroup > 0)
        iStatus = -1;
    else if(ControlIndex > 8)
        iStatus = -1;
    else
    {
        Control = controls[ControlGroup].Control[ControlIndex];
        iStatus = CFE_SUCCESS;
    }

    return iStatus;
}

#ifdef __cplusplus
}
#endif

/************************/
/*  End of File Comment */
/************************/
