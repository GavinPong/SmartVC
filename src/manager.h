#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "cross_platform.h"




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

#ifdef __cplusplus
extern "C"{
#endif

int32_t manager_system_autorise();
int32_t manager_system1_init();
int32_t manager_system2_init();
int32_t manager_system2_uninit();
int32_t manager_system1_uninit();
int32_t manager_system_out();
int32_t manager_feed_watchdog();

#ifdef __cplusplus
};
#endif

extern manager_ctx_t g_manager_ctx;

#endif