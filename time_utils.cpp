#include "time_utils.h"
#include <iomanip>
#include <sstream>

std::time_t parseISO8601(const std::string &datetime) {
    std::tm tm = {};
    std::istringstream iss(datetime);
    iss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    if (iss.fail()) {
        return -1;
    }
    return std::mktime(&tm);
}

std::string time_t_to_iso8601(std::time_t t) {
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}