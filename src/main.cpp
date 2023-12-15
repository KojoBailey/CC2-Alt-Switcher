#include "header.h"

int main(int argc, char* argv[]) {

    // Create JSON if it does not exist, or open it if existing
    json json_data;
    std::string json_name = "_alt_manager.json";
    if (!fs::exists(json_name)) {
        std::ofstream new_json(json_name);
        new_json.close();
    }
    std::fstream json_file(json_name, std::ios::in | std::ios::out);

    // Load directory information into JSON
    std::string input_directory = fs::current_path().string();
    if (fs::exists(input_directory) || input_directory == "") {
        LoadJson(json_file, json_data, input_directory);
    } else {
        error("Could not locate \"" + input_directory + "\" directory.\n\n");
        pause(); return 0;
    }
    ReOpenFile(json_file, json_name);

    // Deploy JSON information
    std::string output_directory = "../data_win32/spc/";
    if (fs::exists(output_directory)) {
        DeployJson(json_file, json_data, input_directory, output_directory);
    } else {
        error("Could not locate \"" + output_directory + "\" directory.\n\n");
        pause(); return 0;
    }

    std::cout << "\033[32m> Files have been successfully deployed (probably).\033[0m\n\n";

    pause();
}