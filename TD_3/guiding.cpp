/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-23
 ************************************************************/
#include "guiding.h"

float N = 4; //Proportional Guidance Number
float D = 60 * PI/180;
float k = 0.40;
float m = 0.38;
float time_design = 40.2;
float time_left;
float a_required[3];
float state_missile_prev[3];
float q_y, q_y_prev;
float q_z, q_z_prev;
float d_q_y, d_q_z;
float R_missille_to_target;

//中途启动，不考虑初始步
void guiding(float time_current)
{
    float incre = time_INCRE_0;

    float alpha_constrain;
    float theta_V_target;
    float sgn_q_y_dot;

    float R_relative_proj, R_relative_proj_prev;

    R_missille_to_target = sqrt((state_missile[0] - target_pos[0])
                                * (state_missile[0] - target_pos[0])
                                + (state_missile[2] - target_pos[2])
                                * (state_missile[2] - target_pos[2])
                                + (state_missile[1] - target_pos[1])
                                * (state_missile[1] - target_pos[1]));

    R_relative_proj = sqrt((state_missile[0] - target_pos[0])
                           *(state_missile[0] - target_pos[0])
                           + (state_missile[2] - target_pos[2])
                             * (state_missile[2] - target_pos[2]));
    q_y = atan2(target_pos[1] - state_missile[1], R_relative_proj);
    q_z = atan2(target_pos[2] - state_missile[2], target_pos[0] - state_missile[0]);

    R_relative_proj_prev = sqrt((state_missile_prev[0] - target_pos_prev[0])
                                *(state_missile_prev[0] - target_pos_prev[0])
                                + (state_missile_prev[2] - target_pos_prev[2])
                                  * (state_missile_prev[2] - target_pos_prev[2]));
    q_y_prev = atan2(target_pos_prev[1] - state_missile_prev[1], R_relative_proj_prev);
    q_z_prev = atan2(target_pos_prev[2] - state_missile_prev[2], target_pos_prev[0] - state_missile_prev[0]);

    d_q_y = (q_y - q_y_prev) / incre;
    d_q_z = (q_z - q_z_prev) / incre;

    time_left = R_missille_to_target / velocity * (1 + theta_V*theta_V/(4*N-2));

    printf("time_left = %f\n", time_left);

    //时间约束
//    if(d_q_y <= 0)
//        sgn_q_y_dot = -1;
//    else if(d_q_y > 0)
//        sgn_q_y_dot = 1;
//
//    a_required[0] = 0;
//    if(time_design - time_current - time_left > 0)
//    {
//        a_required[1] = N * velocity * d_q_y * cos(q_z - state_missile[8]);
//        a_required[2] = N * velocity * (d_q_y * sin(state_missile[7]) * sin(q_z - state_missile[8]) - d_q_z * cos(state_missile[7])) + m * velocity * sgn_q_y_dot * (time_design - time_current - time_left);
//    }
//    else
//    {
//        a_required[1] = N * velocity * d_q_y * cos(q_z - state_missile[8]);
//        a_required[2] = N * velocity * (d_q_y * sin(state_missile[7]) * sin(q_z - state_missile[8]) - d_q_z * cos(state_missile[7]));
//    }

//    a_required[0] = 0;
//    a_required[1] = N * velocity * d_q_y * cos(q_z - state_missile[8]);
//    a_required[2] = N * velocity * (d_q_y * sin(state_missile[7]) * sin(q_z - state_missile[8]) - d_q_z * cos(state_missile[7])) + m * velocity * sgn_q_y_dot * (time_design - time_current - time_left);


//    //普通
//    a_required[0] = 0;
//    a_required[1] = N * velocity * d_q_y * cos(q_z - state_missile[8]);
//    a_required[2] = N * velocity * (d_q_y * sin(state_missile[7]) * sin(q_z - state_missile[8]) - d_q_z * cos(state_missile[7]));


    //增广比例导引
    a_required[0] = 0;
    a_required[1] = N * velocity * d_q_y * cos(q_z - state_missile[8]) + 0.5 * N * target_acc[1];
    a_required[2] = N * velocity * (d_q_y * sin(state_missile[7]) * sin(q_z - state_missile[8]) - d_q_z * cos(state_missile[7])) - 0.5 * N * target_acc[2];

    //落角约束
//    theta_V_target = atan2(target_vol[1], sqrt(target_vol[0]*target_vol[0]+target_vol[2]*target_vol[2]));
//    alpha_constrain = (3/2*N-1)*theta_V_target + theta_V - 0.5*N*D - N*q_y - 0.5*theta_V_target;   //tf和t没分清楚

//    theta_V_target = atan2(target_vol[1], sqrt(target_vol[0]*target_vol[0]+target_vol[2]*target_vol[2]));
//    alpha_constrain = theta_V - N*D - N*q_y;   //tf和t没分清楚
//
//    if(R_missille_to_target < 20)
//    {
//        a_required[0] = 0;
//        a_required[1] = velocity * (-k*velocity/R_missille_to_target*alpha_constrain);
//        a_required[2] = N * velocity * (d_q_y * sin(state_missile[7]) * sin(q_z - state_missile[8]) - d_q_z * cos(state_missile[7])) - 0.5 * N * target_acc[2];
//    }
//    else
//    {
//        a_required[0] = 0;
//        a_required[1] = N * velocity * d_q_y * cos(q_z - state_missile[8]) + 0.5 * N * target_acc[1] + velocity * (-k*velocity/R_missille_to_target*alpha_constrain);
//        a_required[2] = N * velocity * (d_q_y * sin(state_missile[7]) * sin(q_z - state_missile[8]) - d_q_z * cos(state_missile[7])) + 0.5 * N * target_acc[2];
//    }
}


