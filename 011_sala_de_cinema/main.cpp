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

    std::string toString(){
        std::string os {nome + ":" + std::to_string(telefone) + " "};
        return os;
    }
};

class SALA{
    std::vector<std::shared_ptr<CLIENTE>> cadeiras;
    int maxCadeiras {};

public:
    SALA(int cadeiras = 0) : maxCadeiras{cadeiras} {}

    void init(int maxCadeiras) {
        this->maxCadeiras = maxCadeiras;
        for (int i = 0; i < maxCadeiras; i++)
            cadeiras.push_back(nullptr);
    }

    std::string show(){
        std::string os {"[ "};
        for (int i = 0; i < this->maxCadeiras; i++) {
            if (this->cadeiras[i] != nullptr) {
                os += cadeiras[i]->toString();
            }
            else {
                os += "- ";
            }
        }
        os += "]";
        return os;
    }

    void reservar(const std::shared_ptr<CLIENTE>& c, int cadeira){
        if (cadeiras[cadeira] == nullptr) {
            this->cadeiras[cadeira] = c;
        }
        else {
            std::cout << "fail: cadeira ocupada" << std::endl;
        }
    }

    void cancelar(const std::string& nome){
        bool ver = false;

        for (int i = 0; i < (int)cadeiras.size(); i++) {
            if (cadeiras[i]->getNome() == nome) {
                cadeiras[i] = nullptr;
                ver = true;
            }
        }
        if (ver == false) {
            std::cout << "fail: cliente nao esta na sala" << std::endl;
        }
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