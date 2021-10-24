#include <iostream>
#include <vector>
#include <sstream>

struct GRAFITE {
    float calibre { 0 }; // 0.3 0.5 0.9
    std::string dureza { "" }; // HB, 2B, 4B, 6B
    int tamanho { 0 };
};

struct LAPISEIRA {
    GRAFITE grafite;
    
    LAPISEIRA(){
        std::cout << "\n[Digite as informacoes do grafite]\n";

        bool flag { false };
        while (flag != true) {
            std::cout << "Calibre: ";
            std::cin >> grafite.calibre;

            if (grafite.calibre >= 0.3 || grafite.calibre <= 0.9) {
                flag = true;
            }                
            else {
                std::cout << "\n[DIGITE UM CALIBRE VALIDO]\n";
            }
        }

        bool ver { false };
        while (ver != true) {
            std::cout << "Dureza: ";
            std::cin >> grafite.dureza;

            if (grafite.dureza == "HB" || grafite.dureza == "2B" || grafite.dureza == "4B" || grafite.dureza == "6B")
                ver = true;
            else
                std::cout << "\n[DIGITE UMA DUREZA VALIDA]\n";
        }
        
        std::cout << "Tamanho: ";
        std::cin >> grafite.tamanho;
    }
};

int acoes(){
    int op { 0 };

    std::cout << "\n[ESCOLHA UMA DAS OPCOES]\n" << "[1] Retirar grafite\n" << "[2] Escrever na folha\n" << "\nSua escolha: ";
    std::cin >> op;

    return op;
}

void tirarGrafite(LAPISEIRA& lapiseira){
    lapiseira.grafite.calibre = 0;
    lapiseira.grafite.dureza = "";
    lapiseira.grafite.tamanho = 0;
}

void escrever(LAPISEIRA& lapiseira, int folha, int dim){
    //std::cout << "\nENTROU\n" << "\nTAMANHO: " << lapiseira.grafite.tamanho << "\nFOLHA: " << folha << "\nDIM: " << dim;

    bool flag = true;
    while (flag == true) {
        folha--;
        lapiseira.grafite.tamanho -= dim;
        if (folha <= 0 || lapiseira.grafite.tamanho <= 0)
            flag = false;
    }

    if (lapiseira.grafite.tamanho <= 0) {
        tirarGrafite(lapiseira);
        std::cout << "\nO grafite acabou, sobraram " << folha << " folhas";
    }
    else{
        std::cout << "\nEscrevemos nas folhas e sobraram " << lapiseira.grafite.tamanho << "mm de grafite\n";
    }
}

void atividades(int op, LAPISEIRA& lapiseira){
    if (op == 1) {
        tirarGrafite(lapiseira);
        std::cout << "[LAPISEIRA SEM GRAFITE]\n";
    }
    else if (op == 2) {
        if (lapiseira.grafite.tamanho > 0) {
            int folha { 0 };
            std::cout << "\nDigite a quantidade de folhas: ";
            std::cin >> folha;

            if (lapiseira.grafite.dureza == "HB") {
                escrever(lapiseira, folha, 1);                    
            }
            else if (lapiseira.grafite.dureza == "2B") {
                escrever(lapiseira, folha, 2);
            }
            else if (lapiseira.grafite.dureza == "4B") {
                escrever(lapiseira, folha, 4);
            }
            else {
                escrever(lapiseira, folha, 6);
            }
        }
        else {
            std::cout << "\n[LAPISEIRA SEM GRAFITE]";
        }
    }
}

int main(){
    LAPISEIRA lapiseira;
    int opcao { acoes() };
    atividades(opcao, lapiseira);

    return 0;
}