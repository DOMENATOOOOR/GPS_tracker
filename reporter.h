#ifndef REPORTER_H
#define REPORTER_H

#include <fstream>

class Reporter {
public:
    virtual void write(const std::string& message) = 0;
    virtual ~Reporter() = default;
};

class ConsoleReporter : public Reporter {
public:
    void write(const std::string& message) override;
};

class FileReporter : public Reporter {
    std::ofstream file;
public:
    explicit FileReporter(const std::string& filename);
    void write(const std::string& message) override;
    ~FileReporter() override;
};

#endif // REPORTER_H