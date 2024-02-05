#include "config.h"
#include "motor.h"

#define	PWM_Peri	65535	// PWM�����趨

Motor *motor;				// �������ṹ��
PWMx_Duty *pwmA_duty;		// ����PWMA�ṹ��

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʼ�����
//  @param      PWM					PWMͨ����ȡֵ PWM1~PWM8,PWMA,PWMB
//  @return     void					
//  @since      v1.0
//  Sample usage:	motor_init(PWM1);
//-------------------------------------------------------------------------------------------------------------------
void motor_init(u8 PWMx)
{

	// ��ʼ�� PWMx
	PWMx_InitDefine PWMx_InitStructure;		// ����PWM��ʼ���ṹ��
	
	pwmA_duty -> PWM1_Duty = 128; 			// ��ʼ��PWMA��4��ͨ����ռ�ձ�
	pwmA_duty -> PWM2_Duty = 256;
	pwmA_duty -> PWM3_Duty = 512;
	pwmA_duty -> PWM4_Duty = 1024;
	
	motor->pwm_pin = PWMx;
	
	if(PWMx == PWM1)
	{
		PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1; 			//���� PWM1 ģʽ
		PWMx_InitStructure.PWM_Duty = pwmA_duty -> PWM1_Duty; 				//PWM ռ�ձ�ʱ��, 0~Period
		PWMx_InitStructure.PWM_EnoSelect = ENO1P | ENO1N; 		//���ͨ��ѡ��
		PWM_Configuration(PWM1, &PWMx_InitStructure); 			//��ʼ�� PWM1

		PWM1_USE_P60P61(); 										// PWM1 ��Ӧѡ��ͨ�� P60, P61
	}

	else if(PWMx == PWM2)
	{
		PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1; 			//���� PWM2 ģʽ
		PWMx_InitStructure.PWM_Duty = pwmA_duty -> PWM2_Duty; 				//PWM ռ�ձ�ʱ��, 0~Period
		PWMx_InitStructure.PWM_EnoSelect = ENO2P | ENO2N; 		//���ͨ��ѡ��
		PWM_Configuration(PWM2, &PWMx_InitStructure); 			//��ʼ�� PWM2
		
		PWM2_USE_P62P63(); 										// PWM2 ѡ��ͨ�� P62, P63
	}
	else if(PWMx == PWM3)
	{
		PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1; 			//���� PWM3 ģʽ
		PWMx_InitStructure.PWM_Duty = pwmA_duty -> PWM3_Duty; 				//PWM ռ�ձ�ʱ��, 0~Period
		PWMx_InitStructure.PWM_EnoSelect = ENO3P | ENO3N; 		//���ͨ��ѡ��
		PWM_Configuration(PWM3, &PWMx_InitStructure); 			//��ʼ�� PWM3
		
		PWM3_USE_P64P65(); 										//PWM3 ѡ��ͨ�� P64, P65
	}
	else if(PWMx == PWM4)
	{
		PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1; 			//���� PWM4 ģʽ
		PWMx_InitStructure.PWM_Duty = pwmA_duty -> PWM4_Duty; 				//PWM ռ�ձ�ʱ��, 0~Period
		PWMx_InitStructure.PWM_EnoSelect = ENO4P | ENO4N; 		//���ͨ��ѡ��
		PWM_Configuration(PWM4, &PWMx_InitStructure); 			//��ʼ�� PWM2
		
		PWM4_USE_P66P67(); 										//PWM4 ѡ��ͨ�� P66, P67
	}

	PWMx_InitStructure.PWM_Period = 2047; 						//����ʱ��, 0~65535
	PWMx_InitStructure.PWM_DeadTime = 0; 						//��������������, 0~255
	PWMx_InitStructure.PWM_MainOutEnable= ENABLE;				//�����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE; 				//ʹ�ܼ�����, ENABLE,DISABLE
	
	PWM_Configuration(PWMA, &PWMx_InitStructure); 				//��ʼ�� PWMA ͨ�üĴ���
	//NVIC_PWM_Init(PWMA,DISABLE,Priority_0); 					// PWM �жϹر�, ���ȼ� 0 ��
	
	// ��ʼ�� GPIO��ȫ������Ϊ׼˫���
	GPIO_PU_All_Init();
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ٶ�
//  @param      speed
//  @return     void				
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Set_Lmotor_Speed(float speed)
{
	float duty_cycle = 0;
	
	// �����ٶ���0��100֮��
    if (speed < 0)
        speed = 0;
	else if (speed > 100)
        speed = 100;	    

	// ����ռ�ձȣ�����PWM�ķ�Χ��0��255
    duty_cycle = (speed * PWM_Peri) / 100; 

	// �жϼ������ռ�ձ�������ĸ�PWMͨ��
	if(motor->pwm_pin == PWM1)
	{
		pwmA_duty->PWM1_Duty = duty_cycle;
	}
	else if(motor->pwm_pin == PWM2)
	{
		pwmA_duty->PWM2_Duty = duty_cycle;
	}
		

	UpdatePwm(motor->pwm_pin, pwmA_duty) ;	   // ����PWM������ŵ�ռ�ձ�
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      �����ҵ���ٶ�
//  @param      speed
//  @return     void				
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Set_Rmotor_Speed(float speed)
{
	float duty_cycle = 0;
	
	// �����ٶ���0��100֮��
    if (speed < 0)
        speed = 0;
	else if (speed > 100)
        speed = 100;	    

	// ����ռ�ձȣ�����PWM�ķ�Χ��0��255
    duty_cycle = (speed * PWM_Peri) / 100; 

	// �ж�ռ�ձ�duty_cycle������ĸ�PWMͨ��
	if(motor->pwm_pin == PWM3)
	{
		pwmA_duty->PWM3_Duty = duty_cycle;
	}
	else if(motor->pwm_pin == PWM4)
	{
		pwmA_duty->PWM4_Duty = duty_cycle;
	}

	UpdatePwm(motor->pwm_pin, pwmA_duty) ;	   // ��pwm���ͨ������ռ�ձ�
	
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ʼ������IO��Ϊ׼˫���	�ڲ����ã��û��������
//  @param      void
//  @return     void					
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void GPIO_PU_All_Init(void)
{
	P0_MODE_IO_PU(GPIO_Pin_All);
	P1_MODE_IO_PU(GPIO_Pin_All);
	P2_MODE_IO_PU(GPIO_Pin_All);
	P3_MODE_IO_PU(GPIO_Pin_All);
	P4_MODE_IO_PU(GPIO_Pin_All);
	P5_MODE_IO_PU(GPIO_Pin_All);
	P6_MODE_IO_PU(GPIO_Pin_All);
	P7_MODE_IO_PU(GPIO_Pin_All);
}
