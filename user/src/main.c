#include "config.h"

#pragma userclass (near=CEVENT)	
	CEVENT_EXPORT(0,NULL,NULL);
#pragma userclass (near=default)
extern uint16 All_Signal_Data[4];

int main(void)
{	
	/******************************************************************/
	ceventInit();
	ceventPost(0);
	Screen_Init();
	Signal_Init();
	//��ʼ������
	/******************************************************************/
	EA =1;
	/******************************************************************/

	//��ѭ��
	
	while(1)
	{	
		
	}

}
