#include <iostream>
#include <vector>
#include <sstream>

/*
[3] CONTAGEM:
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

    std::cout << "\n\nESCOLHA UMA DAS OPCOES:\n";
    std::cout << "[1] Qual a media de stress da fila?\n";
    std::cout << "[2] Na fila existem mais homens ou mulheres?\n";
    std::cout << "[3] O nivel de stress somado de todas as pessoas da primeira metade e maior que o nivel de stress somado das pessoas da segunda metade da fila?\n";
    std::cout << "[4] A media do stress dos homens e maior que a das mulheres?\n\n";
    std::cout << "Sua escolha: ";
    std::cin >> opcao;

    return opcao;
}

float calcularStressMedio(std::vector<int> fila){
    int stress { 0 };
    int somaStress { 0 };

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] < 0)
            somaStress += (fila[i] * (-1));
        else
            somaStress += fila[i];
    }

    stress = somaStress / ((int) fila.size());
    
    return stress;
}

std::string maisHomensOuMulheres(std::vector<int> fila){
    std::string quantidade {};

    int homens { 0 };
    int mulheres { 0 };
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] < 0) mulheres++;
        else homens++;
    }

    if (homens > mulheres)
        quantidade = "homens";
    else if (mulheres > homens)
        quantidade = "mulheres";
    else
        quantidade = "empate";

    return quantidade;
}

std::string qualMetadeEhMaisEstressada(std::vector<int> fila){
    std::string maisStress {};

    int metade = ((int) fila.size()) / 2;
    int metade1 { 0 };
    int metade2 { 0 };

    for (int i = 0; i < metade; i++) {
        if (fila[i] < 0)
            metade1 += fila[i] * (-1);
        else
            metade1 += fila[i];
    }

    for (int i = metade; i < (int) fila.size(); i++) {
        if (fila[i] < 0)
            metade2 += fila[i] * (-1);
        else
            metade2 += fila[i];
    }

    if (metade1 > metade2)
        maisStress = "primeira";
    else if (metade2 > metade1)
        maisStress = "segunda";
    else
        maisStress = "empate";

    return maisStress;
}

std::string homensSaoMaisEstressadosQueMulheres(std::vector<int> fila){
    std::string sMaisStress {};

    int stressHomens { 0 };
    int stressMulheres { 0 };

    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] > 0)
            stressHomens += fila[i];
        else
            stressMulheres += fila[i] * (-1);
    }

    if (stressHomens > stressMulheres)
        sMaisStress = "homens";
    else if (stressMulheres > stressHomens)
        sMaisStress = "mulheres";
    else
        sMaisStress = "empate";

    return sMaisStress;
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
        std::cout << "\nA media de stress da fila e " << calcularStressMedio(elementosDaFila);
        break;
    case 2:
        std::cout << "\nNa fila ha mais " << maisHomensOuMulheres(elementosDaFila);
        break;
    case 3:
        std::cout << "\nA metade mais estressada e a " << qualMetadeEhMaisEstressada(elementosDaFila) << " metade";
        break;
    case 4:
        std::cout << "\nOs/As mais estressados(as) sao " << homensSaoMaisEstressadosQueMulheres(elementosDaFila);
        break;
    }

    return 0;
}