function Blst_Main
global Init Aero_angles;
global State Record Failed incre;

Failed = 0;
Blst_Data();    %调用Blst_Data取得初值
incre = 0.01;   %步长
fuse = 80 / incre;  %仿真时间
State = Init;    %运动参数初始化
max_i = 0;
i = 1;

for i = 1: fuse
    Record(1:13, i) = State;   %将i-1时刻参数存储在Record的第i列 
    
    Aero_angles(2, i) = asin( cos(State(4)) * (cos(State(13)) * sin(State(12) - State(9)) +...
            sin(State(3)) * sin(State(13)) * cos(State(12)-State(9))) - ...
            sin(State(4)) * cos(State(3)) * sin(State(13)) );
    Aero_angles(1, i) = asin( (cos(State(4)) * (sin(State(3)) * cos(State(13)) * ...
           cos(State(12)-State(9)) - sin(State(13)) * ...
           sin(State(12)-State(9))) - sin(State(4)) * cos(State(3)) * ...
           cos(State(13))) / cos(Aero_angles(2, i)) );
       
    State = Blst_RK4(incre*i, State, incre);    %调用RK以解算i时刻参数
    if i > 1 && Record(2, i) > Record(2, i - 1)
    	max_i = i;
    end     %到达最高处的时刻max_i
    if State(2) < 0
        disp("****TOUCHDOWN****");
        Failed = 1;
        break       %触地
    end
    
    if abs(State(3) - State(4)) > (10*pi/180)|| ismissing(State(3) - State(4))
        disp("****State value exceeded****")
        Failed = 1;
        break       %超出插值范围
    end
end

Record(3,:) = Record(3,:) * 180 / pi;
Record(4,:) = Record(4,:) * 180 / pi;
Record(6,:) = Record(6,:) * 180 / pi;
Record(9,:) = Record(9,:) * 180 / pi;
Record(10,:) = Record(10,:) * 180 / pi;
Record(12,:) = Record(12,:) * 180 / pi;
Blst_Disp( Record, incre, i, max_i, Aero_angles * 180 / pi)  %调用Blst_Disp以输出结果