//
// Created by YangLinzhuo on 2023/12/19.
//

#include <common.h>

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class logger {
    fs::path log_path;
    std::ofstream log_file;
public:
    logger()
    {
        auto name = uuids::to_string(uuids::uuid_random_generator{}());
        log_path = fs::temp_directory_path() / (name + ".tmp");
        log_file.open(log_path.c_str(), std::ios::out | std::ios::trunc);
    }
    ~logger() noexcept
    {
        try {
            if(log_file.is_open()) log_file.close();
            if (!log_path.empty()) fs::remove(log_path);
        }
        catch (...) {}
    }
    void persist(fs::path const & path)
    {
        log_file.close();
        fs::rename(log_path, path);
        log_path.clear();
    }
    logger& operator<<(std::string_view message)
    {
        log_file << message.data() << '\n';
        return *this;
    }
};

int main()
{
    logger log;
    try
    {
        log << "this is a line" << "and this is another one";
        throw std::runtime_error("error");
    }
    catch (...)
    {
        log.persist(R"(lastlog.txt)");
    }
    return 0;
}
