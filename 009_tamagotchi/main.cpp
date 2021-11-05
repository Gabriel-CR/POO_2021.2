#include <iostream>
#include <sstream>

class TAMAGOTCHI {
public:
    int energiaMax;
    int saciedadeMax;
    int limpezaMax;
    int energia;
    int saciedade;
    int limpeza;
    int idade { 0 };
    int diamante { 0 };
    bool vivo { true };

    void dados(int energia, int saciedade, int limpeza){
        this->energiaMax = energia;
        this->saciedadeMax = saciedade;
        this->limpezaMax = limpeza;
        this->energia = energia;
        this->saciedade = saciedade;
        this->limpeza = limpeza;
    }

    void estaVivo(){
        if (this->energia <= 0) {
            vivo = false;
            std::cout << "seu pet morreu de fraqueza" << std::endl;            
        }
        else if (this->saciedade <= 0) {
            vivo = false;   
            std::cout << "seu pet morreu de fome" << std::endl;
        }
        else if (this->limpeza <= 0) {
            vivo = false;
            std::cout << "seu pet morreu de sujeira" << std::endl;   
        }
    }

    void estaMorto(){
        std::cout << "fail: seu pet esta morto" << std::endl;
    }
};

class JOGO {
public:
    TAMAGOTCHI tam;

    void setCfg(int energia, int saciedade, int limpeza) {
        tam.dados(energia, saciedade, limpeza);
    }

    void show() {
        std::cout << "E:" << tam.energia << "/" << tam.energiaMax << ",    S:" << tam.saciedade << "/" << tam.saciedadeMax << ",    L:" << tam.limpeza << "/" << tam.limpezaMax << ",    D:" << tam.diamante << ",    I:" << tam.idade << std::endl;
    }

    void play() {
        if (tam.vivo == true) {
            if (tam.energia - 2 < 0) tam.energia = 0; else tam.energia -= 2;
            if (tam.saciedade - 1 < 0) tam.saciedade = 0; else tam.saciedade -= 1;
            if (tam.limpeza - 3 < 0) tam.limpeza = 0; else tam.limpeza -= 3;
            tam.diamante++;
            tam.idade++;
            tam.estaVivo();
        }
        else {
            tam.estaMorto();
        }        
    }

    void eat() {
        if (tam.vivo == true) {
            if (tam.energia-- < 0) tam.energia = 0; else tam.energia--;
            if (tam.saciedade + 4 > tam.saciedadeMax) tam.saciedade = tam.saciedadeMax; else tam.saciedade += 4;
            if (tam.limpeza - 2 < 0) tam.limpeza = 0; else tam.limpeza -= 2;
            tam.idade++;
            tam.estaVivo();
        }
        else {
            tam.estaMorto();
        }
    }

    void sleep() {
        if (tam.vivo == true) {
            if (tam.energia <= tam.energiaMax - 5) {
                tam.energia = tam.energiaMax;
                tam.idade++;
            }
            else {
                std::cout << "fail: nao esta com sono" << std::endl;
            }
            tam.estaVivo();
        }
        else {
            tam.estaMorto();
        }        
    }

    void clean() {
        if (tam.vivo == true) {
            if (tam.energia - 3 < 0) tam.energia = 0; else tam.energia -= 3;
            if (tam.saciedade - 1 < 0) tam.saciedade = 0; else tam.saciedade -= 1;
            tam.limpeza = tam.limpezaMax;
            tam.idade += 2;
            tam.estaVivo();
        }
        else {
            tam.estaMorto();
        }        
    }
};

int main(){
    JOGO tamagotchi;

    std::cout << "SEU JOGO ESTA PRONTO PARA INICIAR" << std::endl;

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
            int energia { 0 };
            int saciedade { 0 };
            int limpeza { 0 };
            ss >> energia >> saciedade >> limpeza;
            tamagotchi.setCfg(energia, saciedade, limpeza);
        }
        else if (cmd == "show") {
            tamagotchi.show();
        }
        else if (cmd == "play") {
            tamagotchi.play();
        }
        else if (cmd == "eat") {
            tamagotchi.eat();
        }
        else if (cmd == "sleep") {
            tamagotchi.sleep();
        }
        else if (cmd == "clean") {
            tamagotchi.clean();
        }
        else {
            std::cout << "COMANDO INEXISTENTE" << std::endl;
        }
    }

    return 0;
}