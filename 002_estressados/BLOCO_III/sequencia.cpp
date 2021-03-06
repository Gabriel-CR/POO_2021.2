#include <iostream>
#include <vector>
#include <sstream>

/*
[7] SEQUÊNCIA:
    [1] quantos_times Duas ou mais pessoas do mesmo sexo seguidas podem formar um time. Quantos times existem na fila?
    [2] maior_time Qual o maior time que apareceu na fila?
    [3] sozinhos Quantas pessoas não estavam em um time?
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
    std::cout << "[1] Quantos times existem na fila?\n";
    std::cout << "[2] Qual o maior time que apareceu na fila?\n";
    std::cout << "[3] Quantas pessoas nao estavam em um time?\n\n";
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

int quantosTimes(std::vector<int> fila){
    int times { 0 };
    int cont { 0 };
    
    for (int i { 0 }; i < (int) fila.size(); i++) {
        cont = 0;

        while (fila[i] > 0) {
            i++;
            cont++;
        }
        if (cont > 1)
            times++;
        
        while (fila[i] < 0) {
            i++;
            cont++;
        }
        if (cont > 1)
            times++;          
    }

    return times;
}

std::vector<int> maiorTime(const std::vector<int> fila){
    std::vector<int> time;
    int maior { 0 };
    int pos { 0 };
    int cont { 0 };

    for (int i { 0 }; i < (int) fila.size(); i++) {
        cont = 0;

        while (fila[i] > 0) {
            i++;
            cont++;
        }
        if (cont > maior) {
            maior = cont;
            pos = i - cont;
        }

        cont = 0;

        while (fila[i] < 0) {
            i++;
            cont++;
        }
        if (cont > maior) {
            maior = cont;
            pos = i - cont;
        }
            
    }

    //std::cout << "\npos: " << pos << "\ntam: " << maior << '\n';

    for (int j = pos; j < (maior + pos); j++)
        time.push_back(fila[j]);

    return time;
}

int sozinhos(const std::vector<int> fila){
    int so { 0 };
    int tam = (int) fila.size();

    for (int i = 0; i < tam; i++) {
        if (i == 0) {
            if ((fila[i] > 0 && fila[i + 1] < 0) || (fila[i] < 0 && fila[i + 1] > 0))
                so++;
        }
        else if (fila[i] > 0) {
            if (fila[i - 1] < 0 && fila[i + 1] < 0)
                so++;
        }
        else if (fila[i] < 0) {
            if (fila[i - 1] > 0 && fila[i + 1] > 0)
                so++;
        }
        else {
            if ((fila[i - 1] > 0 && fila[i] < 0) || (fila[i - 1] < 0 && fila[i] > 0))
                so++;
        }
    }

    return so;
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
        std::cout << "\nExistem " << quantosTimes(elementosDaFila) << " times na fila.\n";
    }
    else if (opcaoMenu == 2) {
        std::vector<int> maior { maiorTime(elementosDaFila) };
        std::cout << "\nO maior time na fila e o [" << toString(maior) << "] com " << (int) maior.size() << " elementos\n";
    }
    else {
        std::cout << "\nExistem " << sozinhos(elementosDaFila) << " pessoas sem time na fila.\n";
    }
    
    return 0;
}