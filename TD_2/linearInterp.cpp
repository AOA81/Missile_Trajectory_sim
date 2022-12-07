/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include "linearInterp.h"

static void _Init(struct LinearInterp *self,
                  float *arr_x, float *arr_y,
                  uint32_t size)
{
    self->pvt.arr_x = arr_x;
    self->pvt.arr_y = arr_y;
    self->pvt.size = size;
}

static float _Cal(struct LinearInterp *self, float val)
{
    int32_t left = 0, mid = 0;
    int32_t right = self->pvt.size - 1;

    float x0,y0,x1,y1;

    // 二分法
    while (left <= right)
    {
        mid = (left + right) / 2;

        if (val<self->pvt.arr_x[mid])
            right = mid - 1;
        else if (self->pvt.arr_x[mid] < val)
            left = mid + 1;
        else
            break;
    }

    // 头尾检测
    if (mid == (self->pvt.size - 1))
        mid = mid-1;
    else if (mid == 0)
        mid = 0;
    else
        mid = (self->pvt.arr_x[mid] <= val) ? mid : mid-1; // 中间二分查找出现的情况

    // 3.Linear interpolation
    x0 = self->pvt.arr_x[mid];
    y0 = self->pvt.arr_y[mid];
    x1 = self->pvt.arr_x[mid + 1];
    y1 = self->pvt.arr_y[mid + 1];

    self->out = y0 + (((y1 - y0) * (val - x0)) / (x1 - x0));

    return self->out;
}

void LinearInterp_Create(struct LinearInterp *self)
{
    memset(self , 0 , sizeof(struct LinearInterp));

    self->Init = _Init;
    self->Cal = _Cal;
}

float linearInterp_two_dim(int row, int col, float * pr, float input)
{
    if(input>44)
        input = 44;

    float res;
    LinearInterp line_interp;
    LinearInterp_Create(&line_interp);
    float arr_x[col];
    float arr_y[col];

    for (int i = 0; i < col; i++)
        arr_x[i] = pr[0*col + i];

    for (int j = 0; j < col; j++)
        arr_y[j] = pr[1*col + j];

    line_interp.Init(&line_interp, arr_x, arr_y, sizeof(arr_x) / sizeof(float));
    res = line_interp.Cal(&line_interp, input);
    return res;
}

float linearInterp_three_dim(int row, int col, float * pr, float Ma, float alpha)
{

    if(Ma < 0.1)
    {
        int index_alpha = (int)alpha / 2;
        int index_Ma = (int)(Ma * 10) - 1;


        float data_top_right = pr[index_alpha*col + index_Ma + 1];
        float data_top_right2 = pr[index_alpha*col + index_Ma + 2];
        float data_but_right = pr[(index_alpha+1)*col + index_Ma + 1];
        float data_but_right2 = pr[(index_alpha+1)*col + index_Ma + 2];

        float data_top_left = data_top_right - (data_top_right2 - data_top_right);
        float data_but_left = data_but_right2 - (data_but_right2 - data_but_right);

        float left_tmp = (data_but_left - data_top_left) * (alpha - ((float)index_alpha * 2)) / 2 + data_top_left;
        float right_tmp = (data_but_right - data_top_right) * (alpha - ((float)index_alpha * 2)) / 2 + data_top_right;

        float res = (right_tmp - left_tmp) * (Ma - ((float)index_Ma + 1) / 10) / 0.1 + left_tmp;

        return res;
    }
    else
    {
        int index_alpha = (int)alpha / 2;
        int index_Ma = (int)(Ma * 10) - 1;

        float data_top_left = pr[index_alpha*col + index_Ma];
        float data_top_right = pr[index_alpha*col + index_Ma + 1];
        float data_but_left = pr[(index_alpha+1)*col + index_Ma];
        float data_but_right = pr[(index_alpha+1)*col + index_Ma + 1];

        float left_tmp = (data_but_left - data_top_left) * (alpha - ((float)index_alpha * 2)) / 2 + data_top_left;
        float right_tmp = (data_but_right - data_top_right) * (alpha - ((float)index_alpha * 2)) / 2 + data_top_right;

        float res = (right_tmp - left_tmp) * (Ma - ((float)index_Ma + 1) / 10) / 0.1 + left_tmp;

        return res;
    }
}
