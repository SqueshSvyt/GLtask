#include "searchlib.h"

namespace fs = std::filesystem;

const unsigned int MaxThreads = std::thread::hardware_concurrency() > 8 ? 8 : std::thread::hardware_concurrency();

void JoinThreads(std::vector<std::thread> &threads){
    for(auto &thread : threads)
        thread.join();
}

std::string GetFileNameWithoutExtension(const std::string& filename) {
    char lastDotPos = filename.find_last_of(".");

    if (lastDotPos != std::string::npos) {
        return filename.substr(0, lastDotPos);
    }

    return filename;
}

bool EqualWithoutExtension(const std::string& filename1, const std::string& filename2) {
    return GetFileNameWithoutExtension(filename1) == GetFileNameWithoutExtension(filename2);
}

void searchFileDeep(const std::string& fileName, const std::string& searchPath, std::string& Result_path) {
    for (const auto& entry : fs::recursive_directory_iterator(searchPath)) {
        if(!Result_path.empty()) return;

        if(entry.is_directory()){

            try{
                searchFileDeep(fileName, entry.path().string(), Result_path);
            }

            catch (const std::exception& e){
                std::cout << '\n' << e.what();
            }

        }

        if (entry.is_regular_file() && EqualWithoutExtension(entry.path().filename().string(), fileName))
            Result_path = entry.path().string();
    }
}

void searchFile(const std::string& fileName, const std::string& searchPath, std::string& Result_path){
    //Build threads vector to control thread
    std::vector<std::thread> threads;

    //Start Finding file
    for (const auto& entry : fs::recursive_directory_iterator(searchPath)) {
        if(!Result_path.empty()){
            JoinThreads(threads);
            return;
        }
        if(entry.is_directory()){
            try{

                if(threads.size() >= MaxThreads - 1){
                    JoinThreads(threads);
                    threads.clear();
                }

                else
                    threads.emplace_back(searchFileDeep, std::ref(fileName), entry.path().string(), std::ref(Result_path));

            }
            catch (const std::exception& e){
                std::cout << '\n' << e.what();
            }
        }
        if (entry.is_regular_file() && EqualWithoutExtension(entry.path().filename().string(), fileName))
            Result_path = entry.path().string();
    }
    JoinThreads(threads);
}

