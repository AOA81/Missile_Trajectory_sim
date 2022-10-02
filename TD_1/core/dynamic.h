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

extern float state_missile[13];

//状态变量
extern float velocity_x_dot;       //加速度-x
extern float velocity_y_dot;       //加速度-y
extern float velocity_z_dot;       //加速度-z

extern float velocity;             //合成速度
extern float velocity_x;           //空速-x
extern float velocity_y;           //空速-y
extern float velocity_z;           //空速-z

extern float pos_x;                //位置-x
extern float pos_y;                //位置-y
extern float pos_z;                //位置-z

//弹体坐标系三轴速度
extern float u;
extern float v;
extern float w;

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

float * dynamic(float state[13], float time);

#endif //MISSILE_TRAJECTORY_DYNAMIC_H
