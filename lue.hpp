//
// Lista Unicamente Encadeada Genérica
//
#include <iostream>

struct Autor {
    int matricula;
    std::string nome;
    Autor *proximo;
};

struct Editora {
    int matricula;
    std::string nome;
    Editora *proximo;
};

struct Livro {
    int matricula;
    std::string titulo;
    std::string assunto;
    Autor autor;
    Livro *proximo;
};

struct Revista {
    int matricula;
    std::string titulo;
    std::string assunto;
    Editora editora;
    bool disponivel;
    Revista *proximo;
};

struct Usuario {
    int matricula;
    std::string nome;
    Usuario *proximo;
    struct Data {
        int dia, mes, ano;
        Livro livro;
        Data *proxima;
    };
};

struct ListaLivros {
    Livro *inicio;
    Livro *fim;
};

struct ListaRevistas {
    Revista *inicio;
    Revista *fim;
};

struct ListaUsuarios {
    Usuario *inicio;
    Usuario *fim;
};

struct ListaAutores {
    Autor *inicio;
    Autor *fim;
};

struct ListaEditoras {
    Editora *inicio;
    Editora *fim;
};

void inicializarListas(ListaLivros &listaLivros, ListaRevistas &listaRevistas, ListaUsuarios &listaUsuarios,
                       ListaAutores &listaAutores, ListaEditoras &listaEditoras) {
    listaLivros.inicio = nullptr;
    listaLivros.fim = nullptr;
    listaRevistas.inicio = nullptr;
    listaRevistas.fim = nullptr;
    listaUsuarios.inicio = nullptr;
    listaUsuarios.fim = nullptr;
    listaAutores.inicio = nullptr;
    listaAutores.fim = nullptr;
    listaEditoras.inicio = nullptr;
    listaEditoras.fim = nullptr;
}

void mostrarLivro(ListaLivros &lista, char frase[]) {
    std::cout << frase << ": ";
    if (lista.inicio == nullptr) std::cout << " vazia";

    Livro *aux = lista.inicio;
    while (aux != nullptr) {
        std::cout << std::endl << " |-> " << aux->matricula << " - " << aux->titulo << " - autor: " << aux->autor.nome;
        aux = aux->proximo;
    }
}

void mostrarAutor(ListaAutores &lista, char frase[]) {
    std::cout << frase << ": ";
    if (lista.inicio == nullptr) std::cout << " vazia";

    Autor *aux = lista.inicio;
    while (aux != nullptr) {
        std::cout << std::endl << " |-> " << aux->matricula << " - " << aux->nome;
        aux = aux->proximo;
    }
}

bool inserirLivro(ListaLivros &lista, int matricula, std::string titulo, std::string assunto, Autor autor) {
    Livro *novo = new Livro;
    if (novo == nullptr) {
        return false;
    }
    novo->matricula = matricula;
    novo->titulo = titulo;
    novo->assunto = assunto;
    novo->autor = autor;
    novo->proximo = nullptr;
    if (lista.inicio == nullptr) {
        lista.inicio = novo;
        lista.fim = novo;
        return true;
    }
    if (matricula < lista.inicio->matricula) {
        novo->proximo = lista.inicio;
        lista.inicio = novo;
        return true;
    }
    Livro *atual = lista.inicio;
    Livro *anterior = nullptr;
    while (atual != nullptr && atual->matricula < matricula) {
        anterior = atual;
        atual = atual->proximo;
    }
    novo->proximo = atual;
    if (anterior != nullptr) {
        anterior->proximo = novo;
    }
    if (atual == nullptr) {
        lista.fim = novo;
    }
    return true;
}

