#include "cevent.h"

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "config.h"

#define MAXENCODER 		(3000.0)

//����ԭ��
void Encoder_init();
u16 get_EncoderL();
u16 get_EncoderR();

// �ڲ���������	�û��������
void EncoderL();
void EncoderR();


#endif