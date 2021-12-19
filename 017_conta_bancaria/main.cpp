#include <iostream>
#include <vector>

class CONTA {
protected:
    int id { 0 };
    float balance { 0 };
    std::string clientId;
    std::string type; //CC or CP
public:
    CONTA(int id, std::string clientId) : id{id}, clientId{clientId}{
    }
    ~CONTA();

    virtual void monthlyUpdate();
    //saque
    void withdraw(float value){
        if (this->balance - value < 0)
            std::cout << "fail: voce nao tem esse valor na sua conta" << std::endl;
        else
            this->balance -= value;
    }
    //depósito
    void deposit(float value){
        this->balance += value;
    }
    //transferencia
    void transfer(CONTA other, float value){
        if (this->balance - value < 0)
            std::cout << "fail: voce nao tem esse valor na sua conta" << std::endl;
        else
            other.deposit(value);
    }

    //GETS and SETS
    int getId(){
        return this->id;
    }
    float getBalance(){
        return this->balance;
    }
    std::string getClientId(){
        return this->clientId;
    }
    std::string getType(){
        return this->type;
    }

    friend std::ostream& operator<<(std::ostream& os, const CONTA& conta) {
        os << conta.id << ":" << conta.clientId << ":" << conta.balance << ":" << conta.type;
        return os;
    }
};

class CONTA_CORRENTE : public CONTA {
public:
    //inicializa conta.type com "CC"
    CONTA_CORRENTE(int id, std::string idClient) : CONTA{id, idClient}{
        this->type = "CC";
    }
    //retira 20 do saldo
    void monthlyUpdate(){
        this->balance -= 20;
    }
};

class CONTA_POUPANCA : public CONTA {
public:
    CONTA_POUPANCA(int id, std::string idClient) : CONTA{id, idClient} {
        this->type = "CP";
    }
    //aumenta saldo em 1%
    void monthlyUpdate(){
        this->balance *= 1.01;
    }
};

class CLIENTE {
    std::string clientId;
    std::vector<CONTA> contas;

public:
    CLIENTE(std::string clientId) : clientId{clientId}{
    }
    void addAccount(CONTA conta){;
        contas.push_back(conta);
    }
    //GETS and SETS
    std::string getClientId(){
        return this->clientId;
    }
    void setClientId(std::string clientId){
        this->clientId = clientId;
    }
    std::vector<CONTA> getAccounts(){
        return this->contas;
    }
    void setAccounts(std::vector<CONTA> contas){
        this-> contas = contas;
    }
};

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