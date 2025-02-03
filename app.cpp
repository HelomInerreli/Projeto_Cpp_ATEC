#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <locale> // biblioteca para mudar charset para UTF-8
#include <cctype> //biblioteca para a função de validação std::isdigit(c)
#include <unistd.h>
#include <sstream>

using namespace std;

// Função para imprimir a matriz formatada com ajuste automático de colunas
void printMatrix(string **mat, int l, int c, bool showAll = false)
{
    int *larguras = new int[c]; // Array dinâmico para armazenar as larguras de cada coluna

    // Inicializar o array de larguras com zero
    for (int j = 0; j < c; j++)
    {
        larguras[j] = 0;
    }

    // Calcular a largura máxima de cada coluna
    for (int j = 0; j < c; j++)
    {
        for (int i = 0; i < l; i++)
        {
            if ((int)mat[i][j].size() > larguras[j])
            {
                larguras[j] = mat[i][j].size();
            }
        }
    }

    // Adicionar margem de espaço para cada coluna
    for (int j = 0; j < c; j++)
    {
        larguras[j] += 2; // Margem de 2 espaços
    }

    // Imprimir a borda superior
    cout << "+";
    for (int j = 0; j < c; j++)
    {
        cout << string(larguras[j], '-');
        cout << "+";
    }
    cout << endl;

    // Função para imprimir uma linha da matriz
    auto printLine = [&](int i)
    {
        cout << "|";
        for (int j = 0; j < c; j++)
        {
            cout << " " << setw(larguras[j] - 1) << left << mat[i][j] << "|";
        }
        cout << endl;
        cout << "+";
        for (int j = 0; j < c; j++)
        {
            cout << string(larguras[j], '-');
            cout << "+";
        }
        cout << endl;
    };

    // Imprimir as linhas da matriz
    if (l > 6 && !showAll)
    {
        for (int i = 0; i < 3; i++)
        {
            printLine(i);
        }
        // Imprimir linha de "..."
        cout << "|";
        for (int j = 0; j < c; j++)
        {
            cout << " " << setw(larguras[j] - 1) << left << "..." << "|";
        }
        cout << endl;
        cout << "+";
        for (int j = 0; j < c; j++)
        {
            cout << string(larguras[j], '-');
            cout << "+";
        }
        cout << endl;
        for (int i = l - 2; i < l; i++)
        {
            printLine(i);
        }
    }
    else
    {
        for (int i = 0; i < l; i++)
        {
            printLine(i);
        }
    }

    // Liberar a memória alocada para o array de larguras
    delete[] larguras;
}

string addZero(int num, int digitos)
{
    string numStr = to_string(num);
    while (numStr.size() < digitos)
    {
        numStr = string(digitos - numStr.size(), '0') + numStr;
    }
    return numStr;
}

string arredondar(float num)
{
    std::stringstream stream;
    stream << fixed << setprecision(2) << num;
    return stream.str();
}

string getDateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    // string dateTime = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    string dateTime = addZero(ltm->tm_mday, 2) + "/" + addZero(1 + ltm->tm_mon, 2) + "/" + to_string(1900 + ltm->tm_year) + " " + addZero(ltm->tm_hour, 2) + ":" + addZero(ltm->tm_min, 2) + ":" + addZero(ltm->tm_sec, 2);
    // dateTime = "Data e Hora: " + dateTime;
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

void diminuirLinhas(string **&matriz, int &linhas, int colunas, int linhaRemover)
{
    // Criar uma nova matriz com o número total de linhas diminuídas
    string **novaMatriz = new string *[linhas - 1];
    int count = 0;

    // Copiar os dados da matriz antiga para a nova matriz linha por linha
    for (int i = 0; i < linhas; i++)
    {
        if (i != linhaRemover)
        {
            novaMatriz[count] = matriz[i];
            count++;
        }
        
    }

    // Liberar a matriz antiga sem liberar as linhas
    delete[] matriz;

    // Atualizar a matriz e o número de linhas
    matriz = novaMatriz;
    linhas = linhas - 1;
}

int findItem(string valor, string **matriz, int linha, int colFind)
{
    for (int i = 0; i < linha; i++)
    {
        if (matriz[i][colFind] == valor)
        {
            return i;
        }
    }
    return -1;
}

int findTextInCol(string valor, string **matriz, int linha, int colFind, int *&vecLinha)
{
    int count = 0;
    bool isFound = false;
    string valorMatriz;
    for (int i = 0; i < linha; i++)
    {
        valorMatriz = matriz[i][colFind];
        if (valorMatriz.find(valor) != string::npos)
        {
            count++;
            isFound = true;
        }
    }
    if (isFound)
    {
        int *vecResultado = new int[count]; // cria un novo vetor para os resultados encontrados
        int pos = 0;
        for (int i = 0; i < linha; i++)
        {
            if (matriz[i][colFind].find(valor) != string::npos)
            {
                vecResultado[pos] = i;
                pos++;
            }
        }
        vecLinha = vecResultado;
        return count;
    }
    return -1;
}

