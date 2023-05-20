///TRABALHO FEITO PELOS ALUNOS: RAFAEL FERNANDO DOS REIS MECABÔ, MATHEUS ARMANDO TIMM BARBIERI
//
// Created by rafa_ on 17/05/2023.
//
#include <iostream>
#include <random>

using namespace std;


#ifndef TB2_ESTRUTURA_DE_DADOS_MAIN_UTILS_HPP
#define TB2_ESTRUTURA_DE_DADOS_MAIN_UTILS_HPP

int gerarNumeroAleatorio() {
    // Inicializar o gerador de números aleatórios com um valor de semente
    random_device rd;
    mt19937 generator(rd());

    // Definir a faixa de valores aleatórios (de 0 a 99999)
    std::uniform_int_distribution<int> distribution(0, 99999);

    // Gerar e retornar um número aleatório
    return distribution(generator);
}

template<typename T>
string validarUppercase(T texto) {
    string uppercaseString;
    for (char c: texto) {
        uppercaseString += toupper(c);
    }
    return uppercaseString;
}

bool validaString(const string &str) {
    if (str.length() > 5) {
        return false;
    }

    for (char c: str) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}

#endif //TB2_ESTRUTURA_DE_DADOS_MAIN_UTILS_HPP
