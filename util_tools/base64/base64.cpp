/**
 *  base64���롢����ʵ��
 *       C����Դ����
 *
 *   ע�⣺��ʹ��gcc����
 *
 *             Ҷ����
 *
 * 
 *
 *  ʹ��˵����
 *      �����в���˵�������С�-d����������Ϊbase64���룬����Ϊbase64���롣
 *                      ���С�-o������������ļ��������������׼����ļ���
 *      �������Ա�׼����stdin�����Ϊ��׼���stdout�����ض��������������
 *
 *        base64���룺�������������������ȡ���ļ�������Ϊֹ�����������������ļ���β��Ϊֹ����
 *                    ������ı���base64���롣
 *
 *        base64���룺���봿�ı���base64���룬��ȡ���ļ�������Ϊֹ�����������������ļ���β��Ϊֹ����
 *                    ���ԭ���Ķ���������
 *
 */

#include "cross_platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"


const char * base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char *base64_encode(const unsigned char *bindata, char *base64, int32_t binlength)
{
    int32_t i, j;
    uint8_t current;

    for ( i = 0, j = 0 ; i < binlength ; i += 3 )
    {
        current = (bindata[i] >> 2) ;
        current &= (uint8_t)0x3F;
        base64[j++] = base64char[(int32_t)current];

        current = ( (uint8_t)(bindata[i] << 4 ) ) & ( (uint8_t)0x30 ) ;
        if ( i + 1 >= binlength )
        {
            base64[j++] = base64char[(int32_t)current];
            base64[j++] = '=';
            base64[j++] = '=';
            break;
        }
        current |= ( (uint8_t)(bindata[i+1] >> 4) ) & ( (uint8_t) 0x0F );
        base64[j++] = base64char[(int32_t)current];

        current = ( (uint8_t)(bindata[i+1] << 2) ) & ( (uint8_t)0x3C ) ;
        if ( i + 2 >= binlength )
        {
            base64[j++] = base64char[(int32_t)current];
            base64[j++] = '=';
            break;
        }
        current |= ( (uint8_t)(bindata[i+2] >> 6) ) & ( (uint8_t) 0x03 );
        base64[j++] = base64char[(int32_t)current];

        current = ( (uint8_t)bindata[i+2] ) & ( (uint8_t)0x3F ) ;
        base64[j++] = base64char[(int32_t)current];
    }
    base64[j] = '\0';
    return base64;
}

int32_t base64_decode(const char *base64, unsigned char *bindata)
{
    int32_t i, j;
    uint8_t k;
    uint8_t temp[4];
    for ( i = 0, j = 0; base64[i] != '\0' ; i += 4 )
    {
        memset( temp, 0xFF, sizeof(temp) );
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i] )
                temp[0]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+1] )
                temp[1]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+2] )
                temp[2]= k;
        }
        for ( k = 0 ; k < 64 ; k ++ )
        {
            if ( base64char[k] == base64[i+3] )
                temp[3]= k;
        }

        bindata[j++] = ((uint8_t)(((uint8_t)(temp[0] << 2))&0xFC)) |
                ((uint8_t)((uint8_t)(temp[1]>>4)&0x03));
        if ( base64[i+2] == '=' )
            break;

        bindata[j++] = ((uint8_t)(((uint8_t)(temp[1] << 4))&0xF0)) |
                ((uint8_t)((uint8_t)(temp[2]>>2)&0x0F));
        if ( base64[i+3] == '=' )
            break;

        bindata[j++] = ((uint8_t)(((uint8_t)(temp[2] << 6))&0xF0)) |
                ((uint8_t)(temp[3]&0x3F));
    }
    return j;
}