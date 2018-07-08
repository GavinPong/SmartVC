//level 0 第一步通讯建立,不对外开放，在interface接口内部赋值
typedef enum _interface_0_level_id_e{
	INTERFACE_USER_LOGIN,		//请求建立连接
}interface_0_level_id_e;

//level 1 第二步进入对应服务,不对外开放，在interface接口内部赋值
typedef enum _interface_1_level_id_e{
	INTERFACE_CTRL,				//进入控制流程
	INTERFACE_RTSTREAM,			//进入实时流流程
	INTERFACE_AUDIO,			//音频流流程
	INTERFACE_FILE,				//文件流流程
}interface_1_level_id_e;

//level 2 第三步对消息进行分类,不对外开放，在interface接口内部赋值
typedef enum _interface_2_level_id_e{
	INTERFACE_SET_CONFIG,		//设置配置	
	INTERFACE_GET_CONFIG,		//获取配置
	INTERFACE_CMD,				//命令请求
	INTERFACE_MSG_STATUS,		//状态同步
	INTERFACE_MSG_CONFIG,		//配置同步
	INTERFACE_INTMODULE,		//下发给intmodule
	INTERFACE_LOG,				//日志信息
}interface_2_level_id_e;

//level 3 下发任务给具体模块,对intmodule开放
typedef enum _interface_3_level_id_e{
	INTERFACE_DUMMY,			//样例模块	
}interface_3_level_id_e;