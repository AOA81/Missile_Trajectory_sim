function [R_t V_t] = target_motion(t)
x_t = 6000;
y_t = 0;
z_t = 0;
Vx_t = 100;
Vy_t = 0;
Vz_t = 0;

R_t = [x_t y_t z_t];
V_t = [Vx_t Vy_t Vz_t];


