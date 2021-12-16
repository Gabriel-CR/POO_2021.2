#include "conta.hpp"

CONTA::CONTA(int id, std::string clientId) : id{id}, clientId{clientId}{
}
CONTA::~CONTA(){
}
void CONTA::withdraw(float value){
    if (this->balance - value < 0)
        std::cout << "fail: voce nao tem esse valor na sua conta" << std::endl;
    else
        this->balance -= value;
}
void CONTA::deposit(float value){
    this->balance += value;
}
void CONTA::transfer(CONTA other, float value){
    if (this->balance - value < 0)
        std::cout << "fail: voce nao tem esse valor na sua conta" << std::endl;
    else
        other.deposit(value);
}
int CONTA::getId(){
    return this->id;
}
float CONTA::getBalance(){
    return this->balance;
}
std::string CONTA::getClientId(){
    return this->clientId;
}
std::string CONTA::getType(){
    return this->type;
}
std::ostream& operator<<(std::ostream& os, const CONTA& conta) {
    os << conta.id << ":" << conta.clientId << ":" << conta.balance << ":" << conta.type;
    return os;
}