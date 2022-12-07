%%%%%%本部分利用原始数据列出微分方程%%%%%%
function Dyna_State = Blst_Dyna(t, State)
global AoA Mach;
global c_x c_y c_z P dm Jz XG m_z0a_a m_y0beta_beta m_zwz m_ywy;
global S L Sos Ad g;

Blst_Data();    %调用Blst_Data以取得原始数据
%%Ad = 1.225 * exp(-1 * State(2) / 10700);    %大气密度
Ad = 1.225;

%几何关系方程
Dyna_beta = asin( cos(State(4)) * (cos(State(13)) * sin(State(12) - State(9)) +...
            sin(State(3)) * sin(State(13)) * cos(State(12)-State(9))) - ...
            sin(State(4)) * cos(State(3)) * sin(State(13)) );
Dyna_AoA = asin( (cos(State(4)) * (sin(State(3)) * cos(State(13)) * ...
           cos(State(12)-State(9)) - sin(State(13)) * ...
           sin(State(12)-State(9))) - sin(State(4)) * cos(State(3)) * ...
           cos(State(13))) / cos(Dyna_beta) );
Dyna_gamma_V = asin( (cos(Dyna_AoA) * sin(Dyna_beta) * sin(State(3)) - ...
               sin(Dyna_AoA) * sin(Dyna_beta) * cos(State(13)) * cos(State(3)) + ...
               cos(Dyna_beta) * sin(State(13)) * cos(State(3))) / cos(State(4)));

           
           
Dyna_Mach = State(5) / Sos;   %此刻马赫数
if Dyna_Mach < 0.1
    Dyna_Mach = 0.1;
end

Abs_AoA = abs(180 * Dyna_AoA / pi); %此刻攻角绝对值[角度]
Abs_beta = abs(180 * Dyna_beta / pi); %此刻攻角绝对值[角度]

if Dyna_AoA < 0
    c_y = -c_y;
    m_z0a_a = -m_z0a_a;
end

if Dyna_beta < 0
    c_z = - c_z;
    m_y0beta_beta = -m_y0beta_beta;
end


%%插值%%
Interp_P = interp1(P(1, :), P(2, :), t, 'linear');  %估算此刻推力，千克力
Interp_dm = interp1(dm(1, :), dm(2, :), t, 'linear');   %估算此刻质量流量
Interp_Jz = interp1(Jz(1, :), Jz(2, :), t, 'linear');   %估算此刻转动惯量
Interp_XG = interp1(XG(1, :), XG(2, :), t, 'linear');   %估算此刻重心位置
Interp_c_x = interp2(AoA, Mach, c_x, Abs_AoA, Dyna_Mach, 'linear');    %估算此刻阻力系数
Interp_c_y = interp2(AoA, Mach, c_y, Abs_AoA, Dyna_Mach, 'linear');    %估算此刻升力系数
Interp_c_z = interp2(AoA, Mach, c_z, Abs_beta, Dyna_Mach, 'linear');    %估算此刻侧向力系数
Interp_m_z0a_a = interp2(AoA, Mach, m_z0a_a, Abs_AoA, Dyna_Mach, 'linear');    %估算此刻俯仰静稳定力矩系数
Interp_m_y0beta_beta = interp2(AoA, Mach, m_y0beta_beta, Abs_beta, Dyna_Mach, 'linear');    %估算此刻偏航静稳定力矩系数
Interp_m_zwz = interp3(AoA, Mach, [XG(2), XG(end)], m_zwz, Abs_AoA, Dyna_Mach, Interp_XG, 'linear');  %估算此刻z阻尼力矩导数
Interp_m_ywy = interp3(AoA, Mach, [XG(2), XG(end)], m_ywy, Abs_beta, Dyna_Mach, Interp_XG, 'linear');  %估算此刻y阻尼力矩导数


Dyna_P = Interp_P * g;  %此刻推力
Jx_2 = 1;           %%%%%%%%%无数据%%%%%%%%%
Jy_2 = Interp_Jz;
Jz_2 = Interp_Jz; %此刻转动惯量

qS = .5 * Ad * State(5) ^ 2 * S;    %动压·面积
X = Interp_c_x * qS; %阻力
Y = Interp_c_y * qS; %升力
Z = Interp_c_z * qS; %侧向力
Interp_m_z0a_a = Interp_m_z0a_a + Interp_c_y * (Interp_XG - 0.9381) / L;    %修正此刻静稳定力矩
Interp_m_y0beta_beta = Interp_m_y0beta_beta - Interp_c_z * (Interp_XG - 0.9381) / L;    %修正此刻静稳定力矩

Mz = (Interp_m_z0a_a + Interp_m_zwz * State(6) * L  / State(5) )* qS * L;    %z轴外力力矩
Mx = 0;%%%%%%无滚转力矩导数数据%%%%%%%%%
My = (Interp_m_y0beta_beta + Interp_m_ywy * State(10) * L  / State(5) )* qS * L;    %z轴外力力矩;


Dyna_State = [
    State(5) * cos(State(4)) * cos(State(9));   %1 dx/dt
    State(5) * sin(State(4));   %2 dy/dt
    State(10) * sin(State(13)) + State(6) * cos(State(13));   %3 d theta /dt
    (Dyna_P * (sin(Dyna_AoA) * cos(Dyna_gamma_V) + cos(Dyna_AoA) * sin(Dyna_beta) * ...
    sin(Dyna_gamma_V)) + Y * cos(Dyna_gamma_V) - Z * sin(Dyna_gamma_V) - ...
    State(7) * g * cos(State(4))) / (State(7) * State(5));  %4 dθ/dt
    (Dyna_P * cos(Dyna_AoA) * cos(Dyna_beta) - X - State(7) * g * sin(State(4))) / State(7);   %5 dV/dt
    (Mz - (Jy_2 - Jx_2) * State(10) * State(11)) / Jz_2;    %6 dω_z/dt
    -Interp_dm    %7 dm/dt
    -State(5) * cos(State(4)) * sin(State(9));      %8 dz/dt
    (Dyna_P * (sin(Dyna_AoA) * sin(Dyna_gamma_V) - cos(Dyna_AoA) * ...
    sin(Dyna_beta) * cos(Dyna_gamma_V)) + Y * sin(Dyna_gamma_V) + Z * ...
    cos(Dyna_gamma_V)) / ( - State(7) * State(5) * cos(State(4)));      %9 dpsi_V/dt
    (My - (Jx_2 - Jz_2) * State(11) * State(6)) / Jy_2;     %10 dω_y/dt
    (Mx - (Jz_2 - Jy_2) * State(10) * State(6)) / Jx_2;     %11 dω_x/dt
    (State(10) * cos(State(13)) - State(6) * sin(State(13))) / cos(State(3));   %12 dpsi/dt
    State(11) - tan(State(3)) * (State(10) * cos(State(13)) - State(6) * sin(State(13)));   %13 dgamma/dt
    ];    