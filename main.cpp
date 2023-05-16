#include <iostream>
#include "lue.hpp"

#define TAM 16


using namespace std;

int calcularEndereco(int num) { ///calcula endereço do HASH
    return num % TAM;
}

bool
inserirHashLivro(ListaLivros lista[], int matriculaLivro, int matriculaAutor, int matriculaEditora, string titulo,
                 string assunto) { ///insere dentro do HASH
    int chaveLivro = calcularEndereco(matriculaLivro);
    return inserirLivro(lista[chaveLivro], matriculaLivro, matriculaAutor, matriculaEditora, titulo, assunto);
}

bool inserirHashAutor(ListaAutores lista[], int matriculaAutor, string nome) { ///insere dentro do HASH
    int chaveAutor = calcularEndereco(matriculaAutor);
    return inserirAutor(lista[chaveAutor], matriculaAutor, nome);
}

bool buscarHashAutores(ListaAutores lista[], int num) { ///busca o valor no HASH
    int pos = calcularEndereco(num);
    return buscarAutor(lista[pos], num);
}

bool buscarHashLivros(ListaLivros lista[], int num) { ///busca o valor no HASH
    int pos = calcularEndereco(num);
    return buscarLivro(lista[pos], num);
}

bool buscarHashEditoras(ListaEditoras lista[], int num) { ///busca o valor no HASH
    int pos = calcularEndereco(num);
    return buscarEditora(lista[pos], num);
}

bool buscarHashRevitas(ListaRevistas lista[], int num) { ///busca o valor no HASH
    int pos = calcularEndereco(num);
    return buscarRevista(lista[pos], num);
}

bool buscarHashUsuarios(ListaUsuarios lista[], int num) { ///busca o valor no HASH
    int pos = calcularEndereco(num);
    return buscarUsuario(lista[pos], num);
}

Autor retornarAutor(ListaAutores lista[], int num) {
    int pos = calcularEndereco(num);
    return *buscarAutor(lista[pos], num);
}

void AlterarHashAutores(ListaAutores lista[], int matricula) {
    int pos = calcularEndereco(matricula);
    int op, matriculaNova, novo;
    string novoNome;
    cout << " O que deseja alterar " << endl << "\t1 - Alterar Nome" << endl << "\t2-Alterar Matricula" << endl;
    cin >> op;
    switch (op) {
        case 1:
            cout << "Informe o novo nome: " << endl;
            cin >> novoNome;
            alterarNomeAutor(lista[pos], matricula, novoNome);
            break;
        case 2:
            cout << "Informa a nova matricula";
            cin >> matriculaNova;
            novo = calcularEndereco(matriculaNova);
            inserirHashAutor(&lista[novo], matriculaNova, retornarAutor(&lista[pos], matricula).nome);
            retirarAutores(lista[pos], matricula);
            break;
        default:
            break;
    }

}

void cadastros(ListaLivros *listaLivros, ListaRevistas *listaRevistas, ListaAutores *listaAutores,
               ListaEditoras *listaEditoras, ListaUsuarios *listaUsuarios) {
    int matriculaLivro, matriculaAutor, matriculaEditora;
    string nome, assunto;
    cout << "informe o nome do autor e a matricula dele:" << endl;
    cin >> nome >> matriculaAutor;
    inserirHashAutor(listaAutores, matriculaAutor, nome);

    cout << "Nome: Matricula: Assunto:" << endl;
    cin >> nome >> matriculaLivro >> assunto;
    inserirHashLivro(listaLivros, matriculaLivro, matriculaAutor, matriculaEditora, nome, assunto);

}

void pesquisa(ListaLivros *listaLivros, ListaRevistas *listaRevistas, ListaAutores *listaAutores,
              ListaEditoras *listaEditoras, ListaUsuarios *listaUsuarios) {
    int matricula;


    string texto;
    cout << "informer Matricula, titulo, autor, editora ou assunto que deseja buscar: " << endl;
    cin >> matricula;
    int chave = calcularEndereco(matricula);
    system("cls");
    if (buscarLivro(listaLivros[chave], matricula)->matricula == matricula ||
        buscarLivro(listaLivros[chave], matricula)->titulo == texto ||
        buscarLivro(listaLivros[chave], matricula)->assunto == texto) {
        cout << "Matricula: " << buscarLivro(listaLivros[chave], matricula)->matricula;
        cout << " - Titulo: " << buscarLivro(listaLivros[chave], matricula)->titulo;
        cout << " - Assunto: " << buscarLivro(listaLivros[chave], matricula)->assunto;
    }
    if (buscarRevista(listaRevistas[chave], matricula)->matricula == matricula ||
        buscarRevista(listaRevistas[chave], matricula)->titulo == texto ||
        buscarRevista(listaRevistas[chave], matricula)->assunto == texto) {
        cout << "Matricula: " << buscarRevista(listaRevistas[chave], matricula)->matricula;
        cout << " - Titulo: " << buscarRevista(listaRevistas[chave], matricula)->titulo;
        cout << " - Assunto: " << buscarRevista(listaRevistas[chave], matricula)->assunto;
    }
    if (buscarAutor(listaAutores[chave], matricula)->matricula == matricula ||
        buscarAutor(listaAutores[chave], matricula)->nome == texto) {
        cout << "Matricula: " << buscarAutor(listaAutores[chave], matricula)->matricula;
        cout << " - Cadastro: " << buscarAutor(listaAutores[chave], matricula)->nome << endl;
        system("pause");
    }
    if (buscarEditora(listaEditoras[chave], matricula)->matricula == matricula ||
        buscarEditora(listaEditoras[chave], matricula)->nome == texto) {
        cout << "Matricula: " << buscarEditora(listaEditoras[chave], matricula)->matricula;
        cout << " - Titulo: " << buscarEditora(listaEditoras[chave], matricula)->nome;
        system("pause");
    }
    if (buscarUsuario(listaUsuarios[chave], matricula)->matricula == matricula ||
        buscarUsuario(listaUsuarios[chave], matricula)->nome == texto) {
        cout << "Matricula: " << buscarUsuario(listaUsuarios[chave], matricula)->matricula;
        cout << " - Nome de usuario: " << buscarUsuario(listaUsuarios[chave], matricula)->nome;
    }
    system("pause");
}

