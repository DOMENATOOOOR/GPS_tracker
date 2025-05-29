#ifndef GEO_UTILS_H
#define GEO_UTILS_H


#include <vector>
#include <ctime>

struct TrackPoint {
    double latitude;
    double longitude;
    double elevation;
    std::time_t timestamp;
};

class GeoUtils {
public:
    static const double STOP_SPEED_THRESHOLD;

    static double toRadians(double degrees);
    static double calculateDistance(const TrackPoint& a, const TrackPoint& b);
    static double calculateSpeed(const TrackPoint& a, const TrackPoint& b);
};

#endif //GEO_UTILS_H
