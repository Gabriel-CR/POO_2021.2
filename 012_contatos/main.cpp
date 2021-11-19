#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class FONE {
    std::string operadora;
    std::string numero;

public:
    FONE(std::string operadora = "", std::string numero = "") : operadora{operadora}, numero{numero} {}

    std::string toString(){
        std::string os {operadora + ":" + numero};
        return os;
    }

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

    std::string getOperadora(){ return this->operadora; }
    std::string getNumero(){ return this->numero; }

    void setNome(std::string id){ this->operadora = id; }
    void setNumero(std::string numero){
        if (validacao(numero) == true)
            this->numero = numero;
        else
            std::cout << "fail: numero invalido" << std::endl;
    }
};

class CONTATO {
    std::string prefixo;
    std::vector<FONE> contatos;
    std::string nome;

public:
    CONTATO(std::string nome = "") : nome{nome} {}

    void addFone(FONE f) {
        if (f.validacao(f.getNumero()) == true)
            contatos.push_back(f);
        else
            std::cout << "fail: numero invalido" << std::endl;
    }

    std::string getNome() { return this->nome; }
    void setNome(std::string nome) { this->nome = nome; }

    std::string show(){
        std::string os {"- " + nome + " "};
        for (int i = 0; i < (int)contatos.size(); i++)
            os += "[" + std::to_string(i) + ":" + contatos[i].toString() + "] ";
        return os;
    }

    void removerTelefone(int indice){
        if (indice > (int)contatos.size())
            std::cout << "fail: indice nao encontrado na lista" << std::endl;
        else
            contatos.erase(contatos.begin() + indice);
    }
};

int main(){
    CONTATO contatos;
    std::cout << "SUA LISTA DE CONTATOS ESTA PRONTA" << std::endl;

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
            std::string nome {};
            ss >> nome;
            contatos.setNome(nome);
        }
        else if (cmd == "show") {
            std::cout << contatos.show() << std::endl;
        }
        else if (cmd == "add") {
            std::string operadora {};
            std::string numero {};
            ss >> operadora >> numero;
            FONE aux(operadora, numero);
            contatos.addFone(aux);
        }
        else if (cmd == "rm") {
            int indice {};
            ss >> indice;
            contatos.removerTelefone(indice);
        }
        else {
            std::cout << "fail: comando invalido" << std::endl;
        }
    }

    return 0;
}