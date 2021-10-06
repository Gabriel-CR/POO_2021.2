#include <iostream>
#include <vector>
#include <sstream>

/*
[5] CONJUNTOS:
    [1] exclusivos: O fiscal permitiu a entrada de um único representante de cada valor, ou seja, uma lista dos valores que aparecem na fila sem repetição. Que conjunto foi formado?
    [2] diferentes: Qual a lista dos diferentes níveis de stress que aparecem?
    [3] abandonados: quais pessoas ficaram na fila após remover um exemplar de cada valor?
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
    std::cout << "[1] Lista dos valores que aparecem na fila sem repeticao\n";
    std::cout << "[2] Lista dos diferentes niveis de stress que aparecem\n";
    std::cout << "[3] Pessoas que ficaram na fila apos remover um exemplar de cada valor\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

std::string toString(std::vector<int>& fila){
    std::string lista = " ";

    for (int i = 0; i < (int) fila.size(); i++){
        lista = lista + std::to_string(fila[i]) + " ";
    }

    return lista;
}

std::vector<int> exclusivos(const std::vector<int>& fila){
    std::vector<int> unicos;

    for (int i = 0; i < (int) fila.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (fila[i] == fila[j])
                break;
            else
                unicos.push_back(fila[j]);
        }
    }
    
    return unicos;
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
        std::vector<int> repetidoRemove { exclusivos(elementosDaFila) };
        std::cout << "Elementos na fila, sem repeticao [" << toString(repetidoRemove) << "]";
    }
    
    return 0;
}