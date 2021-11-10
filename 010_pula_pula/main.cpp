#include <iostream>
#include <vector>
#include <sstream>

class CRIANCA {
    int idade { 0 };
    std::string nome;
    int saldo { 0 };

    public:
        // CRIA UMA NOVA CRIANÇA
        CRIANCA(std::string nome, int idade) : nome{ nome }, idade{ idade } {};
        CRIANCA(){};

        // ADICIONA UMA UM NOME A IDADE E O SALDO
        void setNome(std::string name){ this->nome = name; }
        void setIdade(int idade){ this->idade = idade; }
        void setSaldo(){ this->saldo += 1; }

        // RETORNA O NOME E A IDADE E O SALDO
        std::string getNome(){ return this->nome; }
        int getIdade(){ return this->idade; }
        int getSaldo(){ return this->saldo; }
};

class PULA_PULA {
    CRIANCA brincando {};
    std::vector<CRIANCA> fila;
    int caixa { 0 };
    int max { 0 };

    public:
        void setCaixa(){ this->caixa += 1; }
        int getCaixa(){ return this->caixa; }

        void setSaldo(std::string nome){
            for (int i = 0; i < (int)fila.size(); i++)
                if (fila[i].getNome() == nome)
                    fila[i].setSaldo();
        }
        int getSaldo(std::string nome){
            for (int i = 0; i < (int)fila.size(); i++)
                if (fila[i].getNome() == nome)
                    fila[i].getSaldo();
        }

        void setFila(std::string nome, int idade){ this->fila.push_back(CRIANCA(nome, idade)); }
        void getFila(){
            std::cout << "=> ";
            for (int i = 0; i < (int)fila.size(); i++) {
                std::cout << fila[i].getNome() << ":" << fila[i].getIdade() << " ";
            }
            std::cout << "=> " << " [" << this->brincando.getNome() << ":" << this->brincando.getIdade() << "]" << std::endl;
        }

        void setMax(int max){ this->max = max; }
        int getMax(){ return this->max; }

        void removerDoPulaPula() {
            CRIANCA aux = brincando;
            brincando.setSaldo();
            brincando = fila[(int)fila.size()];
            fila.push_back(aux);
        }

        void papaiChegou(std::string nome) {
            for (int i = 0; i < (int)fila.size(); i++)
                if (fila[i].getNome() == nome)
                    fila.erase(fila.begin() + i);
        }

        void fechar() {
            for (int i = 0; i < (int)fila.size(); i++) {
                fila.erase(fila.begin());
                brincando = {};
            }
        }

        void entrar() {
            CRIANCA aux = brincando;
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
        else if (cmd == "show") {
            sistema.getFila();
        }
        else if (cmd == "papaichegou") {
            std::string nome;
            ss >> nome;
            sistema.papaiChegou(nome);
        }
        else if (cmd == "fechar") {
            sistema.fechar();
        }
        else if (cmd == "init") {
            int max { 0 };
            ss >> max;
            sistema.setMax(max);
        }
        else if (cmd == "saldo") {
            std::string nome;
            ss >> nome;
            sistema.getSaldo(nome);
        }
        else if (cmd == "arrive") {
            std::string nome;
            int idade;
            ss >> nome >> idade;
            sistema.setFila(nome, idade);
        }
        else if (cmd == "in") {
            sistema.entrar();
        }
    }
    
    return 0;
}