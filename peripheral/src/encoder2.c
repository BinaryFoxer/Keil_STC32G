#include "encoder2.h"
#include "intrins.h"
#include "STC32G_Timer.h"
#include "timer.h"


#define R_Wheel 	0.03		// ���Ӱ뾶
#define CyclePulses 512		// תһȦ�������� 

u16 Encoder1_cnt, Encoder2_cnt;
float speedL, speedR;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      2����������Ӧ��GPIO��ʼ��
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
//  @brief      ��ȡ������1�ļ���ֵ���ٶ�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	���ú���֮��ֱ��ʹ�ñ���Encoder1_cnt, speedL
//-------------------------------------------------------------------------------------------------------------------
void Encoder1()
{
	// pit_timer_ms(TIM_0, 10);
	Encoder1_cnt = ctimer_count_read(CTIM3_P04);
	speedL = (Encoder1_cnt / 5) * (2*PI*R_Wheel / CyclePulses);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ������2�ļ���ֵ���ٶ�
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	���ú���֮��ֱ��ʹ�ñ���Encoder2_cnt, speedR
//-------------------------------------------------------------------------------------------------------------------
void Encoder2()
{
	//pit_timer_ms(TIM_0, 10);
	Encoder2_cnt = ctimer_count_read(CTIM4_P06);
	speedR = (Encoder2_cnt / 5) * (2*PI*R_Wheel / CyclePulses);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������1��Ӧ��GPIO�ڳ�ʼ��(�ڲ����ã��û��������)
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
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);				//��ʼ��
	
	ctimer_count_init(CTIM3_P04);							//��ʱ��3��ʼ����Ϊ�ⲿ����
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������2��Ӧ��GPIO�ڳ�ʼ��(�ڲ����ã��û��������)
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
	GPIO_Inilize(GPIO_P0,&GPIO_InitStructure);				//��ʼ��
	
	ctimer_count_init(CTIM4_P06);							//��ʱ��4��ʼ����Ϊ�ⲿ����
}


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
