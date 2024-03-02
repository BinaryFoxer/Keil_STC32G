#include "cevent.h"

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "config.h"


// 内部函数声明	用户无需关心
void EncoderL();
void EncoderR();

//函数原型
void Encoder_init();
u16 get_EncoderL();
u16 get_EncoderR();


#endif