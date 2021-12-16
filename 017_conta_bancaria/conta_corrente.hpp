#include "conta.hpp"

class CONTA_CORRENTE : public CONTA {
public:
    //inicializa conta.type com "CC"
    CONTA_CORRENTE(int id, std::string idClient);
    //retira 20 do saldo
    void monthlyUpdate();
};