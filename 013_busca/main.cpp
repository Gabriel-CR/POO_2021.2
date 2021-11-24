#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

class FONE {
    std::string operadora;
    std::string numero;

public:
    FONE(std::string id = "", std::string numero = "") : operadora{id}, numero{numero} {};

    std::string toString(){
        std::string os {operadora + ":" + numero};
        return os;
    }

    // RETORNA TRUE CASO O NÚMERO SEJA VÁLIDO
    bool validacao(std::string numero){
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

    void setNumero(std::string numero){
        if (validacao(numero) == true) {
            this->numero = numero;
        }
        else {
            std::cout << "fail: numero invalido" << std::endl;
        }
    }
    std::string getNumero(){ return this->numero; }

};

class CONTATO {
    std::string nome;
    std::string prefixo;
    std::vector<FONE> fones;

public:
    CONTATO(std::string nome, FONE f) : nome{nome}{
        if (f.validacao(f.getNumero()) == true) {
            fones.push_back(f);
        }
        else {
            std::cout << "fail: numero invalido" << std::endl;
        }
    };

    std::string toString(){
        std::string os {"- " + nome + " "};
        for (int i=0; i < (int)fones.size(); i++) {
            os += "[" + std::to_string(i) + ":" + fones[i].toString() + "] ";
        }
        return os;
    }

    void setNome(std::string nome){ this->nome = nome; }
    std::string getNome(){ return this->nome; }

    void setFone(FONE f) {
        if (f.validacao(f.getNumero()) == true) {
            fones.push_back(f);
        }
        else {
            f.validacao(f.getNumero());
        }
    }
    std::string getFone(int indice){ return this->fones[indice].getNumero(); }
    int getQtdFones(){ return this->fones.size(); }
    void removeFone(int indice) { this->fones.erase(fones.begin() + indice); }
};

class AGENDA {
    std::vector<CONTATO> contatos;

    // RETORNA -1 CASO NÃO TENHA O CONTATO NA LISTA, RETORNA A POSIÇÃO CASO CONTRÁRIO
    int findPos(std::string nome){
        for (int i = 0; i < (int) contatos.size(); i++) {
            if (contatos[i].getNome() == nome) {
                return i;
            }
        }
        return -1;
    }

public:
    AGENDA(){};

    void addContato(std::string nome, std::string operadora, std::string numero){
        if (findPos(nome) == -1) { // CASO NOVO CONTATO
            contatos.push_back(CONTATO(nome, FONE(operadora, numero)));
        }
        else { // CASO CONTATO JÁ EXISTENTE
            int pos = findPos(nome);
            contatos[pos].setFone(FONE(operadora, numero));
        }
    }

    void rmFone(std::string nome, int indice) {
        int pos = findPos(nome);
        contatos[pos].removeFone(indice);
    }

    void rm(std::string nome){
        int pos = findPos(nome);
        contatos.erase(contatos.begin() + pos);
    }

    void search(std::string proc){
        for (int i = 0; i < (int)contatos.size(); i++) {
            if (contatos[i].toString().find(proc) != std::string::npos) {
                std::cout << contatos[i].toString() << std::endl;
            }
        }
    }

    std::string show(){
        std::sort(contatos.begin(), contatos.end(), [](CONTATO c1, CONTATO c2){
            return c1.getNome() < c2.getNome();
        });
        
        std::string os {};
        for (int i = 0; i < (int)contatos.size(); i++) {
            os += contatos[i].toString() + "\n";
        }
        return os;
    }
};

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