#include <iostream>
#include <vector>
#include <sstream>

/*
[1] Busca
    [1] existe: Alguém com o valor X está na fila?
    [2] contar: Quantas vezes o valor X apareceu na fila?
    [3] procurar_valor: Em que posição da fila aparece X pela primeira vez?
    [4] procurar_valor_apos: Dada a posição para iniciar a busca, qual a próxima posição em que aparece X?
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
    std::cout << "[1] Alguem com o valor X esta na fila?\n";
    std::cout << "[2] Quantas vezes o valor X apareceu na fila?\n";
    std::cout << "[3] Em que posicao da fila aparece X pela primeira vez?\n";
    std::cout << "[4] Dada a posicao para iniciar a busca, qual a proxima posicao em que aparece X?\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

void existe(std::vector<int> fila){
    int proc { 0 };
    std::cout << "\n\nDigite o elemento procurado: ";
    std::cin >> proc;

    int ver { 0 };
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == proc) {
            std::cout << "\nO valor " << proc << " aparece na fila";
            ver++;
            break;
        }
    }

    if (ver == 0) {
        std::cout << "\nO valor " << proc << " nao aparece na fila";
    }
}

void contar(std::vector<int> fila){
    int valorProcurado { 0 };
    std::cout << "\n\nDigite o elemento a ser contado: ";
    std::cin >> valorProcurado;

    int contador { 0 };
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == valorProcurado)
            contador++;
    }

    std::cout << "\n" <<valorProcurado << " aparecena fila " << contador << " vezes";
}

void procurarValor(std::vector<int> fila) {
    int valorProcurado { 0 };
    std::cout << "\n\nDigite o valor procurado: ";
    std::cin >> valorProcurado;

    int posicao {(int) fila.size() + 1};
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == valorProcurado && i < posicao) 
            posicao = i;
    }

    if (posicao < ((int) fila.size() + 1)) 
        std::cout << "\n" << valorProcurado << " aparece pela primeira vez na posicao " << posicao;
    else
        std::cout << "\n" << valorProcurado << " nao aparece na fila";
}

void procurarValorApos(std::vector<int> fila){
    int valorProcurado { 0 };
    std::cout << "\n\nDigite o valor procurado: ";
    std::cin >> valorProcurado;

    int posicaoIniciarProcura { 0 };
    std::cout << "Posicao para iniciar a procurar: ";
    std::cin >> posicaoIniciarProcura;

    int posicao {(int) fila.size() + 1};
    for (int i = posicaoIniciarProcura; i < (int) fila.size(); i++) {
        if (fila[i] == valorProcurado && i < posicao) {
            posicao = i;
            break;
        }
    }

    if (posicao < ((int) fila.size() + 1))
        std::cout << "\n" << "O valor " << valorProcurado << " aparece na posicao " << posicao;
    else
        std::cout << "\n" << "O valor " << valorProcurado << " nao aparece na fila se iniciarmos a contagem da posicao " << posicaoIniciarProcura;
}

int main(){
    //RECEBENDO ELEMENTOS DA FILA DO USUÁRIO
    std::cout << "Digite as pessoas presentes na fila: ";
    std::string entrada;
    getline(std::cin, entrada);
    std::vector<int> elementosDaFila { popularFila(entrada) };

    int opcaoMenu { 0 };
    opcaoMenu = menu01();

    switch (opcaoMenu) {
    case 1:
        existe(elementosDaFila);
        break;
    case 2:
        contar(elementosDaFila);
        break;
    case 3:
        procurarValor(elementosDaFila);
        break;
    case 4:
        procurarValorApos(elementosDaFila);
        break;
    }

    return 0;
}