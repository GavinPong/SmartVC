#ifndef __SYSSIGNALHANDLER_H__
#define __SYSSIGNALHANDLER_H__

#include "cross_platform.h"

#ifndef SDK_API
#if (PLATFORM == WINDOWS_PLATFORM)
#ifdef SYS_SIGNAL_EXPORTS
#define ISDK_API __declspec(dllexport)
#else
#define ISDK_API __declspec(dllimport)
#endif
#else
#define ISDK_API 
#endif
#endif

// #ifdef __cplusplus
// extern "C"
// {
// #endif
/***********注册所有系统信号*************/
/*str:错误信息*/
typedef int32_t (*SysCommandHandlerCallBack)(int32_t signal_id, char *out_str);

void SytemSignal_StartCaptureAllSignal();

void SytemSignal_StopCaptureAllSignal();

/***********注册系统命令处理函数*********/
int32_t SytemSignal_RegisterSignalHandler(int32_t signal_id, SysCommandHandlerCallBack handler);

int32_t SytemSignal_UnRegisterSignalHandler(int32_t signal_id, SysCommandHandlerCallBack handler);

int32_t SytemSignal_AddPidIdFuncName(uint32_t pid_id, const char *fun_name, uint32_t fun_name_size);

#ifndef gettid
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)
#endif
#include <stdlib.h>
#include <string.h>
#define SysSignal_AddPidIdAndFuncName() {\
	char *func_name = (char *)calloc(1, strlen(__FILE__) + strlen("->") + strlen(__FUNCTION__) + 2 + strlen("SmartVC:") + 1);\
	if(func_name)\
	{\
		sprintf(func_name, "[SmartVC:%s->%s]", __FILE__, __FUNCTION__);\
		SytemSignal_AddPidIdFuncName(gettid(), func_name, strlen(func_name));\
		free(func_name);\
	};\
}

// #ifdef __cplusplus
// }
// #endif

#endif