#include <iostream>
#include <vector>
#include <sstream>

using std::vector;

/*
FLUXO DA APLICAÇÃO:
    ESCOLA UMA DAS OPÇÕES:

    [1] Busca
        [1] existe: Alguém com o valor X está na fila?
        [2] contar: Quantas vezes o valor X apareceu na fila?
        [3] procurar_valor: Em que posição da fila aparece X pela primeira vez?
        [4] procurar_valor_apos: Dada a posição para iniciar a busca, qual a próxima posição em que aparece X?

    [2] Melhor caso
        [1] procurar_menor: qual o menor valor da lista?
        [2] procurar_maior: qual o maior valor da lista?
        [3] procurar_menor_pos: qual a posição do menor valor da lista?
        [4] procurar_menor_pos_apos: qual a posição do menor valor da lista depois da posição P?
        [5] procurar_melhor_se: qual a posição do HOMEM mais calmo? (menor valor maior que 0)

    [3] Contagem
        [1] calcular_stress_medio: qual a média de stress da fila? (abs)
        [2] mais_homens_ou_mulheres: Na fila existem mais homens ou mulheres?
        [3] qual_metade_eh_mais_estressada: O nível de stress somado de todas as pessoas da primeira metade é maior que o nível de stress somado das pessoas da segunda metade da fila? (abs)
        [4] homens_sao_mais_estressados_que_mulheres: a média do stress dos homens é maior que a das mulheres?
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

    std::cout << "ESCOLA UMA DAS OPCOES:\n[1] Busca\n[2] Melhor \n[3] Contagem\n\nSua escolha: ";
    std::cin >> opcao;

    system("cls");
    
    return opcao;
}

void menu02(int op, std::vector<int> fila){
    switch (op) {
    // BUSCA
    case 1:
        busca(fila);
        break;
    // MELHOR CASO
    case 2:
        break;
    // CONTAGEM
    case 3:
        break;
    }

    system("cls");
}

void busca(std::vector<int> fila){
    int escolha { 0 };
    std::cout << "ESCOLHA UMA DAS OPCOES: \n[1] Alguem com o valor X esta na fila?\n[2] Quantas vezes o valor X apareceu na fila?\n[3] Em que posicao da fila aparece X pela primeira vez?\n[4] Dada a posicao para iniciar a busca, qual a proxima posicao em que aparece X?\n\nSua escolha: ";
    std::cin >> escolha;

    int proc { 0 };
    std::cout << "Digite o valor procurado: ";
    std::cin >> proc;

    switch (escolha) {
    // existe
    case 1:
        for (int i = 0; i < (int) fila.size(); i++) {
            if (fila[i] == proc) {
                std::cout << "SIM";
                break;
            }
        }
        break;
    // contar
    case 2:
        int cont { 0 };

        for (int i = 0; i < (int) fila.size(); i++) {
            if (fila[i] == proc) {
                cont++;
            }
        }
        std::cout << "O valor " << proc << " aparece " << cont << " vezes";
        break;
    // procurar valor
    case 3:
        for (int i = 0; i < (int) fila.size(); i++) {
            if (fila[i] == proc) {
                std::cout << "O valor " << proc << " aparece primeiro na posicao " << i;
                break;
            }
        }
        break;
    // procurar valor apos
    case 4:
        int val { 0 };

        std::cout << "Digite o valor onde deve-se iniciar a busca: ";
        std::cin >> val;

        for (int i = val; i < (int) fila.size(); i++) {
            if (fila[i] == proc) {
                std::cout << "Iniciando da posicao " << val << " " << proc << " aparece na posicao " << i;
                break;
            }
        }
        break;
    }
}

int main() {
    //RECEBENDO ELEMENTOS DA FILA DO USUÁRIO
    std::cout << "Digite as pessoas presentes na fila (separados por espacos): \n";
    std::string entrada;
    getline(std::cin, entrada);
    std::vector<int> elementosDaFila { popularFila(entrada) };

    system("cls");

    int opcaoMenu01 { 0 };
    int opcaoMenu02 { 0 };

    opcaoMenu01 = menu01();

    switch (opcaoMenu01) {
    //[1] Busca
    case 1:
        opcaoMenu02 = 1;
        break;
    //[2] Melhor caso
    case 2:
        opcaoMenu02 = 2;
        break;
    //[3] Contagem
    case 3:
        opcaoMenu02 = 3;
        break;
    }

    menu02(opcaoMenu02, elementosDaFila);

    // AREA DE TESTES
    for (int i = 0; i < (int) elementosDaFila.size(); i++) {
        std::cout << elementosDaFila[i] << '\n';
    }

    return 0;
}