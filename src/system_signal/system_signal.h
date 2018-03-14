#ifndef __SYSSIGNALHANDLER_H__
#define __SYSSIGNALHANDLER_H__

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

#ifdef __cplusplus
extern "C"
{
#endif
/***********注册所有系统信号*************/
/*str:错误信息*/
typedef int (*SysCommandHandlerCallBack)(char *out_str);

void SytemSignal_StartCaptureAllSignal();

void SytemSignal_StopCaptureAllSignal();

/***********注册系统命令处理函数*********/
int SytemSignal_RegisterSignalHandler(int signal_id, SysCommandHandlerCallBack handler);

int SytemSignal_UnRegisterSignalHandler(int signal_id, SysCommandHandlerCallBack handler);

int SytemSignal_AddPidIdFuncName(int pid_id, const char *fun_name, unsigned int fun_name_size);


#ifdef __cplusplus
}
#endif

#endif