int findItems(string valor, string **matriz, int linha, int colFind, int *&vecLinha) // Se mais que um produto com o mesmo nome
{
    int count = 0;
    bool isFound = false;
    string valorMatriz;
    for (int i = 0; i < linha; i++)
    {
        valorMatriz = matriz[i][colFind];
        if (valorMatriz == valor)
        {
            count++;
            isFound = true;
        }
    }
    if (isFound)
    {
        int *vecResultado = new int[count]; // cria un novo vetor para os resultados encontrados
        int pos = 0;
        for (int i = 0; i < linha; i++)
        {
            if (matriz[i][colFind] == valor)
            {
                vecResultado[pos] = i;
                pos++;
            }
        }
        vecLinha = vecResultado;
        return count;
    }
    return -1;
}

void getMatLines(string **mBase, string **&mResult, int &linhas, int colunas, int *vecLinha)
{
    linhas = linhas + 1;
    int vecLinhaInt, pos = 0;
    string **mReturn = new string *[linhas];
    for (int i = 0; i < linhas; i++)
    {
        mReturn[i] = new string[colunas];
    }
    mReturn[0] = mBase[0];
    for (int i = 1; i < linhas; i++)
    {
        vecLinhaInt = vecLinha[i - 1];
        mReturn[i] = mBase[vecLinhaInt];
    }
    mResult = mReturn;
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

void addProd(string **&mProd, int &linhasProd, int colunasProd, string idProd, string nomeProd, string qtdProd, string precoProd)
{
    int linha = linhasProd;
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

void showMenuSearchStock(string **mat, int linhas, int colunas)
{
    char choice;
    bool mostrarTabelaCompleta = false;
    string valor;
    int qtdLinhas = 0;
    int *vecLinha = new int[1];
    string **mLinhasProd = new string *[1]; // criar matriz para buscar produtos do id solicitado (na modificação de produto)
    for (int i = 0; i < 2; i++)
    {
        mLinhasProd[i] = new string[4];
    }
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                                   CONSULTAR STOCK\033[0m\n";
        cout << endl;
        cout << "  I. PROC. POR ID   " << "D. PROC. POR DESCRIÇÃO   " << "M. MOSTRAR TODOS PRODUTOS   " << "R. RETORNAR\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        cout << endl;
        if (qtdLinhas > 0 && !mostrarTabelaCompleta)
        {
            printMatrix(mLinhasProd, qtdLinhas, colunas, true);
        }
        if (mostrarTabelaCompleta)
        {
            printMatrix(mat, linhas, colunas, true);
        }       
        cout << endl;
        cout << "                          \033[32mData e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\033[0m\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'M':
            mostrarTabelaCompleta = true;
            break;
        case 'I':
            cout << "Digite o ID do produto desejado: ";
            cin.ignore();
            getline(cin, valor);
            qtdLinhas = findItems(valor, mat, linhas, 0, vecLinha);
            if (qtdLinhas < 0)
            {
                cout << "Produto não encontrado!!!\n";
                sleep(1);
                break;
            }
            getMatLines(mat, mLinhasProd, qtdLinhas, 4, vecLinha);
            mostrarTabelaCompleta = false;
            break;
        case 'D':
            cout << "Digite a descrição do produto desejado: ";
            cin.ignore();
            getline(cin, valor);
            valor = textToUpper(valor);
            qtdLinhas = findTextInCol(valor, mat, linhas, 1, vecLinha);
            if (qtdLinhas < 0)
            {
                cout << "Produto não encontrado!!!\n";
                sleep(1);
                break;
            }
            getMatLines(mat, mLinhasProd, qtdLinhas, 4, vecLinha);
            mostrarTabelaCompleta = false;
            break;
        case 'R':
            cout << "Retornando...\n";
            break;

        default:
            cout << "Opção inválida! Tente novamente.\n";
            sleep(1);
        }
    } while (choice != 'R');
}

void showMenuAddProd(string **&mProd, int &linhasProd, int colunasProd)
{
    char choice;
    string id, nomeProd, qtdProd, precoProd;
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                                    ADICIONAR PRODUTO\033[0m\n";
        cout << endl;
        cout << "                                     R. RETORNAR\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        cout << endl;
        printMatrix(mProd, linhasProd, colunasProd);
        cout << endl;
        cout << "                          \033[32mData e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\033[0m\n";
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

        addProd(mProd, linhasProd, colunasProd, id, nomeProd, qtdProd, arredondar(stof(precoProd)));
    } while (choice != 'R');
}

void getMatLine(string **&mBase, string **&mReturn, int linha)
{
    mReturn[0] = mBase[0];
    mReturn[1] = mBase[linha];
}

void getMatLineProd(string **&mBase, string **&mReturn, int linha)
{
    mReturn[0] = mBase[linha];
}

void showMenuAltProd(string **&mProd, int &linhasProd, string id, int linha)
{
    char choice;
    string novoValor;
    string **mLinhaProd = new string *[2]; // criar matriz para buscar produtos do id solicitado (na modificação de produto)
    for (int i = 0; i < 2; i++)
    {
        mLinhaProd[i] = new string[4];
    }
    getMatLine(mProd, mLinhaProd, linha);

    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                                    MODIFICAR PRODUTO\033[0m\n";
        cout << endl;
        cout << "   N. ALTERAR NOME   " << "Q. ALTERAR QUANTIDADE   " << "C. ALTERAR CUSTO   " << "R. RETORNAR\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        cout << endl;
        printMatrix(mLinhaProd, 2, 4);
        cout << endl;
        cout << "                          \033[32mData e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\033[0m\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);
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
            editFildMatrix(mProd, linha, 3, arredondar(stof(novoValor)));
            break;

        default:
            cout << "Opção inválida! Tente novamente.\n";
        }

    } while (choice != 'R');
}

