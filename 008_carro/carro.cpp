#include <iostream>
#include <vector>
#include <sstream>

class CARRO {
    int gas { 0 };
    int maxGas { 100 };
    int km { 0 };
    int passageiro { 0 };
    int passMax { 2 };
public:
    // RETORNA DADOS DO CARRO
    int getPassageiro() { return this->passageiro; }
    int getGas() { return this->gas; }
    int getKm() { return this->km; }

    // EMBARCA E DESEMBARCA PASSAGEIROS
    void embarcar(){
        if (passageiro < passMax)
            this->passageiro++;
        else
            std::cout << "O carro esta lotado" << std::endl;
    }
    void desembarcar(){
        if (passageiro > 0)
            this->passageiro--;
        else
            std::cout << "Nao ha passageiro para desembarcar" << std::endl;
    }

    // ADICIONA GASOLINA NO CARRO
    void abastecer(int agua){
        if (gas + agua > maxGas)
            this->gas = maxGas;
        else
            this->gas += agua;
    }

    // DIRIGINDO O CARRO, AUMENTANDO A QUILOMETRAGEM E DIMINUINDO A GASOLINA
    void dirigir(int kms) {
        if (this->passageiro > 0 && this->gas > 0) {
            bool flag = true;
            while (flag != false) {
                this->km++;
                this->gas--;
                if (this->gas <= 0) {
                    std::cout << "A gasolina acabou, percorremos " << km << "Km" << std::endl;
                    flag = false;
                }
                else if (this->km >= kms) flag = false;
            }
        }
        else if (this->passageiro <= 0) {
            std::cout << "Nao ha passageiro no carro" << std::endl;
        }
        else if (this->gas <= 0) {
            std::cout << "Nao ha gasolina no carro, percorremos " << km << "Km" << std::endl;
        }
    }
};

int main(){
    CARRO carro;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "enter") {
            carro.embarcar();
        }
        else if (cmd == "leave") {
            carro.desembarcar();
        }
        else if (cmd == "show") {
            std::cout << "Passageiro: " << carro.getPassageiro() << "\tGas: " << carro.getGas() << "\tKm: " << carro.getKm() << std::endl;
        }
        else if (cmd == "fuel") {
            int gasolina { 0 };
            ss >> gasolina;
            carro.abastecer(gasolina);
        }
        else if (cmd == "drive") {
            int kms { 0 };
            ss >> kms;
            carro.dirigir(kms);
        }
    }

    return 0;
}