%% part 1
filenames = {'q1_data_O_05_2_S_10.txt',
    'q1_data_O_05_2_S_20.txt',
    'q1_data_O_05_2_S_30.txt', 
    'q1_data_O_05_2_S_40.txt',
    'q1_data_O_15_2_S_100.txt',
    'q1_data_O_05_2_S_200.txt'
    };
titles = {'Size 10', 'Size 20', 'Size 30', 'Size 40','Size 100', 'Size 200'};
colors = ['b', 'r', 'g', 'k','m', 'c'];

figure(1);
hold on
xlabel('Omega');
ylabel('Iterations to convergence');
title('Omega vs. iterations for different array sizes');
delimiterIn = ' ';
for i = 1:length(filenames)
    data = importdata(filenames{i}, delimiterIn);
    scatter(data(:,1),data(:,2),5,colors(i));
    [mi, ind] = min(data(:,2));
    mi_ome = data(ind, 1);
    fprintf('Minimum Omega for %s is %f\n',titles{i}, mi_ome);
end
legend(titles);

hold off;

%% part 2
filename = 'q2_data_total.txt';
delimiterIn = ',';
data = importdata(filename, delimiterIn);
figure(2);
hold on
scatter(data(:,1), data(:,3)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,5)./data(:,1), 5, 'r');
scatter(data(:,1), data(:,7)./data(:,1), 5, 'g');
hold off
xlabel('Array Size');
ylabel('inner_loop_timing');
title('Array size vs. Inner loop timing');
legend('Version 1', 'Version 2', 'Version 3');

%% part 3
filename = 'q3_data.txt';
delimiterIn = ',';
data = importdata(filename, delimiterIn);
figure(3);
hold on
scatter(data(:,1), data(:,2)./data(:,1), 5, 'b');
scatter(data(:,1), data(:,3)./data(:,1), 5, 'r');
scatter(data(:,1), data(:,4)./data(:,1), 5, 'g');

hold off

xlabel('Array Size');
ylabel('Cycles per element');
title('Array size vs. Inner loop timing');
legend('1 thread', '2 threads', '4 threads');

figure(4);
hold on
scatter(data(:,1), (data(:,3)./data(:,1)) - (data(:,2)./data(:,1)), 5, 'r');
scatter(data(:,1), (data(:,4)./data(:,1)) - (data(:,2)./data(:,1)), 5, 'g');

hold off

xlabel('Array Size');
ylabel('Cycle difference per element');
title('Cycle Difference between baseline and threaded version per element');
legend('2 threads', '4 threads');
