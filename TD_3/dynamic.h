/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#ifndef MISSILE_TRAJECTORY_DYNAMIC_H
#define MISSILE_TRAJECTORY_DYNAMIC_H
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "linearInterp.h"
#include "missile_dyn.h"

extern float state_missile[13];

//状态变量
extern float velocity_x_dot;       //加速度-x
extern float velocity_y_dot;       //加速度-y
extern float velocity_z_dot;       //加速度-z

extern float velocity;             //地速
extern float velocity_x;           //地速-x
extern float velocity_y;           //地速-y
extern float velocity_z;           //地速-z

extern float pos_x;                //位置-x
extern float pos_y;                //位置-y
extern float pos_z;                //位置-z

//弹体坐标系三轴速度
extern float u;
extern float v;
extern float w;

extern float u_wind;
extern float v_wind;
extern float w_wind;

extern float thrust_misalignment_d;
extern float thrust_misalignment_theta;

extern float mass_deflection;
extern float velocity_0_deflection;
extern float theta_0_deflection;
extern float psi_0_deflection;
extern float phi_0_deflection;

extern float W_x;                 //风速-x
extern float W_y;                 //风速-y
extern float W_z;                 //风速-z

extern float u_w;                 //空速-x
extern float v_w;                 //空速-y
extern float w_w;                 //空速-z

//弹体坐标系三轴加速度
extern float u_dot;
extern float v_dot;
extern float w_dot;

//地面坐标系-弹体坐标系
extern float theta;                //俯仰角（θ）
extern float phi;                  //滚转角（Φ）
extern float psi;                  //偏航角（ψ）

//风轴坐标系-弹体坐标系
extern float alpha;                //攻角（α）
extern float beta;                 //侧滑角（β）

extern float theta_dot;            //俯仰角速度
extern float phi_dot;              //滚转角速度
extern float psi_dot;              //偏航角速度

extern float p,q,r;                //弹体坐标系下的角速度分量
extern float p_dot, q_dot, r_dot;

extern float mass;                 //质量
extern float thrust;               //推力
extern float dm_dyn;               //发动机秒流量
extern float Ma;                   //马赫数

extern float drag;                 //阻力
extern float lift;                 //升力
extern float lateral_force;        //侧向力

//三轴力矩
extern float M_xb;
extern float M_yb;
extern float M_zb;

//三轴转动惯量
extern float I_x;
extern float I_y;
extern float I_z;

//弹道坐标系-速度坐标系
extern float gamma_V;              //速度倾斜角（γv）

//地面坐标系-弹道坐标系
extern float theta_V;              //弹道倾角（θ）
extern float psi_V;                //弹道偏角（ψv）

extern float theta_V_dot;
extern float psi_V_dot;

extern float velocity_dot;

extern float w_x;
extern float w_y;
extern float w_z;

extern float w_x_dot;
extern float w_y_dot;
extern float w_z_dot;

extern float gamma1;
extern float gamma_dot;

extern float m_yb_w;
extern float m_zb_w;

extern float m_xb;
extern float m_yb;
extern float m_zb;

extern float dyn_pressure;

extern float C_z;
extern float C_x;
extern float m_yb_b;
extern float m_zb_a;
extern float m_yb_w_9381;
extern float m_yb_w_8896;
extern float m_zb_w_9381;
extern float m_zb_w_8896;
extern float C_y;

extern float m_x_delta_x;
extern float m_y_delta_y;
extern float m_z_delta_z;

extern float m_xb_wx;

extern float n_y2;
extern float n_z2;

float * dynamic(float state[13], float time);

#endif //MISSILE_TRAJECTORY_DYNAMIC_H


