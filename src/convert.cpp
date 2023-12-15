#include "header.h"

std::string LetterToNumber(char letter) {
    int number = (int)letter;
    if (number > 0x60 && number < 0x6B) {
        number -= 0x31;
    } else if (number > 0x40 && number < 0x4B) {
        number -= 0x11;
    } else {
        error("Invalid Tint letter. Must be an English letter between A-J.\n\n");
        pause(); std::exit(0);
    }
    return std::string(1, (char)number);
}

char NumberToLetter(std::string val) {
    return (char)(std::stoi(val) + 0x41);
}

std::string GetXfbinType(std::string file) {
    if (file.find("col") != std::string::npos) {
        return "col";
    } else {
        return "";
    }
}

char GetXfbinAlt(std::string file) {
    int i = 1;
    for (i; !isInt(file.at(i)); i++);
    for (i; isInt(file.at(i)); i++);
    for (i; !isInt(file.at(i)); i++);

    std::string output;
    for (i; isInt(file.at(i)); i++) {
        output = file.at(i);
    }
    return NumberToLetter(output);
}

std::string GetOutputFileName(std::string inputFileName, std::string tint) {
    std::string outputFileName = stringRange(inputFileName, 0, 6) + "col" + tint + ".xfbin";
    // if (inputFileName.at(inputFileName.length() - 2) == 'l') {
    //     outputFileName += tint + ".xfbin";
    // } else {
    //     outputFileName += inputFileName.at(inputFileName.length() - 2) + tint + ".xfbin";
    // }
    return outputFileName;
}