#include "encoder.h"
#include "intrins.h"
#include "STC32G_Timer.h"
#include "timer.h"

#define R_Wheel 		0.03	// ���Ӱ뾶
#define CyclePulses 	512		// תһȦ�������� 
#define Timer_Period	10		// ��ʱ������

u16 Encoder1_cnt, Encoder2_cnt;
float speedL, speedR;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      2����������Ӧ�Ķ�ʱ����GPIO��ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	��Ҫ�޸�Ҫ��ʼ����GPIO��
//-------------------------------------------------------------------------------------------------------------------
void Encoder_init()
{
	Encoder1_init();
	Encoder2_init();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ2���������ļ���ֵ���ٶ�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	���øú�����ֱ��ʹ�ñ���Encoder1_cnt, speedL, Encoder2_cnt, speedR
//-------------------------------------------------------------------------------------------------------------------
void Encoder()
{
	Encoder1();
	Encoder2();
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ������1�ļ���ֵ���ٶ�	(�ڲ����ã��û��������)
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	���ú���֮��ֱ��ʹ�ñ���Encoder1_cnt, speedL
//-------------------------------------------------------------------------------------------------------------------
void Encoder1()
{
	ctimer_count_clean(CTIM3_P04);			// �������
	//pit_timer_ms(TIM_0, Timer_Period);
	Encoder1_cnt = ctimer_count_read(CTIM3_P04);
	speedL = (Encoder1_cnt / CyclePulses * (2*PI*R_Wheel ) / Timer_Period);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ������2�ļ���ֵ���ٶ�	(�ڲ����ã��û��������)
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	���ú���֮��ֱ��ʹ�ñ���Encoder2_cnt, speedR
//-------------------------------------------------------------------------------------------------------------------
void Encoder2()
{
	ctimer_count_clean(CTIM4_P06);			// �������
	pit_timer_ms(TIM_0, Timer_Period);
	//Encoder2_cnt = ctimer_count_read(CTIM4_P06);
	speedR = (Encoder2_cnt / CyclePulses * (2*PI*R_Wheel ) / Timer_Period);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������1��Ӧ��GPIO�ڳ�ʼ��	(�ڲ����ã��û��������)
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Encoder1_init()
{
	GPIO_InitTypeDef	GPIO_InitStructure;					//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_HIGH | GPIO_Pin_4;	//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;					//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);				//��ʼ��P04
	
	ctimer_count_init(CTIM3_P04);							//��ʱ��3��ʼ����Ϊ�ⲿ����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������2��Ӧ��GPIO�ڳ�ʼ��	(�ڲ����ã��û��������)
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void Encoder2_init()
{
	GPIO_InitTypeDef	GPIO_InitStructure;					//�ṹ����
	GPIO_InitStructure.Pin  = GPIO_Pin_HIGH | GPIO_Pin_6;	//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_InitStructure.Mode = GPIO_PullUp;					//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);				//��ʼ��P06
	
	ctimer_count_init(CTIM4_P06);							//��ʱ��4��ʼ����Ϊ�ⲿ����
}


//==================================================================================================================

//-------------------------------------------------------------------------------------------------------------------
//  @brief      Timer3/4��GPIO��ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	��Ҫ�޸�Ҫ��ʼ����GPIO��
//-------------------------------------------------------------------------------------------------------------------
//void Timer_config(u8 TimerX)
//{
//	TIM_InitTypeDef		TIM_InitStructure;					//�ṹ����
//	GPIO_InitTypeDef	GPIO_InitStructure;					//�ṹ����
//	
//	if(TimerX == Timer3)
//	{
//		GPIO_InitStructure.Pin  = GPIO_Pin_HIGH | GPIO_Pin_4;	//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
//		GPIO_InitStructure.Mode = GPIO_PullUp;					//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//		GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);				//��ʼ��
//		
//		TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
//		TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_Ext;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
//		TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
//		TIM_InitStructure.TIM_Value     = (u16)(65536UL - (MAIN_Fosc / 100000UL));		//��ֵ,
//		TIM_InitStructure.TIM_PS        = 0;					//8λԤ��Ƶ��(n+1), 0~255
//		TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
//		Timer_Inilize(Timer0,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer2,Timer3,Timer4
//		NVIC_Timer0_Init(ENABLE,Priority_0);					//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	}
//	else if(TimerX == Timer4)
//	{
//		GPIO_InitStructure.Pin  = GPIO_Pin_HIGH | GPIO_Pin_6;	//ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
//		GPIO_InitStructure.Mode = GPIO_PullUp;					//ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//		GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);				//��ʼ��
//		
//		TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
//		TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_Ext;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
//		TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
//		TIM_InitStructure.TIM_Value     = (u16)(65536UL - (MAIN_Fosc / 100000UL));		//��ֵ,
//		TIM_InitStructure.TIM_PS        = 0;					//8λԤ��Ƶ��(n+1), 0~255
//		TIM_InitStructure.TIM_Run       = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
//		Timer_Inilize(Timer1,&TIM_InitStructure);				//��ʼ��Timer1	  Timer0,Timer1,Timer2,Timer3,Timer4
//		NVIC_Timer0_Init(ENABLE,Priority_0);					//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
//	}
//	
//}


//#include "encoder.h"
//#include "intrins.h"
//#include "STC32G_PWM.h"

//#define R_Wheel 	0.03		// ���Ӱ뾶
//#define CyclePulses 1500		// תһȦ�������� 

//u8  cnt_H, cnt_L;						//����ֵ��8λ����8λ
//u16 count, newcount;					//����ֵ���¼���ֵ
//u8  leftmove, rightmove;				//��ת��־����ת��־
//float speed;							//ͨ����������������ٶ�
//bit numberchange;						//��ֵ�ı��־

////-------------------------------------------------------------------------------------------------------------------
////  @brief      ��������ʼ������
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:	
////-------------------------------------------------------------------------------------------------------------------
//void Encoder_Config(void)
//{
//	// ��ѡ
//	P0M1 = 0x00;P0M0 = 0x00;		//����P0��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	P1M1 = 0x00;P1M0 = 0x00;		//����P1��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	P2M1 = 0x00;P2M0 = 0x00;		//����P2��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	P3M1 = 0x00;P3M0 = 0x00;		//����P3��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	P4M1 = 0x00;P4M0 = 0x00;		//����P4��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	P5M1 = 0x00;P5M0 = 0x00;		//����P5��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	P6M1 = 0x00;P6M0 = 0x00;		//����P6��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	P7M1 = 0x00;P7M0 = 0x00;		//����P7��Ϊ׼˫���ģʽ //00��׼˫��� 01��������� 10���������� 11����©���
//	
//	PWMB_ENO = 0x00;					// ���ó� TRGI �� pin ��ص� ENO ��Ӧ bit ����� input
//	
//	PWMB_PSCRH = 0x00;					//Ԥ��Ƶ�Ĵ���
//	PWMB_PSCRL = 0x00;
//	
//	PWMB_CCER1 = 0x00;					// ����CCER���ر�ͨ��
//	PWMB_CCMR1 = 0x21; 					// ͨ��ģʽ����Ϊ���룬�ӱ����� , �˲��� 4 ʱ��
//	PWMB_CCMR2 = 0x21; 					// ͨ��ģʽ����Ϊ���룬�ӱ����� , �˲��� 4 ʱ��
//	PWMB_CCER1 = 0x55; 					// ����ͨ��ʹ�ܺͼ���
//	PWMB_CCER2 = 0x55; 					// ����ͨ��ʹ�ܺͼ���
//	
////	PWMA_SMCR = 0x01; 					// ������ģʽ 1
////	PWMA_SMCR = 0x02; 					// ������ģʽ 2
//	PWMB_SMCR = 0x03; 					// ������ģʽ 3
//	
//	PWMB_IER = 0x02; 					// ʹ���ж�
//	PWMB_CR1 |= 0x01; 					// ʹ��PWM������
//	
//}


////-------------------------------------------------------------------------------------------------------------------
////  @brief      ��������⺯��(��ȡCNTRֵ)
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:	
////-------------------------------------------------------------------------------------------------------------------
//void Encoder_Check()					//������������ֵ
//{
//	newcount = cnt_H * 256 + cnt_L;		//��ȡ�µļ�����ֵ
//	if(newcount < count) 				//����¼���ֵ С�� ����ֵ
//	{
//		leftmove = 1;					//��ת��־��1
//		count = newcount;				//���¼���ֵ
//		numberchange = 1;

//	}
//	else if(newcount > count)			//����¼���ֵ ���� ����ֵ
//	{
//		rightmove = 1;					//��ת��־��1
//		count = newcount;				//���¼���ֵ
//		numberchange = 1;

//	}
//}

////-------------------------------------------------------------------------------------------------------------------
////  @brief      ���ݱ��������������ٶ�
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:	
////-------------------------------------------------------------------------------------------------------------------
//void Encoder_Speed()
//{
//	speed = (count / 5) * (2*PI*R_Wheel / CyclePulses);
//}

////-------------------------------------------------------------------------------------------------------------------
////  @brief      �жϷ�����
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:	
////-------------------------------------------------------------------------------------------------------------------
//void PWMB_ISR() interrupt 26
//{
//	if (PWMB_SR1 & 0x02)				//����1�жϱ�־��1ʱ
//	{
//		cnt_H = PWMB_CCR5H;				//��ȡPWM��������8λ		
//		cnt_L = PWMB_CCR5L;				//��ȡPWM��������8λ
//		PWMB_SR1 &= ~0X02;				//���㲶��1�жϱ�־
//		Encoder_Check();				//������������ֵ
//		Encoder_Speed();				//���ݼ���ֵ�����ٶ�
//	}
//}