bool inserirAutor(ListaAutores &lista, int matricula, std::string nome) {
    Autor *novo = new Autor;
    if (novo == nullptr) return false;
    novo->matricula = matricula;
    novo->nome = nome;
    novo->proximo = nullptr;
    // Inserir em lista vazia
    if (lista.inicio == nullptr) {
        lista.inicio = novo;
        lista.fim = novo;
        return true;
    }
    // Inserir no inicio da lista
    if (matricula < lista.inicio->matricula) {
        novo->proximo = lista.inicio;
        lista.inicio = novo;
        return true;
    }
    // Inserir no final da lista
    if (matricula > lista.fim->matricula) {
        lista.fim->proximo = novo;
        lista.fim = novo;
        return true;
    }
    // Inserir no meio da lista
    Autor *aux = lista.inicio;
    while (aux->matricula < matricula && aux->proximo->matricula < matricula)
        aux = aux->proximo;
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return true;
}

bool inserirEditora(ListaEditoras &lista, int matricula, std::string nome) {
    Editora *novo = new Editora;
    if (novo == nullptr) return false;
    novo->matricula = matricula;
    novo->nome = nome;
    novo->proximo = nullptr;

    // Verificar se já existe uma editora com a mesma matrícula
    if (lista.inicio != nullptr) {
        Editora *aux = lista.inicio;
        while (aux != nullptr) {
            if (aux->matricula == matricula) {
                delete novo;
                return false;
            }
            aux = aux->proximo;
        }
    }

    // Inserir em lista vazia
    if (lista.inicio == nullptr) {
        lista.inicio = novo;
        lista.fim = novo;
        return true;
    }
    // Inserir no inicio da lista
    if (matricula < lista.inicio->matricula) {
        novo->proximo = lista.inicio;
        lista.inicio = novo;
        return true;
    }
    // Inserir no final da lista
    if (matricula > lista.fim->matricula) {
        lista.fim->proximo = novo;
        lista.fim = novo;
        return true;
    }
    // Inserir no meio da lista
    Editora *aux = lista.inicio;
    while (aux->proximo != nullptr && aux->proximo->matricula < matricula)
        aux = aux->proximo;
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return true;
}

bool inserirRevista(ListaRevistas &lista, int matricula, std::string titulo, std::string assunto, Editora editora,
                    bool disponivel) {
    Revista *nova = new Revista;
    if (nova == nullptr) return false;
    nova->matricula = matricula;
    nova->titulo = titulo;
    nova->assunto = assunto;
    nova->editora = editora; // alteração aqui
    nova->disponivel = disponivel;
    nova->proximo = nullptr;

    if (lista.inicio == nullptr) {
        lista.inicio = nova;
        lista.fim = nova;
        return true;
    }

    if (matricula < lista.inicio->matricula) {
        nova->proximo = lista.inicio;
        lista.inicio = nova;
        return true;
    }

    if (matricula > lista.fim->matricula) {
        lista.fim->proximo = nova;
        lista.fim = nova;
        return true;
    }

    Revista *aux = lista.inicio;
    while (aux->proximo != nullptr && aux->proximo->matricula < matricula) {
        aux = aux->proximo;
    }
    nova->proximo = aux->proximo;
    aux->proximo = nova;
    return true;
}

bool inserirUsuario(ListaUsuarios &lista, int matricula, std::string nome) {
    Usuario *novo = new Usuario;
    if (novo == nullptr) return false;
    novo->matricula = matricula;
    novo->nome = nome;
    novo->proximo = nullptr;

    if (lista.inicio == nullptr) {
        lista.inicio = novo;
        lista.fim = novo;
        return true;
    }

    if (matricula < lista.inicio->matricula) {
        novo->proximo = lista.inicio;
        lista.inicio = novo;
        return true;
    }

    if (matricula > lista.fim->matricula) {
        lista.fim->proximo = novo;
        lista.fim = novo;
        return true;
    }

    Usuario *aux = lista.inicio;
    while (aux->proximo != nullptr && aux->proximo->matricula < matricula) {
        aux = aux->proximo;
    }
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    return true;
}

Autor *buscarAutor(ListaAutores &lista, int matricula) {
    Autor *aux = lista.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) return aux;
        aux = aux->proximo;
    }
    return nullptr;
}

