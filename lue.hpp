///TRABALHO FEITO PELOS ALUNOS: RAFAEL FERNANDO DOS REIS MECABÔ, MATHEUS ARMANDO TIMM BARBIERI
#include <iostream>
#include "utils.hpp"

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
    int autor;
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

template<typename T>
void mostrarLista(Lista<T> lista) {
    No<T> *aux = lista.inicio;
    while (aux != nullptr) {
        std::cout << "\t|->________________________________________________: " << endl;
        cout<< "\t"<< aux->valor.matricula << " - ";
        std::cout << "\t|->Titulo: " << aux->valor.nome;

        aux = aux->proximo;
    }
    cout << endl;
}
//buscadores
template<typename T>
No<T> *buscarMatricula(Lista<T> &lista, string info) {
    No<T> *aux = lista.inicio;
    if (validaString(info)) {
        int matricula = stoi(info);
        while (aux != nullptr) {
            if (aux->valor.matricula == matricula) {
                return
                        aux;
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





/*

void mostrarLivro(ListaLivros &lista, char frase[]) {
    std::cout << frase << ": ";
    if (lista.inicio == nullptr) std::cout << " vazia";

    Livro *aux = lista.inicio;
    while (aux != nullptr) {
        std::cout << std::endl << " |-> " << aux->matricula << " - " << aux->titulo;
        aux = aux->proximo;
    }
}

bool inserirRevista(ListaRevistas &revistas, string info) {
    Revista *novo = revistas.inicio;
    if (novo == nullptr) {
        return false;
    }
    int matriculaRevista, matriculaAutor, matriculaEditora;
    string titulo, assunto;
    matriculaRevista = stoi(info);
    cout << "Digite a matricula do autor: ";
    cin >> matriculaAutor;
    cout << "Digite a matricula da editora: ";
    cin >> matriculaEditora;
    cout << "Digite o titulo da revista: ";
    cin >> titulo;
    cout << "Digite o assunto da revista: ";
    cin >> assunto;

    novo->matricula = matriculaRevista;
    novo->autor = matriculaAutor;
    novo->editora = matriculaEditora;
    novo->titulo = titulo;
    novo->assunto = assunto;
    novo->proximo = nullptr;

    return false;
}

bool inserirAutor(ListaAutores &listaAutores, std::string info) {
    Autor *novo = listaAutores.inicio;
    if (novo == nullptr) {
        return false;
    }
    int matriculaAutor;
    string nome;
    matriculaAutor = stoi(info);
    cout << "Digite o nome do autor: ";
    cin >> nome;

    novo->matricula = matriculaAutor;
    novo->nome = nome;
    novo->proximo = nullptr;

    // Adiciona o autor na lista de autores
    if (listaAutores.inicio == nullptr) {
        listaAutores.inicio = novo;
        listaAutores.fim = novo;
    }

    // Inserir no inicio da lista
    if (matriculaAutor < listaAutores.inicio->matricula) {
        novo->proximo = listaAutores.inicio;
        listaAutores.inicio = novo;
        return true;
    }

    // Inserir no final da lista
    if (matriculaAutor > listaAutores.fim->matricula) {
        listaAutores.fim->proximo = novo;
        listaAutores.fim = novo;
        return true;
    }

    Autor *aux = listaAutores.inicio;
    while (aux->matricula < matriculaAutor && aux->proximo->matricula < matriculaAutor)
        aux = aux->proximo;
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return true;
}

bool inserirEditora(ListaEditoras &listaEditoras, std::string info) {
    Editora *novo = listaEditoras.inicio;
    if (novo == nullptr) {
        return false;
    }
    int matriculaEditora;
    string nome;
    matriculaEditora = stoi(info);
    cout << "Digite o nome da editora: ";
    cin >> nome;

    novo->matricula = matriculaEditora;
    novo->nome = nome;
    novo->proximo = nullptr;

    // Adiciona a editora na lista de editoras
    if (listaEditoras.inicio == nullptr) {
        listaEditoras.inicio = novo;
        listaEditoras.fim = novo;
    }

    // Inserir no inicio da lista
    if (matriculaEditora < listaEditoras.inicio->matricula) {
        novo->proximo = listaEditoras.inicio;
        listaEditoras.inicio = novo;
        return true;
    }

    // Inserir no final da lista
    if (matriculaEditora > listaEditoras.fim->matricula) {
        listaEditoras.fim->proximo = novo;
        listaEditoras.fim = novo;
        return true;
    }

    Editora *aux = listaEditoras.inicio;
    while (aux->matricula < matriculaEditora && aux->proximo->matricula < matriculaEditora)
        aux = aux->proximo;
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return true;
}

bool inserirUsuario(ListaUsuarios &listaUsuarios, std::string info) {
    Usuario *novo = listaUsuarios.inicio;
    if (novo == nullptr) {
        return false;
    }
    int matriculaUsuario;
    string nome;
    matriculaUsuario = stoi(info);
    cout << "Digite o nome do usuario: ";
    cin >> nome;

    novo->matricula = matriculaUsuario;
    novo->nome = nome;
    novo->proximo = nullptr;

    // Adiciona o usuario na lista de usuarios
    if (listaUsuarios.inicio == nullptr) {
        listaUsuarios.inicio = novo;
        listaUsuarios.fim = novo;
    }

    // Inserir no inicio da lista
    if (matriculaUsuario < listaUsuarios.inicio->matricula) {
        novo->proximo = listaUsuarios.inicio;
        listaUsuarios.inicio = novo;
        return true;
    }

    // Inserir no final da lista
    if (matriculaUsuario > listaUsuarios.fim->matricula) {
        listaUsuarios.fim->proximo = novo;
        listaUsuarios.fim = novo;
        return true;
    }

    Usuario *aux = listaUsuarios.inicio;
    while (aux->matricula < matriculaUsuario && aux->proximo->matricula < matriculaUsuario)
        aux = aux->proximo;
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return true;
}

bool retirarAutores(ListaAutores &lista, int matricula) {
    Autor *ant = nullptr, *pos;

    pos = lista.inicio;
    while (pos != nullptr && pos->matricula != matricula) {
        ant = pos;
        pos = pos->proximo;
    }
    if (pos == nullptr) return false;  // Lista vazia ou valor n?o encontrado

    // Retirada no inicio da lista
    if (pos == lista.inicio) {
        lista.inicio = lista.inicio->proximo;
        if (pos == lista.fim) lista.fim = nullptr;
    } else {
        ant->proximo = pos->proximo;
        if (pos == lista.fim) lista.fim = ant;
    }
    delete (pos);
    return true;
}

void alterarNomeAutor(ListaAutores &lista, int matricula, std::string novoNome) {
    Autor *autor = buscarMatricula<ListaAutores>(lista, matricula);
    if (autor != nullptr) {
        autor->nome = novoNome;
        std::cout << "Nome do autor alterado com sucesso" << std::endl;
    } else {
        std::cout << "Autor nao encontrado" << std::endl;
    }
}


void *buscarLivroGeral(Lista lst, std::string info) {
    Livro *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->titulo == info || aux->assunto == info) {
            std::cout << "Matricula: " << aux->matricula;
            std::cout << " - Titulo: " << aux->titulo;
            std::cout << " - Assunto: " << aux->assunto;
            system("pause");

        }
        aux = aux->proximo;
    }
    return nullptr;
}

void *buscarRevistaGeral(ListaRevistas lst, std::string info) {
    Revista *aux = lst.inicio;

    while (aux != nullptr) {
        if (aux->titulo == info || aux->assunto == info) {
            std::cout << "Matricula: " << aux->matricula;
            std::cout << " - Titulo: " << aux->titulo;
            std::cout << " - Assunto: " << aux->assunto;
            system("pause");
        }
        aux = aux->proximo;
    }
    return nullptr;
}

Autor *buscarAutorGeral(ListaAutores &lst, const std::string info) {
    Autor *aux = lst.inicio;
    while (aux != nullptr) {
        if (validarUppercase(aux->nome) == validarUppercase(info)) {
            return aux;
        }
        aux = aux->proximo;
    }
    return nullptr;

}

void *buscarEditoraGeral(ListaEditoras lst, std::string info) {
    Editora *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->nome == info) {
            std::cout << "Matricula: " << aux->matricula;
            std::cout << " - Titulo: " << aux->nome;
            system("pause");
        }
        aux = aux->proximo;
    }
    return nullptr;
}

template<typename T>
void *buscarUsuarioGeral(T lst, std::string info) {
    T *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->nome == info) {
            std::cout << "Matricula: " << aux->matricula;
            std::cout << " - Titulo: " << aux->nome;
            system("pause");
        }
        aux = aux->proximo;
    }
    return nullptr;
};
 */