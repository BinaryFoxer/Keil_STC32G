#include "cevent.h"

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "config.h"


// �ڲ���������	�û��������
void EncoderL();
void EncoderR();

//����ԭ��
void Encoder_init();
u16 get_EncoderL();
u16 get_EncoderR();


#endif