function data=paramater(t,v,alpha,beta)

t1=[.000	.15	.49	2.11];
t2=[2.11 2.27	3.53	8.78	25.45	42.80	43.68	44.08];
thrust1=[331.2	614.3	505.4	607.8];
thrust2=[607.8 48.65	43.97	42.01	41.00	40.80	40.79	2.22];
if t<=2.11
    thrust=9.8*interp1(t1,thrust1,t);
elseif t<=44.08
    thrust=9.8*interp1(t2,thrust2,t);
else
    thrust=0;
end

ti=[0.	2.1	2.105	44.1	44.105	];
d_massi=[2.362	2.362	0.21059	0.21059	0.	];
if t<=44.105
    d_m=interp1(ti,d_massi,t);
else
    d_m=0;
end

ma_i=0.1 :0.1: 0.9;
alp_i=0:2:10;
lifti=[0	0	0	0	0	0	0	0	0
0.643	0.6454	0.648	0.6512	0.6554	0.6617	0.6698	0.6792	0.6933
1.4758	1.4807	1.4858	1.4923	1.5007	1.5134	1.5304	1.5501	1.5935
2.287	2.2942	2.3014	2.3107	2.3227	2.3409	2.3661	2.395	2.4706
3.0713	3.0814	3.0915	3.1039	3.1197	3.1436	3.1775	3.2162	3.3273
3.8463	3.8598	3.8731	3.8891	3.9092	3.9401	3.9835	4.0323	4.179
];
dragi=[0.4177	0.3858	0.3779	0.3785	0.3787	0.3829	0.3855	0.4082	0.4947
0.4404	0.4086	0.4007	0.4015	0.4018	0.4062	0.4091	0.4321	0.5192
0.5219	0.4903	0.4827	0.4838	0.4846	0.4897	0.4934	0.5175	0.6073
0.6603	0.629	0.6218	0.6234	0.6249	0.631	0.6363	0.6621	0.7571
0.8534	0.8226	0.816	0.8184	0.8209	0.8284	0.8358	0.8641	0.9672
1.1023	1.0723	1.0666	1.07	1.0738	1.0835	1.0938	1.1254	1.2392
];
[ma_i,alp_i]=meshgrid(ma_i,alp_i);                      
if v>343.13*0.9
    disp('Velocity is out of range!');
    cl=NaN;
    cd=NaN;
elseif alpha>10||alpha<-10
    disp('AOA is out of range!') 
    cl=NaN;
    cd=NaN;
elseif alpha>=0
    cl=interp2(ma_i,alp_i,lifti,v/343.13,alpha,'spline');
    cd=interp2(ma_i,alp_i,dragi,v/343.13,alpha,'spline');
elseif alpha<0
    cl=-interp2(ma_i,alp_i,lifti,v/343.13,-alpha,'spline');
    cd=interp2(ma_i,alp_i,dragi,v/343.13,-alpha,'spline');
end

if beta>10||beta<-10
    disp('beta is out of range!') 
    cl_z=NaN;
elseif beta>=0
    cl_z=interp2(ma_i,alp_i,lifti,v/343.13,beta,'spline');
elseif beta<0
    cl_z=-interp2(ma_i,alp_i,lifti,v/343.13,-beta,'spline');
end

data=[thrust,cl,cd,cl_z,d_m];