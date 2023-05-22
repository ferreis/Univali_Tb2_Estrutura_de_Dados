///TRABALHO FEITO PELOS ALUNOS: RAFAEL FERNANDO DOS REIS MECABÔ, MATHEUS ARMANDO TIMM BARBIERI
#include <iostream>
#include "utils.hpp"
#include <ctime>

#define TAM = 16
struct Autor;

template<typename T>
struct No {
    T valor;
    No<T> *proximo;
};
template<typename T>
struct Lista {
    No<T> *inicio;
    No<T> *fim;
};
struct Livro {
    int matricula;
    int idAutor;
    int editora;
    string nome;
    string extra;
    No<Livro> *proximo;
    Data dataRetirada;
};
struct Revista {
    int matricula;
    int editora;
    string nome;
    string extra;
    No<Revista> *proximo;
    Data dataRetirada;
};
struct Autor {
    int matricula;
    string nome;
    string extra;
    No<Autor> *proximo;
    Lista<Livro> listaLivros;
};
struct Editora {
    int matricula;
    string nome;
    string extra;
    No<Editora> *proximo;
    Lista<Autor> listaAutores;
    Lista<Revista> listaRevistas;
    Lista<Livro> listaLivros;
};
struct Usuario {
    int matricula;
    string nome;
    string extra;
    No<Usuario> *proximo;
    Livro *livroRetirado;
    Revista *listaRevistas;
};

template<typename T>
void inicializarLista(Lista<T> &lista) {
    lista.inicio = nullptr;
    lista.fim = nullptr;
}

template<typename T>
T *buscarElemento(Lista<T> &lista, int matricula) {
    No<T> *atual = lista.inicio;
    while (atual != nullptr) {
        if (atual->valor.matricula == matricula) {
            return &(atual->valor);
        }
        atual = atual->proximo;
    }
    return nullptr; // Elemento não encontrado
}

template<typename T>
No<T> *buscarLista(Lista<T> lista, int valor) {
    No<T> *aux = lista.inicio;
    while (aux != NULL) {
        if (aux->valor.matricula == valor) return aux;
        aux = aux->valor.proximo;
    }
    return NULL;
}

template<typename T, typename T2>
bool inserir(Lista<T> &lst, string info, T2 cadastro) {
    No<T> *novo = new No<T>;
    if (novo == nullptr) {
        return false;
    }

    int matricula = stoi(info);
    T valor = cadastro;
    novo->valor = valor;
    novo->proximo = nullptr;

    // Verifica se a lista está vazia
    if (lst.inicio == nullptr) {
        lst.inicio = novo;
        lst.fim = novo;
        return true;
    }

    // Inserir no início da lista
    if (matricula < lst.inicio->valor.matricula) {
        novo->proximo = lst.inicio;
        lst.inicio = novo;
        return true;
    }

    // Inserir no final da lista
    if (matricula > lst.fim->valor.matricula) {
        lst.fim->proximo = novo;
        lst.fim = novo;
        return true;
    }

    // Inserir no meio da lista
    No<T> *anterior = lst.inicio;
    while (anterior->proximo != nullptr && anterior->proximo->valor.matricula < matricula) {
        anterior = anterior->proximo;
    }
    novo->proximo = anterior->proximo;
    anterior->proximo = novo;
    return true;
}

void inserir(No<Livro> *livro, Lista<Livro> &lista) {
    if (lista.inicio == nullptr) {
        lista.inicio = livro;
        livro->proximo = nullptr;
    } else {
        No<Livro> *ultimo = lista.inicio;
        while (ultimo->proximo != nullptr) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = livro;
        livro->proximo = nullptr;
    }
}

template<typename T>
T obterInformacoes(string matricula) {
    T objeto;

    cout << "Digite as informações do objeto com a matrícula " << matricula << ":" << endl;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, objeto.nome);
    cout << "Extra: ";
    getline(cin, objeto.extra);

    // Preencha os campos adicionais específicos de cada tipo
    if constexpr (is_same<T, Livro>::value) {
        cout << "Matrícula: ";
        cin >> objeto.matricula;
        cout << "Autor: ";
        cin >> objeto.autor;
        cout << "Editora: ";
        cin >> objeto.editora;
        vincularLivros(objeto.listaLivros, objeto.listaLivros);

    } else if constexpr (is_same<T, Revista>::value) {
        cout << "Matrícula: ";
        cin >> objeto.matricula;
        cout << "Editora: ";
        cin >> objeto.editora;
    } else if constexpr (is_same<T, Autor>::value) {
        cout << "Matrícula: ";
        cin >> objeto.matricula;
    } else if constexpr (is_same<T, Editora>::value) {
        cout << "Matrícula: ";
        cin >> objeto.matricula;
    } else if constexpr (is_same<T, Usuario>::value) {
        cout << "Matrícula: ";
        cin >> objeto.matricula;
    }
    return objeto;
}

