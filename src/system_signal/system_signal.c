#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "system_signal.h"
#include <list.h>
#include <cross_platform.h>


#ifndef gettid
//#define  gettid() GetCurrentThreadId()
#define  gettid() syscall(__NR_gettid)
#endif 


#define _SIGHUP_INFO	"SIGHUP signal,the terminal is disconnected"										//<!--�����˳����ն���·�Ҷ�
#define _SIGINT_INFO	"SIGINT signal,The process is terminated,egg Ctrl+C"								//<!--�����˳���ͨ����Ctrl+C����
#define _SIGQUIT_INFO	"SIGQUIT signal,The process is terminated,egg Ctrl+\\"								//<!--�յ��˳����ͨ����Ctrl+\����
#define _SIGILL_INFO	"SIGILL signal, Illegal instruction exception"										//<!--�Ƿ�ָ��
#define _SIGTRAP_INFO	"SIGTRAP signal, Illegal operation causes abnormal hardware or Hardware exception"	//<!--�Ƿ���������Ӳ���쳣�����߱�������Ӳ���쳣
#define _SIGABRT_INFO	"SIGABRT signal, The process is terminated"											//<!--abort�źŵ��½����˳�
#define _SIGBUS_INFO	"SIGBUS signal, Certain hardware error, usually caused by memory access"			//<!--ĳ��Ӳ������ͨ�����ڴ�������𣬵���ĳЩӲ���Ĵ����쳣
#define _SIGFPE_INFO	"SIGFPE signal, Operation exception"												//<!--�������
#define _SIGKILL_INFO	"SIGKILL signal, The process is kill"												//<!--���̱�Ҫ���˳�
#define _SIGUSR1_INFO	"SIGUSR1 signal, Terminate the process user-defined signal 1"						//<!--��ֹ���̣����û��ź�1����
#define _SIGSEGV_INFO	"SIGSEGV signal, Illegal memory access"												//<!--�δ��󣬷Ƿ���ַ����
#define _SIGUSR2_INFO	"SIGUSR2 signal, Terminate the process user-defined signal 2"						//<!--��ֹ���̣����û��ź�1����
#define _SIGPIPE_INFO	"SIGPIPE signal, Write data to the pipe can not be read"							//<!--�����ܶ��Ĺܵ�д����
#define _SIGALRM_INFO	"SIGALRM signal, Timer expires"														//<!--��ʱ����ʱ
#define _SIGTERM_INFO	"SIGTERM signal, Software termination signal, there is unobstructed kill trigger"	//<!--���̱���ֹ��ͨ����kill�����
#define _SIGSTKFLT_INFO	"SIGSTKFLT signal, Stack exception math coprocessor"								//<!--��ѧЭ��������ջ�쳣
#define _SIGCHLD_INFO	"SIGCHLD signal, Child process exits"												//<!--�ӽ����˳�
#define _SIGCONT_INFO	"SIGCONT signal, The recovery process is stop running"								//<!--��ֹͣ�Ľ��ָ̻�����	
#define _SIGSTOP_INFO	"SIGSTOP signal, Non-terminal stop signal"											//<!--ֹͣ�����źţ����ն˷������ź�		
#define _SIGTSTP_INFO	"SIGTSTP signal, terminal stop signal��egg Ctrl+z"									//<!--ֹͣ�����źţ��ն˷������ź�		
#define _SIGTTIN_INFO	"SIGTTIN signal, terminal stop signal��Background processes read data terminal"		//<!--ֹͣ�����źţ���̨���̶��ն�	
#define _SIGTTOU_INFO	"SIGTTOU signal, terminal stop signal��Background processes write data terminal"		//<!--ֹͣ�����źţ���̨����д�ն�	
#define _SIGURG_INFO	"SIGURG signal,  I / O emergency signal"											//<!--IO�����źţ�Ĭ�Ϻ���	
#define _SIGXCPU_INFO	"SIGXCPU signal,  CPU time limit times out"											//<!--CPUʱ�޳�ʱ	
#define _SIGXFSZ_INFO	"SIGXFSZ signal,  File size exceeds the limit"										//<!--�����ļ���С�������̵��������	
#define _SIGVTALRM_INFO	"SIGVTALRM signal,  Virtual timer expires"											//<!--�����ʱ����ʱ		
#define _SIGPROF_INFO	"SIGPROF signal,  Statistical distribution with the timer expires"					//<!--ͳ�Ʒֲ�ͼ�ü�ʱ����ʱ		
#define _SIGWINCH_INFO	"SIGWINCH signal,  Terminal Window size changes"									//<!--�ն˴��ڴ�С�仯
#define _SIGIO_INFO		"SIGIO signal,  May be I / O on a descriptor"										//<!--�������Ͽ��Խ���I/O
#define _SIGPWR_INFO	"SIGPWR signal,  Shutdown"															//<!--�ػ�
#define _SIGSYS_INFO	"SIGSYS signal,  Invalid system call"												//<!--��Чϵͳ����
#define _SIGBREAK_INFO	"SIGBREAK signal,  Ctrl+Break Interrupt"											//<!--Ctrl+Break�ж�
/********Ĭ�Ͻ��̺��Ե��ź��У�SIGCHLD��SIGPWR��SIGURG��SIGWINCH******/


