#ifndef __LOG_H__
#define __LOG_H__

#include "cross_platform.h"

typedef enum log_level_e{
	LOG_LEVEL_SCREEN,			//��Ļ���
	LOG_LEVEL_FILE,				//������ļ�
	LOG_LEVEL_NET,				//���������
	LOG_LEVEL_FILE_SCREEN,		//������ļ�ʱҲ����Ļ���
	LOG_LEVEL_NET_SCREEN,		//���������ʱҲ����Ļ���
	LOG_LEVEL_NET_FILE_SCREEN,	//���������ʱ,ͬʱ����ļ�����Ļ
}log_level_e;

typedef struct log_param_s{
	unsigned int m_dst_ip;
	unsigned short m_dst_port;
	char m_pathname[256];
}log_param_t;

#ifdef __cplusplus
extern "C"{
#endif

//������־ģ��
int32_t log_startup(log_param_t *log_param);
//�ر���־ģ��
int32_t log_shutdown();
//֧������ʱ������־���Ŀ�ĵ�
int32_t log_modify_param(log_param_t log_param);
//�����־
int32_t log_output(log_level_e log_level, const char *log_str, int32_t str_size);

#ifdef __cplusplus
}
#endif

#endif