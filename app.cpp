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
    string dateTime = addZero(ltm->tm_mday) + "/" + addZero(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year) + " " + addZero(ltm->tm_hour) + ":" + addZero(ltm->tm_min) + ":" + addZero(ltm->tm_sec);
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
int findItems(string valor, string **matriz, int linha, int colFind, int*& vecLinha) // Se mais que um produto com o mesmo nome
{
    int count=0;
    bool isFound= false;
    for (int i = 0; i < linha; i++)
    {
        if (matriz[i][colFind] == valor)
        {
           count++;
           isFound=true;
        }
    }
    if  (isFound)
    {
    int *vecResultado=new int[count]; // cria un novo vetor para os resultados encontrados
        for (int i = 0; i < linha; i++)
    {
        if (matriz[i][colFind] == valor)
        {
            vecResultado[i]=i;
        }
    }
    vecLinha=vecResultado;
    return count;
    }
    return -1;
    
    
}


void getMatLines(string** mBase, string**& mResult, int linhas,int colunas, int* vecLinha){
    linhas=linhas+1;
    string** mReturn = new string*[linhas];
    int vecLinhaInt;
    for (int i = 0; i < linhas; i++)
    {
        mReturn[i] = new string[colunas];
    }
    mReturn[0]=mBase[0];
    for (int i = 0; i < linhas; i++)
    {
    vecLinhaInt=vecLinha[i];
    mReturn[i+1]=mBase[vecLinha[i]];

    }
    mResult=mReturn;
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
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                                    ADICIONAR PRODUTO\n";
        cout << endl;
        cout <<  "                                     R. RETORNAR\n";
        cout << "======================================================================================\n";
        cout << endl;
        printMatrix(mProd, linhasProd, colunasProd);
        cout << endl;
        cout << "                          Data e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\n";
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
void getMatLineProd(string**& mBase, string**& mReturn, int linha){
    mReturn[0]=mBase[linha];

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
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                                    MODIFICAR PRODUTO\n";
        cout << endl;
        cout << "   N. ALTERAR NOME   " << "Q. ALTERAR QUANTIDADE   " << "C. ALTERAR CUSTO   " << "R. RETORNAR\n";
        cout << "======================================================================================\n";
        cout << endl;
        printMatrix(mLinhaProd, 2, 4);
        cout << endl;
        cout << "                          Data e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\n";
        cout << "Escolha uma opção: ";
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

float calcSubTotal(string** matCarr, int linhasCarr){
    float total=0;
    for (int i = 1; i < linhasCarr; i++)
    {
        total=total+stof(matCarr[i][5]);
    }
    return total;
}

void inserirProdutoVenda(string idProd, int qtdProd, string**& matCarr, int& linhasCarr, string** matStock, int linhaStock, int linhaProd){
    string texto;
    float valor, valorIva;
    linhasCarr = linhasCarr + 1;
    string** mLinha = new string*[1];
    mLinha[0] = new string[4];
    string** mReturn = new string*[linhasCarr]; 
    for (int i = 0; i < linhasCarr; i++)
    {
        mReturn[i] = new string[6];
    }
    for (int i = 0; i < linhasCarr-1; i++)
    {
        mReturn[i] = matCarr[i];
    }

    
    getMatLineProd(matStock, mLinha, linhaProd);
    mReturn[linhasCarr-1][0] = mLinha[0][0];
    mReturn[linhasCarr-1][1] = mLinha[0][1];
    mReturn[linhasCarr-1][2] = to_string(qtdProd);
    texto = mLinha[0][3];
    valor = stof(mLinha[0][3]) * 1.30;
    valorIva = valor * 1.23;
    mReturn[linhasCarr-1][3] = arredondar(valor);
    mReturn[linhasCarr-1][4] = arredondar(valorIva);
    mReturn[linhasCarr-1][5] = arredondar(valorIva * qtdProd);
    
    matCarr = mReturn;
    delete[] mLinha;


}

bool sorteio(int nSorte){
    string pontos = "";
    bool ganhou = false;
    int contador = 0;
    int qtdSorteios = 10;

    do {
        string sorteio = to_string(rand() % 1000 + 1);
        
        system("clear"); // Limpa o terminal no Windows
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                   NÚMERO DA SORTE CLIENTE: " << nSorte << "   SORTEANDO" << pontos << "\n";
        cout << endl;
        // cout << "F. Finalizar venda   " << "N. NIF Cliente   "<<"C. Cancelar venda   " << "R. Retornar\n";
        cout << "======================================================================================\n";
        cout << endl;
        // cout << sorteio << "\n";
        cout << "                                 ------------- \n";
        cout << "                                 | "<<sorteio[0] << " | "<<sorteio[1] << " | "<<sorteio[2] << " | \n";
        cout << "                                 ------------- \n";
        cout << endl;
        cout << "======================================================================================\n";
        if (stoi(sorteio) == nSorte)
        {
            ganhou = true;
            cout << "                     PARABÉNS!!! VOCÊ GANHOU!!!\n";
            sleep(3);
            break;
        } else if (contador == qtdSorteios-1)
        {
            cout << "                Infelizmente não foi desta vez! Boa sorte na próxima!\n";
            sleep(3);
            break;
        }

        if (pontos == "...")
        {
            pontos = "";
        }else{
            pontos += ".";
        }
        sleep(1);      
        contador++;
    } while (!ganhou && contador < qtdSorteios);
    return ganhou;
}

void showMenuFinalizarVenda(string**& matVenda, int &linhasMatVenda, string**& matCarrinho, int linhasCarrinho, string**& matStock, int linhaStock, int talao, float subTotal, string dataHora)
{
    int idVenda, nSorte, step = 0;
    char opcao = 'Z';
    string cliente, entrada="";
    bool ganhou = false, sair = false;
    float valorPago = 0.00, troco = 0.00;

    idVenda = findLastId(matVenda, linhasMatVenda) + 1;
    nSorte = rand() % 1000 + 1;

    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                          FINALIZAR VENDA - ID VENDA: " << idVenda << "\n";
        cout << endl;
        cout << "              C. CANCELAR VENDA   " << "V. VOLTAR ETAPA" << "R. RETORNAR A VENDA\n";
        cout << "======================================================================================\n";
        printMatrix(matCarrinho, linhasCarrinho, 6);
        cout << endl;
        cout << "======================================================================================\n";
        cout << "        Talão: " << talao << "  Data e Hora: " << dataHora << "  TOTAL A PAGAR: " << arredondar(subTotal) << "€ \n";
        if (cliente.length() > 0)
        {
            cout << "NIF Cliente: " << cliente << "                  Número da Sorte: " << nSorte << "\n";
        }
        cout << "Valor pago: " << valorPago << "€ \n";
        cout << "Troco: " << troco << "€ \n";
        cout << "======================================================================================\n";
        if (step == 0)
        {
            cout << "Insira o NIF do cliente ou N para não adicionar NIF: ";
        } else if (step == 1)
        {
            cout << "Deseja participar do sorteio? (S/N): ";
            cin >> entrada;
            if (textToUpper(entrada) == "S")
            {
                ganhou = sorteio(nSorte);
                if (ganhou)
                {
                    step = 3;
                    break;
                } else {
                    step = 2;
                    break;
                }
                sleep(3);
            } else {
                step = 2;
            }
            // sair = true;
        } else if (step == 2)
        {
            cout << "Insira o valor pago pelo cliente ou opção: ";
        }

        cin >> entrada;

        if (textToUpper(entrada) == "R" || textToUpper(entrada) == "V" || textToUpper(entrada) == "C" || textToUpper(entrada) == "N")
        {
            opcao = entrada[0];
        } else if (!validNum(entrada) && entrada.length() > 0){
            opcao = 'S';
        }

        switch (opcao)
        {
            case 'Z':
                if (step == 0 && entrada.length() == 9)
                {
                    cliente = entrada;
                    step = 1;
                } else if (step == 0 && entrada.length() != 9)
                {
                    cout << "NIF inválido! Insira um NIF válido.\n";
                    sleep(1);
                } else if (step == 1 && !ganhou)
                {
                    step = 2;
                } else if (step == 1 && ganhou)
                {
                    step = 3;

                } else if (step == 2)
                {
                    valorPago = stof(entrada);
                    troco = valorPago - subTotal;
                    step = 3;
                } else if (step == 3)
                {

                    //Adicionar a matriz de vendas
                    cout << "      Compra finalizada com sucesso! Obrigado pela preferência e volte sempre\n";
                    sleep(3);
                }
                
                break;
            case 'V':
                if (step > 0)
                {
                    step--;
                } else {
                    cout << "Não é possível voltar mais etapas.\n";
                    sleep(1);
                }
                
                break;
            case 'C':
                cout << "Cancelando venda...\n";
                sleep(1);
                sair = true;
                //colocar para voltar para menu principal de vendas
                break;
            case 'N':
                cout << "NIF não informado.\n";
                sleep(1);
                step = 2;
                break;
            case 'R':
                cout << "Retornando a venda...\n";
                sleep(1);
                sair = true;
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
                sleep(1);
        }
    } while (!sair);
}

void showMenuNovaVenda(string**& matVenda, int &linhasMatVenda, string**& matStock, int linhasMatStock)
{
    char opcao;
    string choice, qtdProd;
    int talao, linhaProd;
    int linhasCarr = 1;
    float subTotal = 0.00;
    string dataHora = getDateTime();
    talao = findLastId(matVenda, linhasMatVenda) + 1;
    string** mCarrinho = new string*[1]; // criar matriz para buscar produtos do id solicitado (na modificação de produto)
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
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                             NOVA VENDA - TALÃO: " << talao << "\n";
        cout << endl;
        // cout << dataHora <<"                VALOR TOTAL A PAGAR: " << arredondar(subTotal) << "€ \n";
        cout << "              F. FINALIZAR VENDA   " << "C. CANCELAR VENDA   " << "R. RETORNAR\n";
        cout << "======================================================================================\n";
        // cout << "P. Procurar produto\n";
        // cout << "F. Finalizar venda\n";
        // cout << "C. Cancelar venda\n";
        // cout << "R. Retornar\n";
        printMatrix(mCarrinho, linhasCarr, 6);
        cout << endl;
        cout << "Data e Hora: " << dataHora <<"                  VALOR TOTAL A PAGAR: " << arredondar(subTotal) << "€ \n";
        // cout << getDateTime() << "\n";
        cout << "======================================================================================\n";
        cout << "Insira o ID do produto ou opção: ";
        cin >> choice;
        choice=textToUpper(choice);
        if (choice.length() > 0)
        {
            if (validNum(choice))
            {
                opcao = 'Z';
            }else{
                opcao = choice[0];
            }
        }
        
        switch (opcao)
        {
        case 'P':
            break;
        case 'F':
            cout << "Finalizando venda...\n";
            showMenuFinalizarVenda(matVenda, linhasMatVenda, mCarrinho, linhasCarr, matStock, linhasMatStock, talao, subTotal, dataHora);
            break;
        case 'C':
            break;
        case 'Z':
            linhaProd = findItem(choice, matStock, linhasMatStock, 0);
            if (linhaProd < 0)
            {
                cout << "Produto não encontrado!!!\n";
                sleep(1);
                break;
            }
            cout << "Informe a quantidade do produto: ";
            cin >> qtdProd;
            while (!validNum(qtdProd) && (textToUpper(qtdProd) != "R" || textToUpper(qtdProd) != "C"))
            {
                cout << "Valor inserido não é um número.\n";
                cout << "Informe a quantidade do produto: ";
                cin >> qtdProd;
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

    mVendas[0][0] = "TALAO";      // Talão venda
    mVendas[0][1] = "DATA VENDA";  // Hora da venda
    mVendas[0][2] = "CLIENTE";      // nome cliente
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

    mCompras[0][0] = "TALAO";      // id venda
    mCompras[0][1] = "ID PRODUTO";  // Hora da venda
    mCompras[0][2] = "QUANTIDADE";      // nº cliente
    mCompras[0][3] = "PRECO"; // total venda

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

void showMenuVendas(string **mat, int linhas, int colunas, string **& matStock, int& linhasMatStock)
{
    char choice;
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                                    MENU DE VENDAS\n";
        cout << endl;
        cout << "        V.VENDER   " << "C. CONSULTAR PRODUTOS DE UMA VENDA  " << "R. RETORNAR\n";
        cout << "======================================================================================\n";
        cout << endl;
        printMatrix(mat, linhas, colunas);
        cout << endl;
        cout << "                          Data e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'V':
            cout << "Vender...\n";
            showMenuNovaVenda(mat,linhas, matStock, linhasMatStock);
            break;
        case 'C':
            cout << "Consultando Produtos...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (choice != 'R');
}
void showMenuSearchStock(string **mat, int linhas, int colunas)
{
    char choice;
    string valor;
    int qtdLinhas=0;
    int* vecLinha= new int[2];
    string** mLinhasProd = new string*[1]; // criar matriz para buscar produtos do id solicitado (na modificação de produto)
    for (int i = 0; i < 2; i++)
    {
        mLinhasProd[i] = new string[4];
    }
    do
    {
        system("clear"); // Limpa o terminal no Windows
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                                   CONSULTAR STOCK\n";
        cout << endl;
        cout << "             I. PROCURAR POR ID   " << "D. PROCURAR POR DESCRIÇÃO   " << "R. RETORNAR\n";
        cout << "======================================================================================\n";
        cout << endl;
        if  (qtdLinhas>0)
        {
            printMatrix(mLinhasProd, linhas, colunas);
        }
        cout << endl;
        cout << "                          Data e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'I':
            cout << "Digite o ID do produto desejado: ";
            cin.ignore();
            getline(cin,valor);
            qtdLinhas=findItems(valor, mat, linhas, 0, vecLinha); //------------------CORRIGIR TUDO ISSO----------------------
            getMatLines(mat,mLinhasProd,qtdLinhas,4,vecLinha);;
            break;
        case 'D':
            cout << "Digite a descrição do produto desejado: ";
            cin.ignore();
            getline(cin,valor);
            qtdLinhas=findItems(valor, mat, linhas, 1, vecLinha);
            getMatLines(mat,mLinhasProd,qtdLinhas,4,vecLinha);
            break;

        default:
            cout << "Opção inválida! Tente novamente.\n";
            sleep(1);
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
        cout << "======================================================================================\n";
        cout << endl;
        cout << "                                    MENU STOCK\n";
        cout << endl;
        cout << "   C. CONSULTAR STOCK   " << "A. ADICIONAR PRODUTO   " << "M. MODIFICAR PRODUTO   " << "R. RETORNAR\n";
        cout << "======================================================================================\n";
        cout << endl;
        printMatrix(mProd, linhasProd, colunasProd);
        cout << endl;
        cout << "                          Data e Hora: " << getDateTime() << "\n";
        cout << "======================================================================================\n";
        cout << "Escolha uma opção: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'C':
            cout << "Consultando Stock...\n";
            showMenuSearchStock(mProd, linhasProd, colunasProd);
            // break;
        case 'A':
            cout << "Adicionando Produto...\n";
            showMenuAddProd(mProd, linhasProd, colunasProd);
            break;
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
    cout << "======================================================================================\n";
    cout << endl;
    cout << "                                   MENU PRINCIPAL\n";
    cout << endl;
    cout << "                    S. STOCK   " << "V. VENDAS   " << "C. COMPRAS   " << "F. FECHAR\n";
    cout << "======================================================================================\n";
    cout << "                          Data e Hora: " << getDateTime() << "\n";
    cout << "======================================================================================\n";
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
            showMenuVendas(mVendas, linhasVendas, colunasVendas, mProd, linhasProd);
            break;
        case 'C':
            cout << "Abrindo Compras...\n";
            if (sorteio(124))
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

    return 0;
}