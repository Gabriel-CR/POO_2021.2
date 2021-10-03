#include <iostream>
#include <vector>
#include <sstream>

/*
[2] Melhor caso
    [1] procurar_menor: qual o menor valor da lista?
    [2] procurar_maior: qual o maior valor da lista?
    [3] procurar_menor_pos: qual a posição do menor valor da lista?
    [4] procurar_menor_pos_apos: qual a posição do menor valor da lista depois da posição P?
    [5] procurar_melhor_se: qual a posição do HOMEM mais calmo? (menor valor maior que 0)
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
    std::cout << "[1] Qual o menor valor da lista?\n";
    std::cout << "[2] Qual o maior valor da lista?\n";
    std::cout << "[3] Qual a posicao do menor valor da lista?\n";
    std::cout << "[4] Qual a posicao do menor valor da lista depois da posicao P?\n";
    std::cout << "[5] Qual a posicao do HOMEM mais calmo?\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

int procurarMenor(std::vector<int> fila){
    int menor {999999};

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] < menor)
            menor = fila[i];
    }

    return menor;
}

int procurarMaior(std::vector<int> fila){
    int maior { 0 };

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] > maior)
            maior = fila[i];
    }

    return maior;
}

int procurarMenorPos(std::vector<int> fila){    
    int menor {999999};
    int posicao { 0 };

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] < menor) {
            menor = fila[i];
            posicao = i;
        }
    }

    return posicao;
}

int procurarMenorPosApos(std::vector<int> fila){
    int valorP { 0 };
    std::cout << "\n\nDigite o valor de P: ";
    std::cin >> valorP;

    int menor { 999999 };
    int posicao { (int) fila.size() + 1 };
    for (int i = valorP; i < (int) fila.size(); i++) {
        if (fila[i] < menor && i < posicao ) {
            menor = fila[i];
            posicao = i;
        }
    }

    int resposta = fila[posicao + 1];

    return resposta;
}

int procurarHomemCalmo(std::vector<int> fila){
    int posicao { 0 };
    int menor { 999999 };
    
    for (int i = 0; i < (int) fila.size(); i++) {
        // menor valor maior que 0
        if (fila[i] < menor && fila[i] > 0) {
            menor = fila[i];
            posicao = i;
        }
    }

    return posicao;
}

int main(){
    //RECEBENDO ELEMENTOS DA FILA DO USUÁRIO
    std::cout << "Digite as pessoas presentes na fila: ";
    std::string entrada;
    getline(std::cin, entrada);
    std::vector<int> elementosDaFila { popularFila(entrada) };

    int opcaoMenu { 0 };
    opcaoMenu = menu01();

    if (opcaoMenu == 1) {
        std::cout << "\nO menor valor da fila e " << procurarMenor(elementosDaFila);
    }
    else if (opcaoMenu == 2) {
        std::cout << "\nO maior valor da fila e " << procurarMaior(elementosDaFila);
    }
    else if (opcaoMenu == 3) {
        std::cout << "\nA posicao do menor valor da fila e " << procurarMenorPos(elementosDaFila);
    }
    else if (opcaoMenu == 4) {
        int res = procurarMenorPosApos(elementosDaFila);
        std::cout << "\nApos o valor digitado, o menor valor da fila e " << res;
    }
    else {
        std::cout << "\nO homem mais calmo esta na posicao " << procurarHomemCalmo(elementosDaFila);
    }

    return 0;
}