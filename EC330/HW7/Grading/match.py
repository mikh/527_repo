

def find_in_list(name, list):
	for ii in range(0, len(list)):
		if list[ii][0].strip() == name.strip():
			return ii
	return -1

g_lines = []
with open('student_grades.txt' , 'r') as f:
	g_lines = f.readlines()

n_lines = []
with open('student_names.txt', 'r') as f:
	n_lines = f.readlines()

g_s_lines = []
for ii in range(0, len(g_lines)):
	g_s_lines.append(g_lines[ii].split())
print(g_s_lines)
t_lines = []
for ii in range(0, len(n_lines)):
	index = find_in_list(n_lines[ii], g_s_lines)
	if index == -1:
		t_lines.append([n_lines[ii], "0"])
	else:
		t_lines.append(g_s_lines[index])

with open("matched_grades.txt", "w") as f:
	for ii in range(0, len(t_lines)):
		f.write("{0}\n".format(t_lines[ii][1].strip()))

