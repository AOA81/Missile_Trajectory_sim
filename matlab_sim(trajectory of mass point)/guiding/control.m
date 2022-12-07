function[delta_z,delta_y]=control(V,i,h,R_m,R_m_last,theta,psi_v,d_theta,d_psi_v,R_t)


theta0=18;
theta_target(1)=theta0;
h1=200;

distance = sqrt( (R_t(1)-R_m(1))^2 + (R_t(2) - R_m(2))^2 );

y=R_m(2);

if distance > 1000
    
    kp1=100;
    ki1=5;
    kd1=2;
    
    if y<h1
        theta_target(i)=theta0;
    elseif y<300
        r=(h1-300)/(cosd(theta0)-1);
        yy=r-300+y;
        xx=-realsqrt(r^2-yy^2);
        theta_target(i)=atand(-xx/realsqrt(r^2-xx^2));
    else
        theta_target(i)=0;
    end
    
    e_theta(i)=theta-theta_target(i);
    delta_z=kp1*e_theta(i)+ki1*sum(e_theta)+kd1*(e_theta(i)-e_theta(i-1));
    delta_y=0;
    
    
    
else
    
    kp2=0.05;
    ki2=0.1;
    kd2=10;
    
    kp3=0.05;
    ki3=0.1;
    kd3=10;
    
    [d_theta_target(i), d_psi_v_target(i)] = guiding(R_m, R_m_last, i, h, theta, psi_v);
    %d_theta_target(i) = d_theta_target(i) - 9.8/V;
    e_d_theta(i)=d_theta-d_theta_target(i);
    e_d_psi_v(i)=d_psi_v-d_psi_v_target(i);
    delta_z=kp2*e_d_theta(i);
%     +ki2*sum(e_d_theta)+kd2*(e_d_theta(i)-e_d_theta(i));
    delta_y=kp3*e_d_psi_v(i)+ki3*sum(e_d_psi_v)+kd3*(e_d_psi_v(i)-e_d_psi_v(i));
    
end

if delta_z>10
    delta_z=9.9;
elseif delta_z<-10
    delta_z=-9.9;
end






