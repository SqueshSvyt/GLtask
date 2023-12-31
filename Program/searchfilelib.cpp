#include "searchlib.h"

namespace fs = std::filesystem;

std::ofstream exeptionfile("Exeptionhandler.txt");

const unsigned int MaxThreads = std::thread::hardware_concurrency() > 8 ? 8 : std::thread::hardware_concurrency();

bool isHidden(const CHAR *filePath) {
    DWORD attributes = GetFileAttributes(filePath);

    if (attributes & FILE_ATTRIBUTE_HIDDEN)
        return true;

    return false;
}

void JoinThreads(std::vector<std::thread> &threads){
    for(auto &thread : threads)
        thread.join();
}

std::string GetFileNameWithoutExtension(const std::string& filename) {
    std::string::size_type lastDotPos = filename.find_last_of('.');

    if (lastDotPos != std::string::npos) {
        return filename.substr(0, lastDotPos);
    }

    return filename;
}

bool EqualWithoutExtension(const std::string& filename1, const std::string& filename2) {
    return GetFileNameWithoutExtension(filename1) == GetFileNameWithoutExtension(filename2);
}

void searchFileDeep(const std::string& fileName, const std::string& searchPath, std::string& Result_path) {
    for (const auto& entry : fs::directory_iterator(searchPath)) {
        if(!Result_path.empty()) return;

        if(entry.is_directory() && entry.exists()){

            try{
                searchFileDeep(fileName, entry.path().string(), Result_path);
            }

            catch (const fs::filesystem_error& e){
                exeptionfile << e.what() << '\n';
            }
        }

        if (entry.is_regular_file() && EqualWithoutExtension(entry.path().filename().string(), fileName))
            Result_path = entry.path().string();
    }
}

std::string searchFile(const std::string& fileName, const std::string& searchPath){
    //Result param
    std::string Result_path;
    //Clear file before run
    exeptionfile.clear();
    //Add list to save threads
    std::vector<std::thread> threads;

    for (const auto& entry : fs::directory_iterator(searchPath)) {
        if(!Result_path.empty()){
            JoinThreads(threads);
            return Result_path;
        }
        if(entry.is_directory() && entry.exists()){
            try{
                if(isHidden(entry.path().string().c_str())) continue;

                if(threads.size() >= MaxThreads - 1){
                    JoinThreads(threads);
                    threads.clear();
                }

                else
                    threads.emplace_back(searchFileDeep, std::ref(fileName), entry.path().string(), std::ref(Result_path));

            }
            catch (const fs::filesystem_error& e){
                exeptionfile << e.what() << '\n';
            }
        }
        if (entry.is_regular_file() && EqualWithoutExtension(entry.path().filename().string(), fileName))
            Result_path = entry.path().string();
    }

    JoinThreads(threads);
    return Result_path;
}

