%%%%%%本部分用于输出结果%%%%%%
function Blst_Disp(Record, incre, i, max_i, Aero_angles)

Time = num2str(i * incre);
% Time = i * incre;
disp(['Flight time is ', Time, 's']);   %输出飞行时长
Range = num2str(sqrt(Record(1, end)^2 + Record(8, end)^2));
% Range = sqrt(Record(1, end)^2 + Record(8, end)^2);
disp(['Flight range is ' Range, 'm']);  %输出射程
Max_Time = num2str(max_i * incre);
% Max_Time = max_i * incre;
disp(['Max hight time is ', Max_Time, 's']);   %输出飞行时长
Max_Hight = num2str(Record(2, max_i));
% Max_Hight = Record(2, max_i);
disp(['Max hight is ' Max_Hight, 'm']); %输出最大高度


figure(1)
plot3(Record(1, 1:i), Record(8, 1:i), Record(2, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('x/m');
ylabel('y/m')
zlabel('z/m')
grid


figure(2)
plot(0: incre: (i - 1) * incre, Aero_angles(1,1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\alpha/deg')
grid

figure(3)
plot(0: incre: (i - 1) * incre, Record(3, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\vartheta/deg')
grid

figure(4)
title('Ballistic Inclination - time');
plot(0: incre: (i - 1) * incre, Record(4, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\theta/deg')
grid

figure(5)
title('Velocity - time');
plot(0: incre: (i - 1) * incre, Record(5, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('v/m/s')
grid

figure(6)
plot(0: incre: (i - 1) * incre, Record(6, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\omega_z/˚/s')
grid

figure(7)
plot(0: incre: (i - 1) * incre, Record(7, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('m/kg')
grid

figure(8)
plot(0: incre: (i - 1) * incre, Aero_angles(2,1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\beta/deg')
grid

figure(9)
plot(0: incre: (i - 1) * incre, Record(8, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\beta/deg')
grid

figure(10)
plot(0: incre: (i - 1) * incre, Record(9, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\beta/deg')
grid

figure(11)
plot(0: incre: (i - 1) * incre, Record(10, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\beta/deg')
grid

figure(12)
plot(0: incre: (i - 1) * incre, Record(12, 1:i), 'k', 'linewidth', 1.5)
set(gca,'linewidth', .5);
xlabel('t/s');
ylabel('\beta/deg')
grid