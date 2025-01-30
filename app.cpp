#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <locale> // biblioteca para mudar charset para UTF-8
#include <cctype> //biblioteca para a função de validação std::isdigit(c)

using namespace std;

// Função para imprimir a matriz formatada com ajuste automático de colunas
void printMatrix(string** mat, int l, int c)
{
    int* larguras = new int[c]; // Array dinâmico para armazenar as larguras de cada coluna

    // Inicializar o array de larguras com zero
    for (int j = 0; j < c; j++) {
        larguras[j] = 0;
    }

    // Calcular a largura máxima de cada coluna
    for (int j = 0; j < c; j++) {
        for (int i = 0; i < l; i++) {
            if ((int)mat[i][j].size() > larguras[j]) {
                larguras[j] = mat[i][j].size();
            }
        }
    }

    // Adicionar margem de espaço para cada coluna
    for (int j = 0; j < c; j++) {
        larguras[j] += 2; // Margem de 2 espaços
    }

    // Imprimir a borda superior
    cout << "+";
    for (int j = 0; j < c; j++) {
        cout << string(larguras[j], '-');
        cout << "+";
    }
    cout << endl;

    // Função para imprimir uma linha da matriz
    auto printLine = [&](int i) {
        cout << "|";
        for (int j = 0; j < c; j++) {
            cout << " " << setw(larguras[j] - 1) << left << mat[i][j] << "|";
        }
        cout << endl;
        cout << "+";
        for (int j = 0; j < c; j++) {
            cout << string(larguras[j], '-');
            cout << "+";
        }
        cout << endl;
    };

    // Imprimir as linhas da matriz
    if (l > 6) {
        for (int i = 0; i < 3; i++) {
            printLine(i);
        }
        // Imprimir linha de "..."
        cout << "|";
        for (int j = 0; j < c; j++) {
            cout << " " << setw(larguras[j] - 1) << left << "..." << "|";
        }
        cout << endl;
        cout << "+";
        for (int j = 0; j < c; j++) {
            cout << string(larguras[j], '-');
            cout << "+";
        }
        cout << endl;
        for (int i = l - 2; i < l; i++) {
            printLine(i);
        }
    } else {
        for (int i = 0; i < l; i++) {
            printLine(i);
        }
    }

    // Liberar a memória alocada para o array de larguras
    delete[] larguras;
}

string addZero(int num)
{
    if (num < 10)
    {
        return "0" + to_string(num);
    }
    return to_string(num);
}

string getDateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // string dateTime = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    string dateTime = addZero(ltm->tm_mday) + "/" + addZero(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " + addZero(ltm->tm_hour) + ":" + addZero(ltm->tm_min) + ":" + addZero(ltm->tm_sec);
    dateTime = "Data e Hora: " + dateTime;
    return dateTime;
}

string calcFilds(string valorAtual, float valorNovo)
{
    return to_string(stof(valorAtual) + valorNovo);
}

void aumentarLinhas(string **&matriz, int &linhas, int colunas, int novasLinhas)
{
    // Criar uma nova matriz com o número total de linhas aumentadas
    string **novaMatriz = new string *[linhas + novasLinhas];

    // Copiar os dados da matriz antiga para a nova matriz linha por linha
    for (int i = 0; i < linhas; i++)
    {
        novaMatriz[i] = matriz[i];
    }

    // Alocar memória para as novas linhas
    for (int i = linhas; i < linhas + novasLinhas; i++)
    {
        novaMatriz[i] = new string[colunas](); // Inicializa com 0
    }

    // Liberar a matriz antiga sem liberar as linhas
    delete[] matriz;

    // Atualizar a matriz e o número de linhas
    matriz = novaMatriz;
    linhas += novasLinhas;
}

int findID(string id, string **matriz, int linha)
{
    for (int i = 0; i < linha; i++)
    {
        if (matriz[i][0] == id)
        {
            return i;
        }
    }
    return -1;
}

string textToUpper(string text)
{
    string retorno;
    // cout <<"\n######"<< text.size();
    for (char c : text)
    {
        retorno += toupper(c);
    }
    return retorno;
}

int findLastId(string **matriz, int linha)
{
    int maior = 0;

    for (int i = 1; i < linha; i++)
    {
        if (stoi(matriz[i][0]) > maior)
        {
            maior = stoi(matriz[i][0]);
        }
    }
    return maior;
}

