#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "cross_platform.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum _app_run_status_e{
	APP_STATUS_RUNNING,
	APP_STATUS_EXIT,
}app_run_status_e;

typedef enum _app_out_mode_e{
	APP_OUT_MODE_REBOOT,		//<!--重启
	APP_OUT_MODE_SHUTDOWN,		//<!--关机
	APP_OUT_MODE_STANDBY,		//<!--待机
}app_out_mode_e;

typedef struct _manager_ctx_s{
	app_run_status_e m_app_run_status;
	app_out_mode_e m_app_out_mode;
}manager_ctx_t;
//加密验证
int32_t manager_system_authorise();
//系统初始化第一部分：各模块配置的加载在这部分完成
int32_t manager_system1_init();
//系统初始化第二部分：启动各功能模块
int32_t manager_system2_init();
//系统反初始化第二部分:关闭各功能模块
int32_t manager_system2_uninit();
//系统反初始化第一部分：保存各模块配置
int32_t manager_system1_uninit();
//退出系统相关操作
int32_t manager_system_out();
//启动软件狗
int32_t manager_watchdog_open();
//关闭软件狗
int32_t manager_watchdog_close();
//喂狗
int32_t manager_feed_watchdog();

#ifdef __cplusplus
};
#endif

extern manager_ctx_t g_manager_ctx;

#endif