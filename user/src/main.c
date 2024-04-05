#include "config.h"
#include "iic.h"
#include "gyroscope.h"
#include "timer.h"

#pragma userclass (near=CEVENT)	
	CEVENT_EXPORT(0,NULL,NULL);
#pragma userclass (near=default)
//
int main(void)
{	
	WTST = 0;		//���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXSFR();		//��չSFR(XFR)����ʹ�� 
	CKCON = 0;      //��߷���XRAM�ٶ�
	
	/******************************************************************/
	ceventInit();
	ceventPost(0);
	iic_init();
	icm20602_init();
	
	pit_timer_ms(TIM_0, 10);
	//��ʼ������
	/******************************************************************/
	EA =1;
	/******************************************************************/
	//��ѭ��
	while(1)
	{	
		printf("gyro_x : %d,gyro_y: %d,gyro_z:%d\n",gyro_gyro_x,gyro_gyro_y,gyro_gyro_z);
		printf("Angle: %.2f\n",Angle_Z);
		delay_ms(50);
	}

}
