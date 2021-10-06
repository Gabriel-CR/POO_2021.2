#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>

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

std::string toString(std::vector<int>& fila){
    std::string lista = " ";

    for (int i = 0; i < (int) fila.size(); i++){
        lista = lista + std::to_string(fila[i]) + " ";
    }

    return lista;
}

std::vector<int> inverterComCopia(const std::vector<int>& fila){
    std::vector<int> invertido;
    
    for (int i = ((int) fila.size()) - 1; i >= 0; i--) {
        invertido.push_back(fila[i]);
    }
    
    return invertido;
}

void inverterInplace(std::vector<int>& fila){
    for (int i = ((int) fila.size()) - 1; i >= 0; i--)
        std::cout << fila[i] << " ";
}

int sortear(std::vector<int>& fila){
    int posicao = rand() % fila.size();

    int numSorteado = fila[posicao];

    return numSorteado;
}

void embaralhar(std::vector<int>& fila){
    for (int i = 0; i < (int) fila.size(); i++) {
        int randomValue = rand() % ((int) fila.size());

        int aux = fila[i];
        fila[i] = fila[randomValue];
        fila[randomValue] = aux;
    }
}

void ordenar(std::vector<int>& fila){
    for (int i = 0; i < (int) fila.size(); i++) {
        int menor = i;

        for (int j = i + 1; j < (int) fila.size(); j++) {
            if (fila[j] < fila[menor])
                menor = j;
        }

        int aux = fila[i];
        fila[i] = fila[menor];
        fila[menor] = aux;
    }
}

int main(){
    std::srand(std::time(0));
    
    //RECEBENDO ELEMENTOS DA FILA DO USUÁRIO
    std::cout << "Digite as pessoas presentes na fila: ";
    std::string entrada;
    getline(std::cin, entrada);
    std::vector<int> elementosDaFila { popularFila(entrada) };

    int opcaoMenu { 0 };
    opcaoMenu = menu01();

    if (opcaoMenu == 1) {
        std::vector<int> elementosInvertidos { inverterComCopia(elementosDaFila) };
        std::cout << "\nElementos da fila invertidos [" << toString(elementosInvertidos) << "]";
    }
    else if (opcaoMenu == 2) {
        std::cout << "\nElementos da fila invertidos [";
        inverterInplace(elementosDaFila);
        std::cout << "]\n";
    }
    else if (opcaoMenu == 3) {
        std::cout << "Escolhi retornar o elemento " << sortear(elementosDaFila) << '\n';
    }
    else if (opcaoMenu == 4) {
        embaralhar(elementosDaFila);
        std::cout << "\nElementos da fila embaralhados [" << toString(elementosDaFila) << "]";
    }
    else {
        ordenar(elementosDaFila);
        std::cout << "Elementos ordenados [" << toString(elementosDaFila) << "]";
    }

    return 0;
}