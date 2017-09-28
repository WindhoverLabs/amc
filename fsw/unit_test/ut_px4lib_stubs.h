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
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 ****************************************************************************/

#ifndef UT_PX4LIB_STUBS_H
#define UT_PX4LIB_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    UT_PX4LIB_LIB_MATHLIB_MATH_LIMITS_INDEX,
    UT_PX4LIB_MODULES_SYSTEMLIB_MIXER_INDEX,
    UT_OSAPI_BINSEMTAKE_INDEX,
    UT_OSAPI_BINSEMTIMEDWAIT_INDEX,
    UT_OSAPI_MUTSEMTAKE_INDEX,
    UT_OSAPI_GETLOCALTIME_INDEX,
    UT_OSAPI_QUEUEGET_INDEX,
    UT_OSAPI_QUEUEPUT_INDEX,
    UT_OSAPI_TASKDELETE_INDEX,
    UT_OSAPI_BINSEMGIVE_INDEX,
    UT_OSAPI_COUNTSEMCREATE_INDEX,
    UT_OSAPI_COUNTSEMDELETE_INDEX,
    UT_OSAPI_COUNTSEMGIVE_INDEX,
    UT_OSAPI_COUNTSEMTAKE_INDEX,
    UT_OSAPI_COUNTSEMTIMEDWAIT_INDEX,
    UT_OSAPI_COUNTSEMGETIDBYNAME_INDEX,
    UT_OSAPI_COUNTSEMGETINFO_INDEX,
    UT_OSAPI_MUTSEMCREATE_INDEX,
    UT_OSAPI_MUTSEMDELETE_INDEX,
    UT_OSAPI_BINSEMCREATE_INDEX,
    UT_OSAPI_TASKCREATE_INDEX,
    UT_OSAPI_TASKINSTALLDELETEHANDLER_INDEX,
    UT_OSAPI_TASKSETPRIORITY_INDEX,
    UT_OSAPI_TASKREGISTER_INDEX,
    UT_OSAPI_TASKGETID_INDEX,
    UT_OSAPI_TASKGETIDBYNAME_INDEX,
    UT_OSAPI_TASKGETINFO_INDEX,
    UT_OSAPI_QUEUECREATE_INDEX,
    UT_OSAPI_QUEUEDELETE_INDEX,
    UT_OSAPI_QUEUEGETIDBYNAME_INDEX,
    UT_OSAPI_BINSEMDELETE_INDEX,
    UT_OSAPI_BINSEMGETIDBYNAME_INDEX,
    UT_OSAPI_BINSEMGETINFO_INDEX,
    UT_OSAPI_MUTSEMGIVE_INDEX,
    UT_OSAPI_MUTSEMGETIDBYNAME_INDEX,
    UT_OSAPI_MUTSEMGETINFO_INDEX,
    UT_OSAPI_MILLI2TICKS_INDEX,
    UT_OSAPI_TICK2MICROS_INDEX,
    UT_OSAPI_EXCATTACHHANDLER_INDEX,
    UT_OSAPI_EXCENABLE_INDEX,
    UT_OSAPI_EXCDISABLE_INDEX,
    UT_OSAPI_FPUEXCATTACHHANDLER_INDEX,
    UT_OSAPI_FPUEXCENABLE_INDEX,
    UT_OSAPI_FPUEXCDISABLE_INDEX,
    UT_OSAPI_FPUEXCSETMASK_INDEX,
    UT_OSAPI_FPUEXCGETMASK_INDEX,
    UT_OSAPI_INTATTACHHANDLER_INDEX,
    UT_OSAPI_INTENABLE_INDEX,
    UT_OSAPI_INTDISABLE_INDEX,
    UT_OSAPI_INTUNLOCK_INDEX,
    UT_OSAPI_INTLOCK_INDEX,
    UT_OSAPI_INTSETMASK_INDEX,
    UT_OSAPI_INTGETMASK_INDEX,
    UT_OSAPI_INTACK_INDEX,
    UT_OSAPI_SYMBOLLOOKUP_INDEX,
    UT_OSAPI_SYMBOLTABLEDUMP_INDEX,
    UT_OSAPI_MAX_INDEX
} Ut_OSAPI_Index_t;

