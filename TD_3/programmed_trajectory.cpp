/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-24
 ************************************************************/
#include "programmed_trajectory.h"

float climb_programmed(float time)
{
    float h0;   //转平飞高度
    float theta0;   //爬升段弹道倾角
    float theta_V_target;

    float rr;
    float yy;
    float xx;

    h0 = 100;
    theta0 = 18 * PI / 180;

    if(pos_y < h0)
    {
        theta_V_target = theta0;
    }
    else if (time < 6.856)
    {
        rr = (h0 - cruise_height) / (cos(theta0) - 1);
        yy = rr - cruise_height + pos_y;
        xx = -sqrt(rr * rr - yy * yy);
        theta_V_target=atan(-xx / sqrt(rr * rr - xx * xx));
    }
    else
    {
        theta_V_target = 0;
    }

    return theta_V_target;
}
