#include <iostream>
#include <map>
#include <sstream>
#include <memory>

class CLIENTE{
    std::string nome;
    int telefone;

public:
    CLIENTE(std::string nome, int telefone);

    std::string getNome();
    int getTelefone();

    void setTelefone(int fone);
    void setNome(std::string nome);

    std::string toString();
};

class SALA{
    std::map<int, std::shared_ptr<CLIENTE>> cadeiras;
    int maxCadeiras {};

public:
    SALA();

    void init(int maxCadeiras);

    int procurarPessoa(std::string nome);

    std::string show();

    void reservar(const std::shared_ptr<CLIENTE>& c, int cadeira);

    void cancelar(const std::string& nome);
};