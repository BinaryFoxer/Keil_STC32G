#ifndef __SIGNAL_ACQ_H__
#define __SIGNAL_ACQ_H__

#include "config.h"
#define CHANNEL_NUM         1           //һ����Ҫ�ɼ���ͨ����Ŀ
#define CONVERT_TIMES       4           //DMA_ADC�ɼ��Ĵ���
#define MAX_VOLTAGE         2.5           //С���ܲɼ�������ѹ
#define MIN_VOLTAGE         1.6           //С���ܲɼ�����С��ѹ
#define MAX_BIAS          100           //��׼�����ʾ��ѹ��С�Ĳ������ֵ
#define MIN_BIAS          (-100)        //��׼�����ʾ��ѹ��С����Сֵ
#define RATIO              MAX_BIAS/(MAX_VOLTAGE-MIN_VOLTAGE)*(MAX_VOLTAGE-MIN_VOLTAGE)*(MAX_VOLTAGE-MIN_VOLTAGE)
                                        //��ADC�ɼ�ֵת���ɱ�׼��Χ�ı���
#define REF_VOLTAGE         5         //�ο���ѹ
#define CAPTURE_LIMIT       4096

int8 Get_Regularized_Signal_Data(const float * Data_Array);
void Sample_All_Chanel();
uint16 Get_DMA_ADC_Result(uint8 channel);
void Signal_Acq_Init(unsigned char GPIO_PX, unsigned int GPIO_pin);
float Get_Voltage();
#endif