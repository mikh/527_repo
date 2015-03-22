%% part 1
filenames = {'q1_data_O_05_2_S_10.txt','q1_data_O_05_2_S_20.txt'};
titles = {'Size 10', 'Size 20'};
colors = ['b', 'r'];

figure(1);
hold on
xlabel('Omega');
ylabel('Iterations to convergence');
title('Omega vs. iterations for different array sizes');
delimiterIn = ' ';
for i = 1:length(filenames)
    disp(filenames(i));
    data = importdata(filenames{i}, delimiterIn);
    scatter(data(:,1),data(:,2),5,colors(i));
end
legend(titles);

hold off;