typedef struct __SIGNAL_INFO
{
	LIST_HEAD m_signal_desc_list;				//<!--�ź����ź�������Ӧ������ͷ
	LIST_HEAD m_pid_fun_name_list;				//<!--�߳�/����ID��Ӧ�ĺ�����
	// 	pthread_rwlock_t m_signal_desc_m_mutex;		//<!--�ź������д��
	// 	pthread_rwlock_t m_pid_fun_name_mutex;		//<!--�߳�ID/����ID��д��
}SIGNAL_INFO;

//�ź����ź���������
typedef struct __SIGNAL_DESC_LIST
{
	LIST_HEAD m_list;				//<!--���ֶε�����ڵ�
	int m_signal_id;				//<!--�ź�ID
	char *m_signal_mean;			//<!--�ź�ID������
}SIGNAL_DESC_LIST;

//�߳�/����ID��ID��Ӧ�ĺ�����
typedef struct __PID_FUN_NAME_LIST
{
	LIST_HEAD m_list;				//<!--���ֶε�����ڵ�
	int m_pid_id;					//<!--�߳�/����ID
	char *m_send_pid_id_func_name;	//<!--�����߳�/����ID�ĺ�����
}PID_FUN_NAME_LIST;

typedef struct _SYS_CMD_HANDLER_LIST{
	SysCommandHandlerCallBack m_sys_cmd_handler;		//ϵͳ����ص�����ָ��
	struct _SYS_CMD_HANDLER_LIST *m_next;						
}SYS_CMD_HANDLER_LIST, *P_SYS_CMD_HANDLER_LIST;

typedef struct _SYS_COMMAND_LIST
{
	LIST_HEAD m_list;					//�������ݽṹ������ڵ�
	int m_signal_id;				
	P_SYS_CMD_HANDLER_LIST m_handler_list;
}SYS_COMMAND_LIST, *P_SYS_COMMAND_LIST;

typedef struct _SYS_COMMAND_CONTEXT{
	P_SYS_COMMAND_LIST m_p_sys_cmd_list;
	pthread_rwlock_t m_rw_mutex;
}SYS_COMMAND_CONTEXT, P_SYS_COMMAND_CONTEXT;

SYS_COMMAND_CONTEXT s_sys_cmd_ctx = {0};
SIGNAL_INFO s_signal_info_list_head;

static P_SYS_COMMAND_LIST find_command_list(int cmd)
{
	P_SYS_COMMAND_LIST p_sys_cmd_list = s_sys_cmd_ctx.m_p_sys_cmd_list;
	LIST_HEAD *pos, *n;
	if (!p_sys_cmd_list)
	{
		return NULL;
	}

	list_for_each_safe(pos, n, &s_sys_cmd_ctx.m_p_sys_cmd_list->m_list)
	{
		p_sys_cmd_list = list_entry(pos, SYS_COMMAND_LIST, m_list);
		if (p_sys_cmd_list)
		{
			if (p_sys_cmd_list->m_signal_id == cmd)
			{
				return p_sys_cmd_list;
			}
		}
	}
	return NULL;
}

