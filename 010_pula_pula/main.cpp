#include <iostream>
#include <vector>
#include <sstream>

class CRIANCA {
    int idade { 0 };
    std::string nome;

    public:
        // CRIA UMA NOVA CRIANÇA
        CRIANCA(std::string nome, int idade) : nome{ nome }, idade{ idade } {};

        // ADICIONA UMA UM NOME E UMA IDADE
        void setName(std::string name) { this->nome = name; }
        void setIdade(int idade) { this->idade = idade; }

        // RETORNA O NOME E A IDADE
        std::string getNome() { return this->nome; }
        int getIdade() { return this->idade; }
};

class PULA_PULA {
    CRIANCA brincando;
    std::vector<CRIANCA> fila;
    CRIANCA aux;
    int caixa { 0 };

    public:
        void setCaixa() { this->caixa += 1; }
        int getCaixa() { return this->caixa; }

        void setFila(CRIANCA c) { this->fila.push_back(c); }

        void removerDoPulaPula() {
            aux = brincando;
            brincando = fila[(int)fila.size()];
            fila.push_back(aux);
        }
};

int main(){
    PULA_PULA sistema;

    std::cout << "SEU SISTEMA ESTA PRONTO PARA INICIAR" << std::endl;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "caixa") {
            sistema.getCaixa();
        }
    }
    
    return 0;
}