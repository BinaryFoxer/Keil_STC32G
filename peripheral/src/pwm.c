#include "pwm.h"


#define PWM_PSCR 0
#define PWM_ARR  2211
#define PWM_CCR  553

//========================================================================
// ��������: PWMA_Init
// ��������: p60�˿����һ��PWM�ź�
// ��ڲ���: ��
// ��������: ��
// ��ǰ�汾: VER1.0
// �޸�����: 2023
// ��ǰ����: 
// ������ע: 
//���Ƶ��   = sysclk��22.1184mhz��/��pscr+1��/(arr+1) = 22118400 / 1 / �� 999+1�� = 22118.4hz = 22.1184khz 
//���ռ�ձ� = ccr/( arr+1 )*100% = 500/�� 999+1�� = 50%
//========================================================================
void PWMA_Init(void)			//PWMA�ĳ�ʼ��
{
	//1.ʱ��Դѡ��  ���ﲻ�ģ�Ĭ��22.1184mhz
	
	//2.ʱ����Ԫѡ��
	PWMA_PSCRH = (u8)(PWM_PSCR>>8);				//1��Ƶ
	PWMA_PSCRL = (u8)(PWM_PSCR);
	
	PWMA_ARRH  = (u8)(PWM_ARR>>8);
	PWMA_ARRL  = (u8)(PWM_ARR);
	
	PWMA_CCR1H  = (u8)(PWM_CCR>>8);
	PWMA_CCR1L  = (u8)(PWM_CCR);	
	
	
	//3.�����������������
	PWMA_ENO = 0X00;			
	PWMA_ENO |= 0X01;			//ʹ��PWM1pͨ�����
	PWMA_ENO |= 0X02;			//ʹ��PWM1Nͨ�����
	
	PWMA_PS =0x00;				//ѡ��PWM1��P60�������
	PWMA_PS |= (2<<0);	
	
	//4.�������ģʽ����
	PWMA_CCER1 = 0X00;
	PWMA_CCMR1 = 0X68;			//pwmģʽ1 ������λ���
	PWMA_CCER1 = 0x05;			//��������Ƚ�ͨ��
//	PWMA_CCER1 |= 0x08;			//
	
	PWMA_DTR = 175;				//10us����ʱ��
	
	PWMA_BKR = 0X80;			//ʹ�������
	
	PWMA_CR1 |= 0X01;			//����������
}

//========================================================================
// ��������: PWMA1_Set
// ��������: ��·pwm���
// ��ڲ���: @pwm �� 0:ֹͣ   >0: pwmxp���pwm  <0: pwmxn���pwm  
// ��������: ��
// ��ǰ�汾: VER1.0
// �޸�����: 2023
// ��ǰ����:
// ������ע: PWMA1_Set(0);  ֹͣ    PWMA1_Set(100); ��ת    PWMA1_Set(-100); ��ת 
//========================================================================

void PWMA1_Set(int pwm)
{
	if( pwm==0 )		//���ֹͣ
	{
		//1p 1n��Ϊ�͵�ƽ
		PWMA_CCR1H = 0;
		PWMA_CCR1L = 0;
		PWMA_ENO &= 0XFC;		//�ر�1p 1nͨ��
		PWM1P = 0;
		PWM1N = 0;
	}
	else if( pwm>0 )		//�����ת
	{
		if( pwm >(PWM_ARR+1) )
			pwm = (PWM_ARR+1);
		
		PWMA_CCR1H = (u8)(pwm>>8);
		PWMA_CCR1L = (u8)(pwm);	
		PWMA_ENO &= 0XFC;		//�ر�1p 1nͨ��
		PWMA_ENO |= 0X01;			//ʹ��PWM1pͨ�����
		PWM1N = 0;
	}
	else if( pwm<0 )		//�����ת
	{
		pwm = -pwm;
		if( pwm >(PWM_ARR+1) )
			pwm = (PWM_ARR+1);
		
		PWMA_CCR1H = (u8)(pwm>>8);
		PWMA_CCR1L = (u8)(pwm);	
		PWMA_ENO &= 0XFC;		//�ر�1p 1nͨ��
		PWMA_ENO |= 0X02;			//ʹ��PWM1nͨ�����
		PWM1P = 0;	
	}	
}

void PWMA_Init(void)			//PWMA�ĳ�ʼ��
{
	//ʱ��Դѡ��  ���ﲻ�ģ�Ĭ��22.1184mhz
	
	//ʱ����Ԫѡ��
	PWMA_PSCRH = 0;				//1��Ƶ
	PWMA_PSCRL = 0;
	
	PWMA_ARRH  = (u8)(PWM_ARR>>8);
	PWMA_ARRL  = (u8)(PWM_ARR);
	
	PWMA_CCR1H  = (u8)(PWM_CCR>>8);
	PWMA_CCR1L  = (u8)(PWM_CCR);	
	
	
	//�����������������
	PWMA_ENO = 0X00;			//ʹ��PWM1nͨ�����
	PWMA_ENO |= 0X02;
	
	PWMA_PS =0x00;				//ѡ��PWM1��P60�������
	PWMA_PS |= (2<<0);	
	
	//�������ģʽ����
	PWMA_CCER1 = 0X00;
	PWMA_CCMR1 = 0X68;			//pwmģʽ1 ������λ���
	PWMA_CCER1 = 0x04;			//��������Ƚ�ͨ��
	
	PWMA_BKR = 0X80;			//ʹ�������
	
	PWMA_CR1 |= 0X01;			//����������
}

void PWMA_Init(void)			//PWMA�ĳ�ʼ��
{
	//1.ʱ��Դѡ��  ���ﲻ�ģ�Ĭ��22.1184mhz
	
	//2.ʱ����Ԫѡ��
	PWMA_PSCRH = 0;				//1��Ƶ
	PWMA_PSCRL = 0;
	
	PWMA_ARRH  = (u8)(PWM_ARR>>8);
	PWMA_ARRL  = (u8)(PWM_ARR);
	
	PWMA_CCR1H  = (u8)(PWM_CCR>>8);
	PWMA_CCR1L  = (u8)(PWM_CCR);	
	
	
	//3.�����������������
	PWMA_ENO = 0X00;			//ʹ��PWM2pͨ�����
	PWMA_ENO |= 0X04;
	
	PWMA_PS =0x00;				//ѡ��PWM2��P62�������
	PWMA_PS |= (2<<2);	
	
	//4.�������ģʽ����
	PWMA_CCER1 = 0X00;
	PWMA_CCMR2 = 0X68;			//pwmģʽ1 ������λ���
	PWMA_CCER1 = 0x10;			//��������Ƚ�ͨ��
	
	PWMA_BKR = 0X80;			//ʹ�������
	
	PWMA_CR1 |= 0X01;			//����������
}


