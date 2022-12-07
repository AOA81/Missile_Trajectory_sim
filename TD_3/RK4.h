/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#ifndef MISSILE_TRAJECTORY_RK4_H
#define MISSILE_TRAJECTORY_RK4_H
#include <stdio.h>
#include <math.h>
#include "dynamic.h"

float * RK4(float t, float state[13], float incre);

#endif //MISSILE_TRAJECTORY_RK4_H
