//level 0 ��һ��ͨѶ����,�����⿪�ţ���interface�ӿ��ڲ���ֵ
typedef enum _interface_0_level_id_e{
	INTERFACE_USER_LOGIN,		//����������
}interface_0_level_id_e;

//level 1 �ڶ��������Ӧ����,�����⿪�ţ���interface�ӿ��ڲ���ֵ
typedef enum _interface_1_level_id_e{
	INTERFACE_CTRL,				//�����������
	INTERFACE_RTSTREAM,			//����ʵʱ������
	INTERFACE_AUDIO,			//��Ƶ������
	INTERFACE_FILE,				//�ļ�������
}interface_1_level_id_e;

//level 2 ����������Ϣ���з���,�����⿪�ţ���interface�ӿ��ڲ���ֵ
typedef enum _interface_2_level_id_e{
	INTERFACE_SET_CONFIG,		//��������	
	INTERFACE_GET_CONFIG,		//��ȡ����
	INTERFACE_CMD,				//��������
	INTERFACE_MSG_STATUS,		//״̬ͬ��
	INTERFACE_MSG_CONFIG,		//����ͬ��
	INTERFACE_INTMODULE,		//�·���intmodule
	INTERFACE_LOG,				//��־��Ϣ
}interface_2_level_id_e;

//level 3 �·����������ģ��,��intmodule����
typedef enum _interface_3_level_id_e{
	INTERFACE_DUMMY,			//����ģ��	
}interface_3_level_id_e;