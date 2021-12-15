#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
static void foo(const std::string &str, tm &ddl) {
	char c;
	std::istringstream ss(str);
	ss >> ddl.tm_mon >> c >> ddl.tm_mday;
	ddl.tm_mon -= 1;
}
int str2Time(const std::string &str, time_t &out) {
	if (str == "now") {
		out = -1;
		return 0;
	}
	time_t now = time(nullptr);
	tm now_tm;
	localtime_s(&now_tm, &now);
	now_tm.tm_sec = 0;
	now_tm.tm_min = 0;
	now_tm.tm_hour = 0;
	now_tm.tm_wday = 0;
	now_tm.tm_yday = 0;
	foo(str, now_tm);
	out = mktime(&now_tm);
	if(out < now) {
		now_tm.tm_year ++;
		out=mktime(&now_tm);
	}
	return 0;
}
