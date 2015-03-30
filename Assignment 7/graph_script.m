%% part 2

colors = ['b', 'r', 'g', 'k','m', 'c'];

filename = 'q2_data.txt';
delimiterIn = ',';
data = importdata(filename, delimiterIn);

figure(1);
hold on
scatter(data(:,1), data(:,2)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,3)./data(:,1), 5, 'r');

hold off

xlabel('Array Size');
ylabel('Time per element');
title('Compute bound - ijk');
legend('Serial', 'OpenMP');

figure(2);
hold on
scatter(data(:,1), data(:,4)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,5)./data(:,1), 5, 'r');

hold off

xlabel('Array Size');
ylabel('Time per element');
title('Memory Bound - kij');
legend('Serial', 'OpenMP');

figure(3);
hold on
scatter(data(:,1), data(:,6)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,7)./data(:,1), 5, 'r');

hold off

xlabel('Array Size');
ylabel('Time per element');
title('Overhead bound - jki');
legend('Serial', 'OpenMP');

figure(4);
hold on
scatter(data(:,1), data(:,3)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,5)./data(:,1), 5, 'r');
scatter(data(:,1), data(:,7)./data(:,1), 5, 'g');

hold off

xlabel('Array Size');
ylabel('Time per element');
title('Comparison of 3 parallel versions');
legend('Compute Bound', 'Memory Bound', 'Overhead Bound');