float calcSubTotal(string **matCarr, int linhasCarr)
{
    float total = 0;
    for (int i = 1; i < linhasCarr; i++)
    {
        total = total + stof(matCarr[i][5]);
    }
    return total;
}

void inserirProdutoVenda(string idProd, int qtdProd, string **&matCarr, int &linhasCarr, string **matStock, int linhaStock, int linhaProd)
{
    string texto;
    float valor, valorIva;
    linhasCarr = linhasCarr + 1;
    string **mLinha = new string *[1];
    mLinha[0] = new string[4];
    string **mReturn = new string *[linhasCarr];
    for (int i = 0; i < linhasCarr; i++)
    {
        mReturn[i] = new string[6];
    }
    for (int i = 0; i < linhasCarr - 1; i++)
    {
        mReturn[i] = matCarr[i];
    }

    getMatLineProd(matStock, mLinha, linhaProd);
    mReturn[linhasCarr - 1][0] = mLinha[0][0];
    mReturn[linhasCarr - 1][1] = mLinha[0][1];
    mReturn[linhasCarr - 1][2] = to_string(qtdProd);
    texto = mLinha[0][3];
    valor = stof(mLinha[0][3]) * 1.30;
    valorIva = valor * 1.23;
    mReturn[linhasCarr - 1][3] = arredondar(valor);
    mReturn[linhasCarr - 1][4] = arredondar(valorIva);
    mReturn[linhasCarr - 1][5] = arredondar(valorIva * qtdProd);

    matCarr = mReturn;
    delete[] mLinha;
}