static int DeleteHandler(P_SYS_CMD_HANDLER_LIST * plist, SysCommandHandlerCallBack handler)
{
	if (plist==NULL || (*plist)==NULL)
	{
		return -1;
	}
	while (*plist)
	{
		if ((*plist)->m_sys_cmd_handler == handler)
		{
			free((*plist));
			(*plist) = (*plist)->m_next;
		}else{
			plist = &((*plist)->m_next);
		}
	}
	return 0;
}

static int DeleteCommandList(int signal)
{
	P_SYS_COMMAND_LIST p_cmdlist = find_command_list(signal);
	if (p_cmdlist)
	{
		if (p_cmdlist->m_handler_list)
		{
			while(p_cmdlist->m_handler_list)
			{
				P_SYS_CMD_HANDLER_LIST p_hander_list = p_cmdlist->m_handler_list;
				p_cmdlist->m_handler_list = p_cmdlist->m_handler_list->m_next;
				free(p_hander_list);
			}
		}else{
			list_del(&p_cmdlist->m_list);
			free(p_cmdlist);
		}
	}
	return 0;
}

static void HandleDispathDistributor(int signal, char *str)
{
	P_SYS_COMMAND_LIST p_cmdlist = find_command_list(signal);
	P_SYS_CMD_HANDLER_LIST p_hand_list = NULL;
	if (p_cmdlist)
	{
		p_hand_list = p_cmdlist->m_handler_list;
		while (p_hand_list)
		{
			p_hand_list->m_sys_cmd_handler(signal,str);
			p_hand_list = p_hand_list->m_next;
		}
	}
}

/****************����Ϊ�����Žӿ�*************************/
static int InitSignalInfoList(LIST_HEAD *list_head)
{
	if (!list_head)
		return -1;

	INIT_LIST_HEAD(list_head);
	return 0;
}

static int UnInitSignalInfoList(SIGNAL_INFO *signal_info)
{
	if (!signal_info)
		return -1;

	SIGNAL_DESC_LIST *p_signal_info = NULL, *next = NULL;

	list_for_each_entry_safe(SIGNAL_DESC_LIST, p_signal_info, next, &signal_info->m_signal_desc_list, m_list)
	{
		if (p_signal_info->m_signal_mean)
		{
			free(p_signal_info->m_signal_mean);
		}
	}

	PID_FUN_NAME_LIST *p_pid_fun_name_info = NULL, *next_1 = NULL;

	list_for_each_entry_safe(PID_FUN_NAME_LIST, p_pid_fun_name_info, next_1, &signal_info->m_pid_fun_name_list, m_list)
	{
		if (p_pid_fun_name_info->m_send_pid_id_func_name)
		{
			free(p_pid_fun_name_info->m_send_pid_id_func_name);
		}	
	}
	return 0;
}

static char *SignalInfoListGetSignalDesc(LIST_HEAD *list_head, int signal)
{
	if (!list_head)
		return NULL;

	SIGNAL_DESC_LIST *p_signal_info = NULL, *pos = NULL, *next = NULL;

	list_for_each_entry_safe(SIGNAL_DESC_LIST, p_signal_info, next, list_head, m_list)
	{
		if (p_signal_info->m_signal_id == signal)
		{
			if(p_signal_info->m_signal_mean)
			{
				return p_signal_info->m_signal_mean;
			}
		}

	}
	return NULL;
}

static char *SignalInfoListGetPidIdFuncName(LIST_HEAD *list_head, int pid_id)
{
	if (!list_head)
		return NULL;

	PID_FUN_NAME_LIST *p_signal_info = NULL, *pos = NULL, *next = NULL;

	list_for_each_entry_safe(PID_FUN_NAME_LIST, p_signal_info, next, list_head, m_list)
	{
		if (p_signal_info->m_pid_id == pid_id)
		{
			if (p_signal_info->m_send_pid_id_func_name)
			{
				return p_signal_info->m_send_pid_id_func_name;
			}
		}

	}
	return NULL;
}

