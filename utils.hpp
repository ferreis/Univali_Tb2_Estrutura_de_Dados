///TRABALHO FEITO PELOS ALUNOS: RAFAEL FERNANDO DOS REIS MECABÔ, MATHEUS ARMANDO TIMM BARBIERI
//
// Created by rafa_ on 17/05/2023.
//
#include <iostream>
#include <random>
#include <string.h>
#include <vector>
#include <ctime>

using namespace std;


#ifndef TB2_ESTRUTURA_DE_DADOS_MAIN_UTILS_HPP
#define TB2_ESTRUTURA_DE_DADOS_MAIN_UTILS_HPP

struct Data {
    int dia;
    int mes;
    int ano;
};

bool anoBissexto(int ano) {
    return ((ano % 4 == 0) && ((!(ano % 100 == 0)) ||
                               (ano % 400 == 0)));
}

bool soma7dias(Data &data) {
    int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (anoBissexto(data.ano)) dias[2] = 29;

    data.dia += 7;

    // Verifica se ultrapassou o número de dias do mês
    if (data.dia > dias[data.mes - 1]) {
        data.dia -= dias[data.mes - 1];
        data.mes++;

        // Verifica se ultrapassou o número de meses no ano
        if (data.mes > 12) {
            data.mes = 1;
            data.ano++;
        }
    }
    return true;
}


int gerarNumeroAleatorio() {
    // Inicializar o gerador de números aleatórios com um valor de semente
    random_device rd;
    mt19937 generator(rd());

    // Definir a faixa de valores aleatórios (de 0 a 99999)
    uniform_int_distribution<int> distribution(0, 99999);

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
    if (str.empty() || str.length() > 5) {
        return false;
    }

    if (str[0] == '-') {
        return false;
    }

    for (char c: str) {
        if (c < '0' || c > '9') {
            return false;
        }
    }

    return true;
}

bool validaChar(const char str[250]) {
    if (strlen(str) > 5) {
        return false;
    }

    for (int i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }

    return true;
}

#endif //TB2_ESTRUTURA_DE_DADOS_MAIN_UTILS_HPP
