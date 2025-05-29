#include "track_analyzer.h"
#include "track_data_provider.h"
#include <iomanip>
#include <sstream>

TrackAnalyzer::TrackAnalyzer(const std::string& filepath, Reporter* reporter, bool takeOwnership)
    : reporter(reporter ? reporter : new ConsoleReporter()),
      ownsReporter(reporter ? takeOwnership : true) {  
    TrackDataProvider dataProvider;
    tracks = dataProvider.getTracks(filepath);
}

TrackAnalyzer::~TrackAnalyzer() {
    if (ownsReporter) {
        delete reporter;
    }
}

void TrackAnalyzer::analyzeAndReport() {
    reporter->write("Track Analysis Results:");
    reporter->write("----------------------");
    
    reporter->write("Total distance: " + std::to_string(getTotalDistance()) + " meters");
    reporter->write("Total time: " + std::to_string(getTotalTime()) + " seconds");
    reporter->write("Average speed: " + std::to_string(getAverageSpeed()) + " m/s");
    reporter->write("Moving time: " + std::to_string(getMovingTime()) + " seconds");
    reporter->write("Stopping time: " + std::to_string(getStoppingTime()) + " seconds");
    reporter->write("Max speed: " + std::to_string(getMaxSpeed()) + " m/s");
    reporter->write("Min speed: " + std::to_string(getMinSpeed()) + " m/s");
    reporter->write("Min elevation: " + std::to_string(getMinElevation()) + " meters");
    reporter->write("Max elevation: " + std::to_string(getMaxElevation()) + " meters");
    reporter->write("Total ascent: " + std::to_string(getTotalAscent()) + " meters");
    reporter->write("Total descent: " + std::to_string(getTotalDescent()) + " meters");
    
    printSpeedDistribution();
}


double TrackAnalyzer::getTotalDistance() {
    AllDistanceCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getTotalTime() {
    AllTimeCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getAverageSpeed() {
    AverageSpeedCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getMovingTime() {
    MovingTimeCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getStoppingTime() {
    StoppingTimeCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getMaxSpeed() {
    MaxSpeedCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getMinSpeed() {
    MinSpeedCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getMinElevation() {
    MinElevationCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getMaxElevation() {
    MaxElevationCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getTotalAscent() {
    TotalAscentCalculator calculator;
    return calculator.calculate(tracks);
}

double TrackAnalyzer::getTotalDescent() {
    TotalDescentCalculator calculator;
    return calculator.calculate(tracks);
}

void TrackAnalyzer::printSpeedDistribution(double binSize) {
    SpeedDistributionCalculator analyzer(binSize);
    analyzer.calculate(tracks);
    auto distribution = analyzer.getSpeedDistribution();
    
    reporter->write("\nSpeed Distribution (m/s):");
    reporter->write("------------------------");
    
    for (const auto& [range, duration] : distribution) {
        auto [lower, upper] = range;
        
        int minutes = static_cast<int>(duration) / 60;
        int seconds = static_cast<int>(duration) % 60;
        
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1)
            << lower << "-" << upper << " m/s: "
            << minutes << " min " << seconds << " sec";
            
        reporter->write(oss.str());
    }
}
