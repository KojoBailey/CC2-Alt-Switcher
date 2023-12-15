#include "header.h"

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

    // // Ask for Tint to switch to
    // char tint;
    // std::cout << "> Which tint colour do you want to switch to? (A - J)\n";
    // std::cin >> tint;
    // std::cout << "> Changing \"" + fileName + ".xfbin\" file data to Tint Colour " << (char)std::toupper(tint) << "...\n\n";

    // Read through file and store to vector
    ReadXfbin(file, data);

    // Create JSON if it does not exist, or open it if existing
    if (!fs::exists("alt_manager.json")) {
        std::ofstream new_json("alt_manager.json");
        new_json.close();
    }
    std::fstream json_file("alt_manager.json", std::ios::in | std::ios::out);

    // Create output XBFBIN
    std::ofstream output;
    CreateXfbin(output, data, GetOutputFileName(fileName, 0));

    std::cout << "\033[32m> Conversion successful! File has been output as \"" << GetOutputFileName(fileName, 0) << "\".\033[0m\n\n";
    file.close();
    // fs::remove(filePath);

    pause();
}