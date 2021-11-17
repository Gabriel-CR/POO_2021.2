#include <iostream>
#include <list>
#include <sstream>
#include <string>

class FONE {
    std::string nome;
    std::string numero;

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

public:
    FONE(std::string nome = "", std::string numero = "") : nome{nome}, numero{numero} {}

    std::string toString(){
        std::string os {nome + ":" + numero};
        return os;
    }

    std::string getId(){ return this->nome; }
    std::string getNumero(){ return this->numero; }

    void setNome(std::string id){ this->nome = id; }
    void setNumero(std::string numero){
        if (validacao(numero) == true)
            this->numero = numero;
        else
            std::cout << "fail: numero invalido" << std::endl;
    }
};

class CONTATO {
    std::string prefixo;
    std::list<FONE> contatos;
    std::string nome;

public:
    CONTATO(std::string nome = "") : nome{nome} {}

    void addFone(FONE f) { contatos.push_back(f); }
};

int main(){
    FONE teste ("gab", "123456");

    std::cout << teste.toString() << std::endl;
    std::cout << teste.getId() << std::endl;
    std::cout << teste.getNumero() << std::endl;
    teste.setNome("cris");
    teste.setNumero("888");
    teste.setNumero("888+5");
    std::cout << teste.toString() << std::endl;

    return 0;
}