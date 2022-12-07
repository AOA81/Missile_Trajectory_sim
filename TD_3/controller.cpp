/***************************************************************
 * @Project:        project_3
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-10-21
 ************************************************************/
#include "controller.h"

float ail_deflection;
float rud_deflection;
float ele_deflection;

void controller_init()
{
    ail_deflection = 0;
    rud_deflection = 0;
    ele_deflection = 0;
}

void roll_controller(float gamma,float gamma_c,float gamma_dot)
{
    float omega_c = 8;
    float epsilon_c = 0.707;

    float K_ACT = 1;
    float K_ac = 1;

    float K_A = omega_c*omega_c / (b17*K_ACT*K_ac);
    float K_g = (2*epsilon_c*omega_c+b11) / (b17*K_ACT);

    ail_deflection = K_ACT * (K_A*(gamma_c-K_ac*gamma) - gamma_dot*K_g);
}

float height_controller(float H,float H_c)
{
    float omega = 0.02;
    float epsilon = 0.707;
    float tau = 0.5;

    float K_DC = 1;

    float K_P = (2*epsilon/omega+tau) * T_1 * omega*omega;
    float K_I = T_1*omega*omega / (K_DC*velocity*tau);
    float K_D = ((1/(omega*omega)+2*epsilon*tau/omega) * T_1 * omega * omega / tau - 1) / K_DC / velocity;

    //printf("K_P = %f\t\tK_I = %f\t\tK_D = %f\n", K_P, K_I, K_D);

    float error = H_c - H;

    static float integral = 0;
    static float pre_error = 0;

    integral += error * time_INCRE_0;
    float d_error = (error - pre_error) / time_INCRE_0;

    pre_error = error;

    float theta_desire_H_controller = K_P * error + K_I * integral + K_D * d_error;

    return theta_desire_H_controller;
}

float overload_controller(float a_yc, float a_y, float theta_dot_controller)
{
    float K = 1; //闭环增益

    float omega_n = 25;
    float epsilon_n = 0.7;

    float K_s = K * omega_n * omega_n / (velocity * a25 * a34);
    float K_g = (2 * epsilon_n * omega_n - (a34 - a22)) / (a25 * K_s);
    float K_a = (((omega_n * omega_n + a22 * a34 + a24) / (K_s * a25 * a34)) - K_g) / velocity;
    printf("K_s = %f\t\tK_g = %f\t\tK_a = %f\n", K_s, K_g, K_a);

    float deflection = K_s * (a_yc - (K_g * theta_dot_controller + K_a * a_y));
    printf("deflection = %f\n", K_s * (a_yc - (K_g * theta_dot_controller + K_a * a_y)));

    return deflection;
}

float attitute_controller(float theta_c)
{
    float K_A;
    float K_theta = 1;
    float K_theta_dot;
    float K_ACT = 1;
    float n = 4;
    float epsilon = 0.707;
    float tau_1;
    float tau_2;

    float deflection;

    tau_1 = T_M/n;

    K_A=(2*epsilon_M*T_M-T_1+T_M*T_M*T_1/(tau_1*tau_1)-2*epsilon*T_M*T_M/tau_1)/(tau_1*tau_1*K_M-2*epsilon*tau_1*T_1*K_M+K_M*T_1*T_1);
    tau_2=T_M*T_M/tau_1/tau_1/K_M/K_A;
    K_theta_dot=(2*epsilon*tau_1*tau_2*K_A*K_M+tau_1*tau_1*K_A*K_M-2*epsilon_M*T_M)/K_A/K_M/T_1;

//    printf("K_A = %f\t\ttau_2 = %f\t\tK_theta_dot = %f\n", K_A, tau_2, K_theta_dot);

    deflection = K_A * K_ACT * (theta_c - (K_theta_dot * theta_dot + K_theta * theta));

//    printf("K_A = %f\t\tK_theta_dot = %f\t\tK_M = %f\n", K_A, K_theta_dot, K_M);
//    printf("theta_c = %f\t\ttheta = %f\t\ttheta_dot = %f\t\tdeflection = %f\n", theta_c, theta, theta_dot, deflection);

    return deflection;
}

float overload_controller_PID1(float a_c, float a, float _)
{
    float K_P = 0.03;
    float K_I = 0.0;
    float K_D = 0.002;

    float error = -a_c + a;

    static float integral = 0;
    static float pre_error = 0;

    integral += error * time_INCRE_0;
    float d_error = (error - pre_error) / time_INCRE_0;

    pre_error = error;

    float theta_desire_overload_controller = K_P * error + K_I * integral + K_D * d_error;

    return theta_desire_overload_controller;
}

float overload_controller_PID2(float a_c, float a, float _)
{
    float K_P = 0.002;
    float K_I = 0.00006;
    float K_D = 0.0002;

    float error = -a_c + a;

    static float integral = 0;
    static float pre_error = 0;

    integral += error * time_INCRE_0;
    float d_error = (error - pre_error) / time_INCRE_0;

    pre_error = error;

    float theta_desire_overload_controller = K_P * error + K_I * integral + K_D * d_error;

    return theta_desire_overload_controller;
}

void servo_limit()
{
    if(ele_deflection >= 10*PI/180)
        ele_deflection = 10*PI/180;
    else if (ele_deflection < -10*PI/180)
        ele_deflection = -10*PI/180;

    if(rud_deflection >= 10*PI/180)
        rud_deflection = 10*PI/180;
    else if (rud_deflection < -10*PI/180)
        rud_deflection = -10*PI/180;

    if(ail_deflection >= 10*PI/180)
        ail_deflection = 10*PI/180;
    else if (ail_deflection < -10*PI/180)
        ail_deflection = -10*PI/180;
}