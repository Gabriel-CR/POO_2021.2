#include <iostream>
#include <vector>

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

int menu01(){
    int opcao { 0 };

    std::cout << "ESCOLA UMA DAS OPCOES:\n[1] Busca\n[2] Melhor \n[3] Contagem\n\nSua escolha: ";
    std::cin >> opcao;
    
    return opcao;
}

int busca(){
    int opcao { 0 };

    std::cout << "[1] Alguem com o valor X esta na fila?\n[2] Quantas vezes o valor X apareceu na fila?\n[3] Em que posicao da fila aparece X pela primeira vez?\n[4] Dada a posicao para iniciar a busca, qual a proxima posicao em que aparece X?\n\nSua escolha: ";
    std::cin >> opcao;

    return opcao;
}

int melhorCaso(){
    int opcao { 0 };

    std::cout << "[1] Qual o menor valor da lista?\n[2] Qual o maior valor da lista?\n[3] Qual a posicao do menor valor da lista?\n[4] Qual a posicao do menor valor da lista depois da posicao P?\n[5] Qual a posicao do HOMEM mais calmo? (menor valor maior que 0)\n\nSua escolha: ";
    std::cin >> opcao;

    return opcao;
}

int contagem(){

}

int main() {
    int opcaoMenu01 { 0 };
    int opcaoMenu02 { 0 };

    opcaoMenu01 = menu01();

    switch (opcaoMenu01) {
    //[1] Busca
    case 1:
        opcaoMenu02 = busca();
        break;
    //[2] Melhor caso
    case 2:
        opcaoMenu02 = melhorCaso();
        break;
    //[3] Contagem
    case 3:
        opcaoMenu02 = contagem();
        break;
    default:
        std::cout << "[ERRO] Escolha uma opcao valida!";
        break;
    }

    std::cout << opcaoMenu02 << '\n';

    return 0;
}