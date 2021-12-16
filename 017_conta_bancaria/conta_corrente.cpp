#include "conta_corrente.hpp"

CONTA_CORRENTE::CONTA_CORRENTE(int id, std::string idClient): CONTA{id, idClient}{
    this->type = "CC";
}
void CONTA_CORRENTE::monthlyUpdate(){
    this->balance -= 20;
}