void addProd(string**& mProd, int& linhasProd, int colunasProd, string idProd, string nomeProd, string qtdProd, string precoProd){
    int linha=linhasProd;
    aumentarLinhas(mProd, linhasProd, colunasProd, 1);
    mProd[linha][0] = idProd;
    mProd[linha][1] = nomeProd;
    mProd[linha][2] = qtdProd;
    mProd[linha][3] = precoProd;
}

bool validNum(string valor)
{ // funcao de validação de input

    for (char c : valor)
    {
        if (!isdigit(c) && c != '.') // verifica se o valor inserido é um número e aceita ponto.
        {
            return false;
        }
    }
    return true;
}



void editFildMatrix(string **&matriz, int linha, int coluna, string valor)
{
    matriz[linha][coluna] = valor;
}

void showMenuAddProd(string**& mProd, int &linhasProd, int colunasProd)
{
    char choice;
    string id, nomeProd, qtdProd, precoProd;
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "=====================================\n";
        cout << "        ADICIONE UM PRODUTO          \n";
        cout << "=====================================\n";
        cout << "R. Retornar\n";
        printMatrix(mProd, linhasProd, colunasProd);
        cout << endl;
        // cout << getDateTime() << "\n";
        cout << "=====================================\n";
        id = to_string(findLastId(mProd, linhasProd) + 1);
        cout << "ID: " << id << endl;
        cout << "Insira nome do produto: ";
        cin.ignore();
        getline(cin, nomeProd);
        // cout <<"\n----------"<< nomeProd.size();
        nomeProd = textToUpper(nomeProd);
        if (nomeProd == "R")
        {
            choice = 'R';
            break;
        }
        cout << "Insira a quantidade: ";
        cin >> qtdProd;

        while (!validNum(qtdProd) && textToUpper(qtdProd) != "R")
        {
            cout << "Valor inserido não é um numero.\n";
            cout << "Insira a quantidade: ";
            cin >> qtdProd;
        }
        if (textToUpper(qtdProd) == "R")
        {
            choice = 'R';
            break;
        }

        cout << "Insira o custo: ";
        cin >> precoProd;
        while (!validNum(precoProd) && textToUpper(precoProd) != "R")
        {

            cout << "Valor inserido não é um numero.\n";
            cout << "Insira o custo: ";
            cin >> precoProd;
        }
        if (textToUpper(precoProd) == "R")
        {
            choice = 'R';
            break;
        }

        addProd(mProd, linhasProd, colunasProd, id, nomeProd, qtdProd, precoProd);
    } while (choice != 'R');
}

void getMatLine(string**& mBase, string**& mReturn, int linha){
    mReturn[0]=mBase[0];
    mReturn[1]=mBase[linha];

}

void showMenuAltProd(string**& mProd, int &linhasProd, string id, int linha)
{
    char choice;
    string novoValor;
    string** mLinhaProd = new string*[2]; // criar matriz para buscar produtos do id solicitado (na modificação de produto)
    for (int i = 0; i < 2; i++)
    {
        mLinhaProd[i] = new string[4];
    }
        getMatLine(mProd, mLinhaProd, linha);
        
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "=====================================\n";
        cout << "        MODIFICAR PRODUTO          \n";
        cout << "=====================================\n";
        cout << "N. Alterar Nome\n";
        cout << "Q. Alterar Quantidade\n";
        cout << "C. Alterar Custo\n";
        cout << "R. Retornar\n";
        printMatrix(mLinhaProd, 2, 4);
        cout << endl;
        // cout << getDateTime() << "\n";
        cout << "=====================================\n";
        cout << "Escolha a opção: ";
        cin >> choice;
        choice=toupper(choice);
        switch (choice)
        {
        case 'N':
            cout << "Informe o novo nome para o produto: ";
            cin.ignore();
            getline(cin, novoValor);
            novoValor = textToUpper(novoValor);
            editFildMatrix(mProd, linha, 1, novoValor);
            break;
        case 'Q':
            cout << "Informe a nova quantidade para o produto: ";
            cin >> novoValor;
            while (!validNum(novoValor) && textToUpper(novoValor) != "R")
            {
                cout << "Valor inserido não é um número.\n";
                cout << "Informe a nova quantidade para o produto: ";
                cin >> novoValor;
            }
            
            editFildMatrix(mProd, linha, 2, novoValor);
            break;
        case 'C':
            cout << "Informe o novo custo para o produto: ";
            cin >> novoValor;
            while (!validNum(novoValor) && textToUpper(novoValor) != "R")
            {
                cout << "Valor inserido não é um número.\n";
                cout << "Informe o novo custo para o produto: ";
                cin >> novoValor;
            }
            editFildMatrix(mProd, linha, 3, novoValor);
            break;

        default:
         cout << "Opção inválida! Tente novamente.\n";
        }
        
    } while (choice != 'R');
}