static void SignalHander(int signal_id)
{
#if (PLATFORM != LINUX_PLATFORM)	//windows��֧��sigaction���ƣ����Բ�ȡ����ע��
	signal(signal_id, SignalHander);
#endif
	char str[512] = "";
	char *p_signal_dec = SignalInfoListGetSignalDesc(&s_signal_info_list_head.m_signal_desc_list, signal_id);
	char *p_pid_fun_name = SignalInfoListGetPidIdFuncName(&s_signal_info_list_head.m_pid_fun_name_list, gettid());
	if (p_signal_dec && p_pid_fun_name)
	{
		memcpy(str, p_pid_fun_name, sizeof(str));
		if (sizeof(str) > strlen(p_pid_fun_name))
		{
			memcpy(str + strlen(p_pid_fun_name), p_signal_dec, sizeof(str) - strlen(p_pid_fun_name));
		}
// 		if (sizeof(str) > strlen(p_pid_fun_name) + strlen(p_signal_dec))
// 		{
// 			memcpy(str + strlen(p_pid_fun_name) + strlen(p_signal_dec), "\r\n", sizeof(str) - strlen(p_pid_fun_name)  - strlen(p_signal_dec));
// 		}
	}
	else if (p_signal_dec)
	{
		memcpy(str, p_signal_dec, sizeof(str));
//		if (sizeof(str) > strlen(p_signal_dec))
//		{
//			memcpy(str + strlen(p_signal_dec), "\r\n", sizeof(str) - strlen(p_signal_dec));
//		}

	}
	else if (p_pid_fun_name)
	{
		memcpy(str, p_pid_fun_name, sizeof(str));
//		if (sizeof(str) > strlen(p_pid_fun_name))
//		{
			memcpy(str + strlen(p_pid_fun_name), "\r\n", sizeof(str) - strlen(p_pid_fun_name));
//		}
	}
	else
	{
		memcpy(str, "unknown signal", sizeof(str));
	}

	if (SIGSEGV == signal_id)
	{
		Msleep(2 * 1000);
		//��ʱ�����������и�ϵͳ�ź��йص�ȫ���ڶ�Ӧ�Ļص������д���
	}
	//	�ȴ�������������
	HandleDispathDistributor(signal_id, str);
	return;
}

//��Ӷ�Ӧ�ź�����
static int SignalInfoListAddSignalDesc(int signal, const char *desc, unsigned int desc_size)
{
	if (!desc || 0 >= desc_size)
		return -1;

	SIGNAL_DESC_LIST *p_signal_info = NULL, *pos = NULL, *next = NULL;

	list_for_each_entry_safe(SIGNAL_DESC_LIST, p_signal_info, next, &s_signal_info_list_head.m_signal_desc_list, m_list)
	{
		if (p_signal_info->m_signal_id == signal)
		{
			//���ź�ID�Ѿ���ӹ�����
			if (p_signal_info->m_signal_mean)
				return 0;
			p_signal_info->m_signal_mean = (char *)malloc(desc_size);
			if(p_signal_info->m_signal_mean)
			{
				memcpy(p_signal_info->m_signal_mean, desc, desc_size);
				return 1;
			}
		}
	}
	p_signal_info = (SIGNAL_DESC_LIST *)malloc(sizeof(SIGNAL_DESC_LIST));
	if (p_signal_info)
	{
		p_signal_info->m_signal_id = signal;
		p_signal_info->m_signal_mean = (char *)malloc(desc_size);
		if (p_signal_info->m_signal_mean)
		{
			memcpy(p_signal_info->m_signal_mean, desc, desc_size);
			list_add_tail(&p_signal_info->m_list, &s_signal_info_list_head.m_signal_desc_list);
			return 1;
		}
		else
		{
			free(p_signal_info);
		}
	}
	return -1;
}

