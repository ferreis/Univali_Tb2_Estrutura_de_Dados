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
bool inserirHashGeral(Lista<T> lst[], string info, T cadastro) {
    if (validaString(info)) {
        int chave = stoi(info);
        int pos = calcularEndereco(chave);
        return inserir(lst[pos], info, cadastro);
    } else {
        cout << "input inválido." << endl;
        return false;
    }
}

template<typename T>
bool buscarHash(Lista<T> lista[], int num) {
    int pos = calcularEndereco(num);
    return !(buscarLista(lista[pos], num) == nullptr);
}

template<typename T>
T *receberValor(Lista<T> lista[], int matricula) {
    int pos = calcularEndereco(matricula);
    No<T> *elemento = buscarLista(lista[pos], matricula);
    if (elemento != nullptr) {
        return &(elemento->valor);
    } else {
        return nullptr;
    }
}


template<typename T>
void AlterarLista(Lista<T> &lista, int id) {
    No<T> *atual = lista.inicio;
    while (atual != nullptr) {
        if (atual->valor.id == id) {
            int op;
            cout << "O que deseja alterar?" << endl;
            cout << "\t1 - Alterar Nome" << endl;
            cout << "\t2 - Alterar ID" << endl;
            if constexpr (is_same<T, Livro>::value || is_same<T, Revista>::value) {
                cout << "\t3 - Alterar Editora" << endl;
            }
            if constexpr (is_same<T, Livro>::value) {
                cout << "\t4 - Alterar Autor" << endl;
            }
            // Adicione outras opções de alteração conforme necessário

            cin >> op;
            switch (op) {
                case 1: {
                    string novoNome;
                    cout << "Informe o novo nome: ";
                    cin >> novoNome;
                    atual->valor.nome = novoNome;
                    break;
                }
                case 2: {
                    int novoID;
                    cout << "Informe o novo ID: ";
                    cin >> novoID;
                    atual->valor.id = novoID;
                    break;
                }
                case 3: {
                    int novaEditora;
                    cout << "Informe a nova editora: ";
                    cin >> novaEditora;
                    atual->valor.editora = novaEditora;
                    break;
                }
                case 4: {
                    int novoAutor;
                    cout << "Informe o novo autor: ";
                    cin >> novoAutor;
                    atual->valor.idAutor = novoAutor;
                    break;
                }
                default:
                    cout << "Opção inválida." << endl;
                    break;
            }

            // Se necessário, adicione aqui o código para salvar as alterações no arquivo ou em outro local

            cout << "Registro alterado com sucesso." << endl;
            return;
        }
        atual = atual->proximo;
    }
    cout << "Registro não encontrado." << endl;
}

int precadastro(Lista<Livro> listaLivros[], Lista<Revista> listaRevistas[], Lista<Autor> listaAutores[],
                Lista<Editora> listaEditoras[], Lista<Usuario> listaUsuarios[]) {

    Livro livro;
    string matricula = to_string(gerarNumeroAleatorio());
    livro.nome = "timmbonitao 1";
    livro.extra = "Extra 1";
    livro.matricula = stoi(matricula);
    livro.idAutor = gerarNumeroAleatorio();
    inserirHashGeral(listaLivros, matricula, livro);

    Livro livro2;
    string matricula2 = to_string(1016);
    livro2.nome = "Rafael 2";
    livro2.extra = "Extra 2";
    livro2.matricula = stoi(matricula2);
    livro2.idAutor = gerarNumeroAleatorio();
    inserirHashGeral(listaLivros, matricula2, livro2);

    Livro livro3;
    string matricula3 = to_string(1000);
    livro3.nome = "alauakba 3";
    livro3.extra = "Extra 3";
    livro3.matricula = stoi(matricula3);
    livro3.idAutor = gerarNumeroAleatorio();
    inserirHashGeral(listaLivros, matricula3, livro3);

    Autor autor;
    string matriculaautor = to_string(gerarNumeroAleatorio());
    autor.nome = "Autor 1";
    autor.matricula = stoi(matriculaautor);
    inserirHashGeral(listaAutores, matriculaautor, autor);

    Usuario usuario;
    string matriculauser = to_string(69420);
    usuario.nome = "Ferreis 1";
    usuario.extra = "Extra 1";
    usuario.matricula = stoi(matriculauser);
    inserirHashGeral(listaUsuarios, matriculauser, usuario);
}

