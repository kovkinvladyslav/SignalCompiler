#include <Lexer/Error.h>

ErrorLogger errorLogger;

void ErrorLogger::logError(const std::string& module, int line, int column, const std::string& message) {
    errors.emplace_back(module, line, column, message);
}

void ErrorLogger::logWarning(const std::string& module, int line, int column, const std::string& message) {
    warnings.emplace_back(module, line, column, message);
}

void ErrorLogger::printErrors() const {
    if (errors.empty()) {
        std::cout << "No errors found.\n";
        return;
    }

    for (const auto& error : errors) {
        std::cerr << error.module << ": Error (Line "
            << error.line << ", Column " << error.column << "): "
            << error.message << std::endl;
    }
}

bool ErrorLogger::hasErrors() const {
    return !errors.empty();
}

void ErrorLogger::clear()
{
    errors.clear();
}
