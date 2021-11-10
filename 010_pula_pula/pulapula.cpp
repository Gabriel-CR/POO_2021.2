#include <iostream>
#include <vector>
#include <sstream>

class CRIANCA{
    int idade;
    std::string nome;
    int saldo {};

    public:
        CRIANCA(std::string nome = "", int idade = 0) : nome{nome}, idade{idade} {};
        
        // ADICIONA OS DADOS DA CRIANCA;
        //void setIdade(int idade){ this->idade = idade; }
        //void setNome(std::string nome){ this->nome = nome; }
        void setSaldo(int saldo){ this->saldo = saldo; }

        // RETORNA OS DADOS DA CRIANCA
        //int getIdade(){ return this->idade; }
        //std::string getNome(){ return this->nome; }
        int getSaldo(){ return this->saldo; }

        friend std::ostream& operator<<(std::ostream& os, const CRIANCA& c) {
            os << c.nome << ":" << c.idade << " ";
            return os;
        }
};

class PULA_PULA{
    CRIANCA* brincando;
    std::vector<CRIANCA> fila;
    int caixa {};
    int max {};

    public:
        PULA_PULA(CRIANCA* brincando = nullptr) : brincando{brincando} {};

        void arrive(std::string nome, int idade){
            CRIANCA aux(nome, idade);
            fila.push_back(aux);
        }

        void show(){
            std::cout << "=> ";
            for (int i = ((int) fila.size()) - 1; i >= 0; i--)
                std::cout << fila[i];
            std::cout << "=> ";
            if (brincando == nullptr) { std::cout << "[ ]" << std::endl; }
            else { std::cout << "[ " << *this->brincando << "]" << std::endl; }
        }

        void in(){ // ERRO AQUI
            fila.push_back(*brincando);
            brincando = new CRIANCA(fila[0]);
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
            std::string nome {};
            int idade {};
            ss >> nome >> idade;
            sistema.arrive(nome, idade);
        }
        else if (cmd == "show") {
            sistema.show();
        }
        else if (cmd == "in") {
            sistema.in();
        }
    }

    return 0;
}