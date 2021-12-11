#include <ctime>
#include <string>
#include <vector>
const char *TASKFILE = "C:\\.task";
struct Task {
	std::string name;
	std::time_t ddl;
	std::string info;
};
std::vector<Task> readTask();
void removeTask();
void addTask();