#include <iostream>
#include <vector>
#include <sstream>

int opcoes(){
    int opcao { 0 };
    std::cout << "\n[ESCOLHA UMA DAS OPCOES]\n" << "[1] Retirar grafite\n" << "[2] Escrever na folha\n" << "\nSua escolha: ";
    std::cin >> opcao;
    return opcao;
}

struct GRAFITE {
    float calibre { 0 };
    std::string dureza {""};
    std::vector<int> tamanho;

    void tirarGrafite(){
        this->calibre = 0;
        this->dureza = "";
        for (int i = 0; i < (int) tamanho.size(); i++)
            this->tamanho[i] = 0;
    }
};

struct LAPISEIRA {
    GRAFITE* grafite;
};

int main(){
    LAPISEIRA* lapiseira;
    int opcao { opcoes() };
    
    if (opcao == 1) {
        lapiseira->grafite->tirarGrafite();
    }
    else {
        bool flag { false };
        while (flag != true) {
            std::cout << "Digite o calibre do grafite: ";
            std::cin >> lapiseira->grafite->calibre;

            if (lapiseira->grafite->calibre == 0.3 || lapiseira->grafite->calibre == 0.5 || lapiseira->grafite->calibre == 0.9)
                flag = true;
            else
                flag = false;
        }

        flag = false;
        while (flag != true) {
            std::cout << "Digite a dureza do grafite: ";
            std::cin >> lapiseira->grafite->dureza;
            if (lapiseira->grafite->dureza == "HB" || lapiseira->grafite->dureza == "2B" || lapiseira->grafite->dureza == "4B" || lapiseira->grafite->dureza == "6B")
                flag = true;
            else
                flag = false;
        }   

        int qtd { 0 };
        std::cout << "Quantidade de grafites colocados: ";
        std::cin >> qtd;
        for (int i { 0 }; i < qtd; i++) {
            int tam = 0;
            std::cout << "Digite o tamanho do " << i << " grafite: ";
            std::cin >> tam;
            lapiseira->grafite->tamanho.push_back(tam);
        }
    }

    //atividades(lapiseira);

    return 0;
}