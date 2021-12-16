#include "conta.hpp"

class CONTA_POUPANCA : public CONTA {
public:
    CONTA_POUPANCA(int id, std::string idClient);
    //aumenta saldo em 1%
    void monthlyUpdate();
};