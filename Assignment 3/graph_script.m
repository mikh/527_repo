%% part 1
filename = 'p1_data_1.txt';
delimiterIn = ',';
p1_data = importdata(filename, delimiterIn);

p1_base = p1_data(1:64,:);
p1_test = p1_data(65:128,:);

figure(1);
hold on
scatter(p1_base(:,1), p1_base(:,2), 5, 'b');
scatter(p1_test(:,1), p1_test(:,2), 5, 'r');
xlabel('Address Alignment');
ylabel('Cycles');
title('Different offsets on address');
legend('base','test');
hold off