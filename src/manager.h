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
	APP_OUT_MODE_REBOOT,		//<!--����
	APP_OUT_MODE_SHUTDOWN,		//<!--�ػ�
	APP_OUT_MODE_STANDBY,		//<!--����
}app_out_mode_e;

typedef struct _manager_ctx_s{
	app_run_status_e m_app_run_status;
	app_out_mode_e m_app_out_mode;
}manager_ctx_t;
//������֤
int32_t manager_system_authorise();
//ϵͳ��ʼ����һ���֣���ģ�����õļ������ⲿ�����
int32_t manager_system1_init();
//ϵͳ��ʼ���ڶ����֣�����������ģ��
int32_t manager_system2_init();
//ϵͳ����ʼ���ڶ�����:�رո�����ģ��
int32_t manager_system2_uninit();
//ϵͳ����ʼ����һ���֣������ģ������
int32_t manager_system1_uninit();
//�˳�ϵͳ��ز���
int32_t manager_system_out();
//���������
int32_t manager_watchdog_open();
//�ر������
int32_t manager_watchdog_close();
//ι��
int32_t manager_feed_watchdog();

#ifdef __cplusplus
};
#endif

extern manager_ctx_t g_manager_ctx;

#endif