/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-23
 ************************************************************/
#include "target_motion.h"
float target_vol[3];
float target_pos[3];
float target_pos_prev[3];
float target_acc[3];

void target_init()
{
    target_pos[0] = 10000;
    target_pos[1] = 0;
    target_pos[2] = 0;

    target_vol[0] = 10;
    target_vol[1] = 0;
    target_vol[2] = 5;

    target_acc[0] = 0;
    target_acc[1] = 0;
    target_acc[2] = 0;
}

void target_motion(float time_incre)
{
    target_vol[0] += time_incre * target_acc[0];
    target_vol[1] += time_incre * target_acc[1];
    target_vol[2] += time_incre * target_acc[2];

    target_pos[0] += time_incre * target_vol[0];
    target_pos[1] += time_incre * target_vol[1];
    target_pos[2] += time_incre * target_vol[2];
}
