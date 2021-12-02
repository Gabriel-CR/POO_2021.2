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
    CONTATO::CONTATO(std::string nome = "", FONE f) : nome{nome}{
        if (f.validacao(f.getNumero()) == true) {
            int pos = (int)fones.size() + 1;
            fones[pos] = f;
            //fones.insert(std::pair<int, FONE>((int)fones.size() + 1, f));
        }
        else {
            std::cout << "fail: numero invalido" << std::endl;
        }
    };

    std::string CONTATO::toString(){
        std::string os {"- " + nome + " "};
        for (auto it : fones) {
            os += "[" + std::to_string(it.first) + ":" + it.second.toString() + "]";
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
            int pos = (int)fones.size() + 1;
            fones[pos] = f;
            //fones.insert(std::pair<int, FONE>((int)fones.size() + 1, f));
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
    }

// AGENDA
    int AGENDA::findPos(std::string nome = ""){
        for (auto ct : contatos) {
            if (ct.second.getNome() == nome) {
                return ct.first;
            }
        }
        return -1;
    }

    void AGENDA::addContato(std::string nome, std::string operadora, std::string numero){
        if (findPos(nome) == -1) { // CASO NOVO CONTATO
            int pos = (int)contatos.size() + 1;
            contatos[pos] = CONTATO(nome, FONE(operadora, numero));
            //contatos.insert(std::pair<int, CONTATO>((int)contatos.size() + 1, CONTATO(nome, FONE(operadora, numero))));
        }
        else { // CASO CONTATO JÁ EXISTENTE
            int pos = findPos(nome);
            contatos[pos].setFone(FONE(operadora, numero));
        }
    }
    void AGENDA::rmFone(std::string nome, int indice){
        int pos = findPos(nome);
        contatos[pos].removeFone(indice);
    }
    void AGENDA::rm(std::string nome){
        int pos = findPos(nome);
        contatos.erase(pos);
    }
    void AGENDA::search(std::string proc){
        for (auto it : contatos) {
            if (it.second.toString().find(proc) != std::string::npos) {
                std::cout << it.second.toString() << std::endl;
            }
        }
    }
    std::string AGENDA::show(){
        std::sort(contatos.begin(), contatos.end(), [](CONTATO c1, CONTATO c2){
            return c1.getNome() < c2.getNome();
        });
            
        std::string os {};
        for (auto it : contatos) {
            os += it.second.toString() + "\n";
        }
        return os;
    }