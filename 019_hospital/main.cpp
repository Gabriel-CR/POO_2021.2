#include "hospital.hpp"
#include <sstream>

int main(){
    Hospital sistema;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        try {
            if (cmd == "end") {
                break;
            }
            else if (cmd == "show") {
                std::cout << sistema << std::endl;
            }
            else {
                std::cout << "fail: Comando invalido" << std::endl;
            }
        }
        catch(std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}