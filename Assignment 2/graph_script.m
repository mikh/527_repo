%% Question 1: Experiment with basic optimization methods

%% Part a: base code
filename = 'q1_data_double_multiply.txt';
delimiterIn = ',';
q1_data = importdata(filename, delimiterIn);


%%combine1
%figure(1);
%scatter(q1_data(:,1), q1_data(:,2), 5, 'r');
%xlabel('data elements');
%ylabel('cycles');
%title('combine1');
%
%%combine2
%figure(2);
%scatter(q1_data(:,1), q1_data(:,3), 5, 'r');
%xlabel('data elements');
%ylabel('cycles');
%title('combine2');
%
%%combine3
%figure(3);
%scatter(q1_data(:,1), q1_data(:,4), 5, 'r');
%xlabel('data elements');
%ylabel('cycles');
%title('combine3');
%
%
%%combine4
%figure(4);
%scatter(q1_data(:,1), q1_data(:,5), 5, 'r');
%xlabel('data elements');
%ylabel('cycles');
%title('combine4');
%
%%combine5
%figure(5);
%scatter(q1_data(:,1), q1_data(:,6), 5, 'r');
%xlabel('data elements');
%ylabel('cycles');
%title('combine5');
%
%%combine6
%figure(6);
%scatter(q1_data(:,1), q1_data(:,7), 5, 'r');
%xlabel('data elements');
%ylabel('cycles');
%title('combine6');
%
%
%%combine7
%figure(7);
%scatter(q1_data(:,1), q1_data(:,8), 5, 'r');
%xlabel('data elements');
%ylabel('cycles');
%title('combine7');

%double multiply
%combine 1-7
figure(1);
hold on
scatter(q1_data(:,1), q1_data(:,2), 5, 'y');
scatter(q1_data(:,1), q1_data(:,3), 5, 'm');
scatter(q1_data(:,1), q1_data(:,4), 5, 'c');
scatter(q1_data(:,1), q1_data(:,5), 5, 'r');
scatter(q1_data(:,1), q1_data(:,6), 5, 'g');
scatter(q1_data(:,1), q1_data(:,7), 5, 'b');
scatter(q1_data(:,1), q1_data(:,8), 5, 'w');
xlabel('data elements');
ylabel('cycles');
title('All combines double and *');
legend('combine1', 'combine2', 'combine3', 'combine4', 'combine5', 'combine6', 'combine7');
hold off

filename = 'q1_data_double_add.txt';
delimiterIn = ',';
q1_data = importdata(filename, delimiterIn);

%double multiply
%combine 1-7
figure(2);
hold on
scatter(q1_data(:,1), q1_data(:,2), 5, 'y');
scatter(q1_data(:,1), q1_data(:,3), 5, 'm');
scatter(q1_data(:,1), q1_data(:,4), 5, 'c');
scatter(q1_data(:,1), q1_data(:,5), 5, 'r');
scatter(q1_data(:,1), q1_data(:,6), 5, 'g');
scatter(q1_data(:,1), q1_data(:,7), 5, 'b');
scatter(q1_data(:,1), q1_data(:,8), 5, 'w');
xlabel('data elements');
ylabel('cycles');
title('All combines double and +');
legend('combine1', 'combine2', 'combine3', 'combine4', 'combine5', 'combine6', 'combine7');
hold off

filename = 'q1_data_single_multiply.txt';
delimiterIn = ',';
q1_data = importdata(filename, delimiterIn);

%double multiply
%combine 1-7
figure(3);
hold on
scatter(q1_data(:,1), q1_data(:,2), 5, 'y');
scatter(q1_data(:,1), q1_data(:,3), 5, 'm');
scatter(q1_data(:,1), q1_data(:,4), 5, 'c');
scatter(q1_data(:,1), q1_data(:,5), 5, 'r');
scatter(q1_data(:,1), q1_data(:,6), 5, 'g');
scatter(q1_data(:,1), q1_data(:,7), 5, 'b');
scatter(q1_data(:,1), q1_data(:,8), 5, 'w');
xlabel('data elements');
ylabel('cycles');
title('All combines single and *');
legend('combine1', 'combine2', 'combine3', 'combine4', 'combine5', 'combine6', 'combine7');
hold off

filename = 'q1_data_int_add.txt';
delimiterIn = ',';
q1_data = importdata(filename, delimiterIn);

%double multiply
%combine 1-7
figure(4);
hold on
scatter(q1_data(:,1), q1_data(:,2), 5, 'y');
scatter(q1_data(:,1), q1_data(:,3), 5, 'm');
scatter(q1_data(:,1), q1_data(:,4), 5, 'c');
scatter(q1_data(:,1), q1_data(:,5), 5, 'r');
scatter(q1_data(:,1), q1_data(:,6), 5, 'g');
scatter(q1_data(:,1), q1_data(:,7), 5, 'b');
scatter(q1_data(:,1), q1_data(:,8), 5, 'w');
xlabel('data elements');
ylabel('cycles');
title('All combines int and +');
legend('combine1', 'combine2', 'combine3', 'combine4', 'combine5', 'combine6', 'combine7');
hold off

filename = 'q1_data_int_multiply.txt';
delimiterIn = ',';
q1_data = importdata(filename, delimiterIn);

