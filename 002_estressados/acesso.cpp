#include <iostream>
#include <vector>
#include <sstream>

/*
[5] ACESSO:
    [1] inverter_com_copia Retorna um novo vetor com os dados invertidos
    [2] reverter_inplace Inverte os valores do vetor de entrada sem uso de vetor auxiliar
    [3] sortear Retorna aleatoriamente um elemento do vetor
    [4] embaralhar Embaralha o vetor original
    [5] ordenar - selection sort utilizando Ordena o vetor original
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
    std::cout << "[1] Retorna um novo vetor com os dados invertidos\n";
    std::cout << "[2] Inverte os valores do vetor de entrada sem uso de vetor auxiliar\n";
    std::cout << "[3] Retorna aleatoriamente um elemento do vetor\n";
    std::cout << "[4] Embaralha o vetor original\n";
    std::cout << "[5] Ordena o vetor original\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

std::vector<int> inverterComCopia(const std::vector<int>& fila){
    std::vector<int> invertido;
    
    for (int i = ((int) fila.size()) - 1; i >= 0; i--) {
        invertido.push_back(fila[i]);
    }
    
    return invertido;
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
        std::vector<int> elementosInvertidos { inverterComCopia(elementosDaFila) };

        std::cout << "\nElementos da fila invertidos [ ";

        for (int i = 0; i < (int) elementosInvertidos.size(); i++)
            std::cout << elementosInvertidos[i] << " ";

        std::cout << "]\n";
    }
    else if (opcaoMenu == 2) {

    }

    return 0;
}