static int InitSysSignalHandleCfg()
{
	pthread_rwlock_init(&s_sys_cmd_ctx.m_rw_mutex, NULL);
	s_sys_cmd_ctx.m_p_sys_cmd_list = (SYS_COMMAND_LIST *)malloc(sizeof(SYS_COMMAND_LIST));	//���봴��һ��������ͷ�������һ����������޷�ִ��
	INIT_LIST_HEAD(&s_sys_cmd_ctx.m_p_sys_cmd_list->m_list);
	return 0;
}

static int UnInitSysSignalHandleCfg()
{
	int i = 0;
#if (PLATFORM == LINUX_PLATFORM)	
	for(i = 0; i < 31; i++)
	{
		if ((i == SIGPIPE) && (i == SIGCHLD))
		{
			DeleteCommandList(i);
		}
	}
#else

#endif
	return 0;
}

/******************
ע��ϵͳ�������
******************/
int SytemSignal_RegisterSignalHandler(int signal_id, SysCommandHandlerCallBack handler)
{
	P_SYS_CMD_HANDLER_LIST p_handlerlist = (P_SYS_CMD_HANDLER_LIST)malloc(sizeof(SYS_CMD_HANDLER_LIST));
	p_handlerlist->m_sys_cmd_handler = handler;
	p_handlerlist->m_next = NULL;
	pthread_rwlock_wrlock(&s_sys_cmd_ctx.m_rw_mutex);
	P_SYS_COMMAND_LIST p_cmdlist = find_command_list(signal_id);
	P_SYS_COMMAND_LIST p_tmp_cmdlist = p_cmdlist;
	if (p_tmp_cmdlist)
	{
		//�ź��Ѿ�ע�ắ�������ڴ��źŴ������������ټ�һ��������
		p_handlerlist->m_next = p_cmdlist->m_handler_list;
		p_cmdlist->m_handler_list = p_handlerlist;
	}else{
		p_cmdlist = (SYS_COMMAND_LIST *)malloc(sizeof(SYS_COMMAND_LIST));
		if (p_cmdlist)
		{
			p_cmdlist->m_signal_id = signal_id;
			p_cmdlist->m_handler_list  = p_handlerlist;
			list_add_tail(&p_cmdlist->m_list, &s_sys_cmd_ctx.m_p_sys_cmd_list->m_list);
		}
	}
	pthread_rwlock_unlock(&s_sys_cmd_ctx.m_rw_mutex);
	return 0;
}

/******************
��ע��ϵͳ�������
******************/
int SytemSignal_UnRegisterSignalHandler(int signal_id, SysCommandHandlerCallBack handler)
{
	pthread_rwlock_wrlock(&s_sys_cmd_ctx.m_rw_mutex);
	P_SYS_COMMAND_LIST p_cmdlist = find_command_list(signal_id);
	P_SYS_COMMAND_LIST p_tmp_cmdlist = p_cmdlist;
	if (p_tmp_cmdlist)
	{
		DeleteHandler(&p_cmdlist->m_handler_list, handler);
	}
	pthread_rwlock_unlock(&s_sys_cmd_ctx.m_rw_mutex);
	return 0;
}

