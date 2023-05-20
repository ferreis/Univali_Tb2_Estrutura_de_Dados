///TRABALHO FEITO PELOS ALUNOS: RAFAEL FERNANDO DOS REIS MECABÔ, MATHEUS ARMANDO TIMM BARBIERI
#include <iostream>
#include "utils.hpp"
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
    int autor;
    int editora;
    string nome;
    string assunto;
    No<Livro> *proximo;
};


struct Revista {
    int matricula;
    int editora;
    std::string nome;
    std::string assunto;
    No<Revista> *proximo;
};

struct Autor {
    int matricula;
    string nome;
    No<Autor> *proximo;
    Lista<Livro> listaLivros;
};

struct Editora {
    int matricula;
    int autor;
    std::string nome;
    No<Editora> *proximo;
    Lista<Autor> listaaAutores;
    Lista<Revista> listaRevistas;
};

struct Usuario {
    int matricula;
    std::string nome;
    No<Usuario> *proximo;
};


template<typename T>
void inicializarLista(Lista<T> &lista) {
    lista.inicio = nullptr;
    lista.fim = nullptr;

}


//buscadores
template<typename T>
No<T> *buscarMatricula(Lista<T> &lista, string info) {
    No<T> *aux = lista.inicio;
    if (validaString(info)) {
        int matricula = stoi(info);
        while (aux != nullptr) {
            if (aux->valor.matricula == matricula) {
                return aux;
            }
            aux = aux->proximo;
        }
    }
    return nullptr;
}

template<typename T>
T obterInformacoes(int matricula) {
    T objeto;
    objeto.matricula = matricula;

    if constexpr (std::is_same<T, Livro>::value) {
        cout << "Digite a matricula do autor: ";
        cin >> objeto.autor;
        cout << "Digite a matricula da editora: ";
        cin >> objeto.editora;
        cout << "Digite o titulo do livro: ";
        cin >> objeto.nome;
        cout << "Digite o assunto do livro: ";
        cin >> objeto.assunto;
    } else if constexpr (std::is_same<T, Revista>::value) {
        cout << "Digite a matricula da editora: ";
        cin >> objeto.editora;
        cout << "Digite o titulo da revista: ";
        cin >> objeto.nome;
        cout << "Digite o assunto da revista: ";
        cin >> objeto.assunto;
    } else if constexpr (std::is_same<T, Autor>::value) {
        cout << "Digite o nome do autor: ";
        cin >> objeto.nome;
    } else if constexpr (std::is_same<T, Editora>::value) {
        cout << "Digite a matricula do autor: ";
        cin >> objeto.autor;
        cout << "Digite o nome da editora: ";
        cin >> objeto.nome;
    } else if constexpr (std::is_same<T, Usuario>::value) {
        cout << "Digite o nome do usuario: ";
        cin >> objeto.nome;
    }

    return objeto;
}

template<typename T>
bool inserir(Lista<T> &lst, string info) {
    cout << "inserindo" << endl;
    No<T> *novo = new No<T>();
    if (novo == nullptr) {
        return false;
    }

    int matricula = stoi(info);
    T valor = obterInformacoes<T>(matricula);
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

template<typename T>
void mostrarLista(Lista<T> lista) {
    No<T> *aux = lista.inicio;
    while (aux != nullptr) {
        std::cout << "\t|->________________________________________________: " << endl;
        cout << "\t Matricula:" << aux->valor.matricula << " - ";
        std::cout << "\t|->Titulo: " << aux->valor.nome;
        if (std::is_same<T, Livro>::value){//livro
            cout << "\t|->Assunto: " << aux->valor.assunto;
            cout << "\t|->Autor: " << aux->valor.autor;
            cout << "\t|->Autor: " << buscarMatricula(aux->valor.autor, aux->valor.autor).valor.nome;
            cout << "\t|->Editora: " << aux->valor.editora;
            cout << "\t|->Editora: " << buscarMatricula(aux->valor.editora, aux->valor.editora).valor.nome;
        }else if(std::is_same<T, Revista>::value){//revista
            cout << "\t|->Editora: " << aux->valor.editora;
            cout << "\t|->Assunto: " << aux->valor.assunto;
        }else if (std::is_same<T, Editora>::value){//editora
            cout << "\t|->Autor: " << aux->valor.autor;
        }else if (std::is_same<T, Autor>::value) {//autor
            cout << "\t|->Nome: " << aux->valor.nome;
        }
        aux = aux->proximo;
    }
}




