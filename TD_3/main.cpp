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
#include "controller.h"
#include "missile_dyn.h"
#include "linearInterp.h"
#include "guiding.h"
#include "target_motion.h"
#include "programmed_trajectory.h"

int main(int argc, char** argv) {
    int time_MAX = time_MAX_0;
    float time_INCRE = time_INCRE_0;
    int step = time_MAX / time_INCRE;

    Init_state();
    controller_init();
    target_init();

    float state_pr_tmp[13];
    float * state_pr = state_pr_tmp;

    for(int i = 0; i < 13; i++){
        state_missile[i] = state_0[i];
        state_pr[i] = state_0[i];
    }

    float height_max = 0;
    float missile_range = 0;

    FILE *f = fopen("data.txt", "w");

    float R_last_record = 100000;

    for(int j = 0; j < step; j++)
    {
        for(int k = 0; k < 13; k++){
            state_missile_prev[k] = state_missile[k];
            state_missile[k] = state_pr[k];
        }

        for(int ii = 0; ii < 3; ii++)
            target_pos_prev[ii] = target_pos[ii];       //保存前步参数

        target_motion(time_INCRE);                  //目标运动（直接累加）

        state_pr = RK4(j*time_INCRE, state_missile, time_INCRE);

        missile_dyn_update();

        float theta_V_desire;
        float theta_desire;

        guiding(j * time_INCRE);

        if(j < time_climb_to_height / time_INCRE)
        {
            theta_V_desire = climb_programmed(j*time_INCRE);
            theta_desire = alpha + theta_V_desire;
            ele_deflection = attitute_controller(theta_desire);

            //height_controller(pos_y, 300);
        }
        //else if(j < time_height_to_guiding / time_INCRE)
        else if(R_missille_to_target > 3000)
        {
            theta_desire = height_controller(pos_y, cruise_height);
            ele_deflection = attitute_controller(theta_desire);
            rud_deflection = overload_controller(-a_required[2], n_z2*gravity, psi_dot);
        }
        else
        {
//            ele_deflection = overload_controller(a_required[1]+gravity, n_y2*gravity, theta_dot);
//            rud_deflection = overload_controller(-a_required[2], n_z2*gravity, psi_dot);
            ele_deflection = overload_controller_PID1(a_required[1]+gravity, n_y2*gravity, theta_dot);
            rud_deflection = overload_controller_PID2(-a_required[2], n_z2*gravity, psi_dot);
            printf("guiding\n");
        }

        roll_controller(gamma1, 0*PI/180, gamma_dot);

        if(j > 30 / time_INCRE)
        {
            target_acc[0] = 3+0.7*(j*time_INCRE-30);
            target_acc[1] = 4-0.5*(j*time_INCRE-30);
            target_acc[2] = 2+j*time_INCRE-30;
        }

        servo_limit();

        printf("velocity = %f\n",velocity);
        printf("velocity_x = %f\t\tvelocity_y = %f\t\tvelocity_z = %f\n", velocity_x, velocity_y, velocity_z);
        printf("w_x = %f\t\tw_y = %f\t\tw_z = %f\n",w_x*180/PI, w_y*180/PI, w_z*180/PI);
        printf("x = %f\t\ty = %f\t\tz = %f\n",pos_x, pos_y, pos_z);
        printf("theta = %f\t\tpsi = %f\t\tgamma = %f\n",theta *180/PI, psi*180/PI, gamma1*180/PI);
        printf("theta_dot = %f\t\tpsi_dot = %f\t\tgamma_dot = %f\n", theta_dot, psi_dot, gamma_dot);
        printf("alpha = %f\t\tbeta = %f\t\tmass = %f\n", alpha * 180/PI, beta*180/PI, mass);
        printf("drag = %f\t\tlift = %f\t\tlateral_force = %f\n", drag, lift, lateral_force);
        printf("theta_V = %f\t\tgamma_V = %f\n", theta_V*180/PI, gamma_V*180/PI);
        printf("M_xb = %f\t\tM_yb = %f\t\tM_zb = %f\n", M_xb, M_yb, M_zb);
        printf("ail = %f\t\tele = %f\t\trud = %f\n", ail_deflection*180/PI, ele_deflection*180/PI, rud_deflection*180/PI);
        printf("n_y = %f\t\tn_z = %f\n", n_y2, n_z2);
        printf("a_req_y = %f\t\ta_req_z = %f\n", a_required[1], a_required[2]);
        printf("R_m2t = %f\n", R_missille_to_target);
        printf("t = %f\n",j*time_INCRE);
        printf("time_total_est = %f\n", j*time_INCRE+time_left);
        printf("\n");

        fprintf(f, "%d\t", j);
        for(int i = 0; i < 13; i++)
        {
            fprintf(f, "%f\t", state_missile[i]);
        }
        fprintf(f, "%f\t%f\t", n_y2, n_z2);
        fprintf(f, "%f\t%f\t%f\t", target_pos[0], target_pos[1], target_pos[2]);
        fprintf(f, "%f\t", alpha);
        fprintf(f, "%f\t%f\t%f\t", ele_deflection, rud_deflection, ail_deflection);
        fprintf(f, "%f\t", R_missille_to_target);
        fprintf(f, "\n");

        if(pos_y > height_max)
            height_max = pos_y;


        if(R_missille_to_target > R_last_record)
            break;

        R_last_record = R_missille_to_target;



        missile_range = sqrt(pos_x*pos_x + pos_z*pos_z);
    }

    printf("Max Height of the Missile = %f\n", height_max);
    printf("Range of the Missile = %f\n", missile_range);

    fclose(f);

    return 0;
}
