#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

class FONE {
    std::string operadora;
    std::string numero;

public:
    FONE(std::string id, std::string numero);

    std::string toString();

    // RETORNA TRUE CASO O NÚMERO SEJA VÁLIDO
    bool validacao(std::string numero);

    void setNumero(std::string numero);
    std::string getNumero();
    void setOperadora(std::string operadora);
    std::string getOperadora();
};

class CONTATO {
    std::string nome;
    std::string prefixo;
    std::map<int, FONE> fones;

public:
    CONTATO(std::string nome, FONE f);

    CONTATO(){
    }

    std::string toString();

    void setNome(std::string nome);
    std::string getNome();

    void setFone(FONE f);
    std::string getFone(int indice);
    int getQtdFones();
    void removeFone(int indice);
};

class AGENDA {
    std::map<int, CONTATO> contatos;

public:
    // RETORNA -1 CASO NÃO TENHA O CONTATO NA LISTA, RETORNA A POSIÇÃO CASO CONTRÁRIO
    int findPos(std::string nome);

    void addContato(std::string nome, std::string operadora, std::string numero);

    void rmFone(std::string nome, int indice);

    void rm(std::string nome);

    void search(std::string proc);

    std::string show();
};

class CONTATO_STAR : public CONTATO {
    bool star;

public:
    CONTATO_STAR(std::string nome, std::map<int, FONE> fones, bool star);
};