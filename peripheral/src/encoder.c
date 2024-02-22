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
