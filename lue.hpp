///TRABALHO FEITO PELOS ALUNOS: RAFAEL FERNANDO DOS REIS MECABÔ, MATHEUS ARMANDO TIMM BARBIERI
#include <iostream>

struct Livro {
    int matricula;
    int autor;
    int editora;
    std::string titulo;
    std::string assunto;
    Livro *proximo;
};

struct ListaLivros {
    Livro *inicio;
    Livro *fim;
};

struct Revista {
    int matricula;
    int editora;
    std::string titulo;
    std::string assunto;
    Revista *proximo;
};

struct ListaRevistas {
    Revista *inicio;
    Revista *fim;
};

struct Autor {
    int matricula;
    std::string nome;
    Autor *proximo;
    ListaLivros listaLivros;
};

struct ListaAutores {
    Autor *inicio;
    Autor *fim;
};

struct Editora {
    int matricula;
    int autor;
    std::string nome;
    Editora *proximo;
    ListaRevistas listaRevistas;
};

struct ListaEditoras {
    Editora *inicio;
    Editora *fim;
};

struct Usuario {
    int matricula;
    std::string nome;
    Usuario *proximo;
};

struct ListaUsuarios {
    Usuario *inicio;
    Usuario *fim;
};

void inicializarListas(ListaLivros &listaLivros, ListaRevistas &listaRevistas,
                       ListaAutores &listaAutores, ListaEditoras &listaEditoras, ListaUsuarios &listaUsuarios) {
    listaLivros.inicio = nullptr;
    listaLivros.fim = nullptr;
    listaRevistas.inicio = nullptr;
    listaRevistas.fim = nullptr;
    listaAutores.inicio = nullptr;
    listaAutores.fim = nullptr;
    listaEditoras.inicio = nullptr;
    listaEditoras.fim = nullptr;
    listaUsuarios.inicio = nullptr;
    listaUsuarios.fim = nullptr;
}


//Buscadores por martricula
Livro *buscarLivro(ListaLivros lst, int matricula) {
    Livro *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) {
            return aux;
        }
        aux = aux->proximo;
    }
    return nullptr;
}

Revista *buscarRevista(ListaRevistas lst, int matricula) {
    Revista *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) {
            return aux;
        }
        aux = aux->proximo;
    }
    return nullptr;
}

Autor *buscarAutor(ListaAutores lst, int matricula) {
    Autor *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) {
            return aux;
        }
        aux = aux->proximo;
    }
    return nullptr;
}

Editora *buscarEditora(ListaEditoras lst, int matricula) {
    Editora *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) {
            return aux;
        }
        aux = aux->proximo;
    }
    return nullptr;
}

Usuario *buscarUsuario(ListaUsuarios lst, int matricula) {
    Usuario *aux = lst.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) {
            return aux;
        }
        aux = aux->proximo;
    }
    return nullptr;
}
//

void mostrarLivro(ListaLivros &lista, char frase[]) {
    std::cout << frase << ": ";
    if (lista.inicio == nullptr) std::cout << " vazia";

    Livro *aux = lista.inicio;
    while (aux != nullptr) {
        std::cout << std::endl << " |-> " << aux->matricula << " - " << aux->titulo;
        aux = aux->proximo;
    }
}

bool
inserirLivro(ListaLivros &listaLivros, int matriculaLivro, int matriculaAutor, int matriculaEditora, std::string titulo,
             std::string assunto) {
    Livro *novo = new Livro;
    if (novo == nullptr) {
        return false;
    }

    novo->matricula = matriculaLivro;
    novo->autor = matriculaAutor;
    novo->editora = matriculaEditora;
    novo->titulo = titulo;
    novo->assunto = assunto;
    novo->proximo = nullptr;

    //Verifica se a novo é menor que o livro do começo
    if (listaLivros.inicio == nullptr) {
        listaLivros.inicio = novo;
        listaLivros.fim = novo;
        return true;
    }

    // Inserir no inicio da lista
    if (matriculaLivro < listaLivros.inicio->matricula) {
        novo->proximo = listaLivros.inicio;
        listaLivros.inicio = novo;
        return true;
    }

    // Inserir no final da lista
    if (matriculaLivro > listaLivros.fim->matricula) {
        listaLivros.fim->proximo = novo;
        listaLivros.fim = novo;
        return true;
    }

    // Inserir no meio da lista
    Livro *aux = listaLivros.inicio;
    while (aux->matricula < matriculaLivro && aux->proximo->matricula < matriculaLivro)
        aux = aux->proximo;
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return true;
}

bool inserirAutor(ListaAutores &listaAutores, int matriculaAutor, std::string nome) {
    Autor *novo = new Autor;
    if (novo == nullptr) {
        return false;
    }

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
    Autor *autor = buscarAutor(lista, matricula);
    if (autor != nullptr) {
        autor->nome = novoNome;
        std::cout << "Nome do autor alterado com sucesso" << std::endl;
    } else {
        std::cout << "Autor nao encontrado" << std::endl;
    }
}