#include "config.h"
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
	
	//��ʼ������
	/******************************************************************/
	EA =1;
	/******************************************************************/
	mpu6050_init();
	//��ѭ��
	while(1)
	{	
<<<<<<< HEAD
		mpu6050_get_accdata();
		mpu6050_get_gyro();

		delay_ms(50);
		printf("mpu6050_acc_x:%d\nmpu6050_acc_y:%d\nmpu6050_acc_z:%d\n\n\n",mpu6050_acc_x,mpu6050_acc_y,mpu6050_acc_z);
=======

>>>>>>> 079fc3887d85f424bb4e96277e3481119a5a22c3
	}

}
