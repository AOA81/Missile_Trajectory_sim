/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#ifndef MISSILE_TRAJECTORY_LINEARINTERP_H
#define MISSILE_TRAJECTORY_LINEARINTERP_H

#include <cmath>
#include <stdint.h>
#include "string.h"
#include <iostream>
#include "data.h"

struct LinearInterp
{
    // 初始化曲线
    void (*Init)(struct LinearInterp *self,
                 float *arr_x, float *arr_y,
                 uint32_t size);
    // 调用计算
    float (*Cal)(struct LinearInterp *self, float val);

    float out;

    struct
    {
        float *arr_x;
        float *arr_y;
        int32_t size;
    }pvt;
};

void LinearInterp_Create(struct LinearInterp *self);

float linearInterp_two_dim(int row, int col, float * pr, float input);

float linearInterp_three_dim(int row, int col, float * pr, float Ma, float alpha);

#endif //MISSILE_TRAJECTORY_LINEARINTERP_H
