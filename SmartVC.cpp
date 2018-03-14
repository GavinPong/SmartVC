// SmartVC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/log/log.h"
#include "src/system_signal/system_signal.h"
#include <cross_platform.h>

#if (PLATFORM == WINDOWS_PLATFORM) 
#define LOG_OUT_FILE "log.data"
#else
#define LOG_OUT_FILE "log.data"
#endif

int signal_handler(char *outstr){

	log_output(LOG_LEVEL_FILE_SCREEN, outstr, strlen(outstr));

	if (strstr(outstr, "main"))
	{
		SytemSignal_StopCaptureAllSignal();
		log_shutdown();
		exit(-1);
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	log_param_t log_param;
	//3:[ + ]  + \0的长度
	char *func_name = (char *)calloc(1, strlen(__FILE__) + strlen("->") + strlen(__FUNCTION__) + 4);
	if (func_name)
	{
		sprintf(func_name, "[%s->%s]", __FILE__, __FUNCTION__);
	}
	printf("%s->%d:%s\n", __FILE__, __LINE__,func_name);
	log_param.m_dst_ip = inet_addr("192.168.31.188");
	log_param.m_dst_port = 8989;
	memcpy(log_param.m_pathname, LOG_OUT_FILE, sizeof(log_param.m_pathname));
	log_param.m_pathname[strlen(LOG_OUT_FILE)] = '\0';
	printf("__WORDSIZE :%d", _WIN64);
	log_startup(&log_param);
	SytemSignal_StartCaptureAllSignal();
	SytemSignal_AddPidIdFuncName(gettid(), func_name, strlen(func_name));
	free(func_name);
	func_name = NULL;
	SytemSignal_RegisterSignalHandler(11, signal_handler);
	log_output(LOG_LEVEL_FILE_SCREEN, "12346", strlen("12346"));
//#define TEST_SIGNAL_MODULE
#ifdef TEST_SIGNAL_MODULE
	char *ptr = NULL;
	*ptr = 111;
#endif
	SytemSignal_StopCaptureAllSignal();
	log_shutdown();
}

