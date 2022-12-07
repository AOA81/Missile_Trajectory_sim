/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include "RK4.h"

float * RK4(float t, float state[13], float incre)
{
//    float K1[13], K2[13], K3[13], K4[13], RK4[13];
    float * K1 = dynamic(state, t);   //debug

    float K2_tmp[13];
    for(int i = 0; i < 13; i++)
        K2_tmp[i] = state[i] + incre / 2 * K1[i];
    float * K2 = dynamic(K2_tmp, t + incre / 2);

    float K3_tmp[13];
    for(int j = 0; j < 13; j++)
        K3_tmp[j] = state[j] + incre / 2 * K2[j];
    float * K3 = dynamic(K3_tmp, t + incre / 2);

    float K4_tmp[13];
    for(int k = 0; k < 13; k++)
        K4_tmp[k] = state[k] + incre * K3[k];
    float * K4 = dynamic(K4_tmp, t + incre);

    static float RK4[13];
    for(int m = 0; m < 13; m++)
        RK4[m] = state[m] + incre / 6 * (K1[m] + 2*K2[m] + 2*K3[m] + K4[m]);

    return RK4;
}
