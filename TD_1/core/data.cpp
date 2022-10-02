/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include "data.h"
#include <math.h>

//推力（kg*f）
float P[2][11] = {
        {.0, .15, .49, 2.11, 2.27, 3.53, 8.78, 25.45, 42.80, 43.68, 44.08},
        {331.2, 614.3, 505.4, 607.8, 48.65, 43.97, 42.01, 41.00, 40.80, 40.79, 2.22}
};

//发动机质量秒流量（kg/s）
float dm[2][6] = {
        {0, 2.1, 2.105, 44.1, 44.105, 100},
        {2.362, 2.362, 0.21059, 0.21059, 0, 0}
};

//转动惯量（kg*m^2）
float Jy[2][14] = {
        {0, 2.0, 2.4, 6.4, 10.4, 14.4, 18.4, 22.4, 26.4, 30.4, 34.0, 38.4, 42.4, 44.0},
        {8.35, 7.88, 7.86, 7.81, 7.78, 7.75, 7.73, 7.71, 7.70, 7.70, 7.69, 7.69, 7.69, 7.69}
};

//重心位置（m）
float Xg[2][10] = {
        {.0, 2.0, 2.4, 10.0, 18.0, 26.0, 32.0, 38.0, 42.0, 44.0},
        {.9381, .9095, .9091, .9026, .8969, .8928, .8907, .8896, .8895, .8896}
};

//阻力系数
float Cx[6][9] = {
        {0.4177, 0.3858, 0.3779, 0.3785, 0.3787, 0.3829, 0.3855, 0.4082, 0.4947},
        {0.4404, 0.4086, 0.4007, 0.4015, 0.4018, 0.4062, 0.4091, 0.4321, 0.5192},
        {0.5219, 0.4903, 0.4827, 0.4838, 0.4846, 0.4897, 0.4934, 0.5175, 0.6073},
        {0.6603, 0.6290, 0.6218, 0.6234, 0.6249, 0.6310, 0.6363, 0.6621, 0.7571},
        {0.8534, 0.8226, 0.8160, 0.8184, 0.8209, 0.8284, 0.8358, 0.8641, 0.9672},
        {1.1023, 1.0723, 1.0666, 1.0700, 1.0738, 1.0835, 1.0938, 1.1254, 1.2392}
};

//升力系数
float Cz[6][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0.6430, 0.6454, 0.6480, 0.6512, 0.6554, 0.6617, 0.6698, 0.6792, 0.6933},
        {1.4758, 1.4807, 1.4858, 1.4923, 1.5007, 1.5134, 1.5304, 1.5501, 1.5935},
        {2.2870, 2.2942, 2.3014, 2.3107, 2.3227, 2.3409, 2.3661, 2.3950, 2.4706},
        {3.0713, 3.0814, 3.0915, 3.1039, 3.1197, 3.1436, 3.1775, 3.2162, 3.3273},
        {3.8463, 3.8598, 3.8731, 3.8891, 3.9092, 3.9401, 3.9835, 4.0323, 4.1790}
};

//静稳定力矩系数
float mzaf[6][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {-0.0104, -0.0104, -0.0104, -0.0105, -0.0104, -0.0093, -0.0080, -0.0065, -0.0053},
        {-0.0341, -0.0341, -0.0341, -0.0342, -0.0339, -0.0314, -0.0286, -0.0252, -0.0299},
        {-0.0564, -0.0564, -0.0564, -0.0564, -0.0560, -0.0521, -0.0477, -0.0425, -0.0391},
        {-0.0771, -0.0770, -0.0769, -0.0768, -0.0761, -0.0708, -0.0650, -0.0578, -0.0538},
        {-0.0985, -0.0983, -0.0982, -0.0979, -0.0969, -0.0903, -0.0829, -0.0739, -0.0693}
};

