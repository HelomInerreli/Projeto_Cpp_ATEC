#include <iostream>
#include <string>
#include <ctime>
#include <locale> // biblioteca para mudar charset para UTF-8

using namespace std;

//Funcao para imprimir a matriz
void impMatriz(int** mat, int l, int c) {
    // Imprimir a borda superior
    cout << "+";
    for (int j = 0; j < c; j++)
        cout << "-------+";
    cout << endl;

    // Imprimir as linhas da matriz
    for (int i = 0; i < l; i++) {
        cout << "|";
        for (int j = 0; j < c; j++) {
            cout << "   " << mat[i][j] << "   |"; // Cada célula tem uma largura fixa
        }
        cout << endl;

        // Imprimir a borda entre as linhas
        cout << "+";
        for (int j = 0; j < c; j++)
            cout << "-------+";
        cout << endl;
    }
}

//Funcao para ler a matriz
void lerMatriz(int** mat, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int ii = 0; ii < c; ii++) {
            cout << "Digite o valor da posição [" << i + 1 << "][" << ii + 1 << "]: ";
            cin >> mat[i][ii];
        }
    }
    cout << "------------------------------" << endl;
}

//Funcao para inserir uma nova linha na matriz
void inserirLinha(int**& mat, int& l, int c) {
    // Criar uma nova matriz com uma linha a mais
    int** novaMat = new int*[l + 1];
    for (int i = 0; i < l + 1; i++) {
        novaMat[i] = new int[c];
    }

    // Copiar os valores da matriz antiga para a nova
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            novaMat[i][j] = mat[i][j];
        }
    }

    // Ler os valores da nova linha
    for (int j = 0; j < c; j++) {
        cout << "Digite o valor da nova linha na posição [" << l + 1 << "][" << j + 1 << "]: ";
        cin >> novaMat[l][j];
    }

    // Deletar a matriz antiga
    for (int i = 0; i < l; i++) {
        delete[] mat[i];
    }
    delete[] mat;

    // Atualizar a matriz antiga com a nova
    mat = novaMat;
    l++;
}

//Pegar o tamanho de linhas da matriz
// int getLinhas(int** mat, int l) {
//     return l;
// }

string addZero(int num) {  
    if (num < 10) {
        return "0" + to_string(num);
    }
    return to_string(num);
}

string getDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    // string dateTime = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    string dateTime = addZero(ltm->tm_mday) + "/" + addZero(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " + addZero(ltm->tm_hour) + ":" + addZero(ltm->tm_min) + ":" + addZero(ltm->tm_sec);
    dateTime = "Data e Hora: " + dateTime;
    return dateTime;
}

void showMenuVendas(){
    system("clear"); // Limpa o terminal no Windows
    cout << "=====================================\n";
    cout << "          BEM-VINDO AO MENU DE VENDAS          \n";
    cout << "=====================================\n";
    cout << "V. Vender\n";
    cout << "C. Consultar Produtos\n";
    cout << "S. Sair\n";
    cout << endl;
    cout << getDateTime() << "\n";
    cout << "=====================================\n";
    cout << "Escolha uma opção: ";
}

void showMenuEstoque(){
    char choice;
    do {
    system("clear"); // Limpa o terminal no Windows
    cout << "=====================================\n";
    cout << "      BEM-VINDO AO MENU DE ESTOQUE          \n";
    cout << "=====================================\n";
    cout << "C. Consultar Estoque\n";
    cout << "A. Adicionar Produto\n";
    cout << "S. Sair\n";
    cout << endl;
    cout << getDateTime() << "\n";
    cout << "=====================================\n";
    cout << "Escolha uma opção: ";
    cin >> choice;
    choice = toupper(choice);
    
    
    switch (choice) {
        case 'C':
            cout << "Consultando Estoque...\n";
            break;
        case 'A':
            cout << "Adicionando Produto...\n";
            break;
        case 'S':
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
    }
    } while (choice != 'S');
}

void showMenu() {
    // system("clear"); // Limpa o terminal no Windows
    cout << "=====================================\n";
    cout << "          BEM-VINDO AO MENU          \n";
    cout << "=====================================\n";
    cout << "E. Estoque\n";
    cout << "V. Vendas\n";
    cout << "C. Compras\n";
    cout << "F. Fechar\n";
    cout << endl;
    cout << getDateTime() << "\n";
    cout << "=====================================\n";
    cout << "Escolha uma opção: ";
}

int main() {
    setlocale(LC_ALL, ""); //mudar charset para utf-8
    char choice;
    int l = 5;
    int c = 4;
    int** mProd = new int*[l];
    for (int i = 0; i < l; i++) {
        mProd[i] = new int[c];
    }

    do {
        showMenu();
        cin >> choice;
        //Coloca a opção em maiúsculo
        choice = toupper(choice);

        switch (choice) {
            case 'E':
                cout << "Iniciando Estoque...\n";
                showMenuEstoque();
                break;
            case 'V':
                cout << "Carregando Vendas...\n";
                break;
            case 'C':
                cout << "Abrindo Compras...\n";
                break;
            case 'F':
                cout << "Fechando...\n";
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (choice != 'F');

    return 0;
}