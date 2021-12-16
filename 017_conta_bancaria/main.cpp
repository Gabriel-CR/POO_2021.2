#include "conta.hpp"

int main(){
    CONTA teste(0, "Carlos");
    CONTA teste1(1, "Gabriel");
    teste.deposit(1000);
    teste.withdraw(500);
    teste.transfer(teste1, 600);

    std::cout << teste << std::endl;
    std::cout << teste1 << std::endl;

    return 0;
}