#include "config.h"

#pragma userclass (near=CEVENT)	
	CEVENT_EXPORT(0,NULL,NULL);
#pragma userclass (near=default)
//
int main(void)
{	
	int cnt,pre_cnt;
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

	//��ѭ��
	while(1)
	{	
		
	}
//		cpostProcess();

}
