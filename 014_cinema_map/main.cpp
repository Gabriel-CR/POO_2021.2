#include "cinema.hpp"

int main(){
    SALA sistema;
    std::cout << "SEU SISTEMA ESTA PRONTO" << std::endl;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
            int tamCadeiras {0};
            ss >> tamCadeiras;
            sistema.init(tamCadeiras);
        }
        else if (cmd == "show") {
            std::cout << sistema.show() << std::endl;
        }
        else if (cmd == "reservar") {
            std::string nome {};
            int fone {};
            int cadeira {};
            ss >> nome >> fone >> cadeira;
            sistema.reservar(std::make_shared<CLIENTE>(nome, fone), cadeira);
        }
        else if (cmd == "cancelar") {
            std::string nome;
            ss >> nome;
            sistema.cancelar(nome);
        }
        else {
            std::cout << "fail: comando invalido" << std::endl;
        }
    }

    return 0;
}