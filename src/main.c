#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.h"
#include "system_signal.h"
#include "cross_platform.h"

int signal_handler(char *outstr){

	log_output(LOG_LEVEL_FILE_SCREEN, outstr, strlen(outstr));

	if (strstr(outstr, "main"))
	{
		exit(-1);
	}

	return 0;
}


int main(int argc, char *argv[]){
	log_param_t log_param;

	char *func_name = (char *)calloc(1, strlen(__FILE__) + strlen("->") + strlen(__FUNCTION__) + 2);
	if (func_name)
	{
		sprintf(func_name, "[%s->%s]", __FILE__, __FUNCTION__);
	}
	log_param.m_dst_ip = inet_addr("192.168.31.188");
	log_param.m_dst_port = 8989;
	memcpy(log_param.m_pathname, "./log.data", sizeof(log_param.m_pathname));
	log_param.m_pathname[strlen("./log.data")] = '\0';

	log_startup(&log_param);
	SytemSignal_StartCaptureAllSignal();
	SytemSignal_AddPidIdFuncName(gettid(), func_name, strlen(func_name));
	free(func_name);
	func_name = NULL;
	SytemSignal_RegisterSignalHandler(11, signal_handler);
	SytemSignal_RegisterSignalHandler(2, signal_handler);
	printf("__WORDSIZE :%d", __WORDSIZE);
	log_output(LOG_LEVEL_FILE_SCREEN, "12346", strlen("12346"));
#ifndef TEST_SIGNAL_MODULE
	char *ptr = NULL;
	*ptr = 111;
#endif
	SytemSignal_StopCaptureAllSignal();
	log_shutdown();

	return 0;
}
