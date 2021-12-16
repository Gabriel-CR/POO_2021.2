#include <iostream>

class CONTA {
protected:
    int id { 0 };
    float balance { 0 };
    std::string clientId;
    std::string type; //CC or CP
public:
    CONTA(int id, std::string clientId);
    ~CONTA();

    virtual void monthlyUpdate();
    //saque
    void withdraw(float value);
    //depósito
    void deposit(float value);
    //transferencia
    void transfer(CONTA other, float value);

    //GETS and SETS
    int getId();
    float getBalance();
    std::string getClientId();
    std::string getType();

    friend std::ostream& operator<<(std::ostream& os, const CONTA& conta);
};