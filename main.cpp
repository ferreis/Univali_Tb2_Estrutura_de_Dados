#include <iostream>
#include "lue.hpp"

#define TAM 16

using namespace std;

int calcularEndereco(int num) { ///calcula endereço do HASH
    return num % TAM;
}
bool inserirHashLivro(ListaLivros lista[], int matricula, string titulo, string assunto,
                      Autor autor) { ///insere dentro do HASH
    int pos = calcularEndereco(matricula);
    return inserirLivro(lista[pos], matricula, titulo, assunto, autor);
}
bool inserirHashAutor(ListaAutores lista[], int matricula, string nome) { ///insere dentro do HASH
    int pos = calcularEndereco(matricula);
    return inserirAutor(lista[pos], matricula, nome);
}
bool buscarHashAutores(ListaAutores lista[], int num) { ///busca o valor no HASH
    int pos = calcularEndereco(num);
    return (buscarAutor(lista[pos], num) == nullptr);
}
Autor retornarAutor(ListaAutores lista[], int num) {
    int pos = calcularEndereco(num);
    return *buscarAutor(lista[pos], num);
}

void AlterarHashAutores(ListaAutores lista[], int matricula){
    int pos = calcularEndereco(matricula);
    int op, matriculaNova, novo;
    string novoNome;
    cout << " O que deseja alterar " << endl<<"\t1 - Alterar Nome" <<endl <<"\t2-Alterar Matricula"<< endl;
    cin >> op;
    switch (op) {
        case 1:
            cout << "Informe o novo nome: "<< endl;
            cin >> novoNome;
            alterarNomeAutor(lista[pos],matricula, novoNome);
            break;
        case 2:
            cout << "Informa a nova matricula";
            cin >> matriculaNova;
            novo = calcularEndereco(matriculaNova);
            inserirHashAutor(&lista[novo],matriculaNova, retornarAutor(&lista[pos],matricula).nome);
            retirarAutores(lista[pos], matricula);
            break;
        default:
            break;
    }

}
void cadastro_teste(ListaAutores *listaAutores, ListaLivros *listaLivros, ListaEditoras *listaEditoras){
    inserirHashAutor(listaAutores, 10000, "J.R.R. Tolkien");
    inserirHashAutor(listaAutores, 10100, "C.S. Lewis");
    inserirHashAutor(listaAutores, 45767, "J.K. Rowling");

    inserirHashLivro(listaLivros, 30151, "O Senhor dos Anéis", "Fantasia",
                     retornarAutor(listaAutores, 10000));

    inserirHashLivro(listaLivros, 18101, "O Hobbit", "Fantasia",
                     retornarAutor(listaAutores, 10000));

    inserirHashLivro(listaLivros, 19880, "As Crônicas de Nárnia", "Fantasia",
                     retornarAutor(listaAutores, 10100));

    inserirHashLivro(listaLivros, 19880, "As Crônicas dos testes", "Fantasia",
                     retornarAutor(listaAutores, 45767));
}
void cadastro_livro(ListaAutores *listaAutores, ListaLivros *listaLivros, ListaEditoras *listaEditoras){
    int matriculaLivro, matriculaAutor;
    string titulo, assunto, nome;
    Autor autor;
    Editora *editora;
    cout << "Matricula do livro: ";
    cin >> matriculaLivro;
    cout << "Nome do livro: ";
    cin >> titulo;
    cout << "Assunto do livro: ";
    cin >> assunto;
    cout << "Nome do Autor: ";
    cin >> nome;
    cout << "codigo do autor: ";
    cin >> matriculaAutor;
    if (buscarHashAutores(listaAutores, matriculaAutor)) {
        // Matricula já existe na lista de autores, então podemos adicionar o livro a essa lista
        if (inserirHashLivro(listaLivros, matriculaLivro, titulo, assunto, autor)) {
            cout << "Livro cadastrado com sucesso" << endl;
        } else
            cout << "Erro ao cadastrar o livro" << endl;
    } else {
        // Matricula não existe na lista de autores, então precisamos criar um novo autor e adicioná-lo junto com o livro
        if (inserirHashLivro(listaLivros, matriculaLivro, titulo, assunto, autor)) {
            cout << "Livro cadastrado com sucesso" << endl;
            if (inserirHashAutor(listaAutores, matriculaAutor, nome)) {
                cout << " Autor cadastrado com sucesso!" << endl;
            }
        } else
            cout << "Erro ao cadastrar o livro" << endl;
    }
};

int main() {
    ListaLivros listaLivros[TAM];
    ListaRevistas listaRevistas[TAM];
    ListaUsuarios listaUsuarios[TAM];
    ListaAutores listaAutores[TAM];
    ListaEditoras listaEditoras[TAM];
    int op;
    for (int i = 0; i < TAM; i++) {
        inicializarListas(listaLivros[i], listaRevistas[i], listaUsuarios[i], listaAutores[i], listaEditoras[i]);
    }
    cadastro_teste(listaAutores,listaLivros,listaEditoras);
    do {
        cout << "Oque quer fazer: " << endl;
        cout << "\t1. Inserir Livro" << endl;
        cout << "\t2. mostrar Livro" << endl;
        cout << "\t2. pesquise por matrícula" << endl;
        cout << "\t2. mostrar Livro" << endl;

        cout << "\t0. Fim" << endl;
        cin >> op;
        switch (op) {
            /*INSERIR CERTO NAS FUNCOES*/
            case 1:
                cadastro_livro(listaAutores,listaLivros,listaEditoras);
                break;
            case 2:
                cout << "Tabela completa" << endl;
                for (int i = 0; i < TAM; i++) {
                    cout << i;
                    mostrarLivro(listaLivros[i], "");
                    cout << endl;
                }
                cout << "Tabela completa" << endl;
                for (int i = 0; i < TAM; i++) {
                    cout << i;
                    mostrarAutor(listaAutores[i], "");
                    cout << endl;
                }
                break;
            case 3:
                int matricula;
                cout << "Matricula: ";
                cin >>matricula;
                pesquisar( listaLivros, listaAutores, listaEditoras,listaUsuarios,listaRevistas, matricula);
                break;
        }
    } while (op != 0);
    cout << endl;
}
