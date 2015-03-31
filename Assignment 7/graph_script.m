%% part 2

colors = ['b', 'r', 'g', 'k','m', 'c'];

BASE = 0;
ITERS = 50;
DELTA = 5;

NUMBER_OF_THREADS = 4;

filename = 'q2_data_2.txt';
delimiterIn = ',';
data = importdata(filename, delimiterIn);

f = figure(1);
hold on
scatter(data(:,1), data(:,2)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,3)./data(:,1), 5, 'r');
scatter(data(:,1), (data(:,2)./data(:,1))./NUMBER_OF_THREADS, 5, 'g');

hold off

xlabel('Array Size');
ylabel('Time per element');
title('Compute bound - ijk');
legend('Serial', 'OpenMP', 'Serial/NUMBER_OF_THREADS');

cb_difference = (data(:,3)./data(:,1)) - ((data(:,2)./data(:,1))./NUMBER_OF_THREADS);
cb_average = mean(cb_difference);


figure(2);
hold on
scatter(data(:,1), data(:,4)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,5)./data(:,1), 5, 'r');
scatter(data(:,1), (data(:,4)./data(:,1))./NUMBER_OF_THREADS, 5, 'g');

hold off

xlabel('Array Size');
ylabel('Time per element');
title('Memory Bound - kij');
legend('Serial', 'OpenMP', 'Serial/NUMBER_OF_THREADS');

mb_difference = (data(:,5)./data(:,1)) - ((data(:,4)./data(:,1))./NUMBER_OF_THREADS);
mb_average = mean(mb_difference);

figure(3);
hold on
scatter(data(:,1), data(:,6)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,7)./data(:,1), 5, 'r');
scatter(data(:,1), (data(:,6)./data(:,1))./NUMBER_OF_THREADS, 5, 'g');

hold off

xlabel('Array Size');
ylabel('Time per element');
title('Overhead bound - jki');
legend('Serial', 'OpenMP', 'Serial/NUMBER_OF_THREADS');

ob_difference = (data(:,7)./data(:,1)) - ((data(:,6)./data(:,1))./NUMBER_OF_THREADS);
ob_average = mean(ob_difference);

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

fprintf('Compute Bound Overhead = %d\n', cb_average);
fprintf('Memory Bound Overhead = %d\n', mb_average);
fprintf('Overhead Bound Overhead = %d\n', ob_average);