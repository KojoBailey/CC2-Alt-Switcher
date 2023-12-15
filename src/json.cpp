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

void LoadJson(std::fstream& file, json& data, std::string directory) {
    // Get list of XFBINs in directory
    std::vector<std::string> xfbin;
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension().string() == ".xfbin") {
            xfbin.push_back(entry.path().filename().string());
        }
    }
    
    // Add any "col" XFBINs to JSON
    for (const auto& entry : xfbin) {
        if (GetXfbinType(entry) == "col") {
            data[entry]["Tint"] = std::string(1, GetXfbinAlt(entry));
            data[entry]["Deployed?"] = 0;
        }
    }

    // Merge current JSON with current directory data
    json old_json;
    if (file.peek() != EOF) {
        old_json = json::parse(file);
        for (const auto& entry : old_json.items()) {
            if (!fs::exists(entry.key())) {
                old_json.erase(entry.key());
            }
        }
        data.merge_patch(old_json);
    }
}

void ReOpenFile(std::fstream& file, std::string path) {
    file.close();
    std::ofstream temp(path);
    temp.close();
    file.open(path, std::ios::in | std::ios::out);
}

void DeployJson(std::fstream& file, json& data, std::string in_directory, std::string out_directory) {
    std::ifstream in_xfbin;
    std::ofstream out_xfbin;
    std::vector<char> xfbin_data;

    std::string xfbin_name;
    std::string key;
    std::string tintNumber;

    for (auto& entry : data.items()) {
        key = entry.key();
        auto& entry_obj = data[key];
        tintNumber = LetterToNumber(std::string(entry_obj["Tint"]).at(0));
        in_xfbin.open(in_directory + "\\" + key, std::ios::binary);
        out_xfbin.open(out_directory + GetOutputFileName(key, tintNumber), std::ios::binary);

        for (int i = 0; in_xfbin.peek() != EOF; i++) {
            xfbin_data.push_back(in_xfbin.get());
            if (isAnyOf(arrayRange(xfbin_data, i-4, i-1), "_s_#", "_d_#")) {
                xfbin_data[i] = tintNumber.at(0);
            }

            out_xfbin << xfbin_data[i];
        }

        entry_obj["Deployed?"] = 1;
        in_xfbin.close();
        out_xfbin.close();
    }
    
    file << data.dump(2);
}