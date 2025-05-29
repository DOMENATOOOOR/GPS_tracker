#ifndef TIME_UTILS_H
#define TIME_UTILS_H



#include <string>
#include <ctime>

std::time_t parseISO8601(const std::string &datetime);
std::string time_t_to_iso8601(std::time_t t);


#endif //TIME_UTILS_H
