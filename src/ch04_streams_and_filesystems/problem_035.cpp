//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>
#include <filesystem>

namespace fs = std::filesystem;

std::uintmax_t get_directory_size(fs::path const & dir,
                                  bool const follow_symlinks = false) {
    auto dir_options = follow_symlinks ? fs::directory_options::follow_directory_symlink : fs::directory_options::none;
    auto iterator = fs::recursive_directory_iterator(dir,dir_options);
    return std::accumulate(
            fs::begin(iterator), fs::end(iterator),
            0ull,   // Postfix is important!!
            [](std::uintmax_t const total,
               fs::directory_entry const & entry) {
                return total + (fs::is_regular_file(entry) ?
                                fs::file_size(entry.path()) : 0);
            });
}

int main()
{
    std::string path;
    std::cout << "Path: ";
    std::cin >> path;
    std::cout << "Size: " << get_directory_size(path) << std::endl;
    return 0;
}
