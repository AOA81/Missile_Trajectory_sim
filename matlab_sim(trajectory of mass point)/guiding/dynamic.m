function state=dynamic(h,state_last,coefficient)

g=9.8;

v_n=state_last(1);
theta_n=state_last(2);
psi_v_n=state_last(3);
x_n=state_last(4);
y_n=state_last(5);
z_n=state_last(6);
m_n=state_last(7);
T_n=state_last(8);


P=coefficient(1);
X=coefficient(2);
Y=coefficient(3);
Z=coefficient(4);
alpha_b_n=coefficient(5);
beta_b_n=coefficient(6);
gamma_v_n=coefficient(7);
d_m=coefficient(8);



dv1=1/m_n*(P*cosd(alpha_b_n)*cosd(beta_b_n)-X-m_n*g*sind(theta_n));
dtheta1=1/m_n*(P*( sind(alpha_b_n)*cosd(psi_v_n)+cosd(alpha_b_n)*sind(beta_b_n)*sind(gamma_v_n) )+Y*cosd(gamma_v_n)-Z*sind(gamma_v_n)-m_n*g*cosd(theta_n) );
dpsi_v1=(-1/(m_n*v_n))*(P*(sind(alpha_b_n)*sind(gamma_v_n)-cosd(alpha_b_n)*sind(beta_b_n)*cosd(gamma_v_n))+Y*sind(gamma_v_n)+Z*cosd(gamma_v_n));
dx1=v_n*cosd(theta_n)*cosd(psi_v_n);
dy1=v_n*sind(theta_n);
dz1=-v_n*cosd(theta_n)*sind(psi_v_n);
dm1=-d_m;
dT1=1;

dv2=1/(m_n+dm1*h/2)*(P*cosd(alpha_b_n)*cosd(beta_b_n)-X-(m_n+dm1*h/2)*g*sind(theta_n+dtheta1*h/2));
dtheta2=1/(m_n+dm1*h/2)*(P*( sind(alpha_b_n)*cosd(psi_v_n+dpsi_v1*h/2)+cosd(alpha_b_n)*sind(beta_b_n)*sind(gamma_v_n) )+Y*cosd(gamma_v_n)-Z*sind(gamma_v_n)-m_n*g*cosd(theta_n+dtheta1*h/2) );
dpsi_v2=(-1/((m_n+dm1*h/2)*v_n))*(P*(sind(alpha_b_n)*sind(gamma_v_n)-cosd(alpha_b_n)*sind(beta_b_n)*cosd(gamma_v_n))+Y*sind(gamma_v_n)+Z*cosd(gamma_v_n));
dx2=v_n*cosd(theta_n+dtheta1*h/2)*cosd(psi_v_n+dpsi_v1*h/2);
dy2=v_n*sind(theta_n+dtheta1*h/2);
dz2=-v_n*cosd(theta_n+dtheta1*h/2)*sind(psi_v_n+dpsi_v1*h/2);
dm2=-d_m;
dT2=1;

dv3=1/(m_n+dm2*h/2)*(P*cosd(alpha_b_n)*cosd(beta_b_n)-X-(m_n+dm2*h/2)*g*sind(theta_n+dtheta2*h/2));
dtheta3=1/(m_n+dm2*h/2)*(P*( sind(alpha_b_n)*cosd(psi_v_n+dpsi_v2*h/2)+cosd(alpha_b_n)*sind(beta_b_n)*sind(gamma_v_n) )+Y*cosd(gamma_v_n)-Z*sind(gamma_v_n)-m_n*g*cosd(theta_n+dtheta2*h/2) );
dpsi_v3=(-1/((m_n+dm2*h/2)*v_n))*(P*(sind(alpha_b_n)*sind(gamma_v_n)-cosd(alpha_b_n)*sind(beta_b_n)*cosd(gamma_v_n))+Y*sind(gamma_v_n)+Z*cosd(gamma_v_n));
dx3=v_n*cosd(theta_n+dtheta2*h/2)*cosd(psi_v_n+dpsi_v2*h/2);
dy3=v_n*sind(theta_n+dtheta2*h/2);
dz3=-v_n*cosd(theta_n+dtheta2*h/2)*sind(psi_v_n+dpsi_v2*h/2);
dm3=-d_m;
dT3=1;

dv4=1/(m_n+dm3*h)*(P*cosd(alpha_b_n)*cosd(beta_b_n)-X-(m_n+dm3*h)*g*sind(theta_n+dtheta3*h));
dtheta4=1/(m_n+dm3*h)*(P*( sind(alpha_b_n)*cosd(psi_v_n+dpsi_v3*h)+cosd(alpha_b_n)*sind(beta_b_n)*sind(gamma_v_n) )+Y*cosd(gamma_v_n)-Z*sind(gamma_v_n)-m_n*g*cosd(theta_n+dtheta3*h) );
dpsi_v4=(-1/((m_n+dm3*h)*v_n))*(P*(sind(alpha_b_n)*sind(gamma_v_n)-cosd(alpha_b_n)*sind(beta_b_n)*cosd(gamma_v_n))+Y*sind(gamma_v_n)+Z*cosd(gamma_v_n));
dx4=v_n*cosd(theta_n+dtheta3*h)*cosd(psi_v_n+dpsi_v3*h);
dy4=v_n*sind(theta_n+dtheta3*h);
dz4=-v_n*cosd(theta_n+dtheta3*h)*sind(psi_v_n+dpsi_v3*h);
dm4=-d_m;
dT4=1;

v=v_n+h/6*(dv1+2*dv2+2*dv3+dv4);
theta=theta_n+h/6*(dtheta1+2*dtheta2+2*dtheta3+dtheta4);
psi_v=psi_v_n+h/6*(dpsi_v1+2*dpsi_v2+2*dpsi_v3+dpsi_v4);
x=x_n+h/6*(dx1+2*dx2+2*dx3+dx4);
y=y_n+h/6*(dy1+2*dy2+2*dy3+dy4);
z=z_n+h/6*(dz1+2*dz2+2*dz3+dz4);
m=m_n+h/6*(dm1+2*dm2+2*dm3+dm4);
T=T_n+h/6*(dT1+2*dT2+2*dT3+dT4);

state=[v,theta,psi_v,x,y,z,m,T];