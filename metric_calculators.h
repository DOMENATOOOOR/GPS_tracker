#ifndef METRIC_CALCULATORS_H
#define METRIC_CALCULATORS_H

#include <vector>
#include "geo_utils.h"

class IMetricCalculator {
public:
    virtual double calculate(const std::vector<TrackPoint>& tracks) = 0;
    virtual ~IMetricCalculator() = default;
};

class AllDistanceCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class AllTimeCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class AverageSpeedCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class MovingTimeCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class StoppingTimeCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class MaxSpeedCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class MinSpeedCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class MinElevationCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class MaxElevationCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class TotalAscentCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class TotalDescentCalculator : public IMetricCalculator {
public:
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

class SpeedDistributionCalculator : public IMetricCalculator {
private:
    std::vector<std::pair<std::pair<double, double>, double>> speedDistribution;
    double binSize;

public:
    explicit SpeedDistributionCalculator(double binSize = 1.0);
    [[nodiscard]] std::vector<std::pair<std::pair<double, double>, double>> getSpeedDistribution() const;
    double calculate(const std::vector<TrackPoint>& tracks) override;
};

#endif // METRIC_CALCULATORS_H