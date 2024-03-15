#include "gyroscope.h"
#include "config.h"

#define dt 0.01

int16 gyro_gyro_x,gyro_gyro_y,gyro_gyro_z;
int16 gyro_acc_x,gyro_acc_y,gyro_acc_z;


float fil_Acc_x,fil_Acc_y;		//���崦���ļ��ٶ�ֵ
float fil_Gyro_z;				//���崦���Ľ��ٶ�ֵ
float Gyro_z=0;					//����Ĵ�����ٶȵ��м����
float Angle_Z=90;				//���ó�ʼ�Ƕ�Ϊ90��
float Gyroscope_FIFO[11];
int gyro_i=0;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡICM20602���ٶȼ�����
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
//-------------------------------------------------------------------------------------------------------------------
void Get_gyro_accdata(void)
{
    uint8 dat[6];
    uint16 reg =  ICM20602_ACCEL_XOUT_H;
    iic_read_regs(ICM20602_DEV_ADDR, reg, 2 , dat, 6);  
    gyro_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    gyro_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    gyro_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡICM20602����������
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
//-------------------------------------------------------------------------------------------------------------------
void Get_gyro_gyro(void)
{
    uint8 dat[6];
    uint16 reg =  ICM20602_GYRO_XOUT_H;

    iic_read_regs(ICM20602_DEV_ADDR, reg, 2 , dat, 6);  
    gyro_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    gyro_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    gyro_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

/**************************************************************************
�������ܣ�����ƽ���˲��㷨 ������ٶ�
��ڲ�������
����  ֵ����
**************************************************************************/
void Gyroscope_newValues()
{
	float sum=0;
	static float gyro[100],sum_gyro;
	static int gyro_flag=0,Gyro_flag;

	Get_gyro_gyro();		// ��ȡ���ٶ�����
	if(gyro_flag==0)
	{		 
		gyro[gyro_i]=gyro_gyro_z;
		fil_Gyro_z=0.0;
		gyro_i++;
		if(gyro_i==99)
		{
			for(gyro_i=0;gyro_i<100;gyro_i++)
			{
				sum_gyro+=gyro[gyro_i];
			}
			gyro_flag=1;
		}
	} 
	if(gyro_flag==1)
	{
		Gyro_z = (float)(gyro_gyro_z-sum_gyro/100)/16.3835;
		if(abs(Gyro_z)<3)//���ٶ�С��3ʱ  Ĭ��ΪС����ֹ  
		{
			Gyro_z=0;
		}
		for(Gyro_flag=1;Gyro_flag<10;Gyro_flag++)
		{	
			Gyroscope_FIFO[Gyro_flag-1]=Gyroscope_FIFO[Gyro_flag];//FIFO ����
		}
		Gyroscope_FIFO[9]=Gyro_z;
		for(Gyro_flag=0;Gyro_flag<10;Gyro_flag++)
		{	            
			sum+=Gyroscope_FIFO[Gyro_flag];//��ǰ����ĺϣ���ȡƽ��ֵ
		}
		fil_Gyro_z=sum/10;
	}
}		

/**************************************************************************
�������ܣ��Խ��ٶȻ��� �õ��Ƕ�
��ڲ�������
����  ֵ����
**************************************************************************/
float Get_angle()
{
	Gyroscope_newValues();			//ʹ�������ǻ�ȡ���ٶ�
	Angle_Z-=fil_Gyro_z*dt;
	if(Angle_Z>=360) Angle_Z=Angle_Z-360;
	if(Angle_Z<=-360) Angle_Z=Angle_Z+360;
	
	return Angle_Z;
}