%double multiply
%combine 1-7
figure(5);
hold on
scatter(q1_data(:,1), q1_data(:,2), 5, 'y');
scatter(q1_data(:,1), q1_data(:,3), 5, 'm');
scatter(q1_data(:,1), q1_data(:,4), 5, 'c');
scatter(q1_data(:,1), q1_data(:,5), 5, 'r');
scatter(q1_data(:,1), q1_data(:,6), 5, 'g');
scatter(q1_data(:,1), q1_data(:,7), 5, 'b');
scatter(q1_data(:,1), q1_data(:,8), 5, 'w');
xlabel('data elements');
ylabel('cycles');
title('All combines int and *');
legend('combine1', 'combine2', 'combine3', 'combine4', 'combine5', 'combine6', 'combine7');
hold off

%% part b: loop unrolling

filename = 'q1_data_double_multiply.txt';
delimiterIn = ',';
q1_data = importdata(filename, delimiterIn);


figure(6);
hold on
scatter(q1_data(:,1), q1_data(:,9)./q1_data(:,1), 5, 'y');
scatter(q1_data(:,1), q1_data(:,10)./q1_data(:,1), 5, 'm');
scatter(q1_data(:,1), q1_data(:,11)./q1_data(:,1), 5, 'c');
scatter(q1_data(:,1), q1_data(:,12)./q1_data(:,1), 5, 'r');
xlabel('data elements');
ylabel('cycles');
title('Loop unrolling');
legend('5x', '6x', '8x', '10x');
hold off

%% part c: with parallelization and association



filename = 'q1_data_double_multiply.txt';
delimiterIn = ',';
q1_data = importdata(filename, delimiterIn);


figure(7);
hold on
scatter(q1_data(:,1), q1_data(:,9)./q1_data(:,1), 5, 'y');
scatter(q1_data(:,1), q1_data(:,10)./q1_data(:,1), 5, 'm');
scatter(q1_data(:,1), q1_data(:,11)./q1_data(:,1), 5, 'c');
scatter(q1_data(:,1), q1_data(:,12)./q1_data(:,1), 5, 'r');
scatter(q1_data(:,1), q1_data(:,13)./q1_data(:,1), 5, 'b');
xlabel('data elements');
ylabel('cycles');
title('Loop unrolling');
legend('5x', '6x', '8x', '10x', 'parallelized');
hold off

%% Q2

filename = 'q2_data';
delimiterIn = ',';
q2_data = importdata(filename, delimiterIn);


figure(8);
hold on
scatter(q2_data(:,1), q2_data(:,2)./q2_data(:,1), 5, 'y');
scatter(q2_data(:,1), q2_data(:,3)./q2_data(:,1), 5, 'm');
scatter(q2_data(:,1), q2_data(:,4)./q1_data(:,1), 5, 'c');
scatter(q2_data(:,1), q2_data(:,5)./q2_data(:,1), 5, 'r');
scatter(q2_data(:,1), q2_data(:,6)./q2_data(:,1), 5, 'w');
scatter(q2_data(:,1), q2_data(:,7)./q2_data(:,1), 5, 'k');
scatter(q2_data(:,1), q2_data(:,8)./q2_data(:,1), 5, 'g');
scatter(q2_data(:,1), q2_data(:,9)./q2_data(:,1), 5, 'b');
xlabel('data elements');
ylabel('cycles');
title('Dot Product');
legend('dot_base', 'dot_1', 'dot_2', 'dot_3', 'dot_4', 'dot_5', 'dot_6', 'dot_7');
hold off

%% Q3

filename = 'q3_onechoice.txt';
delimiterIn = ',';
q3_data = importdata(filename, delimiterIn);


figure(9);
hold on
scatter(q3_data(:,1), q3_data(:,2)./q3_data(:,1), 5, 'b');
scatter(q3_data(:,1), q3_data(:,4)./q3_data(:,1), 5, 'r');
xlabel('data elements');
ylabel('cycles');
title('One branch always right');
legend('branch1', 'branch2');
hold off

filename = 'q3_split.txt';
delimiterIn = ',';
q3_data = importdata(filename, delimiterIn);


figure(10);
hold on
scatter(q3_data(:,1), q3_data(:,2)./q3_data(:,1), 5, 'b');
scatter(q3_data(:,1), q3_data(:,4)./q3_data(:,1), 5, 'r');
xlabel('data elements');
ylabel('cycles');
title('Branch changes halfway');
legend('branch1', 'branch2');
hold off

filename = 'q3_updown.txt';
delimiterIn = ',';
q3_data = importdata(filename, delimiterIn);


figure(11);
hold on
scatter(q3_data(:,1), q3_data(:,2)./q3_data(:,1), 5, 'b');
scatter(q3_data(:,1), q3_data(:,4)./q3_data(:,1), 5, 'r');
xlabel('data elements');
ylabel('cycles');
title('Branch switches each iteration');
legend('branch1', 'branch2');
hold off

filename = 'q3_random.txt';
delimiterIn = ',';
q3_data = importdata(filename, delimiterIn);


figure(12);
hold on
scatter(q3_data(:,1), q3_data(:,2)./q3_data(:,1), 5, 'b');
scatter(q3_data(:,1), q3_data(:,4)./q3_data(:,1), 5, 'r');
xlabel('data elements');
ylabel('cycles');
title('random values');
legend('branch1', 'branch2');
hold off