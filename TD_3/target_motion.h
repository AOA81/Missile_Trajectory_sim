/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-23
 ************************************************************/

#ifndef PROJECT_3_TARGET_MOTION_H
#define PROJECT_3_TARGET_MOTION_H
#include <stdio.h>
#include <math.h>
extern float target_vol[3];
extern float target_pos[3];
extern float target_pos_prev[3];
extern float target_acc[3];

void target_init();
void target_motion(float time);
#endif //PROJECT_3_TARGET_MOTION_H
