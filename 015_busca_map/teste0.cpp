#include "agenda.hpp"

int main(){
    AGENDA teste;
    //FONE f("cl", "1234");
    //CONTATO c("gab", f);



    teste.addContato("gab", "cl", "1234");
    teste.findPos("gab");

    //std::cout << c.getNome() << std::endl;

    //std::cout << teste.show() << std::endl;

    return 0;
}