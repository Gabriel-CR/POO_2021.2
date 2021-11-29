#include "contato.hpp"

CONTATO::CONTATO(std::string nome, FONE f) : nome{nome}{
    if (f.validacao(f.getNumero()) == true) {
        fones.push_back(f);
    }
    else {
        std::cout << "fail: numero invalido" << std::endl;
    }
};

std::string CONTATO::toString(){
    std::string os {"- " + nome + " "};
    for (int i=0; i < (int)fones.size(); i++) {
        os += "[" + std::to_string(i) + ":" + fones[i].toString() + "] ";
    }
    return os;
}

void CONTATO::setNome(std::string nome){
    this->nome = nome;
}

std::string CONTATO::getNome(){
    return this->nome;
}

void CONTATO::setFone(FONE f){
    if (f.validacao(f.getNumero()) == true) {
        fones.push_back(f);
    }
    else {
        f.validacao(f.getNumero());
    }
}

std::string CONTATO::getFone(int indice){
    return this->fones[indice].getNumero();
}

int CONTATO::getQtdFones(){
    return this->fones.size();
}

void CONTATO::removeFone(int indice){
    this->fones.erase(fones.begin() + indice);
}