/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,��ɿƼ�
 * All rights reserved.
	���߶��壺
	------------------------------------ 
	ICM20602ģ��(IICͨ��)   ��Ƭ��                        
	SCL              		�鿴SEEKFREE_ICM20602.h�ļ��е�ICM20602_SCL_PIN�궨��
	SDA              		�鿴SEEKFREE_ICM20602.h�ļ��е�ICM20602_SDA_PIN�궨��
	------------------------------------ 
 ********************************************************************************************************************/

#include "gyro_IIChard.h"
#include "gyro_IICsoft.h"
#include "STC32G_I2C.h"

//========================================================================
// ����: void I2C_Init(I2C_InitTypeDef *I2Cx)
// ����: I2C��ʼ������.
// ����: I2Cx: �ṹ����,��ο�I2C.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-11-22
//========================================================================
void I2C_Init_hard(I2C_InitTypeDef *I2Cx)
{
	if(I2Cx->I2C_Mode == I2C_Mode_Master)
	{
		I2C_Master();						//��Ϊ����	
		I2CMSST = 0x00;						//���I2C����״̬�Ĵ���
		I2C_SetSpeed(I2Cx->I2C_Speed);
		if(I2Cx->I2C_MS_WDTA == ENABLE)		I2C_WDTA_EN();				//ʹ���Զ�����
		else									I2C_WDTA_DIS();			//��ֹ�Զ�����
	}
	else
	{
		I2C_Slave();						//��Ϊ�ӻ�
		I2CSLST = 0x00;						//���I2C�ӻ�״̬�Ĵ���
		I2C_Address(I2Cx->I2C_SL_ADR);
		if(I2Cx->I2C_SL_MA == ENABLE)		I2C_MATCH_EN();			//�ӻ���ַ�ȽϹ��ܣ�ֻ������ƥ���ַ
		else									I2C_MATCH_DIS();	//��ֹ�ӻ���ַ�ȽϹ��ܣ����������豸��ַ
	}
	
	I2C_Function(I2Cx->I2C_Enable);
}



//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ ICM20602 ���ٶȼ�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     icm20602_get_acc();                                             // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void icm20602_get_acc_hard (void)
{
    uint8 dat[6];

	I2C_ReadNbyte(ICM20602_DEV_ADDR, ICM20602_ACCEL_XOUT_H, dat, 6);   /*  DeviceAddress,WordAddress,First Data Address,Byte lenth   */
    icm20602_acc_x = (int16)(((uint16)dat[0] << 8 | dat[1]));
    icm20602_acc_y = (int16)(((uint16)dat[2] << 8 | dat[3]));
    icm20602_acc_z = (int16)(((uint16)dat[4] << 8 | dat[5]));
}



//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡICM20602����������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     icm20602_get_gyro();                                            // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
void icm20602_get_gyro_hard (void)
{
    uint8 dat[6];

	I2C_ReadNbyte(ICM20602_DEV_ADDR, ICM20602_GYRO_XOUT_H, dat, 6);   /*  DeviceAddress,WordAddress,First Data Address,Byte lenth   */
    icm20602_gyro_x = (int16)(((uint16)dat[0] << 8 | dat[1]));
    icm20602_gyro_y = (int16)(((uint16)dat[2] << 8 | dat[3]));
    icm20602_gyro_z = (int16)(((uint16)dat[4] << 8 | dat[5]));
}
