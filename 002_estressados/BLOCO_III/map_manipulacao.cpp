#include <iostream>
#include <vector>
#include <sstream>

/*
[6] MAP-MANIPULACOES:
    [1] sozinhos: Quais PESSOAS eram as únicas representantes do seu nível de stress na fila? (abs)
    [2] mais_ocorrencias: Qual a maior quantidade de ocorrências do mesmo nível de stress. (abs)
    [3] mais_recorrentes: Quais os níveis de stress mais recorrentes. (abs)
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
    std::cout << "[1] Quais PESSOAS eram as unicas representantes do seu nivel de stress na fila?\n";
    std::cout << "[2] Qual a maior quantidade de ocorrencias do mesmo nivel de stress.\n";
    std::cout << "[3] Quais os niveis de stress mais recorrentes.\n\n";
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

std::vector<int> sozinhos(const std::vector<int>& fila){
    std::vector<int> only;
    int cont { 0 };

    for (int i { 0 }; i < (int) fila.size(); i++) {
        cont = 0;
        for (int j { 0 }; j < (int) fila.size(); j++) {
            if (fila[i] == abs(fila[j]))
                cont++;
        }

        if (cont == 1)
            only.push_back(abs(fila[i]));
    }

    return only;
}

int maisOcorrencias(const std::vector<int>& fila){
    int stressComum { 0 };
    
    for (int i { 0 }; i < (int) fila.size(); i++) {
        int cont { 0 };

        for (int j { 0 }; j < (int) fila.size(); j++) {
            if (abs(fila[i]) == abs(fila[j]))
                cont++;
        }

        if (cont > stressComum)
            stressComum = cont;
    }
    
    return stressComum;
}

int *maisRecorrentes(const std::vector<int>& fila, int arr[]){
    int maior { 0 };
    
    for (int i = { 0 }; i < (int) fila.size(); i++) {
        int cont { 0 };

        for (int j = { 0 }; j < (int) fila.size(); j++) {
            if (abs(fila[i]) == abs(fila[j]))
                cont++;
        }

        if (cont > maior) {
            maior = cont;
            arr[0] = abs(fila[i]);
            arr[1] = cont;
        }
    }
    
    return arr;
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
        std::vector<int> unicos { sozinhos(elementosDaFila) };
        std::cout << "\nUnicos representantes [" << toString(unicos) << "]\n";
    }
    else if (opcaoMenu == 2) {
        std::cout << "\nStress comum " << maisOcorrencias(elementosDaFila) << '\n';
    }
    else {
        int recorrentes[2];
        maisRecorrentes(elementosDaFila, recorrentes);
        std::cout << "\nNivel de stress mais recorente [" << recorrentes[0] << " " << recorrentes[1] << "]\n";
    }
    
    return 0;
}