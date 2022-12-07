/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-20
 ************************************************************/
#include "missile_dyn.h"

float a11, a12, a13, a14, a15, a16;
float a21, a22, a23, a24, a25, a26;
float a31, a32, a33, a34, a35, a36;

float b11, b12, b13, b14, b15, b16, b17, b18;
float b21, b22, b23, b24, b25, b26, b27, b28;
float b31, b32, b33, b34, b35, b36, b37, b38;

float K_M, T_M, epsilon_M, T_1;

void missile_dyn_update()
{
    a22 = m_zb_w * characteristic_length * dyn_pressure * characteristic_area * characteristic_length / I_z / velocity;
    if (pos_x > 8000)
        a22 = -1.2;
    a24 = m_zb_a / alpha * dyn_pressure * characteristic_area * characteristic_length / I_z;  //姿态好用（正确的）
    a25 = m_z_delta_z * dyn_pressure * characteristic_area * characteristic_length / I_z;
    a34 = (thrust + 0.4 * 180 / PI * dyn_pressure * characteristic_area) / mass / velocity;
    a35 = 0;

    printf("a22 = %f\t\ta24 = %f\t\ta25 = %f\t\ta34 = %f\n", a22, a24, a25, a34);

    b11 = m_xb_wx * dyn_pressure * characteristic_area * net_wingspan * net_wingspan / velocity / I_x;
    b17 = m_x_delta_x * dyn_pressure * characteristic_area * net_wingspan / I_x;

    //printf("b11 = %f\t\tb17 = %f\n", b11, b17);

    K_M = -(a25*a34+a35*a24) / (a22*a34+a24);
    T_M = 1/ sqrt(-a22*a34-a24);
    epsilon_M = (-a22+a34) / sqrt(-a22*a34-a24);
    T_1 = a25/(a25*a34-a35*a24);
    //printf("K_M = %f\t\tT_M = %f\t\tepslion_M = %f\t\tT_1 = %f\n", K_M, T_M, epsilon_M, T_1);
}
