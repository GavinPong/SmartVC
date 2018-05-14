#ifndef __FILEFUNC_H__
#define __FILEFUNC_H__
#include <cJSON.h>

#define FILE_FUNC_OK 1
#define FILE_FUNC_FALSE 0
#define FILE_FUNC_ERR_INVALIDPARAM	-1			//�����쳣
#define FILE_FUNC_ERR_OPENFILE		-2			//�ļ���ʧ��
#define FILE_FUNC_ERR_EMPTY			-3			//�ļ�Ϊ��
#define FILE_FUNC_ERR_OVERLOW		-4			//�ڴ治��
#define FILE_FUNC_ERR_PARSE_JSON	-5			//����jsonʧ��


#ifdef __cplusplus
extern "C"{
#endif

int32_t FILE_FUNC_Get_Json_Form_File(const char *path_name, cJSON **out_json);
int32_t FILE_FUNC_Put_Json_Form_File(const char *path_name, cJSON *in_json);

#ifdef __cplusplus
}
#endif

#endif