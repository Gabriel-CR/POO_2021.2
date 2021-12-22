#include <iostream>
#include <vector>
#include <map>
#include <memory>

class CONTA {
protected:
    int id { 0 };
    float balance { 0 };
    std::string clientId;
    std::string type; //CC or CP
public:
    CONTA(int id, std::string idClient) : id{id}, clientId{idClient} {
    }
    virtual ~CONTA(){};

    virtual void monthlyUpdate() = 0;
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
    void transfer(CONTA* other, float value){
        if (this->balance - value < 0)
            std::cout << "fail: voce nao tem esse valor na sua conta" << std::endl;
        else
            other->deposit(value);
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

    friend std::ostream& operator<<(std::ostream& os, const CONTA& conta);
};

std::ostream& operator<<(std::ostream& os, const CONTA& conta) {
    os << conta.id << ":" << conta.clientId << ":" << conta.balance << ":" << conta.type;
    return os;
}

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
    CONTA_POUPANCA(int id, std::string idClient) : CONTA{id, idClient}{
        this->type = "CP";
    }
    //aumenta saldo em 1%
    void monthlyUpdate(){
        this->balance *= 1.01;
    }
};

class CLIENTE {
    std::string nameClient;
    std::vector<CONTA*> contas;

public:
    CLIENTE(std::string clientId) : nameClient{clientId}{
    }
    void addAccount(CONTA* conta){;
        contas.push_back(conta);
    }
    //GETS and SETS
    std::string getClientId(){
        return this->nameClient;
    }
    void setClientId(std::string clientId){
        this->nameClient = clientId;
    }
    std::vector<CONTA*> getAccounts(){
        return this->contas;
    }
    void setAccounts(std::vector<CONTA*> contas){
        this-> contas = contas;
    }

    friend std::ostream& operator<<(std::ostream& os, const CLIENTE& client);
};

std::ostream& operator<<(std::ostream& os, const CLIENTE& client) {
    os << "- " << client.nameClient << '\n';
    for (CONTA* conta : client.contas) {
        os << " " << *conta << '\n';
    }
    return os;
}

class AGENCIA_BANCARIA {
    std::map<std::string, std::shared_ptr<CLIENTE>> clientes;
    std::map<int, std::shared_ptr<CONTA>> contas;
    int nextAccontId {0};
    //obtém conta ou lança excessão
    std::map<int, std::shared_ptr<CONTA>> getAccont(){
        return this->contas;
    }

public:
    AGENCIA_BANCARIA(){
    }
    void addClient(std::string clientId){
        auto cliente = clientes.find(clientId);

        if (cliente == clientes.end()) { //caso cliente não exista
            // CRIANDO CLIENTE COM DUAS CONTAS
            CONTA_CORRENTE cc((int)clientes.size(), clientId);
            CONTA_POUPANCA cp((int)clientes.size(), clientId);
            CLIENTE cliAux(clientId);
            cliAux.addAccount(&cc);
            cliAux.addAccount(&cp);

            // COLOCANDO O CLIENTE NA LISTA DE CLIENTES DO BANCO
            clientes[clientId] = std::make_shared<CLIENTE>(cliAux);

            // COLOCANDO AS CONTAS DO NOVO CLIENTE NA LISTA DE CONTAS DO BANCO
            contas[(int)contas.size()] = std::make_shared<CONTA_CORRENTE>(cc);
            contas[(int)contas.size()] = std::make_shared<CONTA_POUPANCA>(cp);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const AGENCIA_BANCARIA& banco);
};

std::ostream& operator<<(std::ostream& os, const AGENCIA_BANCARIA& banco){
    for (auto cliente : banco.clientes) {
        os << cliente.first << "[0 1]" << "\n";
    }
    for (auto conta : banco.contas) {
        std::cout << conta.first << " " << *conta.second << std::endl;
    }
    return os;
}

int main(){
    AGENCIA_BANCARIA banco;

    banco.addClient("fer");
    banco.addClient("fal");
    banco.addClient("bol");
    banco.addClient("vin");
    banco.addClient("fnx");

    std::cout << banco << std::endl;

    return 0;
}