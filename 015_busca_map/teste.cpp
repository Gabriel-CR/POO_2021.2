#include "agenda.hpp"

int main(){
    std::string op {"oi"};
    std::string num {"1234"};
    std::string nm {"gab"};

    FONE aux(op, num);
    FONE aux1("cl", "3333");
    FONE aux2("vv", "8888");
    FONE aux3("tm", "1111");
    FONE aux4("cs", "2222");
    FONE aux5("rr", "0000");
    CONTATO teste(nm, aux);
    teste.setFone(aux1);
    teste.setFone(aux2);
    teste.setFone(aux3);
    teste.setFone(aux4);
    teste.setFone(aux5);

    std::cout << teste.toString() << std::endl;

    teste.removeFone(1);

    std::cout << teste.toString() << std::endl;


    return 0;
}