//阻尼力矩导数.9381
float mzwz_9381[6][9] = {
        {-0.4686, -0.4707, -0.4744, -0.4797, -0.4882, -0.5089, -0.5366, -0.5738, -0.6272},
        {-0.4829, -0.4850, -0.4886, -0.4939, -0.5022, -0.5227, -0.5502, -0.5871, -0.6407},
        {-0.4982, -0.5003, -0.5039, -0.5090, -0.5173, -0.5376, -0.5649, -0.6014, -0.6553},
        {-0.5130, -0.5150, -0.5186, -0.5237, -0.5318, -0.5520, -0.5790, -0.6153, -0.6694},
        {-0.5272, -0.5292, -0.5327, -0.5378, -0.5458, -0.5658, -0.5927, -0.6287, -0.6830},
        {-0.5409, -0.5429, -0.5464, -0.5514, -0.5593, -0.5791, -0.6058, -0.6415, -0.6960}
};

//阻尼力矩系数.8896
float mzwz_8896[6][9] = {
        {-0.6179, -0.6207, -0.6253, -0.6319, -0.6424, -0.6669, -0.6667, -0.7435, -0.8069},
        {-0.6384, -0.6410, -0.6455, -0.6521, -0.6624, -0.6866, -0.7190, -0.7624, -0.8266},
        {-0.6600, -0.6626, -0.6670, -0.6734, -0.6835, -0.7074, -0.7395, -0.7824, -0.8474},
        {-0.6805, -0.6830, -0.6974, -0.6937, -0.7036, -0.7272, -0.7589, -0.8014, -0.8672},
        {-0.6999, -0.7024, -0.7067, -0.7129, -0.7226, -0.7459, -0.7774, -0.8194, -0.8859},
        {-0.7182, -0.7207, -0.7249, -0.7310, -0.7406, -0.7636, -0.7948, -0.8365, -0.9035}
};

//初值
float x_0 = 0;      //初始x坐标（大地坐标系）（m）
float y_0 = 0;      //初始y坐标（大地坐标系）（m）
float z_0 = -20;    //初始z坐标（大地坐标系）（m）

float theta_0 = 18 * PI / 180;      //初始俯仰角（弧度）
float phi_0 = 0;                    //初始滚转角
float psi_0 = 0;                    //初始偏航角

float velocity_0 = 20;      //初始速度（v/s）

float theta_dot_0 = 0;      //初始俯仰角速度（rad/s）
float phi_dot_0 = 0;        //初始滚转角速度
float psi_dot_0 = 0;        //初始偏航角速度

float p_0 = 0;
float q_0 = 0;
float r_0 = 0*PI/180;

//float theta_V_0 = 18 * PI / 180;    //初始弹道倾角（弧度）
//float psi_V_0 = 0;                  //初始弹道偏角
//float gamma_V_0 = 0;                //初始速度倾斜角

float mass_0 = 52.38;       //初始质量（kg）

//其他常量
float characteristic_area = 0.0227;     //特征面积（m^2）
float characteristic_length = 1.8;      //特征长度（m）
float net_wingspan = 0.5;               //毛翼展（m）
float velocity_of_sound = 343.13;       //音速（m/s）
float atmospheric_density = 1.225;      //大气密度（kg/m^3）
float gravity = 9.81;                   //重力加速度

float time_MAX_0 = 12;
float time_INCRE_0 = 0.01;

float state_0[13];

void Init_state()
{
    state_0[0] = x_0;
    state_0[1] = y_0;
    state_0[2] = z_0;

    state_0[3] = velocity_0 * cos(0) * cos(0);  //数值正确，逻辑错误的代码,uvw
    state_0[4] = velocity_0 * sin(0);
    state_0[5] = velocity_0 * sin(0) * cos(0);

    state_0[6] = p_0;
    state_0[7] = q_0;
    state_0[8] = r_0;

    state_0[9] = theta_0;
    state_0[10] = phi_0;
    state_0[11] = psi_0;

    state_0[12] = mass_0;
}

