#include <iostream>
#include <sstream>

struct PESSOA {
    std::string nome;
    int idade;

    PESSOA(std::string nome = "", int idade = 0) {
        this->nome = nome;
        this->idade = idade;
    }

    PESSOA(int idade) : PESSOA("", idade) {}

    friend std::ostream& operator<<(std::ostream& os, const PESSOA& p) {
        os << "Nome: " << p.nome << " Idade: " << p.idade;
        return os;
    }
};

struct MOTOCA {
    PESSOA * pessoa { nullptr };
    int tempo { 0 };
    int potencia { 1 };

    MOTOCA(int pot) : potencia { pot } {}

    bool inserirPessoa(PESSOA * p) {
        if (this->pessoa != nullptr) {
            std::cout << "Motoca cheia" << std::endl;
            return false;
        }
        this->pessoa = p;
        return true;
    }

    std::string buzinar() {
        return "P" + std::string(this->potencia, 'e') + "m";
    }

    PESSOA * removerPessoa() {
        PESSOA * p = this->pessoa;
        this->pessoa = nullptr;
        return p;
    }

    void comprarTempo(int tempo) {
        this->tempo += tempo;
    }

    bool dirigir(int tempo) {
        if (this->pessoa == nullptr) {
            std::cout << "nao tem gente para dirigir" << std::endl;
            return false;
        }
        if (tempo > this->tempo) {
            std::cout << "so conseguiu dirigir " << this->tempo << " minutos" << std::endl;
            this->tempo  = 0;
            return true;
        }

        std::cout << "conseguiu dirigir " << this->tempo << " minutos" << std::endl;
        this->tempo -= tempo;
    }

    friend std::ostream& operator<<(std::ostream& os, const MOTOCA& m) {
        os << "T: " << m.tempo << " P: " << m.potencia;
        os << "[" << (m.pessoa == nullptr ? "vazio" : m.pessoa->nome) << "]";
        return os;
    }
};

int main(){
    MOTOCA motoca(1);

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
            int pot = 0;
            ss >> pot;
            motoca = MOTOCA(pot);
        }
        else if (cmd == "show") {
            std::cout << motoca << std::endl;
        }
        else if (cmd == "inserir") {
            std::string nome {};
            int idade { 0 };
            ss >> nome >> idade;
            PESSOA * pessoa = new PESSOA(nome, idade);
            if(!motoca.inserirPessoa(pessoa))
                delete pessoa;
        }
        else if (cmd == "retirar") {
            PESSOA * pessoa = motoca.removerPessoa();
            if (pessoa != nullptr)
                delete pessoa;
        }
        else {
            std::cout << "Comando nao existente" << std::endl;
        }
    }
    
    return 0;
}