void prePreencherMatriz(string **mProd, string **mVendas, string **mCompras)
{
    mProd[0][0] = "ID";                     // Coluna ID
    mProd[0][1] = "NOME";                   // Coluna Descrição
    mProd[0][2] = "QUANTIDADE";            // Coluna Quantidade
    mProd[0][3] = "CUSTO";                // Coluna Custo              // Coluna Custo

    mProd[1][0] = "1";                // Coluna ID
    mProd[1][1] = "ARROZ CONTINENTE"; // Coluna Descrição
    mProd[1][2] = "10";               // Coluna Quantidade
    mProd[1][3] = "2";                // Coluna Custo

    mProd[2][0] = "2";               // Coluna ID
    mProd[2][1] = "MASSA ESPAGUETE"; // Coluna Descrição
    mProd[2][2] = "15";              // Coluna Quantidade
    mProd[2][3] = "0.80";            // Coluna Custo

    mProd[3][0] = "3";        // Coluna ID
    mProd[3][1] = "SALSICHA"; // Coluna Descrição
    mProd[3][2] = "3";        // Coluna Quantidade
    mProd[3][3] = "1.2";      // Coluna Custo

    mProd[4][0] = "4";            // Coluna ID
    mProd[4][1] = "CARNE PICADA"; // Coluna Descrição
    mProd[4][2] = "5";            // Coluna Quantidade
    mProd[4][3] = "5";            // Coluna Custo

    mProd[5][0] = "5";                // Coluna ID
    mProd[5][1] = "ARROZ PINGO DOCE"; // Coluna Descrição
    mProd[5][2] = "42";               // Coluna Quantidade
    mProd[5][3] = "1";                // Coluna Custo
    //------------------------------------------------------

    mVendas[0][0] = "ID";      // id venda
    mVendas[0][1] = "DATA VENDA";  // Hora da venda
    mVendas[0][2] = "CLIENTE";      // nº cliente
    mVendas[0][3] = "VALOR"; // total venda

    mVendas[1][0] = "1";      // id venda
    mVendas[1][1] = "01/01/2025 13:00:15";  // Hora da venda
    mVendas[1][2] = "7";      // nº cliente
    mVendas[1][3] = "56.40"; // total venda

    mVendas[2][0] = "2";      // Coluna ID
    mVendas[2][1] = "01/01/2025 14:10:17";  // Hora da venda
    mVendas[2][2] = "25";     // nº cliente
    mVendas[2][3] = "26.72"; // total venda

    mVendas[3][0] = "3";      // Coluna ID
    mVendas[3][1] = "01/01/2025 14:20:35";  // Hora da venda
    mVendas[3][2] = "32";     // nº cliente
    mVendas[3][3] = "78.32"; // total venda

    mVendas[4][0] = "4";     // Coluna ID
    mVendas[4][1] = "01/01/2025 15:06:56"; // Hora da venda
    mVendas[4][2] = "55";    // nº cliente
    mVendas[4][3] = "7.77";  // total venda

    mVendas[5][0] = "5";     // Coluna ID
    mVendas[5][1] = "01/01/2025 15:09:15"; // Hora da venda
    mVendas[5][2] = "7";     // nº cliente
    mVendas[5][3] = "69.54"; // total venda

    //------------------------------------------------------

    mCompras[0][0] = "ID VENDA";      // id venda
    mCompras[0][1] = "ID PRODUTO";  // Hora da venda
    mCompras[0][2] = "QUANTIDADE";      // nº cliente
    mCompras[0][3] = "PREÇO"; // total venda

    mCompras[1][0] = "1";      // id venda
    mCompras[1][1] = "2";  // Hora da venda
    mCompras[1][2] = "7";      // nº cliente
    mCompras[1][3] = "1.05"; // total venda

    mCompras[2][0] = "1";      // Coluna ID
    mCompras[2][1] = "3";  // Hora da venda
    mCompras[2][2] = "2";     // nº cliente
    mCompras[2][3] = "1.55"; // total venda

    mCompras[3][0] = "2";      // Coluna ID
    mCompras[3][1] = "5";  // Hora da venda
    mCompras[3][2] = "3";     // nº cliente
    mCompras[3][3] = "1.30"; // total venda

    mCompras[4][0] = "2";     // Coluna ID
    mCompras[4][1] = "4"; // Hora da venda
    mCompras[4][2] = "5";    // nº cliente
    mCompras[4][3] = "6.50";  // total venda

    mCompras[5][0] = "3";     // Coluna ID
    mCompras[5][1] = "5"; // Hora da venda
    mCompras[5][2] = "7";     // nº cliente
    mCompras[5][3] = "1.30"; // total venda
}

