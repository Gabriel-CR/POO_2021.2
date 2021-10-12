#include <iostream>
#include <vector>
#include <sstream>

/*
[6] PROXIMIDADE:
    [1] briga: Quando alguém super estressado(>50) está ao lado de duas pessoas muito estressadas(>30) pode dar briga. Quantas vezes essa situação acontece?
    [2] apaziguado: Se alguém hiper estressado(>80) estiver ao lado de pelo menos uma pessoa bem tranquila (<10) ela vai ser apaziguada. Em que posições estão esses que serão apaziguados?
*/

std::vector<int> popularFila(std::string linha){
    std::stringstream ss {linha};

    int pessoas {};
    std::vector<int> v;

    while (ss >> pessoas)
        v.push_back(pessoas);

    return v;
}

int menu01(){
    int opcao { 0 };

    std::cout << "\n\nESCOLHA UMA DAS OPCOES:\n";
    std::cout << "[1] Qual a possibilidade de briga?\n";
    std::cout << "[2] Posicao de pessoa estressadas, mas que podem ser controladas?\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

std::string toString(std::vector<int>& fila){
    std::string lista = " ";

    for (int i = 0; i < (int) fila.size(); i++)
        lista = lista + std::to_string(fila[i]) + " ";

    return lista;
}

int chanceDeBriga(const std::vector<int> fila){
    int briga { 0 };
    
    for (int i { 0 }; i < (int) fila.size(); i++) {
        if (abs(fila[i]) > 30 && abs(fila[i + 1]) > 50 && abs(fila[i + 2]) > 30)
            briga++;
    }
    
    return briga - 1;
}

std::vector<int> estressadosApaziguados(const std::vector<int> fila){
    std::vector<int> lista;

    for (int i { 0 }; i < (int) fila.size(); i++) {
        if (abs(fila[i]) > 80 && ( abs(fila[i - 1]) < 10 || abs(fila[i + 1]) < 10 ))
            lista.push_back(i);
    }

    return lista;
}

int main() {
    //RECEBENDO ELEMENTOS DA FILA DO USUÁRIO
    std::cout << "Digite as pessoas presentes na fila: ";
    std::string entrada;
    getline(std::cin, entrada);
    std::vector<int> elementosDaFila { popularFila(entrada) };

    int opcaoMenu { 0 };
    opcaoMenu = menu01();

    if (opcaoMenu == 1) {
        std::cout << "\nHa " << chanceDeBriga(elementosDaFila) << " chances de briga na fila\n";
    }
    else {
        std::vector<int> apaziguados { estressadosApaziguados(elementosDaFila) };
        std::cout << "\nAs pessoas que podem ser apaziguadas estao nas posicoes [" << toString(apaziguados) << "]\n";
    }
    
    return 0;
}