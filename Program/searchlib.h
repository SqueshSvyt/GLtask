#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include <string>
#include <filesystem>
#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>

void searchFile(const std::string& fileName, const std::string& searchPath, std::string& Result_path);

#endif