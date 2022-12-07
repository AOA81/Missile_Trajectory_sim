function FigurePlot(endi,T,x,y,z,v,alpha_b,theta,psi_v,gamma_v,delta_z,delta_y,distance,R_t)

T_o=zeros(1,endi);
x_o=zeros(1,endi);
y_o=zeros(1,endi);
z_o=zeros(1,endi);
v_o=zeros(1,endi);
alpha_b_o=zeros(1,endi);
theta_o=zeros(1,endi);
psi_v_o=zeros(1,endi);
gamma_v_o=zeros(1,endi);
delta_z_o=zeros(1,endi);
delta_y_o=zeros(1,endi);
distance_o=zeros(1,endi);

for i=1:endi
    
    T_o(i)=T(i);
    x_o(i)=x(i);
    y_o(i)=y(i);
    z_o(i)=z(i);
    v_o(i)=v(i);
    alpha_b_o(i)=alpha_b(i);
    theta_o(i)=theta(i);
    psi_v_o(i)=psi_v(i);
    gamma_v_o(i)=gamma_v(i);
    delta_z_o(i)=delta_z(i);
    delta_y_o(i)=delta_y(i);
    distance_o(i)=distance(i);
    
end
    
figure(1)
plot(x_o,y_o,'-')
hold on
plot(R_t(1),R_t(2),'o')
%legend('H_0=250m','H_0=200','H_0=150')
%legend('θ_0=14°','θ_0=18°','θ_0=22°')
legend('导弹','目标');
xlabel('水平位置(m)')
ylabel('高度(m)')
title('弹道曲线')

figure(2)
plot(T_o,v_o)
ylabel('v')
xlabel('时间(s)')
ylabel('速度(m/s)')
title('速度')

figure(3)
plot(T_o,alpha_b_o)
xlabel('时间(s)')
ylabel('攻角(°)')
title('攻角')

figure(4)
plot(T_o,theta_o,'-.')
xlabel('时间(s)')
ylabel('弹道倾角(°)')
title('弹道倾角')
hold on
%legend('θ_0=14°','θ_0=18°','θ_0=22°')

figure(5)
plot(T_o,psi_v_o)
xlabel('时间(s)')
ylabel('弹道偏角(°)')
title('弹道偏角')

figure(6)
plot(T_o,gamma_v_o)
xlabel('时间(s)')
ylabel('滚转角(°)')
title('滚转角')

figure(7)
plot(T_o,delta_z_o)
xlabel('时间(s)')
ylabel('俯仰舵偏角(°)')
title('俯仰舵偏角')

figure(8)
plot(T_o,delta_y_o)
xlabel('时间(s)')
ylabel('偏航舵偏角(°)')
title('偏航舵偏角')


figure(9)
plot(T_o,distance_o)
xlabel('时间(s)')
ylabel('R')
title('弹目距离')



