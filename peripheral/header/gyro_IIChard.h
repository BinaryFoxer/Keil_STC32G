/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 ********************************************************************************************************************/
#ifndef __GYROSCOPE_H__
#define __GYROSCOPE_H__
#include "config.h"
#include "STC32G_I2C.h"

void I2C_Init_hard (I2C_InitTypeDef *I2Cx);
void icm20602_get_acc_hard (void);
void icm20602_get_gyro_hard (void);

#endif
	