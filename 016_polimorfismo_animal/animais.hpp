#include <iostream>
#include <list>

class ANIMAL {
    std::string tipo;
    std::string habitat;
    std::string estruturaOssea;
    std::string meioDeLocomocao;
    std::string alimento;
    std::list<std::string> caracteristicas;

public:
    void setTipo(std::string tipo);
    std::string getTipo();

    void setHabitat(std::string habitat);
    std::string getHabitat();

    void setEstruturaOssea(std::string osso);
    std::string getEstruturaOssea();

    void setMeioDeLocomocao(std::string locomocao);
    std::string getMeioDeLocomocao();

    void setAlimentacao(std::string alimento);
    std::string getAlimentacao();

    void setCaracteristicas(std::string caracteristica);
    std::string getCaracteristicas();
};