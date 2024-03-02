#include "encoder.h"
#include "intrins.h"
#include "STC32G_Timer.h"
#include "timer.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      2����������Ӧ�Ķ�ʱ����GPIO��ʼ��
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	�����޸ĳ�ʼ����GPIO��
//-------------------------------------------------------------------------------------------------------------------
void Encoder_init()
{
	P0_MODE_IO_PU(GPIO_Pin_4);			//P04��ʼ��Ϊ˫���
	ctimer_count_init(CTIM3_P04);		//��ʱ��3��ʼ����Ϊ�ⲿ����

	P0_MODE_IO_PU(GPIO_Pin_6);			//P06��ʼ��Ϊ˫���
	ctimer_count_init(CTIM4_P06);		//��ʱ��4��ʼ����Ϊ�ⲿ����
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ��������ļ���ֵ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	���ú���֮��ֱ��ʹ�ñ���Encoder1_cnt, speedL
//-------------------------------------------------------------------------------------------------------------------
u16 get_EncoderL()
{
	u16 EncoderL_cnt;
	
	EncoderL_cnt = ctimer_count_read(CTIM3_P04);
	ctimer_count_clean(CTIM3_P04);					// �������
	
	return EncoderL_cnt;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ�ұ������ļ���ֵ
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	���ú���֮��ֱ��ʹ�ñ���Encoder2_cnt, speedR
//-------------------------------------------------------------------------------------------------------------------
u16 get_EncoderR()
{
	u16 EncoderR_cnt;

	EncoderR_cnt = ctimer_count_read(CTIM4_P06);
	ctimer_count_clean(CTIM4_P06);			// �������
	
	return EncoderR_cnt;
}
