#include "agenda.hpp"

// FONE
    FONE::FONE(std::string id = "", std::string numero = "") : operadora{id}, numero{numero} {};

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

// CONTATO
    CONTATO::CONTATO(std::string nome, FONE f) : nome{nome}{
        if (f.validacao(f.getNumero()) == true) {
            fones[(int)fones.size()] = f;
        }
        else {
            std::cout << "fail: numero invalido" << std::endl;
        }
    };

    std::string CONTATO::toString(){
        std::string os {"- " + nome + " "};
        for (auto fone : fones) {
            os += "[" + std::to_string(fone.first) + ":" + fone.second.toString() + "] ";
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
            fones[(int)fones.size()] = f;
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
        this->fones.erase(indice);
        while (indice < (int)fones.size()) {
            fones[indice] = fones[indice+1];
            fones.erase(indice+1);
            indice++;
        }
        
    }

// AGENDA
    int AGENDA::findPos(std::string nome){
        for (auto contato : contatos) {
            if (contato.second.getNome() == nome) {
                return contato.first;
            }
        }
        return -1;
    }

    void AGENDA::addContato(std::string nome, std::string operadora, std::string numero){
        int pos = findPos(nome);

        if (pos == -1) { // CASO NOVO CONTATO
            FONE aux(operadora, numero);
            CONTATO novo(nome, aux);
            contatos[(int)contatos.size()] = novo;
        }
        else { // CASO CONTATO JÁ EXISTENTE
            FONE f(operadora, numero);
            contatos[pos].setFone(f);
        }
    }
    /*void AGENDA::rmFone(std::string nome, int indice){
        int pos = findPos(nome);
        contatos[pos].removeFone(indice);
    }
    void AGENDA::rm(std::string nome){
        int pos = findPos(nome);
        contatos.erase(pos);
    }
    void AGENDA::search(std::string proc){
        for (int i = 0; i < (int)contatos.size(); i++) {
            if (contatos[i].toString().find(proc) != std::string::npos) {
                std::cout << contatos[i].toString() << std::endl;
            }
        }
    }
    std::string AGENDA::show(){
        std::sort(contatos.begin(), contatos.end(), [](CONTATO c1, CONTATO c2){
            return c1.getNome() < c2.getNome();
        });
        
        std::string os {};
        for (auto contato : contatos) {
            os += contato.second.toString() + "\n";
        }
        return os;
    }*/