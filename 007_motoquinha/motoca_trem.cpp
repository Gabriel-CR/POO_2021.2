#include <iostream>
#include <sstream>
#include <vector>

struct PESSOA {
    std::string nome;
    int idade {};

    PESSOA(std::string nome = "", int idade = 0) {
        this->nome = nome;
        this->idade = idade;
    }

    std::string toString(){
        std::string os {this->nome + ":" + std::to_string(this->idade) + " "};
        return os;
    }
};

struct MOTOCA {
    std::vector<PESSOA> fila;
    int tempo {};
    int potencia {};

    MOTOCA(int pot = 1) : potencia { pot } {}

    void inserirPessoa(PESSOA p){ fila.push_back(p); }

    void buzinar() {
        if (this->fila.size() == 0) {
            std::cout << "fail: moto vazia" << std::endl;
        }
        else {
            std::string honk {"P" + std::string(this->potencia, 'e') + "m"};
            std::cout << honk << std::endl;
        }
    }

    void removerPessoa(std::string nome){
        for (int i = 0; i < (int)fila.size(); i++)
            if (fila[i].nome == nome)
                fila.erase(fila.begin() + i);
    }

    void comprarTempo(int tempo){ this->tempo += tempo; }

    void dirigir(int tempo) {
        if (this->fila.size() == 0) {
            std::cout << "nao tem gente para dirigir" << std::endl;
        }
        if (tempo > this->tempo) {
            std::cout << "so conseguiu dirigir " << this->tempo << " minutos" << std::endl;
            this->tempo  = 0;
        }
        std::cout << "conseguiu dirigir " << this->tempo << " minutos" << std::endl;
        this->tempo -= tempo;
    }

    void toString(){
        std::cout << "potencia: " << this->potencia << " tempo: " << this->tempo << std::endl;
        std::cout << "pessoas: [ ";
        for (int i = 0; i < (int)fila.size(); i++)
            std::cout << fila[i].toString();
        std::cout << "]" << std::endl;
    }
};

int main(){
    MOTOCA motoca;
    std::cout << "SISTEMA PRONTO PARA INICIAR" << std::endl;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "in") {
            std::string nome {};
            int idade {};
            ss >> nome >> idade;
            PESSOA aux(nome, idade);
            motoca.inserirPessoa(aux);
        }
        else if (cmd == "show") {
            motoca.toString();
        }
        else if (cmd == "honk") {
            motoca.buzinar();
        }
        else if (cmd == "init") {
            int pot {};
            ss >> pot;
            motoca.potencia = pot;
        }
        else if (cmd == "out") {
            std::string out;
            ss >> out;
            motoca.removerPessoa(out);
        }
        else if (cmd == "buy") {
            int tempo {};
            ss >> tempo;
            motoca.comprarTempo(tempo);
        }
        else if (cmd == "drive") {
            int tempo {};
            ss >> tempo;
            motoca.dirigir(tempo);
        }
        else {
            std::cout << "fail: comando invalido" << std::endl;
        }
    }

    return 0;
}