#include <cstdlib>
#include <ctime>
#include <regex>
#include <string>
static int str2TimePrase(const std::string &str, tm &deadline) {
	const std::regex temps[] = {
		std::regex("(\\d+)-(\\d+)"),						// #0 mm-dd
		std::regex("(\\d+)-(\\d+)-(\\d+)"),					// #1 yyyy-mm-dd
		std::regex("(\\d+)m", std::regex_constants::icase), // #2 xm
		std::regex("(\\d+)w", std::regex_constants::icase), // #3 xw
		std::regex("(\\d+)d", std::regex_constants::icase), // #4 xd
	};
	std::smatch res;
	for (int i = 0; (unsigned int)(i) < sizeof(temps) / sizeof(std::regex);
		 i++) {
		const std::regex &temp = temps[i];
		if (std::regex_match(str, res, temp)) {
			switch (i) {
			case 0:
				deadline.tm_mon = atoi(res[1].str().c_str());
				deadline.tm_mon -= 1;
				deadline.tm_mday = atoi(res[2].str().c_str());
				return 0;
			case 1:
				deadline.tm_year = atoi(res[1].str().c_str());
				deadline.tm_year -= 1900;
				deadline.tm_mon = atoi(res[2].str().c_str());
				deadline.tm_mon -= 1;
				deadline.tm_mday = atoi(res[3].str().c_str());
				return 0;
			case 2:
				deadline.tm_mon += atoi(res[1].str().c_str());
				return 0;
			case 3:
				deadline.tm_mday += atoi(res[1].str().c_str()) * 7;
				return 0;
			case 4:
				deadline.tm_mday += atoi(res[1].str().c_str());
				return 0;
			default:
				break;
			}
		}
	}
	return 1;
}
int str2Time(const std::string &str, time_t &out) {
	// #0 now
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
	int err = str2TimePrase(str, now_tm);
	if (err)
		return err;
	out = mktime(&now_tm);
	if (out < now) {
		now_tm.tm_year++;
		out = mktime(&now_tm);
	}
	return 0;
}
