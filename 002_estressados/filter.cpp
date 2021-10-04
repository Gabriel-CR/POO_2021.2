#include <iostream>
#include <vector>
#include <sstream>

/*
[4] FILTER:
    [1] clonar: retorna um novo vetor copiando os valores do vetor de entrada
    [2] pegar_homens: retorne uma lista com os homens (valores positivos)
    [3] pegar_calmos: retorne uma lista com as pessoas com stress menor que 10 (positivos menor que 10) (abs)
    [4] pegar_mulheres_calmas: retorne uma lista com as mulheres com nível de stress menor que 10.(negativos menor que 10)
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
    std::cout << "[1] Retorna um novo vetor copiando os valores do vetor de entrada\n";
    std::cout << "[2] Retorne uma lista com os homens\n";
    std::cout << "[3] Retorne uma lista com as pessoas com stress menor que 10\n";
    std::cout << "[4] Retorne uma lista com as mulheres com nível de stress menor que 10\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

std::vector<int> clonar(const std::vector<int>& fila){
    std::vector<int> clone;

    for (int i = 0; i < (int) fila.size(); i++)
        clone.push_back(fila[i]);
    
    return clone;
}

std::vector<int> pegarHomens(const std::vector<int>& fila){
    std::vector<int> man;

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] > 0)
            man.push_back(fila[i]);
    }

    return man;
}

std::vector<int> pegarCalmos(const std::vector<int>& fila){
    std::vector<int> calm;
    
    for (int i = 0; i < (int) fila.size(); i++) {
        if (std::abs(fila[i]) < 10)
            calm.push_back(std::abs(fila[i]));
    }
    
    return calm;
}

std::vector<int> pegarMulheresCalmas(const std::vector<int>& fila){
    std::vector<int> mulheresCalm;
    
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] < 0 && std::abs(fila[i]) < 10)
            mulheresCalm.push_back(fila[i]);
    }
    
    return mulheresCalm;
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
        std::vector<int> clone = clonar(elementosDaFila);

        std::cout << "\nElementos do vetor clonado [ ";

        for (int i = 0; i < (int) clone.size(); i++)
            std::cout << clone[i] << " ";

        std::cout << "]\n";
    }
    else if (opcaoMenu == 2) {
        std::vector<int> homens = pegarHomens(elementosDaFila);

        std::cout << "\nHomens na fila [ ";

        for (int i = 0; i < (int) homens.size(); i++)
            std::cout << homens[i] << " ";

        std::cout << "]\n";
    }
    else if (opcaoMenu == 3) {
        std::vector<int> calmos = pegarCalmos(elementosDaFila);

        std::cout << "\nStress menores da fila [ ";

        for (int i = 0; i < (int) calmos.size(); i++)
            std::cout << calmos[i] << " ";

        std::cout << "]\n";
    }
    else {
        std::vector<int> mulheresCalmas = pegarMulheresCalmas(elementosDaFila);

        std::cout << "\nMulheres com menores stress da fila [ ";

        for (int i = 0; i < (int) mulheresCalmas.size(); i++)
            std::cout << mulheresCalmas[i] << " ";

        std::cout << "]\n";
    }

    return 0;
}