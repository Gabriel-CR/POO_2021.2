#include <iostream>
#include <vector>
#include <sstream>

class CRIANCA{
    int idade;
    std::string nome;
    int saldo;

    public:
        // ADICIONA OS DADOS DA CRIANCA;
        void setIdade(int idade){ this->idade = idade; }
        void setNome(std::string nome){ this->nome = nome; }
        void setSaldo(int saldo){ this->saldo = saldo; }

        // RETORNA OS DADOS DA CRIANCA
        int getIdade(){ return this->idade; }
        std::string getNome(){ return this->nome; }
        int getSaldo(){ return this->saldo; }
};

class PULA_PULA{
    CRIANCA brincando;
    std::vector<CRIANCA> fila;
    int caixa { 0 };
    int max { 0 };

    public:
        void arrive(std::string nome, int idade){
            CRIANCA aux;
            aux.setNome(nome);
            aux.setIdade(idade);
            fila.push_back(aux);
        }

        void show(){
            std::cout << "=> ";
            for (int i = 0; i < (int)fila.size(); i++) {
                std::cout << fila[i].getNome() << ":" << fila[i].getIdade() << " ";
            }
            std::cout << "=> " << " [ " << this->brincando.getNome() << ":" << this->brincando.getIdade() << " ]" << std::endl;
        }
};

int main(){
    PULA_PULA sistema;
    std::cout << "SEU SISTEMA JA ESTA FUNCIONANDO" << std::endl;

    while(true){
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "arrive") {
            std::string nome;
            int idade { 0 };
            ss >> nome >> idade;
            sistema.arrive(nome, idade);
        }
        else if (cmd == "show") {
            sistema.show();
        }
    }
    return 0;
}