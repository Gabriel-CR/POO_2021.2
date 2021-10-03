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

std::string existe(std::vector<int> fila, int pc){
    int ver { 0 };
    std::string res {};

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == pc) {
            res = "aparece";
            ver++;
            break;
        }
    }

    if (ver == 0) {
        res = "nao aparece";
    }

    return res;
}

int contar(std::vector<int> fila, int proc){
    int contador { 0 };

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == proc)
            contador++;
    }

    return contador;
}

int procurarValor(std::vector<int> fila,int proc) {
    int posicao {(int) fila.size() + 1};

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == proc && i < posicao) 
            posicao = i;
    }

    return posicao;
}

int procurarValorApos(std::vector<int> fila, int proc, int initProc){
    int posicao { (int) fila.size() + 1 };
    
    for (int i = initProc; i < (int) fila.size(); i++) {
        if (fila[i] == proc && i < posicao) {
            posicao = i;
            break;
        }
    }

    return posicao;
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
        int proc { 0 };
        std::cout << "\n\nDigite o elemento procurado: ";
        std::cin >> proc;

        std::cout << "O valor " << proc << " " << existe(elementosDaFila, proc) << " na fila";
    }
    else if (opcaoMenu == 2) {
        int valorProcurado { 0 };
        std::cout << "\n\nDigite o elemento a ser contado: ";
        std::cin >> valorProcurado;

        std::cout << "\n" <<valorProcurado << " aparece na fila " << contar(elementosDaFila, valorProcurado) << " vezes";
    }
    else if (opcaoMenu == 3) {
        int valorProcurado { 0 };
        std::cout << "\n\nDigite o valor procurado: ";
        std::cin >> valorProcurado;

        std::cout << "\n" << valorProcurado << " aparece pela primeira vez na posicao " << procurarValor(elementosDaFila, valorProcurado);
    }
    else {
        int valorProcurado { 0 };
        std::cout << "\n\nDigite o valor procurado: ";
        std::cin >> valorProcurado;

        int posicaoIniciarProcura { 0 };
        std::cout << "Posicao para iniciar a procurar: ";
        std::cin >> posicaoIniciarProcura;

        std::cout << "O valor " << valorProcurado << " aparece na posicao " << procurarValorApos(elementosDaFila, valorProcurado, posicaoIniciarProcura);
    }

    return 0;
}