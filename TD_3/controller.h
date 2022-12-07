/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-21
 ************************************************************/
#ifndef PROJECT_3_CONTROLLER_H
#define PROJECT_3_CONTROLLER_H
#include "dynamic.h"
#include <stdio.h>
#include "missile_dyn.h"

extern float ail_deflection;
extern float rud_deflection;
extern float ele_deflection;

void controller_init();

void roll_controller(float gamma,float gamma_c,float gamma_dot);
float height_controller(float H,float H_c);
float overload_controller(float a_yc, float a_y, float theta_dot_controller);
float overload_controller_PID1(float a_c, float a, float _);
float overload_controller_PID2(float a_c, float a, float _);
float attitute_controller(float theta_c);
void servo_limit();
#endif //PROJECT_3_CONTROLLER_H