template<typename T>
bool RemoverElemento(Lista<T> &lista, int id) {
    No<T> *atual = lista.inicio;
    No<T> *anterior = nullptr;

    while (atual != nullptr) {
        if (atual->valor.id == id) {
            if (anterior == nullptr) {
                // O elemento a ser removido está no início da lista
                lista.inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            delete atual;
            cout << "Elemento removido com sucesso." << endl;
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    cout << "Elemento não encontrado na lista." << endl;
    return false;
}

template<typename T>
void mostrarLista(Lista<T> lista) {
    if (lista.inicio == nullptr) cout << "\t\t|-> vazia" << endl;

    No<T> *aux = lista.inicio;
    while (aux != nullptr) {

        cout << "\t________________________________________________: " << endl;
        cout << "\t\t|->Matricula:" << aux->valor.matricula << " - ";
        cout << "\t\t| Titulo: " << aux->valor.nome << " | Assunto: " << aux->valor.extra << endl;
        cout << "\t\t|________________________________________________: " << endl;

        aux = aux->proximo;
        cout << endl;
    }
}

void vincularLivrosAutor(Lista<Livro> &listaLivros, Lista<Autor> &listaAutores) {
    No<Livro> *livroAtual = listaLivros.inicio;
    while (livroAtual != nullptr) {
        No<Autor> *autorAtual = listaAutores.inicio;
        while (autorAtual != nullptr) {
            if (autorAtual->valor.matricula == livroAtual->valor.idAutor) {
                autorAtual->valor.listaLivros = listaLivros;
                break;
            }
            autorAtual = autorAtual->proximo;
        }
        livroAtual = livroAtual->proximo;
    }
}

void vincularRevistasEditora(Lista<Revista> &listaRevistas, Lista<Editora> &listaEditoras) {
    No<Revista> *revistaAtual = listaRevistas.inicio;
    while (revistaAtual != nullptr) {
        No<Editora> *editoraAtual = listaEditoras.inicio;
        while (editoraAtual != nullptr) {
            if (editoraAtual->valor.matricula == revistaAtual->valor.editora) {
                editoraAtual->valor.listaRevistas = listaRevistas;
                break;
            }
            editoraAtual = editoraAtual->proximo;
        }
        revistaAtual = revistaAtual->proximo;
    }
}

void mostrarLivrosAutores(Lista<Livro> &listaLivros, Lista<Autor> listaAutores) {
    if (listaLivros.inicio == nullptr || listaAutores.inicio == nullptr) {
        cout << "A lista de livros ou a lista de autores está vazia." << endl;
        return;
    }

    No<Livro> *livroAux = listaLivros.inicio;
    while (livroAux != nullptr) {
        int idAutor = livroAux->valor.idAutor;
        No<Autor> *autorAux = buscarLista(listaAutores, idAutor);
        if (autorAux != nullptr) {
            cout << "Livro: " << livroAux->valor.nome << " | Autor: " << autorAux->valor.nome << endl;
        } else {
            cout << "Livro: " << livroAux->valor.nome << " | Editora: " << livroAux->valor.editora << endl;
        }
        livroAux = livroAux->proximo;
    }
}

void vincularLivrosAutores(Lista<Livro> *listaLivros, Lista<Autor> *listaAutores) {
    No<Livro> *livroAtual = listaLivros->inicio;
    while (livroAtual != nullptr) {
        int idAutor = livroAtual->valor.idAutor;
        No<Autor> *autorAtual = listaAutores->inicio;
        while (autorAtual != nullptr) {
            if (autorAtual->valor.matricula == idAutor) {
                inserir(livroAtual, autorAtual->valor.listaLivros);
                break;
            }
            autorAtual = autorAtual->proximo;
        }
        livroAtual = livroAtual->proximo;
    }
}


void retirarLivro(Usuario &usuario, Livro &livro, Data &data1) {

    soma7dias(data1);

    usuario.livroRetirado->dataRetirada.dia = data1.dia;
    usuario.livroRetirado->dataRetirada.mes = data1.mes;
    usuario.livroRetirado->dataRetirada.ano = data1.ano;

    cout << "Livro retirado com sucesso!" << endl;
    cout << "Data de retirada: " << usuario.livroRetirado->dataRetirada.dia << "/"
              << usuario.livroRetirado->dataRetirada.mes << "/" << usuario.livroRetirado->dataRetirada.ano << endl;
}

void retirarRevista(Usuario &usuario, Revista &revista, Data &data1) {

    soma7dias(data1);

    usuario.listaRevistas->dataRetirada.dia = data1.dia;
    usuario.listaRevistas->dataRetirada.mes = data1.mes;
    usuario.listaRevistas->dataRetirada.ano = data1.ano;

    cout << "Revista retirada com sucesso!" << endl;
    cout << "Data de retirada: " << usuario.listaRevistas->dataRetirada.dia << "/"
              << usuario.listaRevistas->dataRetirada.mes << "/" << usuario.listaRevistas->dataRetirada.ano << endl;
}

