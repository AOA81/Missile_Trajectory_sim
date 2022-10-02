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

//状态变量
float velocity_x_dot;       //加速度-x
float velocity_y_dot;       //加速度-y
float velocity_z_dot;       //加速度-z

float velocity;             //合成速度
float velocity_x;           //空速-x
float velocity_y;           //空速-y
float velocity_z;           //空速-z

float pos_x;                //位置-x
float pos_y;                //位置-y
float pos_z;                //位置-z

//弹体坐标系三轴速度
float u;
float v;
float w;

//弹体坐标系三轴加速度
float u_dot;
float v_dot;
float w_dot;

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

float p,q,r;                //弹体坐标系下的角速度分量
float p_dot, q_dot, r_dot;

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


float * dynamic(float state[13], float time)
{
    pos_x = state[0];
    pos_y = state[1];
    pos_z = state[2];

    u = state[3];
    v = state[4];
    w = state[5];

    p = state[6];
    q = state[7];
    r = state[8];

    theta = state[9];
    phi = state[10];
    psi = state[11];

    mass = state[12];

    //velocity = sqrt(velocity_x * velocity_x + velocity_y * velocity_y + velocity_z * velocity_z);
    velocity = sqrt(u*u + v*v + w*w);

    Ma = velocity / velocity_of_sound;

    alpha = atan(w / u);
    beta = asin(v / sqrt(u*u + v*v + w*w));

    float Ma_interp;
    if(Ma < 0.1)
        Ma_interp = 0.1;
    else
        Ma_interp = Ma;

    float Xg_current = linearInterp_two_dim(2, 10, Xg[0], time);
    thrust = linearInterp_two_dim(2, 11, P[0], time) * 10;
    dm_dyn = linearInterp_two_dim(2, 6, dm[0], time);
    I_z = linearInterp_two_dim(2, 14, Jy[0], time);
    I_y = I_z;
    I_x = 5;

    float C_z;
    float C_x;
    float m_yb_a;
    float m_zb_b;
    float m_yb_w_9381;
    float m_yb_w_8896;
    float m_zb_w_9381;
    float m_zb_w_8896;
    float C_y;

    if(alpha < 0)
    {
        C_z = -linearInterp_three_dim(6, 9, Cz[0], Ma_interp, -alpha*180/PI);
        C_x = linearInterp_three_dim(6, 9, Cx[0], Ma_interp, -alpha*180/PI);
        m_yb_a = -linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, -alpha*180/PI);
        m_yb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, -alpha*180/PI);
        m_yb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, -alpha*180/PI);
    }
    else
    {
        C_z = linearInterp_three_dim(6, 9, Cz[0], Ma_interp, alpha*180/PI);
        C_x = linearInterp_three_dim(6, 9, Cx[0], Ma_interp, alpha*180/PI);
        m_yb_a = linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, alpha*180/PI);
        m_yb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, alpha*180/PI);
        m_yb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, alpha*180/PI);
    }

    if(beta < 0)
    {
        C_y = linearInterp_three_dim(6, 9, Cz[0], Ma_interp, -beta*180/PI);
        m_zb_b = linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, -beta*180/PI);
        m_zb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, -beta*180/PI);
        m_zb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, -beta*180/PI);
    }
    else
    {
        C_y = -linearInterp_three_dim(6, 9, Cz[0], Ma_interp, beta*180/PI);
        m_zb_b = -linearInterp_three_dim(6, 9, mzaf[0], Ma_interp, beta*180/PI);
        m_zb_w_9381 = linearInterp_three_dim(6, 9, mzwz_9381[0], Ma_interp, beta*180/PI);
        m_zb_w_8896 = linearInterp_three_dim(6, 9, mzwz_8896[0], Ma_interp, beta*180/PI);
    }

    lift = C_z * 0.5 * atmospheric_density * characteristic_area * velocity * velocity;
    lateral_force = C_y * 0.5 * atmospheric_density * characteristic_area * velocity * velocity;
    drag = C_x * 0.5 * atmospheric_density * characteristic_area * velocity * velocity;
    //阻力系数代的角度是多少

    u_dot = (thrust - drag*cos(alpha)*cos(beta) - lateral_force*cos(alpha)*sin(beta) + lift*sin(alpha)
             - mass*gravity*sin(theta) - mass*q*w + mass*r*v) / mass;
    v_dot = (drag*sin(beta) + lateral_force*cos(beta) + mass*gravity*sin(phi)*cos(theta) - mass*r*u + mass*p*w) / mass;
    w_dot = (-drag*sin(alpha)*cos(beta) - lateral_force*sin(alpha)*sin(beta) - lift*cos(alpha) +
             mass*gravity*cos(phi)*cos(theta) - mass*p*v + mass*q*u) / mass;

    velocity_x = u*cos(psi)*cos(theta) + v*(sin(phi)*sin(theta)*cos(psi)-cos(phi)*sin(psi)) +
                 w*(cos(phi)*sin(theta)*cos(psi)+sin(phi)*sin(psi));
    velocity_y = u*cos(theta)*sin(psi) + v*(sin(phi)*sin(theta)*sin(psi)+cos(phi)*cos(psi)) +
                 w*(cos(phi)*sin(theta)*sin(psi)-sin(phi)*cos(psi));
    velocity_z = -u*sin(theta) + v*cos(theta)*sin(phi) + w*cos(theta)*cos(phi);

    phi_dot = p + tan(theta)*sin(phi)*q + cos(phi)*tan(theta)*r;
    theta_dot = cos(phi)*q - sin(phi)*r;
    psi_dot = sin(phi)*q/cos(theta) + cos(phi)*r/cos(theta);

    float m_yb_w = (m_yb_w_9381-m_yb_w_8896)/(0.9381-0.8896)*(Xg_current-0.8896) + m_yb_w_8896;// debug
    float m_zb_w = (m_zb_w_9381-m_zb_w_8896)/(0.9381-0.8896)*(Xg_current-0.8896) + m_zb_w_8896;// debug

    float dyn_pressure = 0.5 * atmospheric_density * velocity * velocity;  //动压

    m_yb_a += C_z * (Xg_current - 0.9381) / characteristic_length;
    m_zb_b += C_y * (Xg_current - 0.9381) / characteristic_length;

    float m_xb = 0;
    float m_yb = m_yb_a + m_yb_w*q*characteristic_length/velocity;
    float m_zb = m_zb_b + m_zb_w*r*characteristic_length/velocity;

    M_xb = 0;//debug
    M_yb = m_yb * dyn_pressure * characteristic_area * characteristic_length;
    M_zb = m_zb * dyn_pressure * characteristic_area * characteristic_length;

    p_dot = (M_xb - (I_z - I_y) * q * r) / I_x;
    q_dot = (M_yb - (I_x - I_z) * p * r) / I_y;
    r_dot = (M_zb - (I_y - I_x) * p * q) / I_z;

    theta_V = theta - alpha;
    psi_V = psi - beta;

    static float state_dot[13];

    state_dot[0] = velocity_x;
    state_dot[1] = velocity_y;
    state_dot[2] = velocity_z;

    state_dot[3] = u_dot;
    state_dot[4] = v_dot;
    state_dot[5] = w_dot;

    state_dot[6] = p_dot;
    state_dot[7] = q_dot;
    state_dot[8] = r_dot;

    state_dot[9] = theta_dot;
    state_dot[10] = phi_dot;
    state_dot[11] = psi_dot;

    state_dot[12] = -dm_dyn;

    return state_dot;
}


