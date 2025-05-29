#include "geo_utils.h"
#include <cmath>

const double GeoUtils::STOP_SPEED_THRESHOLD = 0.1;

double GeoUtils::toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double GeoUtils::calculateDistance(const TrackPoint& a, const TrackPoint& b) {
    double lat1 = toRadians(a.latitude);
    double lon1 = toRadians(a.longitude);
    double lat2 = toRadians(b.latitude);
    double lon2 = toRadians(b.longitude);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double haversine = sin(dlat/2) * sin(dlat/2) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);
    double c = 2 * atan2(sqrt(haversine), sqrt(1-haversine));

    return 6371000 * c;
}

double GeoUtils::calculateSpeed(const TrackPoint& a, const TrackPoint& b) {
    double distance = calculateDistance(a, b);
    double timeDiff = difftime(b.timestamp, a.timestamp);
    return timeDiff > 0 ? distance / timeDiff : 0;
}
