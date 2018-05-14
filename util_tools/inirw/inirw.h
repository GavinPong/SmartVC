/**
 * �ļ���inirw.h
 * �汾��1.0
 * ���ߣ�taoyuanmin@gmail.com
 *
 * ˵����ini�����ļ���д
 * 1��֧��;��#ע�ͷ��ţ�֧����βע�͡�
 * 2��֧�ִ�����'��"�ɶ�ƥ����ַ�������ȡʱ�Զ�ȥ���š������пɴ��������Ż�;#ע�ͷ���
 * 3��֧����section���section(����Ϊ��)��
 * 4��֧��10��16��8��������0x��ͷΪ16��������0��ͷΪ8���ơ�
 * 5��֧��section��key��=��ǰ����ո�
 * 6��֧��\n��\r��\r\n��\n\r���и�ʽ��
 * 7��������section��key��Сд����д��ʱ���´�Ϊ׼�����������Сд��
 * 8����������ʱ����section�������ڸý����һ����Ч���ݺ���ӣ��������ļ�β����ӡ�
 * 9��֧��ָ��key��������ɾ������ɾ���ü�ֵ������ע�͡�
 * 10�����Զ�������ʽ�����У��޸�ʱ��Ȼ������
 * 11���޸�ʱ����ԭע�ͣ���������ע�͡���βע��(����ǰ��ո�)��
 * 12���޸�ʱ����ԭ���С�����������Ҫ�Ǿ�������ԭ��ʽ��
 */
 

#ifndef _INI_RW_H_
#define _INI_RW_H_

#include "cross_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

//����ini�ļ����ڴ�
int32_t iniFileLoad(const char *filename);
//�ͷ�ini�ļ���ռ��Դ
void iniFileFree();

//��ȡ�ַ�������������
int32_t iniGetString(const char *section, const char *key, char *value, int32_t size, const char *defvalue);
//��ȡ����ֵ
int32_t iniGetInt(const char *section, const char *key, int32_t defvalue);
//��ȡ������
double iniGetDouble(const char *section, const char *key, double defvalue);

//�����ַ�������valueΪNULL����ɾ����key�����У�����ע��
int32_t iniSetString(const char *section, const char *key, const char *value);
//��������ֵ��baseȡֵ10��16��8���ֱ��ʾ10��16��8���ƣ�ȱʡΪ10����
int32_t iniSetInt(const char *section, const char *key, int32_t value, int32_t base);

#ifdef __cplusplus
}
#endif

#endif