void mostrarDetalhadoLivro(ListaLivros &listaLivros, ListaAutores *listaAutores, ListaEditoras *listaEditoras) {
    std::cout << "Livros:" << std::endl;
    Livro *auxLivro = listaLivros.inicio;
    while (auxLivro != nullptr) {
        int chave = calcularEndereco(auxLivro->autor);
        std::cout << "\t|->________________________________________________: " << endl;
        std::cout << "\t|->Titulo: " << auxLivro->titulo;
        if (buscarHashAutores(listaAutores, auxLivro->autor)) {
            cout << endl << "\t\t |-> Matricula Autor: "
                 << buscarAutor(listaAutores[chave], auxLivro->autor)->matricula;
            cout << " - Cadastro: " << buscarAutor(listaAutores[chave], auxLivro->autor)->nome << endl;
        } else {
            std::cout << "\t\t |-> Autor desconhecido" << std::endl;
        }
        if (buscarHashEditoras(listaEditoras, auxLivro->editora)) {
            cout << endl << "\t\t |-> Matricula Editora: "
                 << buscarEditora(listaEditoras[chave], auxLivro->autor)->matricula;
            cout << " - Cadastro: " << buscarEditora(listaEditoras[chave], auxLivro->autor)->nome << endl;
        } else {
            std::cout << "\t\t |-> Editora desconhecido" << std::endl;
        }
        auxLivro = auxLivro->proximo;
    }
}

void cadastrarTestes(ListaLivros *listaLivros, ListaAutores *listaAutores) {
    // Cadastro de autores
    inserirHashAutor(listaAutores, 1, "Machado de Assis");
    inserirHashAutor(listaAutores, 2, "Clarice Lispector");
    inserirHashAutor(listaAutores, 3, "Jose Saramago");

    // Cadastro de livros
    inserirHashLivro(listaLivros, 1000, 1, -1, "Dom Casmurro", "Romance");
    inserirHashLivro(listaLivros, 1100, 1, -1, "Memorias Postumas de Bras Cubas", "Romance");
    inserirHashLivro(listaLivros, 1010, 2, -1, "A Hora da Estrela", "Romance");
    inserirHashLivro(listaLivros, 1003, 2, -1, "A Paixao Segundo G.H.", "Romance");
    inserirHashLivro(listaLivros, 1004, 3, -1, "Ensaio Sobre a Cegueira", "Romance");
    inserirHashLivro(listaLivros, 1001, 3, -1, "teste", "Romance");

}

int main() {
    system("cls");

    ListaLivros listaLivros[TAM];
    ListaRevistas listaRevistas[TAM];
    ListaAutores listaAutores[TAM];
    ListaEditoras listaEditoras[TAM];
    ListaUsuarios listaUsuarios[TAM];
    int op;
    for (int i = 0; i < TAM; i++) {
        inicializarListas(listaLivros[i], listaRevistas[i], listaAutores[i], listaEditoras[i], listaUsuarios[i]);
    }
    do {
        system("cls");
        cout << "Oque quer fazer: " << endl;
        cout << "\t1. Cadastros" << endl;
        cout << "\t2. Pesquisar " << endl;
        cout << "\t9  Mostrar tudo" << endl;
        cout << "\t10 Cadastro testes" << endl;
        cout << "\t0. Fim" << endl;
        cin >> op;
        string nome, assunto = "Fantasia";;
        int matricula;
        switch (op) {
            /*INSERIR CERTO NAS FUNCOES*/
            case 1:
                cadastros(listaLivros, listaRevistas, listaAutores, listaEditoras, listaUsuarios);
                break;
            case 2:
                pesquisa(listaLivros, listaRevistas, listaAutores, listaEditoras, listaUsuarios);
                break;
            case 3:
                system("pause");
                break;
            case 9:
                cout << "Tabela: " << endl;
                for (int i = 0; i < TAM; ++i) {
                    cout << i << "- ";
                    mostrarDetalhadoLivro(listaLivros[i], listaAutores, listaEditoras);
                    //mostrarLivro(listaLivros[i], " ");
                    cout << endl;
                }

                system("pause");
                break;
            case 10:
                // cadastrar testes
                cadastrarTestes(listaLivros, listaAutores);
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    } while (op != 0);
    cout << endl;
};