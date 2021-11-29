#include "agenda.hpp"

int AGENDA::findPos(std::string nome){
    for (int i = 0; i < (int) contatos.size(); i++) {
        if (contatos[i].getNome() == nome) {
            return i;
        }
    }
    return -1;
}

AGENDA::AGENDA(){};

void AGENDA::addContato(std::string nome, std::string operadora, std::string numero){
    if (findPos(nome) == -1) { // CASO NOVO CONTATO
        contatos.push_back(CONTATO(nome, FONE(operadora, numero)));
    }
    else { // CASO CONTATO JÁ EXISTENTE
        int pos = findPos(nome);
        contatos[pos].setFone(FONE(operadora, numero));
    }
}
void AGENDA::rmFone(std::string nome, int indice){
    int pos = findPos(nome);
    contatos[pos].removeFone(indice);
}
void AGENDA::rm(std::string nome){
    int pos = findPos(nome);
    contatos.erase(contatos.begin() + pos);
}
void AGENDA::search(std::string proc){
    for (int i = 0; i < (int)contatos.size(); i++) {
        if (contatos[i].toString().find(proc) != std::string::npos) {
            std::cout << contatos[i].toString() << std::endl;
        }
    }
}
std::string AGENDA::show(){
    std::sort(contatos.begin(), contatos.end(), [](CONTATO c1, CONTATO c2){
        return c1.getNome() < c2.getNome();
    });
        
    std::string os {};
    for (int i = 0; i < (int)contatos.size(); i++) {
        os += contatos[i].toString() + "\n";
    }
    return os;
}