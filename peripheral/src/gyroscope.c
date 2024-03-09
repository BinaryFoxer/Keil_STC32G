#include "gyroscope.h"
#include "config.h"
#include "gyro_IICsoft.h"
#include "gyro_IIChard.h"

#define dt 0.01

float Gyro_z=0;
float fil_Acc_x,fil_Acc_y,fil_Gyro_z;
float Angle_Z1=0,Angle_Z2=90;
float coe_Gyro_z=0.2;
float ICM20602_FIFO[11];
int moto_flag=0;
int gyro_i=0;


/**************************************************************************
�������ܣ�����ƽ���˲��㷨 ������ٶ�
��ڲ�������
����  ֵ����
**************************************************************************/
void ICM20602_newValues()
{
	 float sum=0;
	 static float gyro[100],sum_gyro;
	 static int gyro_flag=0,Gyro_flag;
	 
	 icm20602_get_acc_hard();		// ʹ��Ӳ��IIC��ȡicm20602 acc����
		if(gyro_flag==0)
	 {		 
		  gyro[gyro_i]=icm20602_gyro_z;
		  fil_Gyro_z=0.0;
		  gyro_i++;
		 if(gyro_i==99)
		 {
			 moto_flag=1;
			 for(gyro_i=0;gyro_i<100;gyro_i++)
			 {
				 sum_gyro+=gyro[gyro_i];
			 }
			 gyro_flag=1;
		 }
	 } 
	 if(gyro_flag==1)
	 {
    Gyro_z = (float)(icm20602_gyro_z-sum_gyro/100)/16.3835;
	  if(abs(Gyro_z)<3)//���ٶ�С��3ʱ  Ĭ��ΪС����ֹ  
	  {
		  Gyro_z=0;
	  }
	  for(Gyro_flag=1;Gyro_flag<10;Gyro_flag++)
		{	
		  ICM20602_FIFO[Gyro_flag-1]=ICM20602_FIFO[Gyro_flag];//FIFO ����
		}
	  ICM20602_FIFO[9]=Gyro_z;
	  for(Gyro_flag=0;Gyro_flag<10;Gyro_flag++)
		{	            
			sum+=ICM20602_FIFO[Gyro_flag];//��ǰ����ĺϣ���ȡƽ��ֵ
		}
	  fil_Gyro_z=sum/10;
	}
}		
/**************************************************************************
�������ܣ��Խ��ٶȻ��� �õ��Ƕ�
��ڲ�������
����  ֵ����
**************************************************************************/
void Get_angle()
{
   ICM20602_newValues();
	 Angle_Z2-=fil_Gyro_z*dt;
	 if(Angle_Z2>=360) Angle_Z2=Angle_Z2-360;
	 if(Angle_Z2<=-360) Angle_Z2=Angle_Z2+360;
}