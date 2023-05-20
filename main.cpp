///TRABALHO FEITO PELOS ALUNOS: RAFAEL FERNANDO DOS REIS MECABÔ, MATHEUS ARMANDO TIMM BARBIERI
#include <iostream>
#include "utils.hpp"
#include "lue.hpp"

#define TAM 16
using namespace std;

int calcularEndereco(int num) { ///calcula endereço do HASH
    return num % TAM;
}

template<typename T>
bool inserirHashGeral(Lista<T> lst[], const std::string &info) {
    if (validaString(info)) {
        int chave = stoi(info);
        int pos = calcularEndereco(chave);
        return inserir(lst[pos], info);
    } else {
        std::cout << "input inválido." << std::endl;
        return false;
    }
}

template<typename T>
bool buscarHashMatricula(T lista[], string info) {
    if (validaString(info)) {
        int chave = stoi(info);
        int pos = calcularEndereco(chave);
        cout << "posicao: " << pos << endl;
        return (buscarMatricula(lista[pos], info) == nullptr) ? false : true;;
    } else {
        cout << "input inválido." << endl;
        return false; // Return nullptr for invalid input
    }
}

int main() {
    system("cls");
    Lista<Livro> listaLivros[TAM];;
    Lista<Revista> listaRevistas[TAM];;
    Lista<Autor> listaAutores[TAM];
    Lista<Editora> listaEditoras[TAM];
    Lista<Usuario> listaUsuarios[TAM];

    int op;
    for (int i = 0; i < TAM; i++) {
        inicializarLista(listaLivros[i]);
        inicializarLista(listaRevistas[i]);
        inicializarLista(listaAutores[i]);
        inicializarLista(listaEditoras[i]);
        inicializarLista(listaUsuarios[i]);

    }
    do {
        string input;
        cout << "Oque quer fazer: " << endl;
        cout << "\t1. Cadastros" << endl;
        cout << "\t2. Pesquisar " << endl;
        cout << "\t3. Mostrar tudo " << endl;
        cout << "\t0. Fim" << endl;
        cin >> op;
        int opcao;
        switch (op) {
            case 1:
                cout << "Digite uma matricula caracteres: " << endl;
                cin >> input;

                cout << "Oque quer cadastrar: " << endl;
                cout << "\t1. Livro" << endl;
                cout << "\t2. Revista" << endl;
                cout << "\t3. Autor" << endl;
                cout << "\t4. Editora" << endl;
                cout << "\t5. Usuario" << endl;
                cin >> opcao;
                if (opcao == 1)
                    inserirHashGeral(listaLivros, input);
                else if (opcao == 2)
                    inserirHashGeral(listaRevistas, input);
                else if (opcao == 3)
                    inserirHashGeral(listaAutores, input);
                else if (opcao == 4)
                    inserirHashGeral(listaEditoras, input);
                else if (opcao == 5)
                    inserirHashGeral(listaUsuarios, input);
                else
                    cout << "Opcao invalida" << endl;
                break;
            case 2:
                cout << "Digite uma matricula caracteres: " << endl;
                cin >> input;

                cout << "Oque quer pesquisar: " << endl;
                cout << "\t1. Livro" << endl;
                cout << "\t2. Revista" << endl;
                cout << "\t3. Autor" << endl;
                cout << "\t4. Editora" << endl;
                cout << "\t5. Usuario" << endl;
                cin >> opcao;

                if (opcao == 1) {
                    if (buscarHashMatricula(listaLivros, input)) {
                        std::cout << "Livro encontrado: " << std::endl;
                        // Faça algo com livroEncontrado

                    } else {
                        std::cout << "Livro não encontrado." << std::endl;
                    }
                } else if (opcao == 2) {
                    if (buscarHashMatricula(listaRevistas, input)) {
                        std::cout << "Revista encontrada: " << std::endl;
                        // Faça algo com revistaEncontrada
                    } else {
                        std::cout << "Revista não encontrada." << std::endl;
                    }
                } else if (opcao == 3) {
                    if (buscarHashMatricula(listaAutores, input)) {
                        std::cout << "Autor encontrado: " << std::endl;
                        // Faça algo com autorEncontrado
                    } else {
                        std::cout << "Autor não encontrado." << std::endl;
                    }
                } else if (opcao == 4) {
                    if (buscarHashMatricula(listaEditoras, input)) {
                        std::cout << "Editora encontrada: " << std::endl;
                        // Faça algo com editoraEncontrada
                    } else {
                        std::cout << "Editora não encontrada." << std::endl;
                    }
                } else if (opcao == 5) {
                    if (buscarHashMatricula(listaUsuarios, input)) {
                        std::cout << "Usuário encontrado: " << std::endl;
                        // Faça algo com usuarioEncontrado
                    } else {
                        std::cout << "Usuário não encontrado." << std::endl;
                    }
                } else {
                    cout << "Opcao invalida!" << endl;
                }
                break;
            case 3:
                cout << "Tabela completa" << endl;
                for (int i = 0; i < TAM; i++) {
                    cout << "\t"<< i << " Livros:" << std::endl;;
                    mostrarLista(listaLivros[i]);
                    mostrarLista(listaRevistas[i]);
                    mostrarLista(listaAutores[i]);
                    mostrarLista(listaEditoras[i]);
                    mostrarLista(listaUsuarios[i]);
                    cout << endl;
                }
                system("pause");

                break;
            case 9:
                cout << "Tabela: " << endl;
                for (int i = 0; i < TAM; ++i) {
                    cout << i << "- ";
                    //mostrarDetalhadoLivro(listaLivros[i], listaAutores, listaEditoras);
                    //mostrarLivro(listaLivros[i], " ");
                    cout << endl;
                }

                system("pause");
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    } while (op != 0);
    cout << endl;
}
