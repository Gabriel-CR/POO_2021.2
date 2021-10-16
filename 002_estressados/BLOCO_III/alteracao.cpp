#include <iostream>
#include <vector>
#include <sstream>

/*
[11] GRUPOS:
    [1] remove: Dado a pessoa X, como fica a fila após remover X?
    [2] insert: Como fica a fila se eu inserir a pessoa X na posição Y.
    [3] dance: O coordenador disse: se você está do lado de alguém com o mesmo nível de stress que você, saia da fila com ele. Quando os pares saiam, as vezes se formavam novos pares que também saíam. Quem ficou na fila?
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
    std::cout << "[1] Dado a pessoa X, como fica a fila apos remover X?\n";
    std::cout << "[2] Como fica a fila se eu inserir a pessoa X na posição Y.\n";
    std::cout << "[3] Pessoas na fila após remover pares.\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

int main(){
    //RECEBENDO ELEMENTOS DA FILA DO USUÁRIO
    std::cout << "Digite as pessoas presentes na fila: ";
    std::string entrada;
    getline(std::cin, entrada);
    std::vector<int> elementosDaFila { popularFila(entrada) };

    int opcaoMenu { 0 };
    //opcaoMenu = menu01();
    opcaoMenu = 1;

    if (opcaoMenu == 1) {
        
    }
    
    return 0;
}