#include "reporter.h"
#include <iostream>
#include <fstream>

void ConsoleReporter::write(const std::string& message) {
    std::cout << message << std::endl;
}

FileReporter::FileReporter(const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing");
    }
}

void FileReporter::write(const std::string& message) {
    file << message << std::endl;
}

FileReporter::~FileReporter() {
    if (file.is_open()) {
        file.close();
    }
}