#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cctype>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

// functions.cpp

std::string arrayRange(std::vector<char>& array, int start, int end);
std::string stringRange(std::string& text, int start,   int end);

template<typename T, typename ... Cs>
constexpr bool isAnyOf(const T& cmp, const Cs& ... others) {
    return ((cmp == others) || ...);
}

void pause(std::string spaces = "");
void error(std::string message);

// json.cpp

void ReadXfbin(std::ifstream& file, std::vector<char>& data);
void CreateXfbin(std::ofstream& file, std::vector<char>& data, std::string fileName);


//convert.cpp

int LetterToNumber(char letter);
std::string GetOutputFileName(std::string inputFileName, int tint);