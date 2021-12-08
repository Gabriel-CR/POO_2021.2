#include "animais.hpp"

// ANIMAL
void ANIMAL::setTipo(std::string tipo){
    this->tipo = tipo;
}
std::string ANIMAL::getTipo(){
    return this->tipo;
}

void ANIMAL::setHabitat(std::string habitat){
    this->habitat = habitat;
}
std::string ANIMAL::getHabitat(){
    return this->habitat;
}

void ANIMAL::setEstruturaOssea(std::string osso){
    this->estruturaOssea = osso;
}
std::string ANIMAL::getEstruturaOssea(){
    return this->estruturaOssea;
}

void ANIMAL::setMeioDeLocomocao(std::string locomocao){
    this->meioDeLocomocao = locomocao;
}
std::string ANIMAL::getMeioDeLocomocao(){
    return this->meioDeLocomocao;
}

void ANIMAL::setAlimentacao(std::string alimento){
    this->alimento = alimento;
}
std::string ANIMAL::getAlimentacao(){
    return this->alimento;
}

void ANIMAL::setCaracteristicas(std::string caracteristica){
    this->caracteristicas.push_back(caracteristica);
}
std::string ANIMAL::getCaracteristicas(){
    std::string os;
    for (auto caracteristica : caracteristicas)
        os += "- " + caracteristica + '\n';
    return os;
}