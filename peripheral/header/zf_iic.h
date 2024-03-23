/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		iic
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_IIC_H
#define __ZF_IIC_H


#include "config.h"

typedef enum
{
    IIC_1 = 0,
    IIC_2 = 1,
    IIC_3 = 2,	//STC8H 48�ź��İ�û�и������š�
    IIC_4 = 3,
	
} IICN_enum;

typedef enum
{
    IIC1_SCL_P15 = 0x00, IIC1_SDA_P14,
    IIC2_SCL_P25 = 0x10, IIC2_SDA_P24,
    IIC3_SCL_P77 = 0x20, IIC3_SDA_P76,	//STC8H 48�ź��İ�û�и������š�
    IIC4_SCL_P32 = 0x30, IIC4_SDA_P33,
} IIC_PIN_enum;






#define IIC_SEND_OK 	0
#define IIC_SEND_FAIL	1




void  Zf_IIC_init(IICN_enum iic_n, IIC_PIN_enum scl_pin, IIC_PIN_enum sda_pin, uint32 wait_time);
uint8 Zf_IIC_write_reg(uint8 dev_add, uint8 reg, uint8 dat);
uint8 Zf_IIC_read_reg(uint8 dev_add, uint8 reg, uint8 *dat);
uint8 Zf_IIC_read_reg_bytes(uint8 dev_add, uint8 reg, uint8 *dat, uint8 num);
void Zf_IIC_change_pin(IICN_enum iic_n,IIC_PIN_enum scl_pin,IIC_PIN_enum sda_pin);
uint8 Zf_IIC_transfer(const uint8 dev_add, const uint8 *write_add, uint8 write_num, uint8 *read_add, uint8 read_num);
#endif