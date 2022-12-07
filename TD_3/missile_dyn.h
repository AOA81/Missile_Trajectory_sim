/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-20
 ************************************************************/

#ifndef PROJECT_3_MISSILE_DYN_H
#define PROJECT_3_MISSILE_DYN_H
#include "dynamic.h"
#include "math.h"
#include "controller.h"

extern float a11, a12, a13, a14, a15, a16;
extern float a21, a22, a23, a24, a25, a26;
extern float a31, a32, a33, a34, a35, a36;

extern float b11, b12, b13, b14, b15, b16, b17, b18;
extern float b21, b22, b23, b24, b25, b26, b27, b28;
extern float b31, b32, b33, b34, b35, b36, b37, b38;

extern float K_M, T_M, epsilon_M, T_1;

void missile_dyn_update();

#endif //PROJECT_3_MISSILE_DYN_H
