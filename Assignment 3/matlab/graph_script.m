%% part 1
filename = 'pa_1.txt';
delimiterIn = ',';
pa1_data = importdata(filename, delimiterIn);
colors = ['b', 'r'];

x = pa1_data(:,1);
y = [pa1_data(:,2), pa1_data(:,3)];

figure(1);
hold on
for i = 1:2
    scatter(x,y(:,i), 5, colors(i));
end

xlabel('Boundary Alignment');
ylabel('Cycles');
title('Unmodified test_align Cycles vs. Boundary Alignment');
legend('base','test');
hold off

filename = 'pa_2.txt';
pa2_data = importdata(filename, delimiterIn);

x = pa2_data(:,1);
y = [pa2_data(:,2), pa2_data(:,3)];

figure(2);
hold on
for i = 1:2
    scatter(x,y(:,i), 5, colors(i));
end

xlabel('Boundary Alignment');
ylabel('Cycles');
title('Modified test_align Cycles vs. Boundary Alignment');
legend('base','test');
hold off







%% part 2
colors = ['b', 'r', 'm', 'c', 'g', 'y', 'k'];
delimiterIn = ',';

filename = 'pb_1.txt';
legend_strings = {'combine4', 'combine6 5', 'combine8', 'combine8 4'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'Unmodified test_combine8 Size vs. CPE';
Y_SIZE = 4;
CPE = 1;
figure_number = 3;



data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings');
hold off


filename = 'pb_2.txt';
legend_strings = {'combine4', 'combine6 5', 'combine8', 'combine8 4', 'combine8 2', 'combine8 8'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'Modified test_combine8 Size vs. CPE';
Y_SIZE = 6;
CPE = 1;
figure_number = 4;


data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings');
hold off


filename = 'pb_3.txt';
legend_strings = {'dot4', 'dot5', 'dot6 2', 'dot6 5', 'dot8', 'dot8 2'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'Unmodified test_dot Size vs. CPE';
Y_SIZE = 6;
CPE = 1;
figure_number = 5;

data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings');
hold off

filename = 'pb_4.txt';
legend_strings = {'dot4', 'dot5', 'dot6 2', 'dot6 5', 'dot8', 'dot8 2', 'dot8 4'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'Modified test_dot Size vs. CPE';
Y_SIZE = 7;
CPE = 1;
figure_number = 6;

data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings');
hold off










%% part 4
colors = ['b', 'r', 'm', 'c', 'g', 'y', 'k'];
delimiterIn = ',';

filename = 'pd_1.txt';
legend_strings = {'ij', 'ji'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'O1 Transpose Size vs. CPE';
Y_SIZE = 2;
CPE = 1;
figure_number = 10;



data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings');
hold off

filename = 'pd_2.txt';
legend_strings = {'ij', 'ji', 'SSE', 'SSE with blocking'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'SSE With Blocking Transpose Size vs. CPE';
Y_SIZE = 4;
CPE = 1;
figure_number = 11;



data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings');
hold off

filename = 'pd_3.txt';
legend_strings = {'ij', 'ji'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'O2 Transpose Size vs. CPE';
Y_SIZE = 2;
CPE = 1;
figure_number = 12;



data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings);
hold off


colors = ['b', 'r', 'm', 'c', 'g', 'y', 'k'];
delimiterIn = ',';

filename = 'pd_4.txt';
legend_strings = {'ij', 'ji'};
xlabel_string = 'Vector Size';
ylabel_string = 'CPE';
title_string = 'O3 Transpose Size vs. CPE';
Y_SIZE = 2;
CPE = 1;
figure_number = 13;



data = importdata(filename, delimiterIn);
x = data(:,1);
y = [];
for i = 1:Y_SIZE
	if CPE == 1
		y = [y, data(:,i+1)./x];
	else
		y = [y, data(:,i+1)];
	end
end

figure(figure_number);
hold on
for i = 1:Y_SIZE
    scatter(x,y(:,i), 5, colors(i));
end
xlabel(xlabel_string);
ylabel(ylabel_string);
title(title_string);
legend(legend_strings');
hold off

