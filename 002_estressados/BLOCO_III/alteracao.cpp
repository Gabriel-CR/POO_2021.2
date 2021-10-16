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
    std::cout << "[3] Pessoas na fila apos remover pares.\n\n";
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

std::vector<int> remove(std::vector<int> fila, int num){
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == num) {
            fila.erase(fila.begin() + i);
            i--;
        }
            
    }

    return fila;
}

std::vector<int> insert(std::vector<int> fila, int pessoa, int pos){
    std::vector<int> nFila;
    
    for (int i = 0; i < (int) fila.size(); i++) {
        if (i == pos)
            nFila.push_back(pessoa);

        nFila.push_back(fila[i]);
    }

    if (pos == (int) fila.size())
        nFila.push_back(pessoa);
    
    return nFila;
}

std::vector<int> dance(std::vector<int> fila){
    int flag { 0 };

    while (flag != 1) {
        for (int i = 0; i < (int) fila.size(); i++) {
            if (abs(fila[i]) == abs(fila[i + 1]))
                fila.erase(fila.begin() + i, fila.begin() + i + 2);
        }

        int ver = 0;

        for (int j = 0; j < (int) fila.size(); j++) {
            if (abs(fila[j]) == abs(fila[j + 1]))
                ver++;
        }
        if (ver == 0)
            flag = 1;
    }
    
    return fila;
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
        int num { 0 };

        std::cout << "\nDigite o numero a ser removido: ";
        std::cin >> num;

        std::vector<int> removido { remove(elementosDaFila, num) };
        std::cout << "\nFila removendo o numero " << num << " fica [" << toString(removido) << "]\n";
    }
    else if (opcaoMenu == 2) {
        int pessoa { 0 };
        int pos { 0 };

        std::cout << "\nDigite a pessoa a ser colocada na fila: ";
        std::cin >> pessoa;
        std::cout << "\nDigite a posicao que devemos colocar esta pessoa: ";
        std::cin >> pos;

        std::vector<int> novaFila { insert(elementosDaFila, pessoa, pos) };
        std::cout << "\nNova fila [" << toString(novaFila) << "]\n";
    }
    else {
        std::vector<int> removePares { dance(elementosDaFila) };
        std::cout << "\nFila sem pares [" << toString(removePares) << "]\n";
    }
    
    return 0;
}