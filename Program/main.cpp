#include "searchlib.h"

int main() {
    //Set basic configuration to a program
    SetConsoleOutputCP(CP_UTF8);
    std::string searchPath = R"(C:\)";

    //Program Interface basic
    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;
    std::cout << "Searching for file '" << fileName << "'..." << '\n';

    //Searching
    std::string Result_path;
    searchFile(fileName, searchPath, Result_path);

    //Output result and end
    if (!Result_path.empty()) {
        std::cout << '\n' << "File '" << fileName << "' find file by way: " << Result_path << std::endl;
    } else {
        std::cout << '\n' << "File '" << fileName << "' not found." << std::endl;
    }

    system("pause");
    return 0;
}