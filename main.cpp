#include "track_analyzer.h"
#include "reporter.h"
#include <iostream>

int main() {
    try {
        // Вариант 1: с reporter по умолчанию (ConsoleReporter)
        {
            TrackAnalyzer analyzer1("/Users/mac_aleksandr/Desktop/gps_data");
            analyzer1.analyzeAndReport();
        }

        // Вариант 2: с явным ConsoleReporter (не передаем владение)
        {
            ConsoleReporter consoleReporter;
            TrackAnalyzer analyzer2("/Users/mac_aleksandr/Desktop/gps_data", &consoleReporter, false);
            analyzer2.analyzeAndReport();
        }

        // Вариант 3: с FileReporter (не передаем владение)
        {
            FileReporter fileReporter("output.txt");
            TrackAnalyzer analyzer3("/Users/mac_aleksandr/Desktop/gps_data", &fileReporter, false);
            analyzer3.analyzeAndReport();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}