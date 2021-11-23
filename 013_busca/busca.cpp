#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

class FONE {
    std::string operadora;
    std::string numero;

public:
    FONE(std::string id = "", std::string numero = "") : operadora{id}, numero{numero} {};

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

    std::string getOperadora(){
        return this->operadora;
    }
    std::string getNumero(){
        return this->numero;
    }
    void setOperadora(std::string operadora){
        this->operadora = operadora;
    }
    void setNumero(std::string numero){
        if (validacao(numero) == true)
            this->numero = numero;
        else
            std::cout << "fail: numero invalido" << std::endl;
    }

    std::string toString(){
        std::string os {operadora + ":" + numero};
        return os;
    }
};

class CONTATO {
    std::string prefixo;
    std::vector<FONE> fones;
    std::string nome;

public:
    CONTATO(std::string prefixo = "", std::string nome = "") : prefixo{prefixo}, nome{nome} {}

    void removerFone(int indice){
        if ((int) fones.size() > indice) {
            std::cout << "fail: numero nao encontrado" << std::endl;
            return;
        }
        else {
            fones.erase(fones.begin() + indice);
        }
    }

    void addFone(FONE f) {
        if (f.validacao(f.getNumero()) == true)
            fones.push_back(f);
        else
            std::cout << "fail: numero invalido" << std::endl;
    }
    std::string getFone(int indice){
        if ((int)fones.size() < indice) {
            return fones[indice].toString();
        }
        else {
            std::cout << "fail: contato nao encontrado" << std::endl;
        }
    }
    std::string getNome(){
        return this->nome;
    }
    void setNome(std::string nome){
        this->nome = nome;
    }

    std::string toString(){
        std::string os {"- " + nome + " "};
        for (int i=0; i < (int) fones.size(); i++) {
            os += "[" + std::to_string(i) + fones[i].toString() + "] ";
        }
        return os;
    }
};

class AGENDA {
    std::vector<CONTATO> contatos;

    int findPos(std::string nome){
        for (int i = 0; i < (int) contatos.size(); i++) {
            if (contatos[i].getNome() == nome) {
                return i;
            }
        }
        return -1;
    }

public:
    AGENDA(){}

    void addContato(std::string nome, std::string prefixo, std::string operadora, std::string numero){
        if (findPos(nome) == -1) {
            contatos.push_back(CONTATO(prefixo, nome));
            contatos[(int)contatos.size()].addFone(FONE(operadora, numero));
        }
        else {
            int pos = findPos(nome);
            contatos[pos].addFone(FONE(operadora, numero));
        }
    }

    std::string show(){
        std::string os {};
        for (int i = 0; i < (int)contatos.size(); i++){
            os += contatos[i].toString() + "\n";
        }
        return os;
    }
};

int main(){
    AGENDA sistema;
    std::cout << "SUA AGENDA DE CONTATOS ESTA PRONTA" << std::endl;

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
            std::cout << sistema.show() << std::endl;
        }
        else if (cmd == "add") {
            std::string nome;
            std::string prefixo;
            std::string operadora;
            std::string numero;
            ss >> nome >> prefixo >> operadora >> numero;
            sistema.addContato(nome, prefixo, operadora, numero);
        }
    }

    return 0;
}