void pesquisar(ListaLivros *listaLivros, ListaAutores *listaAutores, ListaEditoras *listaEditoras,
               ListaUsuarios *listaUsuarios, ListaRevistas *listaRevistas, int matricula) {
    std::cout << "Resultados da pesquisa para \"" << matricula << "\":" << std::endl;

    // Pesquisar por matrícula de livro
    Livro *auxLivro = listaLivros->inicio;
    while (auxLivro != nullptr) {
        if (auxLivro->matricula == matricula) {
            std::cout << "Livro: " << auxLivro->titulo << " - Autor: " << auxLivro->autor.nome << std::endl;
        }
        auxLivro = auxLivro->proximo;
    }
    // Pesquisar por matrícula de autores
    Autor *auxAutor = listaAutores->inicio;
    while (auxAutor != nullptr) {
        if (auxAutor->matricula == matricula) {
            std::cout << "Autor: " << auxAutor->nome << std::endl;
        }
        auxAutor = auxAutor->proximo;
    }
    // Pesquisar por matrícula de editora
    Editora *auxEditora = listaEditoras->inicio;
    while (auxEditora != nullptr) {
        if (auxEditora->matricula == matricula) {
            std::cout << "Editora: " << auxEditora->nome << std::endl;
        }
        auxEditora = auxEditora->proximo;
    }
    // Pesquisar por matrícula de usuario
    Usuario *auxUsuario = listaUsuarios->inicio;
    while (auxUsuario != nullptr) {
        if (auxUsuario->matricula == matricula) {
            std::cout << "Usuario: " << auxUsuario->nome << std::endl;
        }
        auxUsuario = auxUsuario->proximo;
    }
    // Pesquisar por matrícula de usuario
    Revista *auxRevista = listaRevistas->inicio;
    while (auxRevista != nullptr) {
        if (auxRevista->matricula == matricula) {
            std::cout << "auxRevista: " << auxRevista->titulo << std::endl;
        }
        auxRevista = auxRevista->proximo;
    }
}
Livro *buscarLivro(ListaLivros &lista, int matricula) {
    Livro *aux = lista.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) return aux;
        aux = aux->proximo;
    }
    return nullptr;
}

Editora *buscarEditora(ListaEditoras &lista, int matricula) {
    Editora *aux = lista.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) return aux;
        aux = aux->proximo;
    }
    return nullptr;
}

Revista *buscarRevista(ListaRevistas &lista, int matricula) {
    Revista *aux = lista.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) return aux;
        aux = aux->proximo;
    }
    return nullptr;
}

Usuario *buscarUsuario(ListaUsuarios &lista, int matricula) {
    Usuario *aux = lista.inicio;
    while (aux != nullptr) {
        if (aux->matricula == matricula) return aux;
        aux = aux->proximo;
    }
    return nullptr;
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

bool retirarLivro(ListaLivros &lista, int matricula) {
    Livro *ant = nullptr, *pos;

    pos = lista.inicio;
    while (pos != nullptr && pos->matricula != matricula) {
        ant = pos;
        pos = pos->proximo;
    }
    if (pos == nullptr) return false;  // Lista vazia ou valor não encontrado

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
bool retirarAutores( ListaAutores &lista, int matricula ){
    Autor *ant= nullptr, *pos;

    pos = lista.inicio;
    while( pos != nullptr && pos->matricula != matricula ){
        ant = pos;
        pos = pos->proximo;
    }
    if( pos == nullptr ) return false;  // Lista vazia ou valor n?o encontrado

    // Retirada no inicio da lista
    if( pos == lista.inicio ){
        lista.inicio = lista.inicio->proximo;
        if( pos == lista.fim ) lista.fim = nullptr;
    }
    else{
        ant->proximo = pos->proximo;
        if( pos == lista.fim ) lista.fim = ant;
    }
    delete( pos );
    return true;
}
