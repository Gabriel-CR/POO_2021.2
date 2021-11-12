#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

class CLIENTE{
    std::string nome;
    int telefone;

public:
    CLIENTE(std::string nome = "", int telefone = 0) : nome{nome}, telefone{telefone} {}

    std::string getNome(){ return this->nome; }
    int getTelefone(){ return this->telefone; }

    void setTelefone(int fone){ this->telefone = fone; }
    void setNome(std::string nome){ this->nome = nome; }

    friend std::ostream& operator<<(std::ostream& os, const CLIENTE& c){
        os << c.nome << ":" << c.telefone << " ";
        return os;
    }
};

class SALA{
    std::shared_ptr<std::vector<CLIENTE>> cadeiras;
    int maxCadeiras {};

public:
    SALA(int cadeiras = 0) : maxCadeiras{cadeiras} {}

    void init(int maxCadeiras) { this->maxCadeiras = maxCadeiras; }

    void show(){
        if (cadeiras == nullptr) {
            std::cout << "[ ";
            for (int i = 0; i < maxCadeiras; i++) {
                std::cout << "- ";
            }
            std::cout << "]" << std::endl;
        }
        else {
            std::cout << "[ ";
            std:: cout << "]" << std::endl;
        }
    }

    void reservar(const std::shared_ptr<CLIENTE>& c, int cadeira){
        this->cadeiras[cadeira] = c;
    }
};

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
            sistema.show();
        }
        else if (cmd == "reservar") {
            std::string nome {};
            int fone {};
            int cadeira {};
            ss >> nome >> fone >> cadeira;
            CLIENTE aux(nome, fone);
            sistema.reservar(aux, cadeira);
        }
    }

    return 0;
}