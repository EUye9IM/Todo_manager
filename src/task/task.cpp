#include "task.h"
#include "b64/b64.h"
#include <fstream>
#include <iostream>
#include <sstream>
int printTask(const Tasks &tasks) {
	std::string fmt;
	char buf[64];
	int namelen = 0;
	for (Task t : tasks) {
		if (namelen < int(t.name.length()))
			namelen = int(t.name.length());
	}
	namelen += 10;
	printf("\n");

	time_t now = time(nullptr);
	tm now_tm;
	localtime_s(&now_tm, &now);
	strftime(buf, 64, "%m-%d %Y", &now_tm);
	printf("               Today is %s\n\n", buf);

	fmt = "%8s%" + std::to_string(namelen) + "s%12s\n";
	printf(fmt.c_str(), "No.", "task name", "deadLine");
	fmt = "%8d%" + std::to_string(namelen) + "s%12s";
	printf("\n");
	for (int i = 0; i < int(tasks.size()); i++) {
		tm tt;
		localtime_s(&tt, &tasks[i].deadline);
		strftime(buf, 64, "%m-%d %Y", &tt);
		printf(fmt.c_str(), i, tasks[i].name.c_str(), buf);
		if (now < tasks[i].deadline) {
			if (now_tm.tm_year < tt.tm_year)
				printf("  +%2d y", tt.tm_year - now_tm.tm_year);
			else if (tt.tm_mon > now_tm.tm_mon)
				printf("  +%2d m", tt.tm_mon - now_tm.tm_mon);
			else if (tt.tm_yday > now_tm.tm_yday)
				printf("  +%2d d", tt.tm_yday - now_tm.tm_yday);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}
int printTaskWithDetail(const Tasks &tasks) {
	std::string fmt;
	char buf[64];
	int namelen = 0;
	for (Task t : tasks) {
		if (namelen < int(t.name.length()))
			namelen = int(t.name.length());
	}
	namelen += 10;
	printf("\n");

	time_t now = time(nullptr);
	tm now_tm;
	localtime_s(&now_tm, &now);
	strftime(buf, 64, "%m-%d %Y", &now_tm);
	printf("               Today is %s\n\n", buf);

	fmt = "%8s%" + std::to_string(namelen) + "s%12s\n";
	printf(fmt.c_str(), "No.", "task name", "deadLine");
	fmt = "%8d%" + std::to_string(namelen) + "s%12s";
	printf("\n");
	std::string hline(22 + namelen, '-');
	for (int i = 0; i < int(tasks.size()); i++) {
		printf("%s\n", hline.c_str());
		tm tt;
		localtime_s(&tt, &tasks[i].deadline);
		strftime(buf, 64, "%m-%d %Y", &tt);
		printf(fmt.c_str(), i, tasks[i].name.c_str(), buf);
		if (now < tasks[i].deadline) {
			if (now_tm.tm_year < tt.tm_year)
				printf("  +%2d y", tt.tm_year - now_tm.tm_year);
			else if (tt.tm_mon > now_tm.tm_mon)
				printf("  +%2d m", tt.tm_mon - now_tm.tm_mon);
			else if (tt.tm_yday > now_tm.tm_yday)
				printf("  +%2d d", tt.tm_yday - now_tm.tm_yday);
		}
		printf("\n");
		printf("detail:\n%s\n\n", tasks[i].detail.c_str());
	}
	printf("%s\n", hline.c_str());
	printf("\n");
	return 0;
}
int readTask(const std::string &path, Tasks &tasks) {
	tasks.clear();
	std::ifstream file(path);
	if (!file.is_open())
		return -1;
	while (!file.eof()) {
		std::string line;
		std::getline(file, line);
		if (file.eof()) {
			file.close();
			return 0;
		}

		Task t;
		std::stringstream ss(line);
		unsigned char *s1, *s2;
		ss >> t.name >> t.deadline;
		ss >> t.detail;
		s1 = b64_decode(t.name.c_str(), t.name.length());
		s2 = b64_decode(t.detail.c_str(), t.detail.length());
		t.name = std::string((char *)s1);
		t.detail = std::string((char *)s2);
		tasks.push_back(t);
		free(s1);
		free(s2);
	}
	file.close();
	return 0;
}
int saveTask(const std::string &path, const Tasks &tasks) {
	std::ofstream file(path);
	if (!file.is_open())
		return -1;
	for (Task t : tasks) {
		char *s1, *s2;
		s1 = b64_encode((const unsigned char *)t.name.c_str(), t.name.length());
		s2 = b64_encode((const unsigned char *)t.detail.c_str(),
						t.detail.length());
		file << s1 << " " << t.deadline << " " << s2 << std::endl;
		free(s1);
		free(s2);
	}
	file.close();

	return 0;
}
