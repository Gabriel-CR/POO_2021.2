#include <algorithm>
#include "contato.hpp"

class AGENDA {
    std::vector<CONTATO> contatos;
    // RETORNA -1 CASO NÃO TENHA O CONTATO NA LISTA, RETORNA A POSIÇÃO CASO CONTRÁRIO
    int findPos(std::string nome);

public:
    AGENDA(){};

    void addContato(std::string nome, std::string operadora, std::string numero);
    void rmFone(std::string nome, int indice);
    void rm(std::string nome);
    void search(std::string proc);
    std::string show();
};