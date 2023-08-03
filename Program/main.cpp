#include "searchlib.h"

int main() {
    //Set basic configuration to a program
    SetConsoleOutputCP(CP_UTF8);
    std::string searchPath = R"(C:\)";

    //Program Interface basic
    while (true) {
        std::cout << "Select an option:" << std::endl;
        std::cout << "1. Run Search" << std::endl;
        std::cout << "2. Exit the Program" << std::endl;
        std::string fileName;
        std::string Result_path;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                fileName = "";
                std::cout << "Enter file name: ";
                std::cin >> fileName;
                std::cout << "Searching for file '" << fileName << "'..." << '\n';

                //Searching
                Result_path = "";
                searchFile(fileName, searchPath, Result_path);


                //Output result and end
                if (!Result_path.empty()) {
                    std::cout << '\n' << "File '" << fileName << "' find file by way: " << Result_path << std::endl;
                } else {
                    std::cout << '\n' << "File '" << fileName << "' not found." << std::endl;
                }


                system("pause");
                break;
            case 2:
                std::cout << "Thank you for using the program. Goodbye!" << std::endl;
                return 0; // Exit the program
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}