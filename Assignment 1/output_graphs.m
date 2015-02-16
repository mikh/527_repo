%% Part 1 Question 1
filename = 'data_q1.txt';
delimiterIn = ',';
p1_data = importdata(filename, delimiterIn);

% graph a and b
figure(1)
scatter(p1_data(:,1),p1_data(:,2),5,'r');
hold on
scatter(p1_data(:,1),p1_data(:,3),5,'b');
hold off
xlabel('log(data elements)');
ylabel('log(cycle)');
title('log(Cycles) x log(Data)');
legend('combine2d','combine2d_ rev');

%graph c
figure(2)
scatter(p1_data(:,1), p1_data(:,3)-p1_data(:,2),5,'b');
xlabel('log(data elements)');
ylabel('cycle difference');
title('Cycle difference between combine2d vs. combine2d rev');

%graph d and e
figure(3)
scatter(p1_data(:,1), p1_data(:,2)./p1_data(:,1),5,'r');
hold on
scatter(p1_data(:,1), p1_data(:,3)./p1_data(:,1),5,'b');
hold off
xlabel('log(data elements)');
ylabel('cycles/data');
title('Ratio of Number of Cycles to Number of elements');
legend('combine2d', 'combine2d rev');

%graph ratio of combine2d to combine2d rev
figure(4)
scatter(p1_data(:,1),p1_data(:,3)./p1_data(:,2),5,'b');
xlabel('log(data elements)');
ylabel('ratio of combine2d to combine2d rev');
title('Ratio between combine2d vs. combine2d rev');

%% Part 1 Question 2

filename = 'p1q2_data_1_p1.txt';
delimiterIn = ',';
p1q2_data_1 = importdata(filename, delimiterIn);

filename = 'p1q2_data_1_p2.txt';
p1q2_data_2 = importdata(filename, delimiterIn);

%graph log(cycles) vs log(elements)
%for clock_gettime
figure(5)
scatter(p1q2_data_1(:,1), p1q2_data_1(:,2), 5, 'r');
hold on
scatter(p1q2_data_1(:,1),p1q2_data_1(:,3),5,'b');
hold off
xlabel('log(data elements)');
ylabel('log(cycle)');
title('log(Cycles) x log(Data) for range BASE=30, ITERS=200, DELTA=1 using clock_gettime');
legend('combine2d','combine2d_ rev');

%graph log(cycles) vs log(elements)
%for RDTSC
figure(6)
scatter(p1q2_data_2(:,1), p1q2_data_2(:,2), 5, 'r');
hold on
scatter(p1q2_data_2(:,1),p1q2_data_2(:,3),5,'b');
hold off
xlabel('log(data elements)');
ylabel('log(cycle)');
title('log(Cycles) x log(Data) for range BASE=30, ITERS=200, DELTA=1, using RDTSC');
legend('combine2d','combine2d_ rev');

filename = 'p1q2_data_2_p1.txt';
delimiterIn = ',';
p1q2_data_1 = importdata(filename, delimiterIn);

filename = 'p1q2_data_2_p2.txt';
p1q2_data_2 = importdata(filename, delimiterIn);

%graph log(cycles) vs log(elements)
%for clock_gettime
figure(7)
scatter(p1q2_data_1(:,1), p1q2_data_1(:,2), 5, 'r');
hold on
scatter(p1q2_data_1(:,1),p1q2_data_1(:,3),5,'b');
hold off
xlabel('log(data elements)');
ylabel('log(cycle)');
title('log(Cycles) x log(Data) for range BASE=9500, ITERS=200, DELTA=5 using clock_gettime');
legend('combine2d','combine2d_ rev');

%graph log(cycles) vs log(elements)
%for RDTSC
figure(8)
scatter(p1q2_data_2(:,1), p1q2_data_2(:,2), 5, 'r');
hold on
scatter(p1q2_data_2(:,1),p1q2_data_2(:,3),5,'b');
hold off
xlabel('log(data elements)');
ylabel('log(cycle)');
title('log(Cycles) x log(Data) for range BASE=9500, ITERS=200, DELTA=5, using RDTSC');
legend('combine2d','combine2d_ rev');


%% Part 1 Q3

filename = 'p1q3_data.txt';
delimiterIn = ',';
p1_data = importdata(filename, delimiterIn);

%graph d and e
figure(9)
scatter(p1_data(:,1), p1_data(:,2)./p1_data(:,1),5,'r');
hold on
scatter(p1_data(:,1), p1_data(:,3)./p1_data(:,1),5,'b');
hold off
xlabel('log(data elements)');
ylabel('cycles/data');
title('Ratio of Number of Cycles to Number of elements with BASE = 10000 ITERS = 200 DELTA = 10');
legend('combine2d', 'combine2d rev');

%% Part 2 Q1
filename = 'p2q1_data.txt';
p2_data = importdata(filename, delimiterIn);

figure(10)
scatter(p2_data(:,1), p2_data(:,2),5,'r');
hold on
scatter(p2_data(:,1), p2_data(:,3), 5, 'b');
scatter(p2_data(:,1), p2_data(:,4), 5, 'g');
hold off
xlabel('log(data elements)');
ylabel('log(cycles)');
title('Comparison of 3 loop different loop combinations');
legend('ijk', 'kij', 'jki');


%% Part 2 Q2
filename = 'p2q2_data.txt';
p2_data = importdata(filename, delimiterIn);

figure(11)
scatter(p2_data(:,1), p2_data(:,2),5,'r');
hold on
scatter(p2_data(:,1), p2_data(:,3), 5, 'b');
scatter(p2_data(:,1), p2_data(:,4), 5, 'g');
hold off
xlabel('log(data elements)');
ylabel('log(cycles)');
title('Comparison of 3 loop different loop combinations');
legend('ijk', 'kij', 'jki');