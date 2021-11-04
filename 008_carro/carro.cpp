#include <iostream>
#include <vector>

class CARRO {
    int gas { 0 };
    int maxGas { 100 };
    int km { 0 };
    int passageiro { 0 };
    int passMax { 2 };
public:
    int getPassageiro() {
        return this->passageiro;
    }
    int getGasolina() {
        return this->gas;
    }
    int getKm() {
        return this->km;
    }

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

    
};

int main(){
    CARRO carro;

    carro.embarcar();

    std::cout << carro.getPassageiro() << std::endl;

    return 0;
}