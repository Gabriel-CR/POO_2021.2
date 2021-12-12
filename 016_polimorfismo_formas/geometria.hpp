#include <iostream>
#include <vector>
#include <sstream>

class FORMA {
    std::string forma;
    int qtdRetas {0};
    std::vector<int> tamRetas;
    int qtdAngulos;
    std::vector<int> tamAngulos;

public:
    FORMA(std::string forma);

    virtual void setQtdRetas(int retas);
    int getQtdRetas();

    void setTamRetas(int retas);
    std::string getTamRetas();

    void setTamAngulos(int tam);
    int getQtdAngulos();
    std::string getAngulos();
};

class QUADRADO : public FORMA {
    int retas {4};

public:
    QUADRADO();
    std::string toString();
};

class TRIANGULO : public FORMA {
    int retas {3};

public:
    TRIANGULO();
    std::string toString();
};

class RETANGULO : public FORMA {
    int retas {4};

public:
    RETANGULO();
    std::string toString();
};