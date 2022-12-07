/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include "dynamic.h"

float state_missile[13];

float velocity;             //合成速度
float velocity_x;           //空速-x
float velocity_y;           //空速-y
float velocity_z;           //空速-z

float pos_x;                //位置-x
float pos_y;                //位置-y
float pos_z;                //位置-z

//地面坐标系-弹体坐标系
float theta;                //俯仰角（θ）
float phi;                  //滚转角（Φ）
float psi;                  //偏航角（ψ）

//风轴坐标系-弹体坐标系
float alpha;                //攻角（α）
float beta;                 //侧滑角（β）

float theta_dot;            //俯仰角速度
float phi_dot;              //滚转角速度
float psi_dot;              //偏航角速度

float mass;                 //质量
float thrust;               //推力
float dm_dyn;               //发动机秒流量
float Ma;                   //马赫数

float drag;                 //阻力
float lift;                 //升力
float lateral_force;        //侧向力

//三轴力矩
float M_xb;
float M_yb;
float M_zb;

//三轴转动惯量
float I_x;
float I_y;
float I_z;

//弹道坐标系-速度坐标系
float gamma_V;              //速度倾斜角（γv）

//地面坐标系-弹道坐标系
float theta_V;              //弹道倾角（θ）
float psi_V;                //弹道偏角（ψv）

float velocity_dot;

float w_x;
float w_y;
float w_z;

float w_x_dot;
float w_y_dot;
float w_z_dot;

float gamma1;
float gamma_dot;

float theta_V_dot;
float psi_V_dot;

float m_yb_w;
float m_zb_w;

float m_xb;
float m_yb;
float m_zb;

float dyn_pressure;

float C_z;
float C_x;
float m_yb_b;
float m_zb_a;
float m_yb_w_9381;
float m_yb_w_8896;
float m_zb_w_9381;
float m_zb_w_8896;
float C_y;

float m_x_delta_x;
float m_y_delta_y;
float m_z_delta_z;

float m_xb_wx;

float n_y2;
float n_z2;

