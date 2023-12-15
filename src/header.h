#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cctype>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::ordered_json;

// functions.cpp

std::string arrayRange(std::vector<char>& array, int start, int end);
std::string stringRange(std::string& text, int start, int end);

template<typename T, typename ... Cs>
constexpr bool isAnyOf(const T& cmp, const Cs& ... others) {
    return ((cmp == others) || ...);
}

bool isInt(char s);

void pause(std::string spaces = "");
void error(std::string message);

// json.cpp

void ReadXfbin(std::ifstream& file, std::vector<char>& data);
void CreateXfbin(std::ofstream& file, std::vector<char>& data, std::string fileName);
void LoadJson(std::fstream& file, json& data, std::string directory);
void ReOpenFile(std::fstream& file, std::string path);
void DeployJson(std::fstream& file, json& data, std::string in_directory, std::string out_directory);

//convert.cpp

std::string LetterToNumber(char letter);
char NumberToLetter(std::string val);
std::string GetXfbinType(std::string file);
char GetXfbinAlt(std::string file);
std::string GetOutputFileName(std::string inputFileName, std::string tint);