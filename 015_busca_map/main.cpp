#include <sstream>
#include "agenda.hpp"

int main(){
    AGENDA agenda;
    std::cout << "SUA AGENDA" << std::endl;

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
            std::cout << agenda.show() << std::endl;
        }
        else if (cmd == "add") {
            std::string nome;
            std::string operadora;
            std::string numero;
            ss >> nome >> operadora >> numero;
            agenda.addContato(nome, operadora, numero);
        }
        else if (cmd == "rmFone") {
            std::string nome {};
            int indice {};
            ss >> nome >> indice;
            agenda.rmFone(nome, indice);
        }
        else if (cmd == "rm") {
            std::string nome {};
            ss >> nome;
            agenda.rm(nome);
        }
        else if (cmd == "search") {
            std::string proc {};
            ss >> proc;
            agenda.search(proc);
        }
        else {
            std::cout << "fail: comando invalido" << std::endl;
        }
    }

    return 0;
}