#pragma once
#include <iostream>
#include <vector>
#include <string>

struct ErrorEntry {
    std::string module;
    int line;
    int column;
    std::string message;

    ErrorEntry(const std::string& mod, int ln, int col, const std::string& msg)
        : module(mod), line(ln), column(col), message(msg) {
    }
};

class ErrorLogger {
private:
    std::vector<ErrorEntry> errors;
    std::vector<ErrorEntry> warnings;

public:
    void logError(const std::string& module, int line, int column, const std::string& message);

    void printErrors() const;

    bool hasErrors() const;

    void logWarning(const std::string& module, int line, int column, const std::string& message);

    void clear();
};

extern ErrorLogger errorLogger;
