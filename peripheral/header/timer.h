#include "cevent.h"
#include "STC32G_Timer.h"

#ifndef __TIMER_H__
#define __TIMER_H__


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    CTIM0_P34=0,    
	CTIM1_P35,    	
	CTIM2_P12,     	
	CTIM3_P04,
	CTIM4_P06,
}CTIMN_enum;


//��ö�ٶ��岻�����û��޸�
typedef enum    // ö��ADCͨ��
{
    TIM_0,    
	TIM_1,    	
	TIM_2,     	
	TIM_3,
	TIM_4,
}TIMN_enum;


#define TIM2_CLEAR_FLAG		AUXINTIF &= ~0x01; 
#define TIM3_CLEAR_FLAG		AUXINTIF &= ~0x02; // ���жϱ�־
#define TIM4_CLEAR_FLAG		AUXINTIF &= ~0x04; // ���жϱ�־


void   ctimer_count_init(CTIMN_enum tim_n);
void   ctimer_count_clean(CTIMN_enum tim_n);
uint16 ctimer_count_read(CTIMN_enum tim_n);

void pit_timer_ms(TIMN_enum tim_n,uint16 time_ms);


#endif