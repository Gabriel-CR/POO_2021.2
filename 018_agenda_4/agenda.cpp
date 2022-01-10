#include <iostream>
#include <vector>

class FONE {
    std::string numero {""};
    std::string operadora {""};

public:
    FONE(std::string operadora, std::string numero){
        if (validate(numero) == true) {
            this->numero = numero;
            this->operadora = operadora;
        }
        else {
            throw std::runtime_error("fail: numero invalido");
        }
    }

    bool validate(std::string numero){ // VERIFICA SE O NÚMERO TEM APENAS CARACTERES VÁLIDOS
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

    //GETS e SETS
    std::string getId(){
        return this->operadora;
    }
    void setId(std::string operadora){
        this->operadora = operadora;
    }
    std::string getNumber(){
        return this->numero;
    }
    void setNumber(std::string numero){
        if (validate(numero) == true)
            this->numero = numero;
        else
            throw std::runtime_error("fail: numero invalido");
    }

    std::string toString(){
        std::string os;
        if (operadora != "" && numero != "")
            os = operadora + ":" + numero;
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const FONE& fone);
};

std::ostream& operator<<(std::ostream& os, const FONE& fone) {
    if (fone.operadora != "" && fone.numero != "")
        os << fone.operadora << ":" << fone.numero;
    return os;
}

class CONTATO {
    std::string nome {""};
    std::vector<FONE> fones;

public:
    CONTATO(std::string nome, std::vector<FONE> fones) : nome{nome}, fones{fones} {
    }

    void addFone(FONE fone){
        if (fone.validate(fone.getNumber()) == true)
            fones.push_back(fone);
        else {
            throw std::runtime_error("fail: fone invalido");
        }
    }

    void rmFone(int index){
        if ((int)fones.size() >= index)
            fones.erase(fones.begin() + index);
        else
            throw std::runtime_error("fail: numero nao encontrado");
    }

    //GETS e SETS
    std::string getName(){
        return this->nome;
    }
    void setName(std::string nome){
        this->nome = nome;
    }
    std::vector<FONE> getFones(){
        return this->fones;
    }

    friend std::ostream& operator<<(std::ostream& os, const CONTATO& contato);
};

std::ostream& operator<<(std::ostream& os, const CONTATO& contato) {
    os << "- " << contato.nome << " ";
    for (FONE fone : contato.fones)
        os << "[" << fone << "] ";
    return os;
}

int main(){
    /*try {
        
    }
    catch (std::runtime_error& e ){
        std::cerr << e.what() << std::endl;
    }*/

    FONE gab("oi", "1234");
    FONE car("cl", "3456");

    std::vector<FONE> fones {gab, car};
    std::string nome {"gabriel"};

    CONTATO eu(nome, fones);

    std::cout << eu << std::endl;

    FONE t("tm", "7890");
    eu.addFone(t);

    std::cout << eu << std::endl;

    return 0;
}