int main() {
    setlocale(LC_ALL, "portuguese");
    system("cls");
    Lista<Livro> listaLivros[TAM];
    Lista<Revista> listaRevistas[TAM];
    Lista<Autor> listaAutores[TAM];
    Lista<Editora> listaEditoras[TAM];
    Lista<Usuario> listaUsuarios[TAM];
    Data data1;


    int op;
    for (int i = 0; i < TAM; i++) {
        inicializarLista(listaLivros[i]);
        inicializarLista(listaRevistas[i]);
        inicializarLista(listaAutores[i]);
        inicializarLista(listaEditoras[i]);
        inicializarLista(listaUsuarios[i]);
    }

    precadastro(listaLivros, listaRevistas, listaAutores, listaEditoras, listaUsuarios);
    do {

        cout << endl << endl;
        cout << "---------------------------------------------" << endl;
        cout << "BIBLIOTECA" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "1 - Inserir livro" << endl;
        cout << "2 - Inserir revista" << endl;
        cout << "3 - Inserir autor" << endl;
        cout << "4 - Inserir editora" << endl;
        cout << "5 - Inserir usuário" << endl;
        cout << "6 - Buscar livro por matrícula" << endl;
        cout << "7 - Buscar revista por matrícula" << endl;
        cout << "8 - Buscar autor por matrícula" << endl;
        cout << "9 - Buscar editora por matrícula" << endl;
        cout << "10 - Buscar usuário por matrícula" << endl;
        cout << "11 - Listas simples" << endl;
        cout << "12 - Alugar um livro/revista" << endl;
        cout << "13 - Alterar cadastro" << endl;
        cout << "14 - Sair" << endl;
        cout << "---------------------------------------------" << endl;

        cout << "Digite sua opção: ";
        cin >> op;

        switch (op) {

            case 1: {//inserir livro
                string matricula;
                cout << "Digite a matrícula do livro: ";
                cin >> matricula;
                if (validaString(matricula)) {
                    Livro livro;
                    cin.ignore();
                    cout << "Digite o nome do livro: ";
                    getline(cin, livro.nome);
                    cout << "Digite o assunto do livro: ";
                    getline(cin, livro.extra);
                    cout << "Digite o id do autor: ";
                    cin >> livro.idAutor;
                    cin.ignore();
                    cout << "Digite o id da editora: ";
                    cin >> livro.editora;
                    system("pause");
                    int chaveLivro = calcularEndereco(stoi(matricula));
                    int chaveAutor = calcularEndereco(livro.idAutor);
                    inserirHashGeral(listaLivros, matricula, livro);
                    vincularLivrosAutor(listaLivros[chaveLivro], listaAutores[chaveAutor]);
                } else {
                    cout << "Entrada inválida." << endl;

                }
                break;
            }
            case 2: {//inserir revista

                string matricula;
                cout << "Digite a matrícula da revista: ";
                cin >> matricula;
                if (validaString(matricula)) {
                    Revista revista;
                    cin.ignore();
                    cout << "Digite o nome do livro: ";
                    getline(cin, revista.nome);
                    cout << "Digite o assunto do livro: ";
                    getline(cin, revista.extra);
                    cin.ignore();
                    cout << "Digite o id da editora: ";
                    cin >> revista.editora;
                    int chaveRevista = calcularEndereco(stoi(matricula));
                    int chaveEditora = calcularEndereco(revista.editora);
                    vincularRevistasEditora(listaRevistas[chaveRevista], listaEditoras[chaveEditora]);
                    inserirHashGeral(listaRevistas, matricula, revista);
                } else {
                    cout << "Entrada inválida." << endl;
                }
                break;
            }
            case 3: {//inserir autor
                string matricula;
                cout << "Digite a matrícula do autor: ";
                cin >> matricula;

                if (validaString(matricula)) {
                    Autor autor;
                    cin.ignore();
                    cout << "Digite o nome do autor: ";
                    getline(cin, autor.nome);
                    cin.ignore();
                    cout << "Digite a observacao: ";
                    getline(cin, autor.extra);
                    cin.ignore();
                    autor.matricula = stoi(matricula);
                    int chaveAutor = calcularEndereco(autor.matricula);
                    inserirHashGeral(listaAutores, matricula, autor);
                } else {
                    cout << "Entrada inválida." << endl;

                }
                break;
            }
            case 4: {//inserir editora
                string matricula;
                cout << "Digite a matrícula da editora: ";
                cin >> matricula;

                if (validaString(matricula)) {
                    Editora editora;
                    cin.ignore();
                    cout << "Digite o nome da editora: ";
                    getline(cin, editora.nome);
                    cin.ignore();
                    cout << "Digite a observacao: ";
                    getline(cin, editora.extra);
                    cin.ignore();
                    editora.matricula = stoi(matricula);
                    int chaveEditora = calcularEndereco(editora.matricula);
                    inserirHashGeral(listaEditoras, matricula, editora);
                } else {
                    cout << "Entrada inválida." << endl;

                }
                break;
            }
            case 5: {//inserir usuario
                string matricula;
                cout << "Digite a matrícula do usuario: ";
                cin >> matricula;

                if (validaString(matricula)) {
                    Usuario usuario;
                    cin.ignore();
                    cout << "Digite o nome do usuario: ";
                    getline(cin, usuario.nome);
                    cin.ignore();
                    cout << "Digite a observacao: ";
                    getline(cin, usuario.extra);
                    cin.ignore();
                    usuario.matricula = stoi(matricula);
                    int chaveUsuario = calcularEndereco(usuario.matricula);
                    inserirHashGeral(listaUsuarios, matricula, usuario);
                } else {
                    cout << "Entrada inválida." << endl;

                }
                break;
            }
            case 6: {//buscar livro
                string matricula;
                cout << "Digite a matrícula do livro: ";
                cin >> matricula;
                if (buscarHash(listaLivros, stoi(matricula))) {
                    mostrarLista(listaLivros[calcularEndereco(stoi(matricula))]);
                } else {
                    cout << "Livro não encontrado." << endl;
                }
                break;
            }
            case 7: {//buscar revista
                string matricula;
                cout << "Digite a matrícula da revista: ";
                cin >> matricula;
                if (buscarHash(listaRevistas, stoi(matricula))) {
                    mostrarLista(listaRevistas[calcularEndereco(stoi(matricula))]);
                } else {
                    cout << "Revista não encontrada" << endl;
                }
            }
            case 8: {//buscar autor
                string matricula;
                cout << "Digite a matrícula do autor: ";
                cin >> matricula;
                if (buscarHash(listaAutores, stoi(matricula))) {
                    mostrarLista(listaAutores[calcularEndereco(stoi(matricula))]);
                } else {
                    cout << "Autor não encontrado" << endl;
                }
                break;
            }
            case 9: {//buscar editora
                string matricula;
                cout << "Digite a matrícula da editora: ";
                cin >> matricula;
                if (buscarHash(listaEditoras, stoi(matricula))) {
                    mostrarLista(listaEditoras[calcularEndereco(stoi(matricula))]);
                } else {
                    cout << "Editora não encontrada." << endl;
                }
                break;
            }
            case 10: {//buscar usuario
                string matricula;
                cout << "Digite a matrícula do usuário: ";
                cin >> matricula;
                if (buscarHash(listaUsuarios, stoi(matricula))) {
                    mostrarLista(listaUsuarios[calcularEndereco(stoi(matricula))]);
                } else {
                    cout << "Usuario não encontrado." << endl;
                }
                break;
            }
            case 11: {//mostrar tudo
                cout << "Listas simples:  " << endl;
                for (int i = 0; i < TAM; ++i) {
                    cout << "Lista " << i << ": " << endl;
                    cout << "Livros|-> " << endl;
                    mostrarLista(listaLivros[i]);
                    cout << "Revista|->  " << endl;
                    mostrarLista(listaRevistas[i]);
                    cout << "Autores|->  " << endl;
                    mostrarLista(listaAutores[i]);
                    cout << "Editoras|->  " << endl;
                    mostrarLista(listaEditoras[i]);
                    cout << "Usuarios|->  " << endl;
                    mostrarLista(listaUsuarios[i]);
                }
                break;
            }
            case 12: {//alugar
                string aux, aux2;
                string matricula;
                cout << "Diga a data em que você deseja alugar o livro/revista: " << endl;
                cin >> data1.dia >> data1.mes >> data1.ano;

                cout << "Diga sua matrícula: " << endl;
                cin >> matricula;
                int chaveusuario = calcularEndereco(stoi(matricula));
                if (buscarHash(listaUsuarios, stoi(matricula))) {
                    cout << "O que deseja alugar? [1 = livro, 2 = revista]: " << endl;
                    cin >> aux;
                    if (stoi(aux) == 1) {//livro
                        for (int i = 0; i < TAM; ++i) {

                            cout << "\tLista " << i << ": " << endl;
                            mostrarLista(listaLivros[i]);
                        }
                        cout << "Qual a matricula do livro que deseja alugar?" << endl;
                        cin >> matricula;
                        if (buscarHash(listaLivros, stoi(matricula))) {
                            int chaveLivro = calcularEndereco(stoi(matricula));
                            Usuario usuarioInput = *receberValor(&listaUsuarios[chaveusuario], chaveusuario);
                            Livro livroInput = *receberValor(&listaLivros[chaveLivro], chaveLivro);
                            retirarLivro(usuarioInput, livroInput, data1);

                        } else {
                            cout << "Livro não encontrado." << endl;
                        }

                    } else if (stoi(aux) == 2) {//revista
                        for (int i = 0; i < TAM; ++i) {
                            cout << "Lista " << i << ": " << endl;
                            mostrarLista(listaRevistas[i]);
                            cout << "Qual a matricula da revista que deseja alugar?" << endl;
                            cin >> matricula;
                            if (buscarHash(listaRevistas, stoi(matricula))) {
                                int chaveRevista = calcularEndereco(stoi(matricula));
                                Usuario usuarioInput = *receberValor(&listaUsuarios[chaveusuario], chaveusuario);
                                Revista revistaInput = *receberValor(&listaRevistas[chaveRevista], chaveRevista);
                                retirarRevista(usuarioInput, revistaInput, data1);
                            } else {
                                cout << "Revista não encontrada." << endl;
                            }
                        }
                    } else {
                        cout << "Opção indisponível." << endl;
                    }
                } else {
                    cout << "Usuário não encontrado." << endl;
                }

                break;
            }
            case 13: {

                break;
            }
            default:
                cout << "Opção inválida." << endl;
        }

    } while (op != 14);


    return 0;
}