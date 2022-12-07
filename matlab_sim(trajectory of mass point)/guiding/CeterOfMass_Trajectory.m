clear
clc
close all

h=0.001;    %计算步长
tmax=50;
t=0:h:tmax;    %计算时间

%% 各参数定义
N=length(t);    %总时长
v=zeros(1,N);   %速度
theta=zeros(1,N);   %俯仰角
psi_v=zeros(1,N);
gamma_v=zeros(1,N);
x=zeros(1,N);   %水平位移
y=zeros(1,N);
z=zeros(1,N);  


alpha_b=zeros(1,N);   %攻角
beta_b=zeros(1,N);
m=zeros(1,N);   %导弹质量
T=zeros(1,N);   %计时 

delta_z=zeros(1,N);
delta_y=zeros(1,N);

theta_target=zeros(1,N);
e_theta=zeros(1,N);

d_theta_target=zeros(1,N);
e_d_theta=zeros(1,N);
d_theta=zeros(1,N);
d_psi_v=zeros(1,N);

distance=zeros(1,N);


%% 参数初值
v(1)=20;
theta(1)=22;
psi_v(1)=0;
gamma_v(1)=0;
x(1)=0;
y(1)=18;
z(1)=0;
theta(1)=18;
alpha_b(1)=0;
beta_b(1)=0;

m(1)=52.38;
T(1)=0;


L=1.8;  %特征长度
s=0.0227;   %特征面积
air_density=1.225;  %大气密度


for i=2:N
    %% 循环初值
    
    v_n=v(i-1);
    theta_n=theta(i-1);
    psi_v_n=psi_v(i-1);
    gamma_v_n=gamma_v(i-1);
    x_n=x(i-1);
    y_n=y(i-1);
    z_n=z(i-1);
    alpha_b_n=alpha_b(i-1);
    beta_b_n=beta_b(i-1);
    
    m_n=m(i-1);
    T_n=T(i-1);
    
    state_last=[v_n,theta_n,psi_v_n,x_n,y_n,z_n,m_n,T_n];
    
    
    %% 系数
    data=paramater(T_n,v_n,alpha_b_n,beta_b_n);
    P=data(1);
    Cl=data(2);
    Cd=data(3);
    Cl_z=data(4);
    d_m=data(5);
    
    q=0.5*air_density*v_n^2;  %动压
    X=Cd*q*s; %阻力
    Y=Cl*q*s;
    Z=Cl_z*q*s;
    
    coefficient=[P,X,Y,Z,alpha_b_n,beta_b_n,gamma_v_n,d_m];
    
    %% 运动微分方程组
    
    state=dynamic(h,state_last,coefficient);
   
    v(i)=state(1);
    theta(i)=state(2);
    psi_v(i)=state(3);
    x(i)=state(4);
    y(i)=state(5);
    z(i)=state(6);
    m(i)=state(7);
    T(i)=state(8);


    %% 控制

    R_m=[x(i),y(i),z(i)];
    R_m_last=[x(i-1),y(i-1),z(i-1)];
    [R_t,~] = target_motion(i);
    distance(i) = sqrt( (R_t(1)-R_m(1))^2 + (R_t(2) - R_m(2))^2 );
    d_theta(i)=(theta(i)-theta(i-1))/h;
    d_psi_v(i)=(psi_v(i)-psi_v(i-1))/h;
    
    
    [delta_z(i),delta_y(i)]=control(state(1),i,h,R_m,R_m_last,theta(i),psi_v(i),d_theta(i),d_psi_v(i),R_t);
    alpha_b(i)=-delta_z(i);
    beta_b(i)=-delta_y(i);
  
    fprintf('i=%d\nx=%f\ty=%f\tz=%f\t\nalpha=%f\ttheta=%f\n\n',i,x(i),y(i),z(i),alpha_b(i),theta(i));
    
    endi=tmax/h;
    if distance(i)<10
        endi=i;
        break;
    end
%     if state(4)>1600
%         endi=i;
%         break;
%     end

end

FigurePlot(endi,T,x,y,z,v,alpha_b,theta,psi_v,gamma_v,delta_z,delta_y,distance,R_t)
