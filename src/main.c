#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.h"
#include "system_signal.h"
#include "cross_platform.h"
#include "manager.h"

int signal_handler(int signal_id, char *out_str){

	log_output(LOG_LEVEL_FILE_SCREEN, out_str, strlen(out_str));
	g_manager_ctx.m_app_out_mode = APP_OUT_MODE_REBOOT;
	g_manager_ctx.m_app_run_status = APP_STATUS_EXIT;
	if (strstr(out_str, "main"))
	{
		SytemSignal_StopCaptureAllSignal();
		log_shutdown();
		exit(-1);
	}

	return 0;
}

void signal_handler_bind_signal_id(){
	int i = 0;

	for (;i < 32; i++)
	{
		SytemSignal_RegisterSignalHandler(i, signal_handler);
	}
}


int main(int argc, char *argv[]){
	log_param_t log_param;

	log_param.m_dst_ip = inet_addr("192.168.31.188");
	log_param.m_dst_port = 8989;
	memcpy(log_param.m_pathname, "./log.data", sizeof(log_param.m_pathname));
	log_param.m_pathname[strlen("./log.data")] = '\0';

	//step_1
	log_startup(&log_param);
	//step_2
	SytemSignal_StartCaptureAllSignal();
	signal_handler_bind_signal_id();
	SysSignal_AddPidIdAndFuncName();
	//step_3
	manager_system_autorise();//ÊÚÈ¨Ê§°Ü½øÈëÊ§°Ü
	manager_system1_init();
	manager_system2_init();

	while (APP_STATUS_RUNNING == g_manager_ctx.m_app_run_status)
	{
		manager_feed_watchdog();
	}

#ifdef TEST_SYS_BIT_SIZE
	printf("__WORDSIZE :%d", __WORDSIZE);
#endif

#ifdef TEST_SIGNAL_MODULE
	log_output(LOG_LEVEL_FILE_SCREEN, "12346", strlen("12346"));
	char *ptr = NULL;
	*ptr = 111;
#endif
	manager_system2_uninit();
	manager_system1_uninit();
	SytemSignal_StopCaptureAllSignal();
	if (APP_OUT_MODE_REBOOT == g_manager_ctx.m_app_out_mode)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "app quit width reboot!", strlen("app quit width reboot!"));	
	}
	else if (APP_OUT_MODE_SHUTDOWN == g_manager_ctx.m_app_out_mode)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "app quit width shutdown!", strlen("app quit width shutdown!"));	
	}
	else if (APP_OUT_MODE_STANDBY == g_manager_ctx.m_app_out_mode)
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "app quit width standby!", strlen("app quit width standby!"));	
	}
	else
	{
		log_output(LOG_LEVEL_FILE_SCREEN, "app quit width unknown mode!", strlen("app quit width unknown mode!"));	
	}
	log_shutdown();
	manager_system_out();

	return 0;
}
