#include "header.h"

void ReadXfbin(std::ifstream& file, std::vector<char>& data) {
    data.clear();
    for (int i = 0; file.peek() != EOF; i++) {
        data.push_back(file.get());
    }

    if (arrayRange(data, 0, 3) != "NUCC") {
        error("Magic \"NUCC\" could not be found. File is either encrypted or invalid.\n\n");
        pause(); std::exit(0);
    }
}

void CreateXfbin(std::ofstream& file, std::vector<char>& data, std::string fileName) {
    // Create output file and write modified data to it
    file.open(fileName, std::ios::binary);
    for (int i = 0; i < data.size(); i++) {
        file << data[i];
    }
}