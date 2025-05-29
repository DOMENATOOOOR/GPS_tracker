#include "metric_calculators.h"
#include <algorithm>
#include <map>
#include <cmath>

void Throw(const std::vector<TrackPoint>& tracks) {
    if (tracks.empty()) {
        throw std::runtime_error("No tracks found");
    }
}

double AllDistanceCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double all_distance = 0;
    for (int i = 0; i < tracks.size()-1; ++i) {
        all_distance += GeoUtils::calculateDistance(tracks[i], tracks[i + 1]);
    }
    return all_distance;
}

double AllTimeCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    return difftime(tracks.back().timestamp, tracks.front().timestamp);
}

double AverageSpeedCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double average_s = 0;
    for (int i = 0; i < tracks.size()-1; ++i) {
        average_s += GeoUtils::calculateSpeed(tracks[i], tracks[i + 1]);
    }
    return average_s / difftime(tracks.back().timestamp, tracks.front().timestamp);
}

double MovingTimeCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double movingTime = 0;
    for (size_t i = 0; i < tracks.size()-1; ++i) {
        if (GeoUtils::calculateSpeed(tracks[i], tracks[i+1]) > GeoUtils::STOP_SPEED_THRESHOLD) {
            movingTime += difftime(tracks[i+1].timestamp, tracks[i].timestamp);
        }
    }
    return movingTime;
}

double StoppingTimeCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    AllTimeCalculator totalTimeCalc;
    MovingTimeCalculator movingTimeCalc;
    return totalTimeCalc.calculate(tracks) - movingTimeCalc.calculate(tracks);
}

double MaxSpeedCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double maxSpeed = 0;
    for (size_t i = 0; i < tracks.size()-1; ++i) {
        if(GeoUtils::calculateSpeed(tracks[i], tracks[i+1]) > maxSpeed)
            maxSpeed = GeoUtils::calculateSpeed(tracks[i], tracks[i+1]);
    }
    return maxSpeed;
}

double MinSpeedCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double minSpeed = 10000;
    for (size_t i = 0; i < tracks.size()-1; ++i) {
        if(GeoUtils::calculateSpeed(tracks[i], tracks[i+1]) < minSpeed)
            minSpeed = GeoUtils::calculateSpeed(tracks[i], tracks[i+1]);
    }
    return minSpeed;
}

double MinElevationCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double minElev = tracks[0].elevation;
    for (const auto& track : tracks) {
        if (track.elevation < minElev) minElev = track.elevation;
    }
    return minElev;
}

double MaxElevationCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double maxElev = tracks[0].elevation;
    for (const auto& track : tracks) {
        if (track.elevation > maxElev) maxElev = track.elevation;
    }
    return maxElev;
}

double TotalAscentCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double totalAscent = 0;
    for (size_t i = 0; i < tracks.size()-1; ++i) {
        if (tracks[i+1].elevation - tracks[i].elevation > 0)
            totalAscent += tracks[i+1].elevation - tracks[i].elevation;
    }
    return totalAscent;
}

double TotalDescentCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);
    double totalDescent = 0;
    for (size_t i = 0; i < tracks.size()-1; ++i) {
        if (tracks[i+1].elevation - tracks[i].elevation < 0)
            totalDescent += -(tracks[i+1].elevation - tracks[i].elevation);
    }
    return totalDescent;
}

SpeedDistributionCalculator::SpeedDistributionCalculator(double binSize) : binSize(binSize) {}

std::vector<std::pair<std::pair<double, double>, double>> SpeedDistributionCalculator::getSpeedDistribution() const {
    return speedDistribution;
}

double SpeedDistributionCalculator::calculate(const std::vector<TrackPoint>& tracks) {
    Throw(tracks);

    std::vector<double> speeds;
    for (size_t i = 0; i < tracks.size() - 1; ++i) {
        double speed = GeoUtils::calculateSpeed(tracks[i], tracks[i+1]);
        speeds.push_back(speed);
    }

    double maxSpeed = *std::max_element(speeds.begin(), speeds.end());
    int numBins = static_cast<int>(std::ceil(maxSpeed / binSize)) + 1;

    std::map<std::pair<double, double>, double> distribution;
    for (int i = 0; i < numBins; ++i) {
        double lower = i * binSize;
        double upper = (i + 1) * binSize;
        distribution[{lower, upper}] = 0.0;
    }

    for (size_t i = 0; i < tracks.size() - 1; ++i) {
        double speed = speeds[i];
        double timeDiff = difftime(tracks[i+1].timestamp, tracks[i].timestamp);

        int binIndex = static_cast<int>(std::floor(speed / binSize));
        double lower = binIndex * binSize;
        double upper = (binIndex + 1) * binSize;

        distribution[{lower, upper}] += timeDiff;
    }

    speedDistribution.clear();
    for (const auto& entry : distribution) {
        if (entry.second > 0) {
            speedDistribution.emplace_back(entry);
        }
    }

    return 0;
}