bool sorteio(int nSorte, float minCompra, float valorCompra)
{
    string pontos = "";
    bool ganhou = false;
    int contador = 0;
    int qtdSorteios;

    if (valorCompra > minCompra)
    {
        qtdSorteios = valorCompra / minCompra;
    }
    else
    {
        cout << "Valor da compra não atingiu o mínimo para participar do sorteio.\n";
        sleep(3);
        return false;
    }

    do
    {
        string sorteio = to_string(rand() % 100 + 1);
        sorteio = addZero(stoi(sorteio), 3);

        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                   NÚMERO DA SORTE CLIENTE: \033[0m" << addZero(nSorte, 3) << "   \033[32mSORTEANDO" << pontos << "\n";
        cout << endl;
        // cout << "F. Finalizar venda   " << "N. NIF Cliente   "<<"C. Cancelar venda   " << "R. Retornar\n";
        cout << "======================================================================================\n";
        cout << endl;
        // cout << sorteio << "\n";
        cout << "                                 ------------- \n";
        cout << "                                 | \033[0m" << sorteio[0] << "\033[32m | \033[0m" << sorteio[1] << "\033[32m | \033[0m" << sorteio[2] << "\033[32m | \n";
        cout << "                                 ------------- \n";
        cout << endl;
        cout << "======================================================================================\033[0m\n";
        if (stoi(sorteio) == nSorte)
        {
            ganhou = true;
            cout << "                           PARABÉNS!!! VOCÊ GANHOU!!!\n";
            sleep(3);
            break;
        }
        else if (contador == qtdSorteios - 1)
        {
            cout << "                Infelizmente não foi desta vez! Boa sorte na próxima!\n";
            sleep(3);
            break;
        }

        if (pontos == "...")
        {
            pontos = "";
        }
        else
        {
            pontos += ".";
        }
        sleep(1);
        contador++;
    } while (!ganhou && contador < qtdSorteios);
    return ganhou;
}

void updateStockVenda(string **&matStock, string **matVenda, int linhaStock, int linhaVendas)
{
    for (int i = 1; i < linhaVendas; i++)
    {
        int linhaProd = findItem(matVenda[i][0], matStock, linhaStock, 0);
        int qtdNova = stoi(matStock[linhaProd][2]) - stoi(matVenda[i][2]);
        editFildMatrix(matStock, linhaProd, 2, to_string(qtdNova));
    }
}

void updateMatProdVendas(string **&matProdVendas, string **matCarrinho, int &linhasProdVendas, int colunasProdVendas, int linhasCarrinho, string talao)
{
    for (int i = 1; i < linhasCarrinho; i++)
    {
        aumentarLinhas(matProdVendas, linhasProdVendas, colunasProdVendas, 1);
        matProdVendas[linhasProdVendas - 1][0] = talao;
        matProdVendas[linhasProdVendas - 1][1] = matCarrinho[i][0];
        matProdVendas[linhasProdVendas - 1][2] = matCarrinho[i][1];
        matProdVendas[linhasProdVendas - 1][3] = matCarrinho[i][2];
        matProdVendas[linhasProdVendas - 1][4] = matCarrinho[i][4];
    }
}

bool showMenuFinalizarVenda(string **&matVenda, int &linhasMatVenda, string **&matProdVendas, int &linhasProdVendas, string **&matCarrinho, int linhasCarrinho, string **&matStock, int linhaStock, int talao, float subTotal, string dataHora)
{
    // srand(time(NULL));
    int nSorte, step = 0;
    char opcao = 'Z';
    string cliente, entrada = "";
    bool ganhou = false, sair = false, sorteado = false;
    float valorPago = 0.00, troco = 0.00;

    // idVenda = findLastId(matVenda, linhasMatVenda) + 1;
    // nSorte = rand() % 100 + 1;
    nSorte = talao;

    do
    {
    reexibir:
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                          FINALIZAR VENDA - ID VENDA: \033[0m" << talao << "\n";
        cout << endl;
        cout << "              C. CANCELAR VENDA   " << "V. VOLTAR ETAPA   " << "R. RETORNAR A VENDA\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        printMatrix(matCarrinho, linhasCarrinho, 6);
        cout << endl;
        cout << "\033[32m======================================================================================\n";
        cout << "                 Talão: \033[0m" << talao << "  \033[32mData e Hora: \033[0m" << dataHora << " \n";
        if (cliente.length() > 0)
        {
            cout << "\033[32mNIF Cliente: \033[0m" << cliente << "                  \033[32mNúmero da Sorte: \033[0m" << addZero(nSorte, 3) << "\n";
        }
        cout << "\033[32mTotal a pagar: \033[0m" << arredondar(subTotal) << "€ \n";
        cout << "\033[32mValor pago: \033[0m" << arredondar(valorPago) << "€ \n";
        cout << "\033[32mTroco: \033[0m" << arredondar(troco) << "€ \n";
        cout << "\033[32m======================================================================================\033[0m\n";
        opcao = 'Z';
        if (step == 0)
        {
            cout << "Insira o NIF do cliente ou N para não adicionar NIF: ";
        }
        else if (step == 1)
        {
            cout << "Deseja participar do sorteio? (S/N): ";
            cin >> entrada;
            entrada = textToUpper(entrada);
            if (entrada == "S")
            {
                ganhou = sorteio(nSorte, 5.00, subTotal);
                if (ganhou)
                {
                    cout << "Sua compra será grátis desta vez! Parabéns\n";
                    step = 3;
                    sorteado = true;
                    goto reexibir;
                }
                else
                {
                    step = 2;
                    sorteado = true;
                    opcao = 'Z';
                    goto reexibir;
                }
            }
            else
            {
                step = 2;
                goto reexibir;
            }
            // sair = true;
        }
        if (step == 2)
        {
            cout << "Insira o valor pago pelo cliente ou opção: ";
        }
        if (step == 3)
        {
            goto finalizar;
        }

        cin >> entrada;
        entrada = textToUpper(entrada);

        if (entrada == "R" || entrada == "V" || entrada == "C" || entrada == "N")
        {
            opcao = entrada[0];
        }
        else if (!validNum(entrada) && entrada.length() > 0)
        {
            opcao = 'S';
        }

        switch (opcao)
        {
        case 'Z':
            if (step == 0 && entrada.length() == 9)
            {
                cliente = entrada;
                step = 1;
            }
            else if (step == 0 && entrada.length() != 9)
            {
                cout << "NIF inválido! Insira um NIF válido.\n";
                sleep(1);
            }
            if (step == 2)
            {

                valorPago = stof(entrada);
                while (valorPago < subTotal && entrada != "C" && entrada != "R" && entrada != "V")
                {
                    cout << "Valor pago é inferior ao total a pagar. Insira um valor igual ou superior ao total a pagar.\n";
                    cout << "Insira o valor pago pelo cliente ou opção: ";
                    cin >> entrada;
                    entrada = textToUpper(entrada);
                    while (!validNum(entrada) && entrada != "C" && entrada != "R" && entrada != "V")
                    {
                        cout << "Valor inserido não é um número.\n";
                        cout << "Insira o valor pago pelo cliente ou opção: ";
                        cin >> entrada;
                        entrada = textToUpper(entrada);
                    }
                    valorPago = stof(entrada);
                    if (entrada == "C" || entrada == "R" || entrada == "V")
                    {
                        break;
                    }
                }
                if (entrada == "C" || entrada == "R" || entrada == "V")
                {
                    opcao = entrada[0];
                    goto finalizar;
                }
                troco = valorPago - subTotal;
                step = 3;
                goto reexibir;
            }
        finalizar:
            if (step == 3)
            {

                // Adicionar a matriz de vendas
                updateStockVenda(matStock, matCarrinho, linhaStock, linhasCarrinho);
                updateMatProdVendas(matProdVendas, matCarrinho, linhasProdVendas, 5, linhasCarrinho, to_string(talao));
                aumentarLinhas(matVenda, linhasMatVenda, 4, 1);
                matVenda[linhasMatVenda - 1][0] = to_string(talao);
                matVenda[linhasMatVenda - 1][1] = dataHora;
                matVenda[linhasMatVenda - 1][2] = cliente;
                matVenda[linhasMatVenda - 1][3] = arredondar(subTotal);
                cout << "      Compra finalizada com sucesso! Obrigado pela preferência e volte sempre\n";
                sleep(5);
                return false;
            }

            break;
        case 'V':
            if (step > 0)
            {
                if (step == 2)
                {
                    step = 0;
                }
                else
                {
                    step--;
                }
            }
            else
            {
                cout << "Não é possível voltar mais etapas.\n";
                sleep(1);
            }

            break;
        case 'C':
            cout << "Cancelando venda...\n";
            sleep(1);
            sair = true;
            // colocar para voltar para menu principal de vendas
            return false;
            break;
        case 'N':
            cout << "NIF não informado.\n";
            sleep(1);
            step = 2;
            break;
        case 'R':
            cout << "Retornando a venda...\n";
            sleep(1);
            sair = false;
            return true;
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
            sleep(2);
        }
    } while (!sair);
    return false;
}

void showMenuNovaVenda(string **&matVenda, int &linhasMatVenda, string **&matProdVendas, int &linhasMatProdVendas, string **&matStock, int linhasMatStock)
{
    char opcao;
    bool retorno;
    string choice, qtdProd;
    int talao, linhaProd;
    int linhasCarr = 1;
    float subTotal = 0.00;
    string dataHora = getDateTime();
    talao = findLastId(matVenda, linhasMatVenda) + 1;
    string **mProduto = new string *[1];
    mProduto[0] = new string[4];
    string **mCarrinho = new string *[1]; // criar matriz para buscar produtos do id solicitado (na modificação de produto)
    for (int i = 0; i < linhasCarr; i++)
    {
        mCarrinho[i] = new string[6];
    }
    mCarrinho[0][0] = "ID PROD";
    mCarrinho[0][1] = "DESCRICAO DO PRODUTO";
    mCarrinho[0][2] = "QTD PROD";
    mCarrinho[0][3] = "VALOR";
    mCarrinho[0][4] = "VALOR + IVA";
    mCarrinho[0][5] = "VALOR TOTAL";

    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                             NOVA VENDA - TALÃO: \033[0m" << talao << "\n";
        cout << endl;
        // cout << dataHora <<"                VALOR TOTAL A PAGAR: " << arredondar(subTotal) << "€ \n";
        cout << "     F. FINALIZAR VENDA   " << "P. CONSULTAR PRODUTO   " << "C. CANCELAR VENDA   " << "R. RETORNAR\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        printMatrix(mCarrinho, linhasCarr, 6);
        cout << endl;
        cout << "\033[32mData e Hora: " << dataHora << "                  VALOR TOTAL A PAGAR: " << arredondar(subTotal) << "€ \n";
        // cout << getDateTime() << "\n";
        cout << "======================================================================================\033[0m\n";
        cout << "Insira o ID do produto ou opção: ";
        cin >> choice;
        choice = textToUpper(choice);
        if (choice.length() > 0)
        {
            if (validNum(choice))
            {
                opcao = 'Z';
            }
            else
            {
                opcao = choice[0];
            }
        }

        switch (opcao)
        {
        case 'P':
            showMenuSearchStock(matStock, linhasMatStock, 4);
            break;
        case 'F':
            cout << "Finalizando venda...\n";
            retorno = showMenuFinalizarVenda(matVenda, linhasMatVenda, matProdVendas, linhasMatProdVendas, mCarrinho, linhasCarr, matStock, linhasMatStock, talao, subTotal, dataHora);
            if (retorno)
            {
                break;
            }

            return;
        case 'C':
            return;
            break;
        case 'Z':
            linhaProd = findItem(choice, matStock, linhasMatStock, 0);
            if (linhaProd < 0)
            {
                cout << "Produto não encontrado!!!\n";
                sleep(1);
                break;
            }
            getMatLineProd(matStock, mProduto, linhaProd);
            cout << endl;
            cout << "\033[32m======================================================================================\n";
            cout << "                    Produto: \033[0m" << mProduto[0][1] << "  \033[32mPreço: \033[0m" << arredondar(stof(mProduto[0][3]) * 1.30) << "€\n";
            cout << "\033[32m======================================================================================\033[0m\n";
            cout << endl;
            cout << "Informe a quantidade do produto: ";
            cin >> qtdProd;
            while (!validNum(qtdProd) && (textToUpper(qtdProd) != "R" || textToUpper(qtdProd) != "F" || textToUpper(qtdProd) != "P" || textToUpper(qtdProd) != "C"))
            {
                cout << "Valor inserido não é um número.\n";
                cout << "Informe a quantidade do produto: ";
                cin >> qtdProd;
            }
            while (qtdProd == "0" || stoi(qtdProd) > stoi(mProduto[0][2]) && (textToUpper(qtdProd) != "R" || textToUpper(qtdProd) != "F" || textToUpper(qtdProd) != "P" || textToUpper(qtdProd) != "C"))
            {
                cout << "Quantidade inválida! Insira uma quantidade maior que 0 e menor que o stock atual do produto\n";
                cout << "Stock Atual do produto: " << mProduto[0][2] << "\n";
                cout << "Informe a quantidade do produto: ";
                cin >> qtdProd;
            }
            if (textToUpper(qtdProd) == "R")
            {
                break;
            }
            if (textToUpper(qtdProd) == "C")
            {
                return;
            }

            inserirProdutoVenda(choice, stoi(qtdProd), mCarrinho, linhasCarr, matStock, linhasMatStock, linhaProd);
            subTotal = calcSubTotal(mCarrinho, linhasCarr);
            break;
        default:
            if (opcao != 'R')
            {
                cout << "Opção inválida! Tente novamente.\n";
                sleep(1);
            }
        }

    } while (opcao != 'R');
}

void prePreencherMatriz(string **mProd, string **mVendas, string **mCompras)
{
    mProd[0][0] = "ID";         // Coluna ID
    mProd[0][1] = "NOME";       // Coluna Descrição
    mProd[0][2] = "QUANTIDADE"; // Coluna Quantidade
    mProd[0][3] = "CUSTO";      // Coluna Custo              // Coluna Custo

    mProd[1][0] = "1";                // Coluna ID
    mProd[1][1] = "ARROZ CONTINENTE"; // Coluna Descrição
    mProd[1][2] = "10";               // Coluna Quantidade
    mProd[1][3] = "2.00";                // Coluna Custo

    mProd[2][0] = "2";               // Coluna ID
    mProd[2][1] = "MASSA ESPAGUETE"; // Coluna Descrição
    mProd[2][2] = "15";              // Coluna Quantidade
    mProd[2][3] = "0.80";            // Coluna Custo

    mProd[3][0] = "3";        // Coluna ID
    mProd[3][1] = "SALSICHA"; // Coluna Descrição
    mProd[3][2] = "3";        // Coluna Quantidade
    mProd[3][3] = "1.20";      // Coluna Custo

    mProd[4][0] = "4";            // Coluna ID
    mProd[4][1] = "CARNE PICADA"; // Coluna Descrição
    mProd[4][2] = "5";            // Coluna Quantidade
    mProd[4][3] = "5.00";            // Coluna Custo

    mProd[5][0] = "5";                // Coluna ID
    mProd[5][1] = "ARROZ PINGO DOCE"; // Coluna Descrição
    mProd[5][2] = "42";               // Coluna Quantidade
    mProd[5][3] = "1.00";                // Coluna Custo

    mProd[6][0] = "6";                // Coluna ID
    mProd[6][1] = "MANTEIGA"; // Coluna Descrição
    mProd[6][2] = "50";               // Coluna Quantidade
    mProd[6][3] = "1.85";                // Coluna Custo

    mProd[7][0] = "7";                // Coluna ID
    mProd[7][1] = "BOLACHA"; // Coluna Descrição
    mProd[7][2] = "9";               // Coluna Quantidade
    mProd[7][3] = "1.00";                // Coluna Custo

    mProd[8][0] = "8";                // Coluna ID
    mProd[8][1] = "LEITE"; // Coluna Descrição
    mProd[8][2] = "35";               // Coluna Quantidade
    mProd[8][3] = "0.90";                // Coluna Custo

    mProd[9][0] = "12";                // Coluna ID
    mProd[9][1] = "ARROZ MERCADONA"; // Coluna Descrição
    mProd[9][2] = "17";               // Coluna Quantidade
    mProd[9][3] = "1.75";                // Coluna Custo
    //------------------------------------------------------

    mVendas[0][0] = "TALAO";      // Talão venda
    mVendas[0][1] = "DATA VENDA"; // Hora da venda
    mVendas[0][2] = "CLIENTE";    // nome cliente
    mVendas[0][3] = "VALOR";      // total venda

    mVendas[1][0] = "1";                   // id venda
    mVendas[1][1] = "01/01/2025 13:00:15"; // Hora da venda
    mVendas[1][2] = "123456789";           // nº cliente
    mVendas[1][3] = "56.40";               // total venda

    mVendas[2][0] = "2";                   // Coluna ID
    mVendas[2][1] = "01/01/2025 14:10:17"; // Hora da venda
    mVendas[2][2] = "987654321";           // nº cliente
    mVendas[2][3] = "26.72";               // total venda

    mVendas[3][0] = "3";                   // Coluna ID
    mVendas[3][1] = "01/01/2025 14:20:35"; // Hora da venda
    mVendas[3][2] = "123123123";           // nº cliente
    mVendas[3][3] = "78.32";               // total venda

    mVendas[4][0] = "4";                   // Coluna ID
    mVendas[4][1] = "01/01/2025 15:06:56"; // Hora da venda
    mVendas[4][2] = "999999999";           // nº cliente
    mVendas[4][3] = "7.77";                // total venda

    mVendas[5][0] = "5";                   // Coluna ID
    mVendas[5][1] = "01/01/2025 15:09:15"; // Hora da venda
    mVendas[5][2] = "111111111";           // nº cliente
    mVendas[5][3] = "69.54";               // total venda

    //------------------------------------------------------

    mCompras[0][0] = "TALAO";
    mCompras[0][1] = "ID PRODUTO";
    mCompras[0][2] = "DESC PRODUTO";
    mCompras[0][3] = "QUANTIDADE";
    mCompras[0][4] = "PRECO";

    mCompras[1][0] = "1";
    mCompras[1][1] = "2";
    mCompras[1][2] = "MASSA ESPAGUETE";
    mCompras[1][3] = "7";
    mCompras[1][4] = "1.05";

    mCompras[2][0] = "1";
    mCompras[2][1] = "3";
    mCompras[2][2] = "SALSICHA";
    mCompras[2][3] = "2";
    mCompras[2][4] = "1.55";

    mCompras[3][0] = "1";
    mCompras[3][1] = "5";
    mCompras[3][2] = "ARROZ PINGO DOCE";
    mCompras[3][3] = "3";
    mCompras[3][4] = "1.30";

    mCompras[4][0] = "1";
    mCompras[4][1] = "4";
    mCompras[4][2] = "CARNE PICADA";
    mCompras[4][3] = "5";
    mCompras[4][4] = "6.50";

    mCompras[5][0] = "2";
    mCompras[5][1] = "5";
    mCompras[5][2] = "ARROZ PINGO DOCE";
    mCompras[5][3] = "7";
    mCompras[5][4] = "1.30";

    mCompras[6][0] = "3";
    mCompras[6][1] = "5";
    mCompras[6][2] = "MANTEIGA";
    mCompras[6][3] = "2";
    mCompras[6][4] = "1.85";

    mCompras[7][0] = "3";
    mCompras[7][1] = "5";
    mCompras[7][2] = "ARROZ MERCADONA";
    mCompras[7][3] = "3";
    mCompras[7][4] = "1.75";
}

void showMenuConsultaProdutosVendas(string **matProdVendas, int linhasProdVendas, string **matVendas, int linhasVendas)
{
    char choice;
    string talao;
    int qtdLinhas = 0;
    int *vecLinha = new int[1];
    string **mLinhasProd = new string *[1]; // criar matriz para buscar produtos do id solicitado (na modificação de produto)
    for (int i = 0; i < 2; i++)
    {
        mLinhasProd[i] = new string[4];
    }
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                           CONSULTAR PRODUTOS DE UMA VENDA\033[0m\n";
        cout << endl;
        cout << "          T. PROCURAR POR TALÃO   " << "I. PROCURAR POR ID PRODUTO   " << "R. RETORNAR\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        cout << endl;
        if (qtdLinhas > 0)
        {
            printMatrix(mLinhasProd, qtdLinhas, 5);
        }
        else
        {
            printMatrix(matProdVendas, linhasProdVendas, 5);
        }
        cout << endl;
        cout << "                          \033[32mData e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\033[0m\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'T':
            cout << "Digite o talão da venda desejada: ";
            cin.ignore();
            getline(cin, talao);
            qtdLinhas = findItems(talao, matProdVendas, linhasProdVendas, 0, vecLinha);
            if (qtdLinhas < 0)
            {
                cout << "Talão não encontrado!!!\n";
                sleep(1);
                break;
            }
            getMatLines(matProdVendas, mLinhasProd, qtdLinhas, 5, vecLinha);
            break;
        case 'I':
            cout << "Digite o ID do Produto desejado: ";
            cin.ignore();
            getline(cin, talao);
            qtdLinhas = findItems(talao, matProdVendas, linhasProdVendas, 1, vecLinha);
            if (qtdLinhas < 0)
            {
                cout << "Produto não encontrado!!!\n";
                sleep(1);
                break;
            }

            getMatLines(matProdVendas, mLinhasProd, qtdLinhas, 1, vecLinha);
            break;
        case 'R':
            cout << "Retornando...\n";
            sleep(1);
            break;

        default:
            cout << "Opção inválida! Tente novamente.\n";
            sleep(1);
        }
    } while (choice != 'R');
}

void showMenuVendas(string **mat, int linhas, int colunas, string **&matProdVendas, int &linhasProdVendas, string **&matStock, int &linhasMatStock)
{
    char choice;
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                                    MENU DE VENDAS\033[0m\n";
        cout << endl;
        cout << "               V.VENDER   " << "C. CONSULTAR PRODUTOS DE UMA VENDA  " << "R. RETORNAR\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        cout << endl;
        printMatrix(mat, linhas, colunas);
        cout << endl;
        cout << "                          \033[32mData e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\033[0m\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'V':
            cout << "Vender...\n";
            showMenuNovaVenda(mat, linhas, matProdVendas, linhasProdVendas, matStock, linhasMatStock);
            break;
        case 'C':
            cout << "Consultando Produtos...\n";
            showMenuConsultaProdutosVendas(matProdVendas, linhasProdVendas, mat, linhas);
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
    string **mProduto = new string *[1];
    mProduto[0] = new string[4];
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "\033[32m======================================================================================\n";
        cout << endl;
        cout << "                                    MENU STOCK\033[0m\n";
        cout << endl;
        cout << "   C. CONSULTAR   " << "E. ELIMINAR   " << "A. ADICIONAR   " << "M. MODIFICAR   " << "R. RETORNAR\n";
        cout << "\033[32m======================================================================================\033[0m\n";
        cout << endl;
        printMatrix(mProd, linhasProd, colunasProd);
        cout << endl;
        cout << "                          \033[32mData e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\033[0m\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'C':
            cout << "Consultando Stock...\n";
            showMenuSearchStock(mProd, linhasProd, colunasProd);
            break;
        case 'A':
            cout << "Adicionando Produto...\n";
            showMenuAddProd(mProd, linhasProd, colunasProd);
            break;
        case 'E':
            cout << "Informe o ID do produto que deseja remover: ";
            cin >> id;
            linha = findItem(id, mProd, linhasProd, 0);
            while (linha < 0 && textToUpper(id) != "R")
            {
                cout << "O id inserido não foi encontrado.\n";
                cout << "Insira novamente o id : ";
                cin >> id;
                linha = findItem(id, mProd, linhasProd, 0);
            }
            if (textToUpper(id) == "R")
            {
                choice = 'R';
                break;
            }
            getMatLineProd(mProd, mProduto, linha);
            cout << endl;
            cout << "\033[32m======================================================================================\n";
            cout << "        Produto: \033[0m" << mProduto[0][1] << "  \033[32mQuantidade: \033[0m" << mProduto[0][2] <<"  \033[32mCusto: \033[0m" << mProduto[0][3] << "\n";
            cout << "\033[32m======================================================================================\033[0m\n";
            cout << endl;
            cout << "Deseja realmente remover o produto? (S/N): ";
            cin >> id;
            id = textToUpper(id);
            if (id == "S")
            {
                diminuirLinhas(mProd, linhasProd, colunasProd, linha);
            }
            break;
        case 'M':
            cout << "Escolha o ID: ";
            cin >> id;
            linha = findItem(id, mProd, linhasProd, 0);
            while (linha < 0 && textToUpper(id) != "R")
            {

                cout << "O id inserido não foi encontrado.\n";
                cout << "Insira novamente o id : ";
                cin >> id;
                linha = findItem(id, mProd, linhasProd, 0);
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
            sleep(1);
        }
    } while (choice != 'R');
}

void showMenu()
{
    system("clear"); // Limpa o terminal no Windows
    cout << "\033[32m======================================================================================\n";
    cout << endl;
    cout << "                                   MENU PRINCIPAL\033[0m\n";
    cout << endl;
    cout << "               S. STOCK   " << "V. VENDAS   " << "A. SORTEIO ALEATÓRIO   " << "F. FECHAR\n";
    cout << "\033[32m======================================================================================\n";
    cout << "                          Data e Hora: " << getDateTime() << "\n";
    cout << "======================================================================================\033[0m\n";
    cout << "Escolha uma opção: ";
}

int main()
{
    setlocale(LC_ALL, ""); // mudar charset para utf-8
    system("color A");     // Mudar cor do terminal no Windows
    char choice;
    int linhasProd = 10, colunasProd = 4, linhasVendas = 6, colunasVendas = 4, linhasCompras = 8, colunasCompras = 5;
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
        mCompras[i] = new string[colunasCompras];
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
            showMenuVendas(mVendas, linhasVendas, colunasVendas, mCompras, linhasCompras, mProd, linhasProd);
            break;
        case 'A':
            cout << "Sorteio Aleatório, digite o número da sorte entre 1 e 99: ";
            int nSorte;
            cin >> nSorte;
            while (nSorte < 1 || nSorte > 99)
            {
                cout << "Número inválido! Digite um número entre 1 e 99\n";
                cin >> nSorte;
            }
            if (sorteio(nSorte, 5.00, 50.00))
            {
                cout << "Parabéns! Você ganhou o sorteio!\n";
            }
            else
            {
                cout << "Não foi dessa vez! Tente novamente.\n";
            }

            break;
        case 'F':
            cout << "Fechando...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (choice != 'F');
}
