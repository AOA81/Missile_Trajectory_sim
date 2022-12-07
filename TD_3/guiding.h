/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-23
 ************************************************************/
#ifndef PROJECT_3_GUIDING_H
#define PROJECT_3_GUIDING_H
#include <stdio.h>
#include <math.h>
#include "target_motion.h"
#include "dynamic.h"
#include "data.h"
extern float state_missile_prev[3];
extern float a_required[3];
extern float q_y, q_y_prev;
extern float q_z, q_z_prev;
extern float d_q_y, d_q_z;
extern float R_missille_to_target;
extern float time_left;

void guiding(float time_current);


#endif //PROJECT_3_GUIDING_H
