#ifndef TRACK_DATA_PROVIDER_H
#define TRACK_DATA_PROVIDER_H


#include <vector>
#include <string>
#include "geo_utils.h"

class ITrackDataProvider {
public:
    virtual std::vector<TrackPoint> getTracks(const std::string& filepath) = 0;
    virtual ~ITrackDataProvider() = default;
};

class TrackDataProvider : public ITrackDataProvider {
public:
    std::vector<TrackPoint> getTracks(const std::string& filepath) override;
};


#endif //TRACK_DATA_PROVIDER_H
