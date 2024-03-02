/*==========�������ͷ�ļ�============*/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "config.h"

// �������ṹ��
typedef struct {
    u8 L_pwm_channel; 		// PWM���ͨ��
	u8 R_pwm_channel; 		// PWM���ͨ��
} Motor;

// �ڲ���������	�û��������
void GPIO_PU_Init();


//����ԭ��
void motor_init(void);					//��ʼ�����
void Set_Lmotor_Speed(long speed);		//���������ٶ�
void Set_Rmotor_Speed(long speed);		//�����ҵ���ٶ�	


#endif
