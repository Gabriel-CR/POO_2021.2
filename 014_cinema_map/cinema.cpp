#include "cinema.hpp"

// CLIENTE

    CLIENTE::CLIENTE(std::string nome = "", int telefone = 0) : nome{nome}, telefone{telefone} {
        this->nome = nome;
        this->telefone = telefone;
    }

    std::string CLIENTE::getNome(){ return this->nome; }
    int CLIENTE::getTelefone(){ return this->telefone; }

    void CLIENTE::setTelefone(int fone){ this->telefone = fone; }
    void CLIENTE::setNome(std::string nome){ this->nome = nome; }

    std::string CLIENTE::toString(){
        std::string os {nome + ":" + std::to_string(telefone) + " "};
        return os;
    }

// SALA

    SALA::SALA(){}

    void SALA::init(int maxCadeiras){
        cadeiras.clear();
        this->maxCadeiras = maxCadeiras;
        for (int i = 0; i < maxCadeiras; i++)
            this->cadeiras.insert(std::make_pair(i, nullptr));
    }

    int SALA::procurarPessoa(std::string nome){
        int pos {-1};
        int i = 0;
        for (auto it : cadeiras) {
            if (it.second != nullptr && it.second->getNome() == nome) {
                pos = i;
                return pos;
            }
            i += 1;
        }
        return pos;
    }

    std::string SALA::show(){
        std::string os {"[ "};
        for (auto it : cadeiras) {
            if (it.second != nullptr) {
                os += it.second->toString();
            }
            else {
                os += "- ";
            }
        }
        os += "]";
        return os;
    }

    void SALA::reservar(const std::shared_ptr<CLIENTE>& c, int cadeira){
        if (procurarPessoa(c->getNome()) == -1 && cadeiras[cadeira] == nullptr)
            this->cadeiras[cadeira] = c;
        else if (procurarPessoa(c->getNome()) != -1)
            std::cout << "fail: pessoa ja esta na sala" << std::endl;
        else
            std::cout << "fail: cadeira ocupada" << std::endl;
    }

    void SALA::cancelar(const std::string& nome){
        if (procurarPessoa(nome) != -1)
            this->cadeiras[procurarPessoa(nome)] = nullptr;
        else
            std::cout << "fail: cliente nao esta na sala" << std::endl;
    }