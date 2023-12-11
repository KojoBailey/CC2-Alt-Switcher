#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cctype>

namespace fs = std::filesystem;

std::string arrayRange(std::vector<char>& array, int start, int end) {
    std::string buffer = "";
    for (int i = start; i < end + 1; i++) {
        buffer += array[i];
    }
    return buffer;
}

std::string stringRange(std::string& text, int start, int end) {
    std::string buffer = "";
    for (int i = start; i < end + 1; i++) {
        buffer += text.at(i);
    }
    return buffer;
}

template<typename T, typename ... Cs>
constexpr bool isAnyOf(const T& cmp, const Cs& ... others) {
    return ((cmp == others) || ...);
}

void pause(std::string spaces = "") {
    std::cout << spaces << "> ";
    system("pause");
}

void error(std::string message) {
    std::cerr << "\033[31m" << "> ERROR: " << message << "\033[0m";
    // TBC: make this red
}

int main(int argc, char* argv[]) {
    // Check if file has been drag-&-dropped
    if (argc < 2) {
        error("To use this tool, drag&drop the file you want to convert onto this EXE.\n\n");
        pause(); return 0;
    }

    // Get dropped file
    fs::path filePath = argv[1];
    std::string fileName = filePath.stem().string();
    std::ifstream file(filePath, std::ios::binary);
    std::vector<char> data;

    // Ask for Tint to switch to
    char tint;
    std::cout << "> Which tint colour do you want to switch to? (A - J)\n";
    std::cin >> tint;
    std::cout << "> Changing \"" + fileName + ".xfbin\" file data to Tint Colour " << (char)std::toupper(tint) << "...\n\n";

    // Convert given Tint to the corresponding integer value
    int tintNumber = (int)tint;
    if (tintNumber > 0x60 && tintNumber < 0x6B) {
        tintNumber -= 0x31;
    } else if (tintNumber > 0x40 && tintNumber < 0x4B) {
        tintNumber -= 0x11;
    } else {
        error("Invalid Tint letter. Must be an English letter between A-J.\n\n");
        pause(); return 0;
    }
    std::string outputFileName = stringRange(fileName, 0, 5) + "col" + (char)tintNumber + ".xfbin";

    // Read through file and store to vector, swapping byte values as needed
    for (int i = 0; file.peek() != EOF; i++) {
        data.push_back(file.get());
        if (isAnyOf(arrayRange(data, i - 4, i - 1), "_s_#", "_d_#")) {
            data[i] = tintNumber;
        }
    }

    // Check if file is actually unencrypted
    if (arrayRange(data, 0, 3) != "NUCC") {
        error("\"NUCC\" could not be found. File is either encrypted or invalid.\n\n");
        pause(); return 0;
    }

    // Create output file and send modified data to it
    std::ofstream output(outputFileName, std::ios::binary);
    for (int i = 0; i < data.size(); i++) {
        output << data[i];
    }
    std::cout << "\033[32m> Conversion successful! File has been output as \"" << outputFileName << "\".\033[0m\n\n";

    pause();
}