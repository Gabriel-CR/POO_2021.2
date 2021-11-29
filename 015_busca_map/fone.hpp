#include <iostream>

class FONE {
    std::string operadora;
    std::string numero;

public:
    FONE(std::string id = "", std::string numero = "");

    std::string toString();

    // RETORNA TRUE CASO O NÚMERO SEJA VÁLIDO
    bool validacao(std::string numero);

    void setNumero(std::string numero);
    std::string getNumero();
};