%% Part 1
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


