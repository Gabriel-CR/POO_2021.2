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

    void init(int maxCadeiras){
        this->maxCadeiras = maxCadeiras;
        for (int i = 0; i < maxCadeiras; i++)
            this->cadeiras.push_back(nullptr);
    }

    std::pair<bool, int> procurarPessoa(std::string nome){
        bool res = false;
        int pos {0};
        for (int i = 0; i < (int)cadeiras.size(); i++) {
            if (cadeiras[i] != nullptr && cadeiras[i]->getNome() == nome) {
                res = true;
                pos = i;
                return std::make_pair(res, pos);
            }
        }
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
        if (procurarPessoa(c->getNome()).first == false && cadeiras[cadeira] == nullptr)
            this->cadeiras[cadeira] = c;
        else if (procurarPessoa(c->getNome()).first == true)
            std::cout << "fail: pessoa ja esta na sala" << std::endl;
        else
            std::cout << "fail: cadeira ocupada" << std::endl;
    }

    void cancelar(const std::string& nome){
        if (procurarPessoa(nome).first == true)
            this->cadeiras[procurarPessoa(nome).second] = nullptr;
        else
            std::cout << "fail: cliente nao esta na sala" << std::endl;
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