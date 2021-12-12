#include "geometria.hpp"

// FORMA
FORMA::FORMA(std::string forma) : forma{forma}{
}
void FORMA::setQtdRetas(int retas){
    this->qtdRetas = retas;
    this->qtdAngulos = retas;
}
int FORMA::getQtdRetas(){
    return this->qtdRetas;
}
void FORMA::setTamRetas(int retas){
    this->tamRetas.push_back(retas);
}
std::string FORMA::getTamRetas(){
    std::string tamR;
    for (float reta : this->tamRetas) {
        tamR += "\t- " + std::to_string(reta) + '\n';
    }
    return tamR;
}
void FORMA::setTamAngulos(int tam){
    this->tamAngulos.push_back(tam);
}
int FORMA::getQtdAngulos(){
    return this->qtdAngulos;
}
std::string FORMA::getAngulos(){
    std::string qtdA;
    for (int angulo : this->tamAngulos) {
        qtdA += "\t- " + std::to_string(angulo) + '\n';
    }
    return qtdA;
}

//QUADRADO
QUADRADO::QUADRADO() : FORMA{"Quadrado"}{
    this->setQtdRetas(4);
    for (int i = 0; i < this->retas; i++)
        this->setTamRetas(10);
    for (int i = 0; i < this->retas; i++)
        this->setTamAngulos(90);
}
std::string QUADRADO::toString(){
    std::string os {"Num. Retas: " + std::to_string(this->getQtdRetas()) + '\n'};
    os += "Tam. Retas: \n" + this->getTamRetas();
    os += "Num. Angulos: " + std::to_string(this->getQtdAngulos()) + '\n';
    os += "Tam. Angulos: \n" + this->getAngulos();
    return os;
}

// TRIANGULO
TRIANGULO::TRIANGULO() : FORMA{"Triangulo"}{
    this->setQtdRetas(3);
    for (int i = 0; i < this->retas; i++)
        this->setTamRetas(5);
    for (int i = 0; i < this->retas; i++)
        this->setTamAngulos(60);
}
std::string TRIANGULO::toString(){
    std::string os {"Num. Retas: " + std::to_string(this->getQtdRetas()) + '\n'};
    os += "Tam. Retas: \n" + this->getTamRetas();
    os += "Num. Angulos: " + std::to_string(this->getQtdAngulos()) + '\n';
    os += "Tam. Angulos: \n" + this->getAngulos();
    return os;
}

// RETANGULO
RETANGULO::RETANGULO() : FORMA{"Retangulo"}{
    this->setQtdRetas(4);
    this->setTamRetas(10);
    this->setTamRetas(20);
    this->setTamRetas(10);
    this->setTamRetas(20);
    for (int i = 0; i < this->retas; i++)
        this->setTamAngulos(90);
}
std::string RETANGULO::toString(){
    std::string os {"Num. Retas: " + std::to_string(this->getQtdRetas()) + '\n'};
    os += "Tam. Retas: \n" + this->getTamRetas();
    os += "Num. Angulos: " + std::to_string(this->getQtdAngulos()) + '\n';
    os += "Tam. Angulos: \n" + this->getAngulos();
    return os;
}