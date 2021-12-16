#include "conta_poupanca.hpp"

CONTA_POUPANCA::CONTA_POUPANCA(int id, std::string idClient) : CONTA{id, idClient} {
    this->type = "CP";
}
void CONTA_POUPANCA::monthlyUpdate(){
    this->balance *= 1.01;
}