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
    int j { 0 };
    int n { 0 };

    for (int i = 0; i < (int) fila.size(); i++) {
        for (j = 0; j < n; j++) {
            if (fila[i] == unicos[j])
                break;
        }

        if (j == n) {
            unicos.push_back(fila[i]);
            n++;
        }
    }
    
    return unicos;
}

std::vector<int> diferentes(const std::vector<int>& fila){
    std::vector<int> stress;
    
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] < 0)
            stress.push_back(fila[i] * (-1));
        else
            stress.push_back(fila[i]);
    }

    std::vector<int> niveis = exclusivos(stress);
    
    return niveis;
}

std::vector<int> abandonados(const std::vector<int>& fila){
    std::vector<int> lista;
    // CRIAÇÃO DE VETOR SEM REPETIÇÃO DE NÚMEROS COM BASE NA FILA
    std::vector<int> unicos = exclusivos(fila);
    
    // CRIANDO UMA LISTA COM O NÚMERO E QUANTAS VEZES ELE APARECE NA FILA "lista[numero, ocorrencia na fila]"
    for (int i = 0; i < (int) unicos.size(); i++) {
        lista.push_back(unicos[i]);

        int contador { 0 };

        for (int j = 0; j < (int) fila.size(); j++) {
            if (unicos[i] == fila[j])
                contador++;
        }

        lista.push_back(contador);
    }

    std::vector<int> resultado;

    // POPULANDO O VETOR RESULTADO, COLOCANDO O numero PRESENTE NA LISTA COM A (ocorrenci - 1)
    for (int i = 0; i < (int) lista.size(); i += 2) {
        for (int j = 0; j < lista[i + 1] - 1; j++)
            resultado.push_back(lista[i]);
    }

    return resultado;
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
        std::vector<int> removeRepetidos { exclusivos(elementosDaFila) };
        std::cout << "Elementos na fila, sem repeticao [" << toString(removeRepetidos) << "]";
    }
    else if (opcaoMenu == 2) {
        std::vector<int> stress { diferentes(elementosDaFila) };
        std::cout << "Niveis de stress na fila [" << toString(stress) << "]";
    }
    else {
        std::vector<int> unicos { abandonados(elementosDaFila) };
        std::cout << "Unicos na fila [" << toString(unicos) << "]";
    }
    
    return 0;
}