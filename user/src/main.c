#include "config.h"
#include "iic.h"
#include "telemeter.h"
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
	dl1b_init();
	//��ʼ������
	/******************************************************************/
	EA =1;
	/******************************************************************/
	//��ѭ��
	while(1)
	{	
		printf("distance : %d\n",dl1b_get_distance());
		delay_ms(50);
	}

}
