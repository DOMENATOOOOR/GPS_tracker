#ifndef TRACK_ANALYZER_H
#define TRACK_ANALYZER_H

#include <vector>
#include "geo_utils.h"
#include "metric_calculators.h"
#include "reporter.h"

class TrackAnalyzer {
private:
    std::vector<TrackPoint> tracks;
    Reporter* reporter;  
    bool ownsReporter;

public:
    
    explicit TrackAnalyzer(const std::string& filepath, Reporter* reporter = nullptr, bool takeOwnership = false);
    ~TrackAnalyzer();  
    
    void analyzeAndReport();
    double getTotalDistance();
    double getTotalTime();
    double getAverageSpeed();
    double getMovingTime();
    double getStoppingTime();
    double getMaxSpeed();
    double getMinSpeed();
    double getMinElevation();
    double getMaxElevation();
    double getTotalAscent();
    double getTotalDescent();
    void printSpeedDistribution(double binSize = 0.5);
};

#endif // TRACK_ANALYZER_H
