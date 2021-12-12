#include "geometria.hpp"

int main(){
    QUADRADO qua;
    TRIANGULO tri;
    RETANGULO ret;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "show") {
            std::string forma;
            ss >> forma;
            if (forma == "q") {
                std::cout << "[QUADRADO]\n" << qua.toString() << std::endl;
            }
            else if (forma == "t") {
                std::cout << "[TRIANGULO]\n" << tri.toString() << std::endl;
            }
            else if (forma == "r") {
                std::cout << "[RETANGULO]\n" << ret.toString() << std::endl;
            }
            else {
                std::cout << "fai: forma invalida" << std::endl;
            }
        }
        else {
            std::cout << "fai: comando invalido" << std::endl;
        }
    }

    return 0;
}