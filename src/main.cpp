#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

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

int main(int argc, char* argv[]) {
    fs::path filePath = argv[1];
    std::string fileName = filePath.stem().string();
    std::ifstream file(filePath, std::ios::binary);
    std::vector<char> data;

    char tint;
    std::cout << "> Which tint colour do you want to switch to? (A, B, C, or D)\n";
    std::cin >> tint;
    std::cout << "> Changing \"" + fileName + ".xfbin\" file data to Tint Colour " << tint << "...\n\n";

    int tintNumber = tint - 0x11;
    std::string outputFileName = stringRange(fileName, 0, 5) + "col" + (char)tintNumber + ".xfbin";
    std::ofstream output(outputFileName, std::ios::binary);

    for (int i = 0; file.peek() != EOF; i++) {
        data.push_back(file.get());
        if (isAnyOf(arrayRange(data, i - 4, i - 1), "_s_#", "_d_#")) {
            data[i] = tintNumber;
        }
        output << data[i];
    }
    std::cout << "> Conversion successful! File has been output as \"" << outputFileName << "\".\n\n";

    std::cout << "> ";
    system("pause");
}