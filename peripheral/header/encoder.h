#include "cevent.h"

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "config.h"

#define MAXENCODER 		(3000.0)
#define Encode_L		P04
#define Encode_R		P06
#define Dir_Encode_L	P20
#define Dir_Encode_R	P22

//����ԭ��
void Encoder_init();
int16 get_EncoderL();
int16 get_EncoderR();

// �ڲ���������	�û��������
void EncoderL();
void EncoderR();


#endif