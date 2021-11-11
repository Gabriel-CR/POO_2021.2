#include <iostream>
#include <list>
#include <sstream>
#include <memory>

class CRIANCA{
    int idade;
    std::string nome;
    int saldo {};

    public:
        CRIANCA(std::string nome = "", int idade = 0) : nome{nome}, idade{idade} {};
        
        // ADICIONA OS DADOS DA CRIANCA;
        //void setIdade(int idade){ this->idade = idade; }
        //void setNome(std::string nome){ this->nome = nome; }
        void setSaldo(){ this->saldo += 1; }

        // RETORNA OS DADOS DA CRIANCA
        //int getIdade(){ return this->idade; }
        std::string getNome(){ return this->nome; }
        int getSaldo(){ return this->saldo; }

        friend std::ostream& operator<<(std::ostream& os, const CRIANCA& c) {
            os << c.nome << ":" << c.idade << " ";
            return os;
        }
};

class PULA_PULA{
    std::shared_ptr<CRIANCA> brincando;
    std::list<std::shared_ptr<CRIANCA>> fila;
    std::list<std::shared_ptr<CRIANCA>>::iterator it;
    std::shared_ptr<int> caixa;
    //int caixa {};
    int max {};

    public:
        PULA_PULA(std::shared_ptr<CRIANCA> brincando = nullptr) : brincando{brincando} {};

        void arrive(const std::shared_ptr<CRIANCA>& c){
            this->fila.push_front(c);
        }

        void show(){
            std::cout << "=> ";
            for (it = this->fila.begin(); it != this->fila.end(); it++)
                std::cout << **it;
            std::cout << "=> ";
            if (brincando == nullptr) { std::cout << "[ ]" << std::endl; }
            else { std::cout << "[ " << *this->brincando << "]" << std::endl; }
        }

        void in(){
            if (brincando != nullptr){
                this->caixa += 1;
                this->brincando->setSaldo();
                this->fila.push_front(brincando);
            }
            this->brincando = fila.back();
            this->fila.pop_back();
        }
        
        void caixa(){ std::cout << "R$ " << this->caixa << std::endl; }

        /*void saldo(std::string nome){
            for (it = this->fila.begin(); it != this->fila.end(); it++)
                if (*it.getNome() == nome)
        }*/
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
            sistema.arrive(std::make_shared<CRIANCA>(nome, idade));
        }
        else if (cmd == "show") {
            sistema.show();
        }
        else if (cmd == "in") {
            sistema.in();
        }
        else if (cmd == "caixa") {
            sistema.caixa();
        }
        /*else if (cmd == "saldo") {
            std::string nome {};
            ss >> nome;
            sistema.saldo(nome);
        }*/
    }

    return 0;
}