void SytemSignal_StartCaptureAllSignal()
{
	InitSysSignalHandleCfg();
	InitSignalInfoList(&s_signal_info_list_head.m_signal_desc_list);
	InitSignalInfoList(&s_signal_info_list_head.m_pid_fun_name_list);
	int i = 0;
#if (PLATFORM == LINUX_PLATFORM)
	for(i = 0; i < 32; i++)
	{
		switch (i)
		{
		case 1:
			SignalInfoListAddSignalDesc(1, _SIGHUP_INFO, strlen(_SIGHUP_INFO) + 1);
			break;
		case 2:
			SignalInfoListAddSignalDesc(2, _SIGINT_INFO, strlen(_SIGINT_INFO) + 1);
			break;
		case 3:
			SignalInfoListAddSignalDesc(3, _SIGQUIT_INFO, strlen(_SIGQUIT_INFO) + 1);
			break;
		case 4:
			SignalInfoListAddSignalDesc(4, _SIGILL_INFO, strlen(_SIGILL_INFO) + 1);
		case 5:
			SignalInfoListAddSignalDesc(5, _SIGTRAP_INFO, strlen(_SIGTRAP_INFO) + 1);
			break;
		case 6:
			SignalInfoListAddSignalDesc(6, _SIGABRT_INFO, strlen(_SIGABRT_INFO) + 1);
			break;
		case 7:
			SignalInfoListAddSignalDesc(7, _SIGBUS_INFO, strlen(_SIGBUS_INFO) + 1);
			break;
		case 8:
			SignalInfoListAddSignalDesc(8, _SIGFPE_INFO, strlen(_SIGFPE_INFO) + 1);
		case 9:
			SignalInfoListAddSignalDesc(9, _SIGKILL_INFO, strlen(_SIGKILL_INFO) + 1);
			break;
		case 10:
			SignalInfoListAddSignalDesc(10, _SIGUSR1_INFO, strlen(_SIGUSR1_INFO) + 1);
			break;
		case 11:
			SignalInfoListAddSignalDesc(11, _SIGSEGV_INFO, strlen(_SIGSEGV_INFO) + 1);
			break;
		case 12:
			SignalInfoListAddSignalDesc(12, _SIGUSR2_INFO, strlen(_SIGUSR2_INFO) + 1);
		case 13:
			SignalInfoListAddSignalDesc(13, _SIGPIPE_INFO, strlen(_SIGPIPE_INFO) + 1);
			break;
		case 14:
			SignalInfoListAddSignalDesc(14, _SIGALRM_INFO, strlen(_SIGALRM_INFO) + 1);
			break;
		case 15:
			SignalInfoListAddSignalDesc(15, _SIGTERM_INFO, strlen(_SIGTERM_INFO) + 1);
			break;
		case 16:
			SignalInfoListAddSignalDesc(16, _SIGSTKFLT_INFO, strlen(_SIGSTKFLT_INFO) + 1);
		case 17:
			SignalInfoListAddSignalDesc(17, _SIGCHLD_INFO, strlen(_SIGCHLD_INFO) + 1);
			break;
		case 18:
			SignalInfoListAddSignalDesc(18, _SIGCONT_INFO, strlen(_SIGCONT_INFO) + 1);
			break;
		case 19:
			SignalInfoListAddSignalDesc(19, _SIGSTOP_INFO, strlen(_SIGSTOP_INFO) + 1);
			break;
		case 20:
			SignalInfoListAddSignalDesc(20, _SIGTSTP_INFO, strlen(_SIGTSTP_INFO) + 1);
		case 21:
			SignalInfoListAddSignalDesc(21, _SIGTTIN_INFO, strlen(_SIGTTIN_INFO) + 1);
			break;
		case 22:
			SignalInfoListAddSignalDesc(22, _SIGTTOU_INFO, strlen(_SIGTTOU_INFO) + 1);
			break;
		case 23:
			SignalInfoListAddSignalDesc(23, _SIGURG_INFO, strlen(_SIGURG_INFO) + 1);
			break;
		case 24:
			SignalInfoListAddSignalDesc(24, _SIGXCPU_INFO, strlen(_SIGXCPU_INFO) + 1);
		case 25:
			SignalInfoListAddSignalDesc(25, _SIGXFSZ_INFO, strlen(_SIGXFSZ_INFO) + 1);
			break;
		case 26:
			SignalInfoListAddSignalDesc(26, _SIGVTALRM_INFO, strlen(_SIGVTALRM_INFO) + 1);
			break;
		case 27:
			SignalInfoListAddSignalDesc(27, _SIGPROF_INFO, strlen(_SIGPROF_INFO) + 1);
			break;
		case 28:
			SignalInfoListAddSignalDesc(28, _SIGWINCH_INFO, strlen(_SIGWINCH_INFO) + 1);
			break;
		case 29:
			SignalInfoListAddSignalDesc(29, _SIGIO_INFO, strlen(_SIGIO_INFO) + 1);
			break;
		case 30:
			SignalInfoListAddSignalDesc(30, _SIGPWR_INFO, strlen(_SIGPWR_INFO) + 1);
			break;
		case 31:
			SignalInfoListAddSignalDesc(31, _SIGSYS_INFO, strlen(_SIGSYS_INFO) + 1);
			break;
		default:
			break;
		}
		if (i == SIGPIPE)
		{
			signal(i, SIG_IGN);
		}
		else if(i == SIGCHLD)
		{
			printf("single SIGCHLD.............!\n");
		}
		else
		{		
			signal(i, SignalHander);
		}
	}
#else
	signal(SIGINT, SignalHander);
	SignalInfoListAddSignalDesc(SIGINT, _SIGINT_INFO, strlen(_SIGINT_INFO) + 1);
	signal(SIGILL, SignalHander);
	SignalInfoListAddSignalDesc(SIGILL, _SIGILL_INFO, strlen(_SIGILL_INFO) + 1);
	signal(SIGFPE, SignalHander);
	SignalInfoListAddSignalDesc(SIGFPE, _SIGFPE_INFO, strlen(_SIGFPE_INFO) + 1);
	signal(SIGSEGV, SignalHander);
	SignalInfoListAddSignalDesc(SIGSEGV, _SIGSEGV_INFO, strlen(_SIGSEGV_INFO) + 1);
	signal(SIGTERM, SignalHander);
	SignalInfoListAddSignalDesc(SIGTERM, _SIGTERM_INFO, strlen(_SIGTERM_INFO) + 1);
	signal(SIGBREAK, SignalHander);
	SignalInfoListAddSignalDesc(SIGBREAK, _SIGBREAK_INFO, strlen(_SIGBREAK_INFO) + 1);
	signal(SIGABRT, SignalHander);
	SignalInfoListAddSignalDesc(SIGABRT, _SIGABRT_INFO, strlen(_SIGABRT_INFO) + 1);
#endif
}