void showMenuVendas(string **mat, int linhas, int colunas)
{
    char choice;
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "=====================================\n";
        cout << "          MENU DE VENDAS          \n";
        cout << "=====================================\n";
        cout << "V. Vender\n";
        cout << "C. Consultar Produtos de uma venda\n";
        cout << "R. Retornar\n";
        cout << endl;
        printMatrix(mat, linhas, colunas);
        cout << endl;
        cout << getDateTime() << "\n";
        cout << "=====================================\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'V':
            cout << "Vender...\n";
            break;
        case 'C':
            cout << "Consultando Produtos...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (choice != 'R');
}

void showMenuStock(string **&mProd, int &linhasProd, int colunasProd)
{
    char choice;
    string id;
    int linha;
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "=====================================\n";
        cout << "      BEM-VINDO AO MENU DE STOCK          \n";
        cout << "=====================================\n";
        cout << "C. Consultar Stock\n";
        cout << "A. Adicionar Produto\n";
        cout << "M. Modificar Produto\n";
        cout << "R. Retornar\n";
        cout << endl;
        cout << endl;
        printMatrix(mProd, linhasProd, colunasProd);
        cout << endl;
        cout << getDateTime() << "\n";
        cout << "=====================================\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'C':
            cout << "Consultando Stock...\n";
            printMatrix(mProd, linhasProd, colunasProd);
            // break;
        case 'A':
            cout << "Adicionando Produto...\n";
            showMenuAddProd(mProd, linhasProd, colunasProd);
            break;
        case 'M':
        cout << "Escolha o ID: ";
        cin >> id;
        linha = findID(id, mProd, linhasProd);
        while (linha < 0 && textToUpper(id) != "R")
        {

            cout << "O id inserido não foi encontrado.\n";
            cout << "Insira novamente o id : ";
            cin >> id;
            linha = findID(id, mProd, linhasProd);
            // system("clear");
        }
        if (textToUpper(id) == "R")
        {
            choice = 'R';
            break;
        }

            showMenuAltProd(mProd, linhasProd, id, linha);
            break;
        case 'R':
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (choice != 'R');
}

void showMenuSearchStock(string **mat, int linhas, int colunas)
{
    char choice;
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "=====================================\n";
        cout << "          CONSULTAR STOCK          \n";
        cout << "=====================================\n";
        cout << "P. Procurar Produto\n";
        cout << "R. Retornar\n";
        cout << endl;
        printMatrix(mat, linhas, colunas);
        cout << endl;
        cout << getDateTime() << "\n";
        cout << "=====================================\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'P':
            cout << "Procurando Produto...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (choice != 'R');
}

void showMenu()
{
    system("clear"); // Limpa o terminal no Windows
    cout << "=====================================\n";
    cout << "          BEM-VINDO AO MENU          \n";
    cout << "=====================================\n";
    cout << "S. Stock\n";
    cout << "V. Vendas\n";
    cout << "C. Compras\n";
    cout << "F. Fechar\n";
    cout << endl;
    cout << getDateTime() << "\n";
    cout << "=====================================\n";
    cout << "Escolha uma opção: ";
}

int main()
{
    setlocale(LC_ALL, ""); // mudar charset para utf-8
    char choice;
    int linhasProd = 6, colunasProd = 4, linhasVendas = 6, colunasVendas = 4, linhasCompras = 6, colunasCompras = 4;
    string **mProd = new string *[linhasProd];
    for (int i = 0; i < linhasProd; i++)
    {
        mProd[i] = new string[colunasProd];
    }

    string **mVendas = new string *[linhasVendas];
    for (int i = 0; i < linhasVendas; i++)
    {
        mVendas[i] = new string[colunasVendas];
    }

    string **mCompras = new string *[linhasCompras];
    for (int i = 0; i < linhasCompras; i++)
    {
        mCompras[i] = new string[linhasCompras];
    }

    prePreencherMatriz(mProd, mVendas, mCompras);

    do
    {
        showMenu();
        cin >> choice;
        choice = toupper(choice); // Coloca a opção em maiúsculo

        switch (choice)
        {
        case 'S':
            cout << "Iniciando Stock...\n";
            showMenuStock(mProd, linhasProd, colunasProd);
            break;
        case 'V':
            cout << "Carregando Vendas...\n";
            showMenuVendas(mVendas, linhasVendas, colunasVendas);
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