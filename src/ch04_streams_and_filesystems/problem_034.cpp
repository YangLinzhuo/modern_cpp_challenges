//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void remove_empty_lines(fs::path filepath) {
    std::ifstream filein(filepath.native(), std::ios::in);
    if (!filein.is_open())
        throw std::runtime_error("cannot open input file");
    auto tmp_path = fs::temp_directory_path() / "temp.txt";
    std::ofstream fileout(tmp_path.native(), std::ios::out | std::ios::trunc);
    if (!fileout.is_open())
        throw std::runtime_error("cannot create temporary file");
    std::string line;
    while (std::getline(filein, line)) {
        if (line.length() > 0 &&
            line.find_first_not_of(' ') != std::string::npos) {
            fileout << line << '\n';
        }
    }
    filein.close();
    fileout.close();
    fs::remove(filepath);
    fs::rename(tmp_path, filepath);
}