void SytemSignal_StopCaptureAllSignal()
{
	UnInitSysSignalHandleCfg();
	UnInitSignalInfoList(&s_signal_info_list_head);
}

//��Ӷ�Ӧ�ź�����
int SytemSignal_AddPidIdFuncName(int pid_id, const char *fun_name, unsigned int fun_name_size)
{
	if (!fun_name || 0 >= fun_name_size)
		return -1;

	PID_FUN_NAME_LIST *p_signal_info = NULL, *pos = NULL, *next = NULL;

	list_for_each_entry_safe(PID_FUN_NAME_LIST, p_signal_info, next, &s_signal_info_list_head.m_pid_fun_name_list, m_list)
	{
		if (p_signal_info->m_pid_id == pid_id)
		{
			//���߳�/����ID�Ѿ���ӹ�������
			if (p_signal_info->m_send_pid_id_func_name)
				return 0;
			p_signal_info->m_send_pid_id_func_name = (char *)malloc(fun_name_size + 1);
			if (p_signal_info->m_send_pid_id_func_name)
			{
				memcpy(p_signal_info->m_send_pid_id_func_name, fun_name, fun_name_size);
				p_signal_info->m_send_pid_id_func_name[fun_name_size] = '\0';
				return 1;
			}
		}
	}
	p_signal_info = (PID_FUN_NAME_LIST *)malloc(sizeof(PID_FUN_NAME_LIST));
	if (p_signal_info)
	{
		p_signal_info->m_pid_id = pid_id;
		p_signal_info->m_send_pid_id_func_name = (char *)malloc(fun_name_size + 1);
		if (p_signal_info->m_send_pid_id_func_name)
		{
			memcpy(p_signal_info->m_send_pid_id_func_name, fun_name, fun_name_size);
			p_signal_info->m_send_pid_id_func_name[fun_name_size] = '\0';
			list_add_tail(&p_signal_info->m_list, &s_signal_info_list_head.m_pid_fun_name_list);
			return 1;
		}
		else
		{
			free(p_signal_info);
		}
	}
	return -1;
}