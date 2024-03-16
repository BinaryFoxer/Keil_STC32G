#ifndef 	__IIC_H__
#define 	__IIC_H__

#include "config.h"

//�����Ƿ�ʹ�����IIC
#define 	USE_SOFT_IIC		(1)
	
#ifdef USE_SOFT_IIC

	//��� IIC �������Ŷ���
	#define		SCL_GPIO_PIN	P15
	#define 	SDA_GPIO_PIN	P14
	#define 	IIC_GPIO					GPIO_P1
	#define 	IIC_SCL_PIN   				GPIO_Pin_5				// ��� IIC SCL ����
	#define 	IIC_SDA_PIN  				GPIO_Pin_4				// ��� IIC SDA ����

	#define 	SDA0()       SDA_GPIO_PIN=0	//IO������͵�ƽ
	#define 	SDA1()       SDA_GPIO_PIN=1	//IO������ߵ�ƽ  
	#define 	SCL0()       SCL_GPIO_PIN=0	//IO������͵�ƽ
	#define 	SCL1()       SCL_GPIO_PIN=1	//IO������ߵ�ƽ
	#define 	ack 			1      	//��Ӧ��
	#define 	no_ack 			0   	//��Ӧ��

#else	//use hardware IIC

#endif	//USE_SOFT_IIC


void iic_write_reg(uint8 dev_add, uint8 * reg_add, uint8 reg_num,uint8 dat);
void iic_write_regs(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 *dat_add, uint8 dat_num);
uint8 iic_read_reg(uint8 dev_add, uint8 * reg_add, uint8 reg_num);
void iic_read_regs(uint8 dev_add, uint8 * reg_add, uint8 reg_num, uint8 *dat_add, uint8 dat_num);
void iic_init(void);

#endif	//__IIC_H__