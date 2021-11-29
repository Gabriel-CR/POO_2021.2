#include <vector>
#include "fone.hpp"

class CONTATO {
    std::string nome;
    std::string prefixo;
    std::vector<FONE> fones;

public:
    CONTATO(std::string nome, FONE f);

    std::string toString();

    void setNome(std::string nome);
    std::string getNome();

    void setFone(FONE f);
    std::string getFone(int indice);
    int getQtdFones();
    void removeFone(int indice);
};