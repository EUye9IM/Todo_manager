#include <ctime>
#include <string>
#include <vector>
struct Task {
	std::string name;
	std::time_t deadline;
	std::string detail;
};
typedef std::vector<Task> Tasks;
int readTask(const std::string &path, Tasks &tasks);
int saveTask(const std::string &path, const Tasks &tasks);
int printTask(const Tasks &tasks);