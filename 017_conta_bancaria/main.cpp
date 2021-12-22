#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <sstream>

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
            throw std::runtime_error("fail: voce nao tem esse valor na sua conta");
        else
            this->balance -= value;
    }
    //depósito
    void deposit(float value){
        this->balance += value;
    }
    //transferencia
    void transfer(std::shared_ptr<CONTA> other, float value){
        if (this->balance - value < 0) {
            throw std::runtime_error("fail: voce nao tem esse valor na sua conta");
        }
        else {
            other->deposit(value);
            this->balance -= value;
        }
            
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
    os << conta.clientId << ":" << conta.balance << ":" << conta.type;
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
    os << "[ ";
    for (int i = 0; i < (int)client.contas.size(); i++) {
        os << client.contas[i]->getId() << " ";
    }
    os << "]\n";
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
            CONTA_CORRENTE cc(nextAccontId, clientId);
            CONTA_POUPANCA cp(nextAccontId + 1, clientId);
            CLIENTE cliAux(clientId);
            cliAux.addAccount(&cc);
            cliAux.addAccount(&cp);

            // COLOCANDO O CLIENTE NA LISTA DE CLIENTES DO BANCO
            clientes[clientId] = std::make_shared<CLIENTE>(cliAux);

            // COLOCANDO AS CONTAS DO NOVO CLIENTE NA LISTA DE CONTAS DO BANCO
            contas[nextAccontId] = std::make_shared<CONTA_CORRENTE>(cc);
            contas[nextAccontId + 1] = std::make_shared<CONTA_POUPANCA>(cp);

            nextAccontId += 2;
        }
        else {
            throw std::runtime_error("fail: cliente ja existe");
        }
    }

    void withdraw(int idConta, float value){
        contas[idConta]->withdraw(value);
    }

    void deposit(int idConta, float value){
        contas[idConta]->deposit(value);
    }

    void transfer(int contaDe, int contaPara, float value){
        auto de = contas.find(contaDe);
        auto para = contas.find(contaPara);
        if (de != contas.end() && para != contas.end()) {
            contas[contaDe]->transfer(contas[contaPara], value);
        }
        else {
            throw std::runtime_error("fail: conta nao encontrada");
        }
    }

    void monthlyUpdate(){
        for (auto conta : contas) {
            conta.second->monthlyUpdate();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const AGENCIA_BANCARIA& banco);
};

std::ostream& operator<<(std::ostream& os, const AGENCIA_BANCARIA& banco){
    os << "Clients: \n";
    int i {0};
    for (auto cliente : banco.clientes) {
        os << "- " << cliente.first << " [" << std::to_string(i) << ", " << std::to_string(i + 1) << "]\n"; // [erro aqui!]
        i += 2;
    }
    os << "Acconts: \n";
    for (auto conta : banco.contas) {
        std::cout << conta.first << ":" << *conta.second << std::endl;
    }
    return os;
}

int main(){
    AGENCIA_BANCARIA banco;
    std::cout << "SISTEMA BANCARIO PRONTO" << std::endl;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        try {
            if (cmd == "end") {
                break;
            }
            else if (cmd == "show") {
                std::cout << banco << std::endl;
            }
            else if (cmd == "addCli") {
                std::string nome;
                ss >> nome;
                banco.addClient(nome);
            }
            else if (cmd == "saque") {
                int id {0};
                float valor {0};
                ss >> id >> valor;
                banco.withdraw(id, valor);
            }
            else if (cmd == "deposito") {
                int id {0};
                float valor {0};
                ss >> id >> valor;
                banco.deposit(id, valor);
            }
            else if (cmd == "transf") {
                int id1 {0};
                int id2 {0};
                float valor {0};
                ss >> id1 >> id2 >> valor;
                banco.transfer(id1, id2, valor);
            }
            else if (cmd == "update") {
                banco.monthlyUpdate();
            }
            else {
                std::cout << "fail: comando invalido" << std::endl;
            }
        }
        catch (std::runtime_error& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}