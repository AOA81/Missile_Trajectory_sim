function [d_theta, d_psi_V] = guiding(R_m, R_m_last, t, h, theta, psi_V)
%输入参数  %1导弹坐标 2上一时刻导弹坐标 3时间 4步长 5导弹弹道倾角 6 导弹弹道偏角
N = 3;      %比例导引比例
[R_t, V_t] = target_motion(t);  
[R_t_last, V_t_last] = target_motion(t-h);

% R_t=[2000,0,0];
% R_t_last=[2000,0,0];

% R_relative = R_t - R_m;
% R_relative_last = R_t_last - R_m_last;
% q_z = theta + atan(R_relative(2)- R_m(2) / (R_relative(1) - R_m(1)));
% q_z_last = theta_last + atan(R_relative_last(2)- R_m_last(2) / (R_relative_last(1) - R_m_last(1)));
% d_q_z = (q_z - q_z_last)./h;

R_relative_proj = sqrt( (R_t(1)-R_m(1))^2 + (R_t(3) - R_m(3))^2 );
q_y = atand( (R_t(2) - R_m(2)) / R_relative_proj);
q_z = -atand( (R_t(3) - R_m(3)) / (R_t(1) - R_m(1)) );
R_relative_proj_last = sqrt( (R_t_last(1)-R_m_last(1))^2 + (R_t_last(3) - R_m_last(3))^2 );
q_y_last = atand( (R_t_last(2) - R_m_last(2)) / R_relative_proj_last);
q_z_last = -atand( (R_t_last(3) - R_m_last(3)) / (R_t_last(1) - R_m_last(1)) );
d_q_y = (q_y - q_y_last) / h;
d_q_z = (q_z - q_z_last) / h;

d_theta = N * d_q_y * cosd(q_z - psi_V);
d_psi_V = N * d_q_z - N * d_q_y * tand(theta) * sind(q_z - psi_V);