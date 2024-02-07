#include "Kalman_Filter.h"
#include <math.h> 

// �������˲�������
#define Q_angle		0.001		// �ǶȵĲ�����������
#define Q_bias		0.003		// ���ٶ�ƫ��Ĳ�����������
#define R_measure	0.03		// ��������������
// ����ȫ�ֱ�����ͬʱ��ʼ��
float angle = 0; 					// �������˲�������ĽǶ�
float bias = 0;  					// �������˲��������������ƫ��
float P_Filt[2][2] = {{0, 0}, {0, 0}}; 	// ���Э�������

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���¿������˲���
//  @param      filter		ָ�򿨶����˲����ṹ���ָ��
//  @param      newAngle	�����ǲ����õ����½Ƕ�ֵ
//  @param      newRate		�����ǲ����õ����½��ٶ�ֵ
//  @param      dt			ʱ��������ʾ���β���֮���ʱ��ͨ������Ϊ��λ��
//  @return     		
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void KalmanFilter(float newAngle, float newRate, float dt)
{
	float S, y_Filt;
	float K_Filt[2] = {0, 0};	// ����������
	
    // Ԥ�����
    angle += dt * (newRate - bias);
    P_Filt[0][0] += dt * (dt*P_Filt[1][1] - P_Filt[0][1] - P_Filt[1][0] + Q_angle);
    P_Filt[0][1] -= dt * P_Filt[1][1];
    P_Filt[1][0] -= dt * P_Filt[1][1];
    P_Filt[1][1] += Q_bias * dt;

    // ��������
    S = P_Filt[0][0] + R_measure;
    K_Filt[0] = P_Filt[0][0] / S;
    K_Filt[1] = P_Filt[1][0] / S;

    y_Filt = newAngle - angle;
    angle += K_Filt[0] * y_Filt;
    bias += K_Filt[1] * y_Filt;

    P_Filt[0][0] -= K_Filt[0] * P_Filt[0][0];
    P_Filt[0][1] -= K_Filt[0] * P_Filt[0][1];
    P_Filt[1][0] -= K_Filt[1] * P_Filt[0][0];
    P_Filt[1][1] -= K_Filt[1] * P_Filt[0][1];
}

