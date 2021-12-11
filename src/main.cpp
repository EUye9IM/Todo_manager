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
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
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
}
void addTask(string name, string ddl, string info = "") {
	cout << "add" << name << ddl << info << endl;
};
void listTask() { cout << "list" << endl; };
void taskDetail(string no) { cout << "detail" << no << endl; };
void removeTask(string no) { cout << "remove" << no << endl; };
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
				listTask();
				return 0;
			} else if (!strcmp(argv[1], "detail")) {
				if (argc < 3 || argc > 3)
					break;
				taskDetail(argv[2]);
				return 0;
			} else if (!strcmp(argv[1], "remove")) {
				if (argc < 3 || argc > 3)
					break;
				removeTask(argv[2]);
				return 0;
			}
		}
	} while (0);
	help();
	return 0;
}