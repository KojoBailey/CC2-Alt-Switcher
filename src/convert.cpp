#include "header.h"

int LetterToNumber(char letter) {
    int number = (int)letter;
    if (number > 0x60 && number < 0x6B) {
        number -= 0x31;
    } else if (number > 0x40 && number < 0x4B) {
        number -= 0x11;
    } else {
        error("Invalid Tint letter. Must be an English letter between A-J.\n\n");
        pause(); std::exit(0);
    }
    return number;
}

std::string GetOutputFileName(std::string inputFileName, int tint) {
    std::string outputFileName = stringRange(inputFileName, 0, 5) + "col";
    if (inputFileName.at(inputFileName.length() - 2) == 'l') {
        outputFileName += (char)tint + ".xfbin";
    } else {
        outputFileName += inputFileName.at(inputFileName.length() - 2) + (char)tint + ".xfbin";
    }
    return outputFileName;
}