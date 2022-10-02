/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include <math.h>
#include <stdio.h>
#include "data.h"
#include "RK4.h"
#include "linearInterp.h"

int main(int argc, char** argv) {
    int time_MAX = time_MAX_0;
    float time_INCRE = time_INCRE_0;
    int step = time_MAX / time_INCRE;

    Init_state();

    if(argc >= 2) {
        float angle_input = atof(argv[1]);
        state_0[9] = angle_input*PI/180;
    }

    float state_pr_tmp[13];
    float * state_pr = state_pr_tmp;

    for(int i = 0; i < 13; i++){
        state_missile[i] = state_0[i];
        state_pr[i] = state_0[i];
    }

    for(int j = 0; j < step; j++)
    {
        for(int k = 0; k < 13; k++)
            state_missile[k] = state_pr[k];

        state_pr = RK4(j*time_INCRE, state_missile, time_INCRE);

        printf("velicity = %f\n",velocity);
        printf("u = %f\t\tv = %f\t\tw = %f\n",u, v, w);
        printf("x = %f\t\ty = %f\t\tz = %f\n",pos_x, pos_y, pos_z);
        printf("x_dot = %f\t\ty_dot = %f\t\tz_dot = %f\n", velocity_x, velocity_y, velocity_z);
        printf("theta = %f\t\tphi = %f\t\tpsi = %f\n",theta *180/PI, phi*180/PI, psi*180/PI);
        printf("alpha = %f\t\tbeta = %f\t\tmass = %f\n", alpha * 180/PI, beta*180/PI, mass);
        printf("drag = %f\t\tlift = %f\t\tlateral_force = %f\n", drag, lift, lateral_force);
        printf("u_dot = %f\t\tv_dot = %f\t\tw_dot = %f\n", u_dot, v_dot, w_dot);
        printf("p = %f\t\tq = %f\t\tr = %f\n", p* 180/PI, q* 180/PI, r* 180/PI);
        printf("p_dot = %f\t\tq_dot = %f\t\tr_dot = %f\n", p_dot, q_dot, r_dot);
        printf("t = %f\n",j*time_INCRE);
    }

    return 0;
}