typedef struct
{
    int32 (*OS_TaskDelay)(uint32);
    int32 (*OS_BinSemFlush)(uint32);
    int32 (*OS_BinSemTake)(uint32);
    int32 (*OS_BinSemTimedWait)(uint32, uint32);
    int32 (*OS_MutSemTake)(uint32);
    int32 (*OS_GetLocalTime)(OS_time_t *);
    int32 (*OS_QueueGet)(uint32, void *, uint32, uint32 *, int32);
    int32 (*OS_QueuePut)(uint32, const void *, uint32, uint32);
    int32 (*OS_TaskDelete)(uint32);
    int32 (*OS_BinSemGive)(uint32);
    int32 (*OS_CountSemCreate)(uint32 *sem_id, const char *sem_name, uint32 sem_initial_value, uint32 options);
    int32 (*OS_CountSemDelete)(uint32 sem_id);
    int32 (*OS_CountSemGive)(uint32 sem_id);
    int32 (*OS_CountSemTake)(uint32 sem_id);
    int32 (*OS_CountSemTimedWait)(uint32 sem_id, uint32 msecs);
    int32 (*OS_CountSemGetIdByName)(uint32 *sem_id, const char *sem_name);
    int32 (*OS_CountSemGetInfo)(uint32 sem_id, OS_count_sem_prop_t *count_prop);
    int32 (*OS_MutSemCreate)(uint32 *sem_id, const char *sem_name, uint32 options);
    int32 (*OS_MutSemDelete)(uint32 sem_id);
    int32 (*OS_BinSemCreate)(uint32 *sem_id, const char *sem_name, uint32 sem_initial_value, uint32 options);
    int32 (*OS_TaskCreate)(uint32 *task_id, const char *task_name, osal_task_entry function_pointer, uint32 *stack_pointer, uint32 stack_size, uint32 priority, uint32 flags);
    int32 (*OS_TaskInstallDeleteHandler)(osal_task_entry function_pointer);
    int32 (*OS_TaskSetPriority)(uint32 task_id, uint32 new_priority);
    int32 (*OS_TaskRegister)(void);
    uint32 (*OS_TaskGetId)(void);
    int32 (*OS_TaskGetIdByName)(uint32 *task_id, const char *task_name);
    int32 (*OS_TaskGetInfo)(uint32 task_id, OS_task_prop_t *task_prop);
    int32 (*OS_QueueCreate)(uint32 *queue_id, const char *queue_name, uint32 queue_depth, uint32 data_size, uint32 flags);
    int32 (*OS_QueueDelete)(uint32 queue_id);
    int32 (*OS_QueueGetIdByName)(uint32 *queue_id, const char *queue_name);
    int32 (*OS_BinSemDelete)(uint32 sem_id);
    int32 (*OS_BinSemGetIdByName)(uint32 *sem_id, const char *sem_name);
    int32 (*OS_BinSemGetInfo)(uint32 sem_id, OS_bin_sem_prop_t *bin_prop);
    int32 (*OS_MutSemGive)(uint32 sem_id);
    int32 (*OS_MutSemGetIdByName)(uint32 *sem_id, const char *sem_name);
    int32 (*OS_MutSemGetInfo)(uint32 sem_id, OS_mut_sem_prop_t *mut_prop);
    int32 (*OS_Milli2Ticks)(uint32 milli_seconds);
    int32 (*OS_Tick2Micros)(void);
    int32 (*OS_ExcAttachHandler)(uint32 ExceptionNumber, void (*ExceptionHandler)(uint32, const void *,uint32), int32 Parameter);
    int32 (*OS_ExcEnable)(int32 ExceptionNumber);
    int32 (*OS_ExcDisable)(int32 ExceptionNumber);
    int32 (*OS_FPUExcAttachHandler)(uint32 ExceptionNumber, void * ExceptionHandler, int32 Parameter);
    int32 (*OS_FPUExcEnable)(int32 ExceptionNumber);
    int32 (*OS_FPUExcDisable)(int32 ExceptionNumber);
    int32 (*OS_FPUExcSetMask)(uint32 Mask);
    int32 (*OS_FPUExcGetMask)(uint32 *Mask);
    int32 (*OS_IntAttachHandler)(uint32 InterruptNumber, osal_task_entry InterruptHandler, int32 parameter);
    int32 (*OS_IntEnable)(int32 Level);
    int32 (*OS_IntDisable)(int32 Level);
    int32 (*OS_IntUnlock)(int32 IntLevel);
    int32 (*OS_IntLock)(void);
    int32 (*OS_IntSetMask)(uint32 Mask);
    int32 (*OS_IntGetMask)(uint32 *Mask);
    int32 (*OS_IntAck)(int32 InterruptNumber);
    int32 (*OS_SymbolLookup)(cpuaddr *SymbolAddress, const char *SymbolName);
    int32 (*OS_SymbolTableDump)(const char *filename, uint32 SizeLimit);
} Ut_OSAPI_HookTable_t;

typedef struct
{
    int32   Value;
    uint32  Count;
    boolean ContinueReturnCodeAfterCountZero;
} Ut_OSAPI_ReturnCodeTable_t;

void Ut_OSAPI_Reset(void);
void Ut_OSAPI_SetFunctionHook(uint32 Index, void *FunPtr);
void Ut_OSAPI_SetReturnCode(uint32 Index, int32 RtnVal, uint32 CallCnt);
void Ut_OSAPI_ContinueReturnCodeAfterCountZero(uint32 Index);

#ifdef __cplusplus
}
#endif

#endif
