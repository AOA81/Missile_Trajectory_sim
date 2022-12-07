/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#ifndef MISSILE_TRAJECTORY_DATA_H
#define MISSILE_TRAJECTORY_DATA_H
#include <math.h>

#define PI acos(-1)

extern float P[2][11];
extern float dm[2][6];
extern float Jy[2][14];
extern float Xg[2][10];
extern float Cx[6][9];
extern float Cz[6][9];
extern float mzaf[6][9];
extern float mzwz_9381[6][9];
extern float mzwz_8896[6][9];

extern float state_0[13];

extern float x_0, y_0, z_0;
extern float theta_0, phi_0, psi_0;
extern float velocity_0;
extern float theta_dot_0, phi_dot_0, psi_dot_0;
extern float p_0, q_0, r_0;

extern float mass_0, characteristic_area, characteristic_length, net_wingspan;
extern float velocity_of_sound, atmospheric_density, gravity;

extern float time_MAX_0;
extern float time_INCRE_0;

void Init_state();
#endif //MISSILE_TRAJECTORY_DATA_H
