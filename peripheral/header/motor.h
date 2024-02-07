/*==========�������ͷ�ļ�============*/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "config.h"

// �������ṹ��
typedef struct {
    u8 pwm_pin; 		// PWM�������
    u8 direction_pin1;  // ��������������1
    u8 direction_pin2;  // ��������������2
} Motor;

// �ڲ���������	�û��������
void GPIO_PU_Init();



//����ԭ��
void motor_init(u8 PWMx);				//��ʼ�����
void Set_Lmotor_Speed(float speed);		//���������ٶ�
void Set_Rmotor_Speed(float speed);		//�����ҵ���ٶ�	



#endif
