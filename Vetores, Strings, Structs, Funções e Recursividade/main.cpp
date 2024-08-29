#include <iostream>

using namespace std;

const int MAX_ATIVOS = 100;  // Maximo de ativos que podem ser registrados
const int TAM_TICKET = 7;    // Tamanho maximo para o ticket, incluindo o caractere nulo

struct Ativo {
    char ticket[TAM_TICKET];
    int quantidade;
    double precoMedio;
};

// Funcao para comparar dois tickets
int compararTickets(const char* ticket1, const char* ticket2) {
    for (int i = 0; i < TAM_TICKET; i++) {
        if (ticket1[i] < ticket2[i]) return -1;
        if (ticket1[i] > ticket2[i]) return 1;
        if (ticket1[i] == '\0' && ticket2[i] == '\0') break;
    }
    return 0;
}

// Funcao recursiva para busca binaria
int buscaBinaria(Ativo ativos[], const char* ticket, int inicio, int fim) {
    if (inicio > fim) return -1;
    int meio = inicio + (fim - inicio) / 2;

    int comparacao = compararTickets(ativos[meio].ticket, ticket);
    if (comparacao == 0) return meio;
    else if (comparacao > 0) return buscaBinaria(ativos, ticket, inicio, meio - 1);
    else return buscaBinaria(ativos, ticket, meio + 1, fim);
}

// Funcao para ordenar os ativos por ticket (insertion sort)
void ordenarAtivos(Ativo ativos[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        Ativo temp = ativos[i];
        int j = i - 1;
        while (j >= 0 && compararTickets(ativos[j].ticket, temp.ticket) > 0) {
            ativos[j + 1] = ativos[j];
            j--;
        }
        ativos[j + 1] = temp;
    }
}

// Funcao para registrar uma compra
void registrarCompra(Ativo ativos[], int &quantidadeAtivos) {
    char ticket[TAM_TICKET];
    int quantidade;
    double valor;

    cout << "Digite o ticket do ativo: ";
    cin >> ticket;
    cout << "Digite a quantidade comprada: ";
    cin >> quantidade;
    cout << "Digite o valor do ativo no momento da compra: ";
    cin >> valor;

    ordenarAtivos(ativos, quantidadeAtivos);  // Ordenar antes de buscar
    int index = buscaBinaria(ativos, ticket, 0, quantidadeAtivos - 1);

    if (index != -1) {  // Ativo ja existe
        Ativo &ativo = ativos[index];
        ativo.precoMedio = ((ativo.precoMedio * ativo.quantidade) + (valor * quantidade)) / (ativo.quantidade + quantidade);
        ativo.quantidade += quantidade;
    } else {  // Novo ativo
        Ativo novoAtivo;
        for (int i = 0; i < TAM_TICKET; i++) {
            novoAtivo.ticket[i] = ticket[i];
        }
        novoAtivo.quantidade = quantidade;
        novoAtivo.precoMedio = valor;
        ativos[quantidadeAtivos] = novoAtivo;
        quantidadeAtivos++;
    }

    cout << "Compra registrada com sucesso!" << endl;
}

// Funcao para registrar uma venda
void registrarVenda(Ativo ativos[], int quantidadeAtivos) {
    char ticket[TAM_TICKET];
    int quantidade;
    double valor;

    cout << "Digite o ticket do ativo: ";
    cin >> ticket;
    cout << "Digite a quantidade vendida: ";
    cin >> quantidade;
    cout << "Digite o valor do ativo no momento da venda: ";
    cin >> valor;

    ordenarAtivos(ativos, quantidadeAtivos);  // Ordenar antes de buscar
    int index = buscaBinaria(ativos, ticket, 0, quantidadeAtivos - 1);

    if (index != -1) {  // Ativo encontrado
        Ativo &ativo = ativos[index];

        if (ativo.quantidade >= quantidade) {
            ativo.quantidade -= quantidade;
            cout << "Venda registrada com sucesso!" << endl;
        } else {
            cout << "Erro: Quantidade insuficiente para a venda." << endl;
        }

    } else {
        cout << "Erro: Ativo nao encontrado." << endl;
    }
}

// Funcao para ver o saldo de um ativo
void verSaldo(Ativo ativos[], int quantidadeAtivos) {
    char ticket[TAM_TICKET];
    cout << "Digite o ticket do ativo: ";
    cin >> ticket;

    ordenarAtivos(ativos, quantidadeAtivos);  // Ordenar antes de buscar
    int index = buscaBinaria(ativos, ticket, 0, quantidadeAtivos - 1);

    if (index != -1) {
        Ativo &ativo = ativos[index];
        cout << "Ticket: " << ativo.ticket << endl;
        cout << "Quantidade: " << ativo.quantidade << endl;
        cout << "Preco medio: " << ativo.precoMedio << endl;
    } else {
        cout << "Erro: Ativo nao encontrado." << endl;
    }
}

// Funcao para listar o patrimonio
void listarPatrimonio(Ativo ativos[], int quantidadeAtivos) {
    if (quantidadeAtivos == 0) {
        cout << "Nenhum ativo registrado." << endl;
    } else {
        for (int i = 0; i < quantidadeAtivos; i++) {
            cout << "Ticket: " << ativos[i].ticket << endl;
            cout << "Quantidade: " << ativos[i].quantidade << endl;
            cout << "Preco medio: " << ativos[i].precoMedio << endl;
            cout << "-----------------------------" << endl;
        }
    }
}

int main() {
    Ativo ativos[MAX_ATIVOS];
    int quantidadeAtivos = 0;
    int opcao;

    do {
        cout << "Menu:" << endl;
        cout << "1. Registrar compra" << endl;
        cout << "2. Registrar venda" << endl;
        cout << "3. Ver saldo de um ativo" << endl;
        cout << "4. Listar patrimonio" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCompra(ativos, quantidadeAtivos);
                break;
            case 2:
                registrarVenda(ativos, quantidadeAtivos);
                break;
            case 3:
                verSaldo(ativos, quantidadeAtivos);
                break;
            case 4:
                listarPatrimonio(ativos, quantidadeAtivos);
                break;
            case 5:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }

    } while (opcao != 5);

    return 0;
}