float * dynamic(float state[13], float time)
{
    pos_x = state[0];
    pos_y = state[1];
    pos_z = state[2];

    w_x = state[3];
    w_y = state[4];
    w_z = state[5];

    velocity = state[6];

    theta_V = state[7];
    psi_V = state[8];

    theta = state[9];
    gamma1 = state[10];
    psi = state[11];

    mass = state[12];

    Ma = velocity / velocity_of_sound;

    beta = asin(cos(theta_V)*(cos(gamma1)*sin(psi-psi_V) + sin(theta)*sin(gamma1)*cos(psi-psi_V)) - sin(theta_V)*cos(theta)*sin(gamma1));
    alpha = asin((cos(theta_V)*(sin(theta)*cos(gamma1)*cos(psi-psi_V) - sin(gamma1)*sin(psi-psi_V))-sin(theta_V)*cos(theta)*cos(gamma1)) / cos(beta));
    gamma_V = asin((cos(alpha)*sin(beta)*sin(theta)-sin(alpha)*sin(beta)*cos(gamma1)*cos(theta)+cos(beta)*sin(gamma1)*cos(theta))/cos(theta_V));

    float Ma_interp;
    if(Ma < 0.1)
        Ma_interp = 0.1;
    else
        Ma_interp = Ma;

    float Xg_current = linearInterp_two_dim(2, 10, Xg[0], time);
    thrust = linearInterp_two_dim(2, 11, P[0], time) * 10;
    dm_dyn = linearInterp_two_dim(2, 6, dm[0], time);
    m_x_delta_x = linearInterp_two_dim(2, 8, mx_detx[0], Ma_interp);
    m_z_delta_z = linearInterp_two_dim(2, 5, mz_detz[0], Ma_interp);
    m_y_delta_y = m_z_delta_z;
    m_xb_wx = linearInterp_two_dim(2, 5, mxwx[0], Ma_interp);
    I_z = linearInterp_two_dim(2, 14, Jy[0], time);
    I_y = I_z;
    I_x = 0.84;

    if(alpha < 0)
    {
        C_y = -linearInterp_three_dim(6, 9, Cz[0], Ma_interp, -alpha*180/PI);
        C_x = linearInterp_three_dim(6, 9, Cx[0], Ma_interp, -alpha*180/PI);
        m_zb_a = -linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, -alpha*180/PI);
        m_zb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, -alpha*180/PI);
        m_zb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, -alpha*180/PI);
    }
    else
    {
        C_y = linearInterp_three_dim(6, 9, Cz[0], Ma_interp, alpha*180/PI);
        C_x = linearInterp_three_dim(6, 9, Cx[0], Ma_interp, alpha*180/PI);
        m_zb_a = linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, alpha*180/PI);
        m_zb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, alpha*180/PI);
        m_zb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, alpha*180/PI);
    }

    if(beta < 0)
    {
        C_z = -linearInterp_three_dim(6, 9, Cz[0], Ma_interp, -beta*180/PI);
        m_yb_b = -linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, -beta*180/PI);
        m_yb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, -beta*180/PI);
        m_yb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, -beta*180/PI);
    }
    else
    {
        C_z = linearInterp_three_dim(6, 9, Cz[0], Ma_interp, beta*180/PI);
        m_yb_b = linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, beta*180/PI);
        m_yb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, beta*180/PI);
        m_yb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, beta*180/PI);
    }

    lift = C_y * 0.5 * atmospheric_density * characteristic_area * velocity * velocity;
    lateral_force = C_z * 0.5 * atmospheric_density * characteristic_area * velocity * velocity;
    drag = C_x * 0.5 * atmospheric_density * characteristic_area * velocity * velocity;
    //阻力系数代的角度是多少

    velocity_x = velocity * cos(theta_V) * cos(psi_V);
    velocity_y = velocity * sin(theta_V);
    velocity_z = -1 * velocity * cos(theta_V) * sin(psi_V);

    velocity_dot = (thrust * cos(alpha) * cos(beta) - drag - mass * gravity * sin(theta_V)) / mass;

    theta_V_dot = (thrust*(sin(alpha)*cos(gamma_V) + cos(alpha)*sin(beta)*sin(gamma_V)) + lift*cos(gamma_V) - lateral_force*sin(gamma_V) - mass*gravity*cos(theta_V)) / mass / velocity;
    psi_V_dot = (thrust*(sin(alpha)*sin(gamma_V) - cos(alpha)*sin(beta)*cos(gamma_V)) + lift*sin(gamma_V) + lateral_force*cos(gamma_V)) / (-1) / mass / velocity;

    theta_dot = w_y*sin(gamma1) + w_z*cos(gamma1);
    psi_dot = (w_y*cos(gamma1)-w_z*sin(gamma1)) / cos(theta);
    gamma_dot = w_x - tan(theta)*(w_y*cos(gamma1) - w_z*sin(gamma1));

    m_yb_w = (m_yb_w_9381-m_yb_w_8896)/(0.9381-0.8896)*(Xg_current-0.8896) + m_yb_w_8896;// debug
    m_zb_w = (m_zb_w_9381-m_zb_w_8896)/(0.9381-0.8896)*(Xg_current-0.8896) + m_zb_w_8896;// debug

    dyn_pressure = 0.5 * atmospheric_density * velocity * velocity;  //动压

    //修正静稳定力矩系数
    m_zb_a += C_z * (Xg_current - 0.9381) / characteristic_length;

    m_xb = m_x_delta_x * ail_deflection + m_xb_wx * w_x * net_wingspan / velocity;
    m_yb = m_y_delta_y * rud_deflection + m_yb_b + m_yb_w*w_y*characteristic_length/velocity;
    m_zb = m_z_delta_z * ele_deflection + m_zb_a + m_zb_w*w_z*characteristic_length/velocity;

    M_xb = m_xb * dyn_pressure * characteristic_area * net_wingspan;//debug
    M_yb = m_yb * dyn_pressure * characteristic_area * characteristic_length;
    M_zb = m_zb * dyn_pressure * characteristic_area * characteristic_length;

    w_x_dot = (M_xb - (I_z - I_y) * w_z * w_y) / I_x;
    w_y_dot = (M_yb - (I_x - I_z) * w_x * w_z) / I_y;
    w_z_dot = (M_zb - (I_y - I_x) * w_y * w_x) / I_z;

    //第一定义
    n_y2 = velocity / gravity * theta_V_dot + cos(theta);
    n_z2 = - velocity / gravity * cos(theta) * psi_V_dot;

    //第二定义
    //n_y2 = velocity / gravity * theta_V_dot;
    //n_z2 = - velocity / gravity * cos(theta) * psi_V_dot;

    static float state_dot[13];

    state_dot[0] = velocity_x;
    state_dot[1] = velocity_y;
    state_dot[2] = velocity_z;

    state_dot[3] = w_x_dot;
    state_dot[4] = w_y_dot;
    state_dot[5] = w_z_dot;

    state_dot[6] = velocity_dot;

    state_dot[7] = theta_V_dot;
    state_dot[8] = psi_V_dot;

    state_dot[9] = theta_dot;
    state_dot[10] = gamma_dot;
    state_dot[11] = psi_dot;

    state_dot[12] = -dm_dyn;

    return state_dot;
}
