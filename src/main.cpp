// int main(int argc,char *argv){

// }

// #include "b64/b64.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// int main(void) {
// 	const char *str = "brian the monkey and bradley the kinkajou are friends";
// 	char *enc = b64_encode((unsigned char *)str, strlen(str));

// 	printf("%s\n", enc);
// 	// YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=

// 	char *dec = (char *)b64_decode((char *)enc, strlen(enc));

// 	printf("%s\n", dec);
// 	// brian the monkey and bradley the kinkajou are friends
// 	free(enc);
// 	free(dec);
// 	return 0;
// }
#include "task/other.hpp"
#include "task/task.h"
#include <Windows.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <locale>
#include <string>

using namespace std;
const char *TASKFILE = "D:/.todo";

void help() {
	cout << "ussage: task [help|add|list|detail|remove] {...}" << endl;
	cout << "" << endl;
	cout << "Show this message:         task help" << endl;
	cout << "Add a task:                task add <name> <deadline>" << endl;
	cout << "Add a task with detail:    task add <name> <deadline> <detail>"
		 << endl;
	cout << "List all tasks:            task list" << endl;
	cout << "Show the task's detail:    task detail <number>" << endl;
	cout << "Remove a task:             task remove <number>" << endl;
	cout << "update a task:             task update <number> "
			"[name|deadline|detail] "
			"{...}"
		 << endl;
}
void addTask(string name, string deadline, string detail = "") {
	time_t t = -1;
	if (str2Time(deadline, t)) {
		cout << "cannot parse time" << endl;
		return;
	}
	Tasks tasks;
	readTask(TASKFILE, tasks);
	tasks.push_back(Task{name, t, detail});
	sort(tasks.begin(), tasks.end(),
		 [](Task a, Task b) { return a.deadline < b.deadline; });
	saveTask(TASKFILE, tasks);
	printTask(tasks);
};
void listTask() {
	Tasks tasks;
	readTask(TASKFILE, tasks);
	printTask(tasks);
};
void listTaskWithDetail() {
	Tasks tasks;
	readTask(TASKFILE, tasks);
	printTaskWithDetail(tasks);
};
void taskDetail(string no) {
	Tasks tasks, tasks2;
	Task t;
	int num = atoi(no.c_str());
	readTask(TASKFILE, tasks);
	if (num < 0 || num >= (int)tasks.size()) {
		cout << "number is not right" << endl;
		return;
	}
	t = tasks[num];
	tasks2.push_back(t);
	printTask(tasks2);
	cout << "detail:" << endl << t.detail << endl << endl;
};
void removeTask(string no) {
	Tasks tasks;
	int num = atoi(no.c_str());
	readTask(TASKFILE, tasks);
	if (num < 0 || num >= (int)tasks.size()) {
		cout << "number is not right" << endl;
		return;
	}
	tasks.erase(tasks.begin() + num);
	saveTask(TASKFILE, tasks);
	printTask(tasks);
};
void updateTask(string no, string col, string val) {

	Tasks tasks, tasks2;
	Task t;
	int num = atoi(no.c_str());
	readTask(TASKFILE, tasks);
	if (num < 0 || num >= (int)tasks.size()) {
		cout << "number is not right" << endl;
		return;
	}
	t = tasks[num];
	if (col == "name") {
		t.name = val;
	} else if (col == "deadline") {
		time_t tt = -1;
		if (str2Time(val, tt)) {
			cout << "cannot parse time" << endl;
			return;
		}
		t.deadline = tt;
	} else if (col == "detail") {
		t.detail = val;
	} else {
		cout << "usage is not right" << endl;
		return;
	}
	tasks2.push_back(t);
	tasks.erase(tasks.begin() + num);
	tasks.push_back(t);
	sort(tasks.begin(), tasks.end(),
		 [](Task a, Task b) { return a.deadline < b.deadline; });
	saveTask(TASKFILE, tasks);

	printTask(tasks2);
	cout << "detail:" << endl << t.detail << endl << endl;
}
int main(int argc, char *argv[]) {
	do {
		if (argc < 2) {
			listTask();
			return 0;
		} else {
			if (!strcmp(argv[1], "help")) {
				if (argc > 2)
					break;
				help();
				return 0;
			} else if (!strcmp(argv[1], "add")) {
				if (argc < 4 || argc > 5)
					break;
				if (argc == 4)
					addTask(argv[2], argv[3]);
				else
					addTask(argv[2], argv[3], argv[4]);
				return 0;
			} else if (!strcmp(argv[1], "list")) {
				if (argc > 2)
					break;
				listTaskWithDetail();
				return 0;
			} else if (!strcmp(argv[1], "detail")) {
				if (argc != 3)
					break;
				taskDetail(argv[2]);
				return 0;
			} else if (!strcmp(argv[1], "remove")) {
				if (argc != 3)
					break;
				removeTask(argv[2]);
				return 0;
			} else if (!strcmp(argv[1], "update")) {
				if (argc == 4)
					if (!strcmp(argv[3], "detail")) {
						updateTask(argv[2], "detail", "");
						return 0;
					} else
						break;
				else if (argc == 5) {
					updateTask(argv[2], argv[3], argv[4]);
					return 0;
				} else
					break;
			}
		}
	} while (0);
	help();
	return 0;
}
