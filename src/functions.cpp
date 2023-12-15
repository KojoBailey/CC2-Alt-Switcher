#include "header.h"

std::string arrayRange(std::vector<char>& array, int start, int end) {
    std::string buffer = "";
    for (int i = start; i < end + 1; i++) {
        buffer += array[i];
    }
    return buffer;
}

std::string stringRange(std::string& text, int start,   int end) {
    std::string buffer = "";
    for (int i = start; i < end + 1; i++) {
        buffer += text.at(i);
    }
    return buffer;
}

void pause(std::string spaces) {
    std::cout << spaces << "> ";
    system("pause");
}

void error(std::string message) {
    std::cerr << "\033[31m" << "> ERROR: " << message << "\033[0m";
}