#include "header.h"

std::string arrayRange(std::vector<char>& array, int start, int end) {
    std::string buffer = "";
    for (int i = start; i < end + 1; i++) {
        buffer += array[i];
    }
    return buffer;
}

std::string stringRange(std::string& str, int start, int end) {
    if (start < str.size() && end <= str.size() && start <= end) {
        return str.substr(start, end - start);
    } else {
        return ""; // Return an empty string if indices are out of bounds
    }
}

bool isInt(char c) {
    return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

void pause(std::string spaces) {
    std::cout << spaces << "> ";
    system("pause");
}

void error(std::string message) {
    std::cerr << "\033[31m" << "> ERROR: " << message << "\033[0m";
}