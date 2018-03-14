#ifndef __LOG_H__
#define __LOG_H__

typedef enum log_level_e{
	LOG_LEVEL_SCREEN,			//屏幕输出
	LOG_LEVEL_FILE,				//输出到文件
	LOG_LEVEL_NET,				//输出到网络
	LOG_LEVEL_FILE_SCREEN,		//输出到文件时也从屏幕输出
	LOG_LEVEL_NET_SCREEN,		//输出到网络时也从屏幕输出
	LOG_LEVEL_NET_FILE_SCREEN,	//输出到网络时,同时输出文件和屏幕
}log_level_e;

typedef struct log_param_s{
	unsigned int m_dst_ip;
	unsigned short m_dst_port;
	char m_pathname[256];
}log_param_t;

#ifdef __cplusplus
extern "C"{
#endif

//启动日志模块
int log_startup(log_param_t *log_param);
//关闭日志模块
int log_shutdown();
//支持运行时调整日志输出目的地
int log_modify_param(log_param_t log_param);
//输出日志
int log_output(log_level_e log_level, char *log_str, int str_size);

#ifdef __cplusplus
}
#endif

#endif