#include <iostream>
#include <vector>

int main(){
    std::vector<int> fila;
    int* p;

    for (int i = 0; i < 11; i++)
        fila.push_back(i);

    std::cout << fila.back() << std::endl;

    return 0;
}