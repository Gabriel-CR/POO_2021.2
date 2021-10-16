#include <iostream>
#include <vector>
#include <sstream>

/*
[10] GRUPOS:
    [1] casais: Casais são formados quando quando um homem e uma mulher com o mesmo nível de stress são formados. O 3 e o -3 formam um casal. Os participantes fossem orientados a sair da fila e procurar seu par. Quantos casais poderiam ser formados?
    [2] trios: Pedimos pros participantes se organizassem em trios. Todos os 3 deveriam estar com o mesmo nível de stress.Quantos trios podem ser formados?
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
    std::cout << "[1] Quantos casais podem ser formados?\n";
    std::cout << "[2] Quantos trios podem ser formados?\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

int casais(const std::vector<int> fila){
    int casal { 0 };
    
    for (int i = 0; i < (int) fila.size(); i++) {
        for (int j = 0; j < (int) fila.size(); j++) {
            if (fila[i] > 0 && fila[j] < 0 && abs(fila[i]) == abs(fila[j])) {
                casal++;
                i++;
            }
        }        
    }
    
    return casal;
}

int trios(const std::vector<int> fila){
    int tri { 0 };

    for (int i = 0; i < (int) fila.size(); i++) {
        for (int j = i + 1; j < (int) fila.size(); j++) {
            for (int k = j + 1; k < (int) fila.size(); k++) {
                if (abs(fila[i]) == abs(fila[j]) && abs(fila[j]) == abs(fila[k]))
                    tri++;
            }
        }
    }

    return tri;
}

int main(){
    //RECEBENDO ELEMENTOS DA FILA DO USUÁRIO
    std::cout << "Digite as pessoas presentes na fila: ";
    std::string entrada;
    getline(std::cin, entrada);
    std::vector<int> elementosDaFila { popularFila(entrada) };

    int opcaoMenu { 0 };
    opcaoMenu = menu01();

    if (opcaoMenu == 1)
        std::cout << "\nPodem ser formados " << casais(elementosDaFila) << " casais com os integrantes da fila.\n";
    else
        std::cout << "\nPodem ser formados " << trios(elementosDaFila) << " trios com os integrantes da fila.\n";
    
    return 0;
}