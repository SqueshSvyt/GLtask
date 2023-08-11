#ifndef FILESYSTEM_SEARCHER_H
#define FILESYSTEM_SEARCHER_H

#include <string>
#include <filesystem>
#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>
#include <fstream>

std::string searchFile(const std::string& fileName, const std::string& searchPath);

#endif