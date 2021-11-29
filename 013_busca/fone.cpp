#include "fone.hpp"

FONE::FONE(std::string id = "", std::string numero = "") : operadora{id}, numero{numero} {
}

std::string FONE::toString(){
    std::string os {operadora + ":" + numero};
    return os;
}

bool FONE::validacao(std::string numero){
    std::string::iterator it1;
    std::string::iterator it2;
    std::string aux {"0123456789()."};
    int ver {0};

    for (it1 = numero.begin(); it1 != numero.end(); ++it1) {
        for (it2 = aux.begin(); it2 != aux.end(); ++it2) {
            if (*it1 == *it2) { ver++; }
        }
        if (ver == 0) { return false; }
        ver = 0;
    }
    return true;
}

void FONE::setNumero(std::string numero){
    if (validacao(numero) == true) {
        this->numero = numero;
    }
    else {
        std::cout << "fail: numero invalido" << std::endl;
    }
}

std::string FONE::getNumero(){
    return this->numero;
}