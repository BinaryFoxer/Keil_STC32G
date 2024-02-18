#include "control.h"
PID_Calibration Left_Speed_PID = {0,0,0};		//�����ٶ�PID����
PID_Calibration Right_Speed_PID = {0,0,0};		//�ҵ���ٶ�PID����
PID_Calibration Turn_PID = {0,0,0};			    //ת��PID����

PID_State Left_Speed_State;				//�����ٶ�״̬����
PID_State Right_Speed_State;			//�ҵ���ٶ�״̬����
PID_State Turn_State;				    //ת��״̬����


/// @brief ͨ��PID�㷨��������ٶȴﵽĿ���ٶ�
/// @param Left_Speed ��������������Ŀ���ٶ�
/// @param Right_Speed ���������ҵ����Ŀ���ٶ�
void Speed_Ctrl(unsigned int Left_Speed,unsigned int Right_Speed)
{
	
}

/// @brief ͨ��PID�㷨��������ٶȴﵽĿ���ٶȺ�Ŀ��Ƕ�
/// @param Gyro ��������С����Ŀ��Ƕ�
void Turn_Ctrl(unsigned int Gyro)
{

}

/// @brief ��׼���������������Ӿ�������������磺���ţ��޷�����һ���Ȳ���
/// @param left_state 
/// @param right_state 
void Regularization(PID_State * left_state,PID_State * right_state)
{

}

/// @brief ���µ��PWMת��
/// @param left_state 
/// @param right_state 
/// @param gyro_state 
void Update_Motors(PID_State * left_state,PID_State * right_state,PID_State * gyro_state)
{
	Set_Rmotor_Speed(right_state->output + gyro_state->output);
	Set_Lmotor_Speed(left_state->output + gyro_state->output);
}

void Stop_Car(void)
{
	Set_Rmotor_Speed(0);
	Set_Lmotor_Speed(0);
}
