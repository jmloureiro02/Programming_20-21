#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

    /*Conceitos importante para a compreens�o dos coment�rios:

        *Foi dado o nome de "escudo" � regi�o em torno do barco onde n�o se pode colocar um outro barco devido � iminente viola��o da restri��o n�1
        *Foi dado o nome de elementos a cada quadricula de uma matriz, sendo 1 elemento de um barco, 1 quadricula desse mesmo barco

    */

int linhas,colunas;

//LABEL FUN�OES

void Modo_p1();
void Modo_p2();
void Modo_d1();
void Modo_d2();
void Modo_d3();

//LABEL FUN�OES AUXILIARES

int Restricao1P1();
int MatrizesVazias();
void peca();
void PecaNula();
int Numpecas();
void Passagem3D2D();
int Mult3();
void VerificacaoDadosInseridos();
void PrintfAlphabet();
void InitBoardMatrix();
void PrintBoard();
int EscolhaIDPeca();
int NumPecas();


//VARI�VEIS

int matrix3D[43][5][5] = {
 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{10,10,10, 0, 0},
  {10, 1, 0, 0, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0,10,10,10, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},


 {{ 0, 0,10,10,10},
  { 0, 0, 0, 1, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 1, 0, 0, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 1, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 1, 0, 0, 0},
  {10, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 1, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 1, 0},
  { 0, 0, 0, 0, 0}},


 {{10,10,10,10, 0},
  {10, 2, 2, 0, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0,10,10,10,10},
  { 0, 0, 2, 2, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 2, 2, 0, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 2, 2, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 2, 2, 0, 0},
  {10, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 2, 2, 0},
  { 0, 0, 0, 0, 0}},


 {{10,10,10, 0, 0},
  {10, 2, 0, 0, 0},
  {10, 2, 0, 0, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0,10,10,10, 0},
  { 0, 0, 2, 0, 0},
  { 0, 0, 2, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0,10,10,10},
  { 0, 0, 0, 2, 0},
  { 0, 0, 0, 2, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 2, 0, 0, 0},
  {10, 2, 0, 0, 0},
  {10, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 2, 0, 0},
  { 0, 0, 2, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 2, 0},
  { 0, 0, 0, 2, 0},
  { 0, 0, 0, 0, 0}},


 {{10,10,10,10,10},
  {10, 3, 3, 3, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 3, 3, 3, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 3, 3, 3, 0},
  {10, 0, 0, 0, 0}},

 {{10,10,10, 0, 0},
  {10, 3, 0, 0, 0},
  {10, 3, 0, 0, 0},
  {10, 3, 0, 0, 0},
  {10, 0, 0, 0, 0}},

 {{ 0,10,10,10, 0},
  { 0, 0, 3, 0, 0},
  { 0, 0, 3, 0, 0},
  { 0, 0, 3, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0,10,10,10},
  { 0, 0, 0, 3, 0},
  { 0, 0, 0, 3, 0},
  { 0, 0, 0, 3, 0},
  { 0, 0, 0, 0, 0}},


 {{10,10,10,10, 0},
  {10, 4, 4, 0, 0},
  {10, 4, 4, 0, 0},
  {10, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0,10,10,10,10},
  { 0, 0, 4, 4, 0},
  { 0, 0, 4, 4, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  {10, 0, 0, 0, 0},
  {10, 4, 4, 0, 0},
  {10, 4, 4, 0, 0},
  {10, 0, 0, 0, 0}},

 {{ 0, 0, 0, 0, 0},
  { 0, 0, 0, 0, 0},
  { 0, 0, 4, 4, 0},
  { 0, 0, 4, 4, 0},
  { 0, 0, 0, 0, 0}},

 {{10,10,10,10,10},
  {10, 5, 5, 5, 0},
  {10, 0, 5, 0, 0},
  { 0, 0, 5, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{10,10,10, 0, 0},
  {10, 5, 0, 0, 0},
  {10, 5, 5, 5, 0},
  {10, 5, 0, 0, 0},
  {10, 0, 0, 0, 0}},

 {{ 0,10,10,10, 0},
  { 0, 0, 5, 0, 0},
  {10, 0, 5, 0, 0},
  {10, 5, 5, 5, 0},
  {10, 0, 0, 0, 0}},

 {{ 0, 0,10,10,10},
  {10, 0, 0, 5, 0},
  {10, 5, 5, 5, 0},
  {10, 0, 0, 5, 0},
  { 0, 0, 0, 0, 0}},


 {{ 0,10,10,10, 0},
  {10, 0, 6, 0, 0},
  {10, 6, 0, 6, 0},
  {10, 6, 6, 6, 0},
  {10, 0, 0, 0, 0}},

 {{ 0,10,10,10,10},
  {10, 0, 6, 6, 0},
  {10, 6, 0, 6, 0},
  {10, 0, 6, 6, 0},
  { 0, 0, 0, 0, 0}},

 {{10,10,10,10,10},
  {10, 6, 6, 6, 0},
  {10, 6, 0, 6, 0},
  {10, 0, 6, 0, 0},
  { 0, 0, 0, 0, 0}},

 {{10,10,10,10, 0},
  {10, 6, 6, 0, 0},
  {10, 6, 0, 6, 0},
  {10, 6, 6, 0, 0},
  {10, 0, 0, 0, 0}},


 {{10,10,10,10,10},
  {10, 7, 0, 7, 0},
  {10, 7, 7, 7, 0},
  {10, 7, 0, 7, 0},
  {10, 0, 0, 0, 0}},

 {{10,10,10,10,10},
  {10, 7, 7, 7, 0},
  {10, 0, 7, 0, 0},
  {10, 7, 7, 7, 0},
  {10, 0, 0, 0, 0}},


 {{10,10,10,10,10},
  {10, 8, 8, 8, 0},
  {10, 8, 0, 8, 0},
  {10, 8, 8, 8, 0},
  {10, 0, 0, 0, 0}},
 };
int matrixD1AUX[15][24];
int boardmatrix[15][24];
int boardmatrixAux[17][26];
int matrix5x5[5][5];
int matrix3x3[3][3];
int matrixAux[15][24];
int id_global;
int qtd_tiros;
int n_pecas,n_pecas1,n_pecas2,n_pecas3,n_pecas4,n_pecas5,n_pecas6,n_pecas7,n_pecas8;
int max_pecas;


    void Modo_d2(int linhas,int colunas){// Fun��o respons�vel pela execu��o do modo de disparo 2
        int l,a,b,i,j,bb=0;
        char res;

        int seconds; // vari�vel que guarda os segundos
        time_t tempo_inicial;// inicializa��o da vari�vel de tempo do jogo
        tempo_inicial = time(NULL);// inicializa��o da vari�vel para guardar o tempo

        a=0;
        while(a<linhas){// ciclo while que percorre as linhas do tabuleiro
            b=0;
            while(b<colunas){// ciclo while que percorre as colunas do tabuleiro
                l=0;
                for(i=a;i<a+3;i++){// percorre as linhas do tabuleiro come�ando em 0 e saltando as linhas de 3 em 3
                    for(j=b;j<b+3;j++){// percorre as colunas do tabuleiro come�ando em 0 e saltando as colunas de 3 em 3

                        if(boardmatrix[i][j]>=1 && boardmatrix[i][j]<=8){// se o elemento em causa for correspondente a uma pe�a,
                        l++;// incrementa a vari�vel l, respons�vel por assinalar a quantidade de elementos de barcos que faltam atingir
                        }
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:

      /*As nested ifs seguintes servem para dar print para stdout das coordenadas do disparo segundo a ordem predefinida para o modo de disparo 2*/

                    if(boardmatrix[a+1][b+1]!=20 && (boardmatrix[a+1][b+1]>=1 && boardmatrix[a+1][b+1]<=8)){
                         printf("%c%d\n",(b+1+65),linhas-(a+1));
                         scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a+1][b+1]!=20 && (boardmatrix[a+1][b+1]==0)){
                         printf("%c%d\n",(b+1+65),linhas-(a+1));
                         scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a][b+1]!=20 && (boardmatrix[a][b+1]>=1 && boardmatrix[a][b+1]<=8)){
                        printf("%c%d\n",(b+65+1),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a][b+1]!=20 && (boardmatrix[a][b+1]==0)){
                        printf("%c%d\n",(b+65+1),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a+2][b+1]!=20 && (boardmatrix[a+2][b+1]>=1 && boardmatrix[a+2][b+1]<=8)){
                        printf("%c%d\n",(b+1+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a+2][b+1]!=20 && (boardmatrix[a+2][b+1]==0)){
                        printf("%c%d\n",(b+1+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a+1][b]!=20 && (boardmatrix[a+1][b]>=1 && boardmatrix[a+1][b]<=8)){
                        printf("%c%d\n",(b+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a+1][b]!=20 && (boardmatrix[a+1][b]==0)){
                        printf("%c%d\n",(b+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a+1][b+2]!=20 && (boardmatrix[a+1][b+2]>=1 && boardmatrix[a+1][b+2]<=8)){
                        printf("%c%d\n",(b+2+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a+1][b+2]!=20 && (boardmatrix[a+1][b+2]==0)){
                        printf("%c%d\n",(b+2+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a][b]!=20 && (boardmatrix[a][b]>=1 && boardmatrix[a][b]<=8)){
                        printf("%c%d\n",(b+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a][b]!=20 && (boardmatrix[a][b]==0)){
                        printf("%c%d\n",(b+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a+2][b+2]!=20 && (boardmatrix[a+2][b+2]>=1 && boardmatrix[a+2][b+2]<=8)){
                        printf("%c%d\n",(b+2+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a+2][b+2]!=20 && (boardmatrix[a+2][b+2]==0)){
                        printf("%c%d\n",(b+2+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a][b+2]!=20 && (boardmatrix[a][b+2]>=1 && boardmatrix[a][b+2]<=8)){
                        printf("%c%d\n",(b+65+2),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a][b+2]!=20  &&  (boardmatrix[a][b+2]==0)){
                        printf("%c%d\n",(b+65+2),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                }
                if(l>0){// se ainda houver elementos a atingir:
                    if(boardmatrix[a+2][b]!=20 && (boardmatrix[a+2][b]>=1 && boardmatrix[a+2][b]<=8)){
                        printf("%c%d\n",(b+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    }
                    if(boardmatrix[a+2][b]!=20 && (boardmatrix[a+2][b]==0)){
                          printf("%c%d\n",(b+65),linhas-(a+2));
                          scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                        }
                }
            b=b+3;// incrementa a coordenada b
            }
        a=a+3;// incrementa a coordenada a
        }
    seconds=time(NULL);// atribui��o do tempo contabilizado � vari�vel seconds
        seconds=seconds-tempo_inicial;// subtra��o do tempo inicial (1 de janeiro de 1970) ao tempo medido
        printf("\nFim de Jogo: %d jogadas em %d segundos\n",bb,seconds);// mensagem de fim de jogo
    }

    void Modo_d1j1(int linhas, int colunas){// Fun��o respons�vel pela execu��o do modo de disparo 1 com modo de posicionamento 1
    int i,j,l=0,b=0,irandom,colu;
    char jrandom;

       for(i=0;i<linhas;i++){// percorre as linhas do tabuleiro
            for(j=0;j<colunas;j++){// percorre as colunas do tabuleiro
                matrixD1AUX[i][j]=boardmatrix[i][j];//passa o tabuleiro atual para a matriz auxiliar "matrixD1Aux"
                if(boardmatrix[i][j]>=1 && boardmatrix[i][j]<=8){// caso haja um elemento de um barco nas coordenadas em causa,
                l++;// incrementa a vari�vel l, respons�vel por assinalar a quantidade de elementos de barcos que faltam atingir
                }
            }
        }

        int seconds;// vari�vel que guarda os segundos
        time_t tempo_inicial;// inicializa��o da vari�vel de tempo do jogo
        tempo_inicial = time(NULL);// inicializa��o da vari�vel para guardar o tempo

        do{// ciclo do while respons�vel por realizar ciclicamente o pedido de coordenadas a disparar enquanto houver elementos de barcos por afundar
            scanf("%c %d",&jrandom,&irandom);// input das coordenadas do utilizador
            colu=jrandom-65;// convers�o de c�digo ASCII para coordenadas matriciais

            if(colu>=0 && irandom>0){// if auxiliar para garantir que n�o ocorriam erros de scan
                irandom=linhas-irandom;// convers�o de n�mero de linha para coordenadas matriciais
                if(boardmatrix[irandom][colu]==20 || boardmatrix[irandom][colu]==0 || boardmatrix[irandom][colu]==21){//caso esse elemento j� tenha sido afundado, esteja vazio ou j� tenha sido realizado um disparo nas coordenadas escolhidas,
                    b++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    printf("-\n");// indica que n�o foi atingido nenhum barco
                    boardmatrix[irandom][colu]=20;// atribui a essas coordenadas o valor 20, respons�vel por indicar que j� foi realizado um disparo falhado nessas coordenadas
                }
                if( (boardmatrix[irandom][colu]>=1 && boardmatrix[irandom][colu]<=8)){// caso haja um barco nessas coordenadas,
                    l--;// decrementa a vari�vel respons�vel pelo n�mero de elementos de barcos que falta afundar
                    b++;// incrementa a vari�vel respons�vel pela contagem n� de jogadas
                    printf("%d\n",boardmatrix[irandom][colu]);// indica que foi atingido um barco e qual foi
                    boardmatrix[irandom][colu]=21;// atribui a essas coordenadas o valor 21, respons�vel por indicar que o elemento j� foi afundado
                }
            }
        }while(l>0);
        for(i=0;i<linhas;i++){// percorre as linhas do tabuleiro
            for(j=0;j<colunas;j++){// percorre as colunas do tabuleiro
                boardmatrix[i][j]=matrixD1AUX[i][j];// passa o que est� na matiz auxiliar para a matriz do tabuleiro de jogo
            }
        }

        seconds=time(NULL);// atribui��o do tempo contabilizado � vari�vel seconds
        seconds=seconds-tempo_inicial;// subtra��o do tempo inicial (1 de janeiro de 1970) ao tempo medido
        printf("\nFim de Jogo: %d jogadas em %d segundos\n",b,seconds);// mensagem de fim de jogo
    }

    void Modo_d1j2( int linhas, int colunas){// Fun��o respons�vel pela execu��o do modo de disparo 1 com modo de posicionamento 2
        int irandom,jrandom,l=0,i,j,b;
        char resp;
        time_t t;
        srand((unsigned) time(&t));// inicializa��o da fun��o rand

        int seconds;// vari�vel que guarda os segundos
        time_t tempo_inicial;// inicializa��o da vari�vel de tempo do jogo
        tempo_inicial = time(NULL);// inicializa��o da vari�vel para guardar o tempo

       for(i=0;i<linhas;i++){// percorre as linhas do tabuleiro
            for(j=0;j<colunas;j++){// percorre as colunas do tabuleiro
                    matrixD1AUX[i][j]=boardmatrix[i][j];// passa os valores da matriz principal para a matriz auxiliar "matrixD1AUX"
                if(boardmatrix[i][j]>=1 && boardmatrix[i][j]<=8){// caso haja um barco nas coordenadas em an�lise,
                l++;// incrementa a vari�vel respons�vel pelo n� de elementos a afundar
                }
            }
        }
        b=0;// inicializa��o da vari�vel respons�vel pelo n� de jogadas
        do{// ciclo do while que repete o processo de disparo at� que n�o haja mais elementos para afundar
            irandom=rand()%linhas;// gera��o aleat�ria da ordenada do tabuleiro
            jrandom=rand()%colunas;// gera��o aleat�ria da abcissa do tabuleiro

                if(boardmatrix[irandom][jrandom]>=1 && boardmatrix[irandom][jrandom]<=8){// se o elemento em an�lise for uma pe�a,
                    boardmatrix[irandom][jrandom]=21;// atribui o n� que representa que o elemento do barco foi afundado
                    printf("%c%d\n",(jrandom+65),linhas-irandom);// impress�o em stdout das coordenadas geradas
                    scanf("%c",&resp);// input da resposta do utilizador
                    l--;// decrementa a vari�vel respons�vel pelo n� de elementos que falta afundar
                    b++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                }

                if(boardmatrix[irandom][jrandom]==0){// se o elemento em an�lise for �gua (aus�ncia de pe�a),
                    boardmatrix[irandom][jrandom]=20;// atribui o n� que representa que foi feito um disparo sem sucesso nesse elemento (�gua)
                    printf("%c%d\n",(jrandom+65),linhas-irandom);// impress�o em stdout das coordenadas geradas
                    scanf("%c",&resp);// input da resposta do utilizador
                    b++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                }
        }while(l>0);// ciclo do while que repete o processo de disparo at� que n�o haja mais elementos para afundar
        for(i=0;i<linhas;i++){// percorre as linhas do tabuleiro
            for(j=0;j<colunas;j++){// percorre as colunas do tabuleiro
                boardmatrix[i][j]=matrixD1AUX[i][j];// copia o que est� na matriz auxiliar "matrixD1AUX" para a matriz do tabuleiro
            }
        }

        seconds=time(NULL);// atribui��o do tempo contabilizado � vari�vel seconds
        seconds=seconds-tempo_inicial;// subtra��o do tempo inicial (1 de janeiro de 1970) ao tempo medido
        printf("\nFim de Jogo: %d jogadas em %d segundos\n",b,seconds);// mensagem de fim de jogo
    }

    void Modo_d3(int linhas, int colunas){// Fun��o respons�vel pela execu��o do modo de disparo 3
        int l,a,b,i,j,bb=0;
        char res;

        int seconds;// vari�vel que guarda os segundos
        time_t tempo_inicial;// inicializa��o da vari�vel de tempo do jogo
        tempo_inicial = time(NULL);// inicializa��o da vari�vel para guardar o tempo

        a=0;    // inicializa��o vari�vel respons�vel pela ordenada
        while(a<linhas){    // ciclo while que percorre as linhas do tabuleiro, de 3 em 3
            b=0;    // inicializa��o vari�vel respons�vel pela abcissa
            while(b<colunas){   // ciclo while que percorre as colunas do tabuleiro, de 3 em 3
                l=0;    // inicializa�ao da vari�vel respons�vel pela quantidade de elementos a afundar
                for(i=a;i<a+3;i++){// percorre 3 linhas
                    for(j=b;j<b+3;j++){// percorre 3 colunas

                        if(boardmatrix[i][j]>=1 && boardmatrix[i][j]<=8){// caso haja um elemento de uma pe�a nas coordenadas em an�lise,
                            l++;// incrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        }
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a+1][b+1]!=20  && ( boardmatrix[a+1][b+1]>=1 && boardmatrix[a+1][b+1]<=8)){
                        printf("%c%d\n",(b+1+65),linhas-(a+1));
                        scanf("%c",&res);
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a+1][b+1]!=20 && matrixAux[a+1][b+1]!=10 && boardmatrix[a+1][b+1]==0){
                        printf("%c%d\n",(b+1+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a][b+1]!=20  && ( boardmatrix[a][b+1]>=1 &&  boardmatrix[a][b+1]<=8)){
                        printf("%c%d\n",(b+1+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a][b+1]!=20  && matrixAux[a][b+1]!=10 &&  (boardmatrix[a][b+1]==0)){
                        printf("%c%d\n",(b+1+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a+2][b+1]!=20  && ( boardmatrix[a+2][b+1]>=1 &&  boardmatrix[a+2][b+1]<=8)){
                        printf("%c%d\n",(b+1+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a+2][b+1]!=20  && matrixAux[a+2][b+1]!=10 && (boardmatrix[a+2][b+1]==0)){
                        printf("%c%d\n",(b+1+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a+1][b]!=20  && ( boardmatrix[a+1][b]>=1 &&  boardmatrix[a+1][b]<=8)){
                        printf("%c%d\n",(b+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a+1][b]!=20  && matrixAux[a+1][b]!=10 &&  (boardmatrix[a+1][b]==0)){
                        printf("%c%d\n",(b+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a+1][b+2]!=20  && ( boardmatrix[a+1][b+2]>=1 &&  boardmatrix[a+1][b+2]<=8)){
                        printf("%c%d\n",(b+2+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a+1][b+2]!=20  && matrixAux[a+1][b+2]!=10 && (boardmatrix[a+1][b+2]==0)){
                        printf("%c%d\n",(b+2+65),linhas-(a+1));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a][b]!=20  && ( boardmatrix[a][b]>=1 &&  boardmatrix[a][b]<=8)){;
                        printf("%c%d\n",(b+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a][b]!=20  && matrixAux[a][b]!=10 &&  (boardmatrix[a][b]==0)){
                        printf("%c%d\n",(b+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a+2][b+2]!=20  && ( boardmatrix[a+2][b+2]>=1 &&  boardmatrix[a+2][b+2]<=8)){
                        printf("%c%d\n",(b+2+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a+2][b+2]!=20  && matrixAux[a+2][b+2]!=10 && (boardmatrix[a+2][b+2]==0)){
                        printf("%c%d\n",(b+2+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a][b+2]!=20  && ( boardmatrix[a][b+2]>=1 &&  boardmatrix[a][b+2]<=8)){
                        printf("%c%d\n",(b+2+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a][b+2]!=20  && matrixAux[a][b+2]!=10 && (boardmatrix[a][b+2]==0)){
                        printf("%c%d\n",(b+2+65),linhas-(a));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                if(l>0){// caso ainda haja elementos a afundar:
                    if( boardmatrix[a+2][b]!=20  && ( boardmatrix[a+2][b]>=1 &&  boardmatrix[a+2][b]<=8)){
                        printf("%c%d\n",(b+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        l--;// decrementa a vari�vel respons�vel pela quantidade de elementos a afundar
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                    if( boardmatrix[a+2][b]!=20  && matrixAux[a+2][b]!=10 &&  (boardmatrix[a+2][b]==0)){
                        printf("%c%d\n",(b+65),linhas-(a+2));
                        scanf("%c",&res);// input da resposta do utilizador
                        bb++;// incrementa a vari�vel respons�vel pelo n� de jogadas
                    }
                }
                for(i=a;i<a+3;i++){// percorre 3 linhas
                    for(j=b;j<b+3;j++){// percorre 3 colunas
                        // caso haja um elemento de um barco nas coordenadas em quest�o,
                        if(boardmatrix[i][j]==1 || boardmatrix[i][j]==2 || boardmatrix[i][j]==3|| boardmatrix[i][j]==4|| boardmatrix[i][j]==5|| boardmatrix[i][j]==6|| boardmatrix[i][j]==7|| boardmatrix[i][j]==8){
                            // atribui o valor 10 (escudo) nos elementos em redor � coordenada em quest�o
                            matrixAux[i][j+1]=10;
                            matrixAux[i+1][j+1]=10;
                            matrixAux[i+1][j]=10;
                            matrixAux[i+1][j-1]=10;
                            matrixAux[i][j-1]=10;
                            matrixAux[i-1][j-1]=10;
                            matrixAux[i-1][j]=10;
                            matrixAux[i-1][j+1]=10;
                        }
                    }
                }
            b=b+3;// incrementa 3 � vari�vel respons�vel pela abcissa
            }
        a=a+3;// incrementa 3 � vari�vel respons�vel pela ordenada
        }
    seconds=time(NULL);// atribui��o do tempo contabilizado � vari�vel seconds
    seconds=seconds-tempo_inicial;// subtra��o do tempo inicial (1 de janeiro de 1970) ao tempo medido
    printf("\nFim de Jogo: %d jogadas em %d segundos\n",bb,seconds);// mensagem de fim de jogo
}

    void Modo_p1(int linhas,int colunas){// Fun��o pelo modo de posicionamento 1
        int a,b,k=0,h=0,m,n,i,j;
        n_pecas1=0, n_pecas2=0, n_pecas3=0, n_pecas4=0, n_pecas5=0, n_pecas6=0, n_pecas7=0, n_pecas8=0;// inicializa��o das vari�veis respons�veis pelo n� de pe�as de cada tipo colocadas

        time_t t;// inicializa��o da vari�vel t para uso no random
        srand((unsigned)time(&t));// inicializa��o da fun��o rand

        a=0;// inicializa��o vari�vel respons�vel pela ordenada
        while(a<linhas){// ciclo while que percorre as linhas do tabuleiro, de 3 em 3
            b=0;// inicializa��o vari�vel respons�vel pela abcissa
            while(b<colunas){// ciclo while que percorre as colunas do tabuleiro, de 3 em 3

                 do{// ciclo do while que gera a pe�a at� haver break (excedeu as 3 tentativas) ou conseguir colocar uma pe�a de acordo com a restri��o
                    id_global = rand()%42+1;// escolha aleat�ria do global id
                    for(m=0;m<3;m++){// percorre 3 linhas
                        for(n=0;n<3;n++){// percorre 3 colunas
                            matrix3x3[m][n] = matrix3D[id_global][m+1][n+1];// atribui � matriz "matrix3x3" (que guarda a pe�a sem escudo) a pe�a com o global id escolhido
                        }
                    }
                    for(i=0;i<5;i++){// percorre 5 linhas
                        for(j=0;j<5;j++){// percorre 5 colunas
                            matrix5x5[i][j] = matrix3D[id_global][i][j];// atribui � matriz "matrix5x5" (que guarda a pe�a e escudo) a pe�a com o global id escolhido
                        }
                    }
                    if(Restricao1P1(a,b)==1){// caso n�o haja viola��o da restri��o 1,
                        peca(a,b);// chama a fun��o que coloca a pe�a escolhida na boardmatrix e na matriz auxiliar ao tabuleiro
                        if(id_global>= 1 && id_global<= 9){n_pecas1++;}// caso o global id perten�a a uma pe�a 1, incrementa "n_pecas1"
                        if(id_global>=10 && id_global<=21){n_pecas2++;}// caso o global id perten�a a uma pe�a 2, incrementa "n_pecas2"
                        if(id_global>=22 && id_global<=27){n_pecas3++;}// caso o global id perten�a a uma pe�a 3, incrementa "n_pecas3"
                        if(id_global>=28 && id_global<=31){n_pecas4++;}// caso o global id perten�a a uma pe�a 4, incrementa "n_pecas4"
                        if(id_global>=32 && id_global<=35){n_pecas5++;}// caso o global id perten�a a uma pe�a 5, incrementa "n_pecas5"
                        if(id_global>=36 && id_global<=39){n_pecas6++;}// caso o global id perten�a a uma pe�a 6, incrementa "n_pecas6"
                        if(id_global>=40 && id_global<=41){n_pecas7++;}// caso o global id perten�a a uma pe�a 7, incrementa "n_pecas7"
                        if(id_global==42 ){n_pecas8++;}// caso o global id perten�a a uma pe�a 8, incrementa "n_pecas8"
                        h++;// incrementa a vari�vel respons�vel por guardar se foi poss�vel colocar a pe�a
                    }else{// caso haja viola��o da restri��o 1,
                        k++;// incrementa a vari�vel respons�vel por contar a quantidade de vezes que houve tentativa de colocar uma nova pe�a
                    }
                    if(k>=3){// caso tenham havido 3 tentativas mal sucedidas de colocar uma pe�a diferente,
                        break;// break do ciclo
                    }
                }while(h==0);// caso n�o tenha sido colocada pe�a, volta a repetir o ciclo
                if(k==3){//se houve 3 tentativas mal sucedidas de colocar uma pe�a nova,
                    id_global=5;// escolhe-se o id global 5
                    boardmatrix[a][b]=matrix3D[id_global][1][1];    //
                    boardmatrix[a][b+1]=matrix3D[id_global][1][2];  //
                    boardmatrix[a][b+2]=matrix3D[id_global][1][3];  //
                    boardmatrix[a+1][b]=matrix3D[id_global][2][1];  //
                    boardmatrix[a+1][b+1]=matrix3D[id_global][2][2];//
                    boardmatrix[a+1][b+2]=matrix3D[id_global][2][3];//
                    boardmatrix[a+2][b]=matrix3D[id_global][3][1];  //
                    boardmatrix[a+2][b+1]=matrix3D[id_global][3][2];//
                    boardmatrix[a+2][b+2]=matrix3D[id_global][3][3];// coloca-se a pe�a com o global id 5 na matriz do tabuleiro "boardmatrix"
                    n_pecas1++;// incrementa a contagem de pe�as do tipo 1
                }
            b=b+3;// incrementa 3 � vari�vel respons�vel pela abcissa
            }
        a=a+3;;// incrementa 3 � vari�vel respons�vel pela ordenada
        }
    }

    void Modo_p2(int linhas,int colunas){// Fun��o pelo modo de posicionamento 2
        time_t t;
        srand((unsigned) time(&t));// inicializa a fun��o random
        int a,b;
        int h,r=0,m,n,i,j;
        int id_peca,rngPeca;
        int pecas_ajuda[]={0,0,0,0,0,0,0,0,0};
        int k=0;

        int pecas_selecionadas[]={1,n_pecas1,n_pecas2,n_pecas3,n_pecas4,n_pecas5,n_pecas6,n_pecas7,n_pecas8};// atribui��o do n� de pe�as para o array que guarda esses valores

        h=0;// Inicializa��o da vari�vel respons�vel pelo n� de tentativas de cria��o de tabuleiros
        while(h<1000){// Enquanto o n� de tentativas de cria��o de tabuleiros for menor que 1000,
            h++;// incrementa a vari�vel respons�vel pelo n� de tentativas de cria��o de tabuleiros
            InitBoardMatrix(linhas,colunas);// chama a fun��o respons�vel pela inicializa��o da matriz do tabuleiro
            pecas_ajuda[0]= pecas_selecionadas[0];//
            pecas_ajuda[1]= pecas_selecionadas[1];//
            pecas_ajuda[2]= pecas_selecionadas[2];//
            pecas_ajuda[3]= pecas_selecionadas[3];//
            pecas_ajuda[4]= pecas_selecionadas[4];// passa o array das pe�as selecionada para um array "pecas_ajuda" que serve de aux�lio
            pecas_ajuda[5]= pecas_selecionadas[5];//
            pecas_ajuda[6]= pecas_selecionadas[6];//
            pecas_ajuda[7]= pecas_selecionadas[7];//
            pecas_ajuda[8]= pecas_selecionadas[8];//
            rngPeca=0;//Inicializa��o da vari�vel respons�vel por guarda o n� da pe�a gerada aleatoriamente
            a=0;// inicializa��o vari�vel respons�vel pela ordenada
            while(a<linhas){// ciclo while que percorre as linhas do tabuleiro, de 3 em 3
                b=0;// inicializa��o vari�vel respons�vel pela abcissa
                while(b<colunas){// ciclo while que percorre as colunas do tabuleiro, de 3 em 3
                    r=0;// inicializa��o da vari�vel respons�vel por contar o n� de vezes que foi tentada uma pe�a diferente
                    while(r<8){// enquanto as tentativas de colocar uma nova pe�a forem menores que 8,
                        rngPeca = rand()%9;// gera aleatoriamente uma nova pe�a a escolher
                        if(pecas_ajuda[rngPeca]>0){// se houver pe�as do identificador de pe�a em quest�o,
                            if(rngPeca>=0){// se a pe�a escolhida for positiva,
                                k=0;// inicializa a vari�vel respons�vel pela contagem de variantes que se tentou escolher
                                while(k<=12){// enquanto o n� de vezes que se tentou uma nova variantes for menor ou igual a 12,
                                    id_peca=EscolhaIDPeca(rngPeca,k);// coloca-se na vari�vel "id_peca" o global id escolhido na fun��o "EscolhaIDPeca"
                                    for( m=0;m<3;m++){// percorre 3 linhas
                                        for( n=0;n<3;n++){// percorre 3 colunas
                                            matrix3x3[m][n] = matrix3D[id_peca][m+1][n+1]; // coloca-se na matriz auxiliar "matrix3x3" apenas a pe�a escolhida (sem o seu escudo)
                                        }
                                    }
                                    for( i=0;i<5;i++){// percorre 5 linhas
                                        for(j=0;j<5;j++){// percorre 5 colunas
                                            matrix5x5[i][j] = matrix3D[id_peca][i][j];// coloca-se na matriz auxiliar "matrix5x5" a pe�a escolhida + o seu escudo
                                        }
                                    }
                                    if(rngPeca==0){// se a pe�a escolhida foi a nula,
                                        PecaNula(a,b);// chama a fun��o que coloca nas coordenadas em quest�o a pe�a nula
                                        break;//break do ciclo while
                                    }
                                    if(rngPeca>0&&Restricao1P1(a,b)==1&&pecas_ajuda[rngPeca]>0){// se a pe�a escolhida n�o for 0, o n� da pe�a em quest�o for maior que zero e a restri��o 1 n�o for violada,
                                        break;//break do ciclo while
                                    }else{
                                        k++;// incrementa a vari�vel respons�vel pela contagem de variantes que se tentou escolher
                                    }
                                }
                            }
                            if(rngPeca==0){// se a pe�a escolhida for 0,
                                break;// break do ciclo while
                            }
                            if(rngPeca>0&&Restricao1P1(a,b)==1){// se a pe�a escolhida n�o for 0 e a restri��o 1 n�o for violada,
                                pecas_ajuda[rngPeca]--;// decrementa o n� de pe�as do tipo de pe�a escolhido
                                peca(a,b);// chama a fun��o que coloca a pe�a escolhida na boardmatrix e na matriz auxiliar ao tabuleiro
                                break;// break do ciclo while
                            }
                            r++;// incrementa a vari�vel respons�vel por contar o n� de vezes que foi tentada uma pe�a diferente
                        }else{
                         r++;// incrementa a vari�vel respons�vel por contar o n� de vezes que foi tentada uma pe�a diferente
                        }
                    }
                    b=b+3;// incrementa 3 � vari�vel respons�vel pela abcissa
                    // se o n� de tentativas de colocar uma nova pe�a for 8 ou o array no n� de pe�as for igual a zero:
                    if(r==8||(pecas_ajuda[1]==0&&pecas_ajuda[2]==0&&pecas_ajuda[3]==0&&pecas_ajuda[4]==0&&pecas_ajuda[5]==0&&pecas_ajuda[6]==0&&pecas_ajuda[7]==0&&pecas_ajuda[8]==0)){
                        break;// break do ciclo while
                    }
                }
                a=a+3;// incrementa 3 � vari�vel respons�vel pela ordenada
                // se o n� de tentativas de colocar uma nova pe�a for 8 ou o array no n� de pe�as for igual a zero:
                if(r==8||(pecas_ajuda[1]==0&&pecas_ajuda[2]==0&&pecas_ajuda[3]==0&&pecas_ajuda[4]==0&&pecas_ajuda[5]==0&&pecas_ajuda[6]==0&&pecas_ajuda[7]==0&&pecas_ajuda[8]==0)){
                break;// break do ciclo while
                }
            }
            // se o array no n� de pe�as for igual a zero:
            if(pecas_ajuda[1]==0&&pecas_ajuda[2]==0&&pecas_ajuda[3]==0&&pecas_ajuda[4]==0&&pecas_ajuda[5]==0&&pecas_ajuda[6]==0&&pecas_ajuda[7]==0&&pecas_ajuda[8]==0){
            break;// break do ciclo while
            }
            if(h==1000){printf(" *N�o consegue gerar o tabuleiro");// se se tiver atingido o n� m�ximo de tentativas de gerar o tabuleiro,
                exit(-1);// sai do programa com retorno -1
                break;// break do ciclo while
            }
        }
    }

//DECLARA��O FUN��ES AUXILIARES AO PROJETO
    int  MatrizesVazias(int linhas,int colunas){// Fun��o respons�vel por calcular o n�mero de matrizes vazias
        int n_matrizes;
        n_matrizes=linhas*colunas/9;// calcula o n�mero de matrizes vazias atrav�s do nr de linahs e colunas
        return (n_matrizes);// retorna o n�mero de matrizes vazias
    }

    void peca(int i, int j){// Fun��o respons�vel por colocar a pe�a escolhida na boardmatrix e na matriz auxiliar ao tabuleiro
        int a,b;
        for( a=0;a<3;a++){// percorre 3 linhas
            for( b=0;b<3;b++){// percorre 3 colunas
                boardmatrix[i+a][j+b]=matrix3x3[a][b];// coloca a pe�a 3x3 na boarmatrix
                boardmatrixAux[i+a+1][j+b+1]=matrix3x3[a][b];// coloca a pe�a 3x3 na boardmatrixAux com um offset de x+1 e y+1
            }
        }
    }

    void PecaNula(int i, int j){// Fun��o respons�vel por colocar na boardmatrix a pe�a nula
        int a,b;
        for( a=0;a<3;a++){// percorre 3 linhas
            for( b=0;b<3;b++){// percorre 3 colunas
                boardmatrix[i+a][j+b]=matrix3D[0][a+1][b+1];//coloca a  pe�a 3x3 nula
            }
        }
    }

    int  NumPecas(int x){// Fun��o respons�vel por verificar as restri��es de escolha do tipo de pe�as

        n_pecas=n_pecas1+n_pecas2+n_pecas3+n_pecas4+n_pecas5+n_pecas6+n_pecas7+n_pecas8;//n_pecas guarda o valor total de pe�as

        max_pecas=(x/2);// o m�ximo de pe�as � metade

            if((n_pecas<=max_pecas) && (n_pecas1>=n_pecas2 && n_pecas2>=n_pecas3 && n_pecas3>=n_pecas4 && n_pecas4>=n_pecas5 && n_pecas5>=n_pecas6 && n_pecas6>=n_pecas7 && n_pecas7>=n_pecas8)&& n_pecas>0){
                return 1;
            }else{          // Se o total de pe�as n�o exceder o m�ximo de pe�as e respeitar as restri��es 3 e 4, retorna o valor 1
                return 0;  // sen�o retorna o valor 0
            }
    }

    void Passagem3D2D(){// Fun��o que passa uma pe�a com uma variante espec�fica para uma matriz 3x3
    int i,j;
        for(i=0;i<3;i++){// percorre as 3 linhas
            for(j=0;j<3;j++){// percorre as 3 colunas
                matrix3x3[i][j] = matrix3D[id_global][i][j];//a pe�a guardada na matrix3D � passada para uma matriz 3x3, a "matrix3x3"
            }
        }
    }

    int  Mult3(int num){// Fun��o que verifica se o n�mero inserido � mutiplo de 3
        if (num%3==0){// se o resto da divis�o por 3 for zero,
                return 1;// retorna o valor 1
        } else {
                return 0;// retorna o valor 0
        }
    }

    void VerificacaoDadosInseridos(int a,int b){ // Fun��o respons�vel por validar as linhas e colunas inseridas

        if(((8<a && a<16) && (8<b && b<25)) && ((Mult3(a)==1) && Mult3(b)==1)){// verifica se o n� de linhas e colunas est�o no intervalo correto e se s�o divis�veis por 3
        } else {
            printf("\n\nDIMENSAO INVALIDA\n\n");    // caso o n� de linhas e colunas esteja no intervalo correto e amabs sejam divis�veis por 3,
             exit(-1);                             // caso contr�rio retorna o valor 0
        }
    }

    void PrintfAlphabet(int colunas){// Fun��o que imprime a numera��o alfab�tica das colunas do tabuleiro
        int n;//index
        char letras = 'A';//vari�vel "letras" guarda a primeira letra do tabuleiro/alfabeto
        printf("  ");//printf para formata��o
            for(n=1;n<=colunas;n++){//percorre as colunas
                printf(" %c ",letras);//printf da letra correspondente
                letras++;//uma vez que o programa guarda a letra como c�digo ASCII, incrementamos para obter a letra seguinte
            }
            printf("\n");//line break
    }

    int  EscolhaIDPeca(int x,int y){// Fun��o respons�vel pela escolha aleat�ria da pe�a (onde x corresponde � pe�a escolhida e o y � o n�mero da tentativa no modo de posicionamento p2)
        int global_id;// vari�vel que guarda o id global da pe�a a escolher

        if(x==0){global_id=0;}// caso a pe�a escolhida seja 0, escolhe o global id da pe�a 0

        if(x==1){// caso a pe�a escolhida seja 1,
            if(y==0){ // caso seja a 1� tentativa,
                global_id=rand()%9+1;// random do global id
            }if(y==1){// caso seja a 2� tentativa,
                global_id=1;
            }if(y==2){// caso seja a 3� tentativa,
                global_id=2;
            }if(y==3){// caso seja a 4� tentativa,
                global_id=3;
            }if(y==4){// caso seja a 5� tentativa,
                global_id=4;
            }if(y==5){// caso seja a 6� tentativa,
                global_id=5;
            }if(y==6){// caso seja a 7� tentativa,
                global_id=6;
            }if(y==7){// caso seja a 8� tentativa,
                global_id=7;
            }if(y==8){// caso seja a 9� tentativa,
                global_id=8;
            }if(y>=9){// a partir da 10� tentativa inclusive,
                global_id=9;
            }

        /* a mesma linha de pensamento usada anteriormente na cadeia de ifs ser� usada nas seguintes cadeias: */

        }if(x==2){// caso a pe�a escolhida seja 2,
            if(y==0){  // caso seja a 1� tentativa,
                global_id=rand()%12+10;// random do global id
            }if(y== 1){// caso seja a 2� tentativa,
                global_id=10;
            }if(y== 2){// caso seja a 3� tentativa,
                global_id=11;
            }if(y== 3){// caso seja a 4� tentativa,
                global_id=12;
            }if(y== 4){// caso seja a 5� tentativa,
                global_id=13;
            }if(y== 5){// caso seja a 6� tentativa,
                global_id=14;
            }if(y== 6){// caso seja a 7� tentativa,
                global_id=15;
            }if(y== 7){// caso seja a 8� tentativa,
                global_id=16;
            }if(y== 8){// caso seja a 9� tentativa,
                global_id=17;
            }if(y== 9){// caso seja a 10� tentativa,
                global_id=18;
            }if(y==10){// caso seja a 11� tentativa,
                global_id=19;
            }if(y==11){// caso seja a 12� tentativa,
                global_id=20;
            }if(y>=12){// caso seja a 13� tentativa,
                global_id=21;
            }
        }if(x==3){// caso a pe�a escolhida seja 3,
            if(y==0){ // caso seja a 1� tentativa,
                global_id=rand()%6+22;// random do global id
            }if(y==1){// caso seja a 2� tentativa,
                global_id=22;
            }if(y==2){// caso seja a 3� tentativa,
                global_id=23;
            }if(y==3){// caso seja a 4� tentativa,
                global_id=24;
            }if(y==4){// caso seja a 5� tentativa,
                global_id=25;
            }if(y==5){// caso seja a 6� tentativa,
                global_id=26;
            }if(y>=6){// caso seja a 7� tentativa,
                global_id=27;
            }
        }if(x==4){// caso a pe�a escolhida seja 4,
             if(y==0){// caso seja a 1� tentativa,
                global_id=rand()%4+28;// random do global id
            }if(y==1){// caso seja a 2� tentativa,
                global_id=28;
            }if(y==2){// caso seja a 3� tentativa,
                global_id=29;
            }if(y==3){// caso seja a 4� tentativa,
                global_id=30;
            }if(y>=4){// caso seja a 5� tentativa,
                global_id=31;
            }
        }if(x==5){// caso a pe�a escolhida seja 5,
             if(y==0){// caso seja a 1� tentativa,
                global_id=rand()%4+32;// random do global id
            }if(y==1){// caso seja a 2� tentativa,
                global_id=32;
            }if(y==2){// caso seja a 3� tentativa,
                global_id=33;
            }if(y==3){// caso seja a 4� tentativa,
                global_id=34;
            }if(y>=4){// caso seja a 5� tentativa,
                global_id=35;
            }
        }if(x==6){// caso a pe�a escolhida seja 6,
             if(y==0){// caso seja a 1� tentativa,
                global_id=rand()%4+36;// random do global id
            }if(y==1){// caso seja a 2� tentativa,
                global_id=36;
            }if(y==2){// caso seja a 3� tentativa,
                global_id=37;
            }if(y==3){// caso seja a 4� tentativa,
                global_id=38;
            }if(y>=4){// caso seja a 5� tentativa,
                global_id=39;
            }
        }if(x==7){// caso a pe�a escolhida seja 7,
             if(y==0){// caso seja a 1� tentativa,
                global_id=rand()%2+40;// random do global id
            }if(y==1){// caso seja a 2� tentativa,
                global_id=40;
            }if(y>=2){// caso seja a 3� tentativa,
                global_id=41;
            }
        }if(x==8){// caso a pe�a escolhida seja 8,
            global_id=rand()%1+42;// random do global id
        }
    return global_id;// retorna o globa id escolhido
}

    int  Restricao1P1(int x, int y){// Fun��o repons�vel por verificar a validade face � restri��o 1
      int i,j;
        for(i=0;i<5;i++){// percorre 5 linhas da zona a analisar
            for(j=0;j<5;j++){// percorre 5 colunas da zona a analisar
                if(x==0){// exce��o aquando da an�lise da 1� linha, para evitar problemas com a an�lise de elementos fora da matriz pretendida
                    if(boardmatrixAux[x+i][y+j]!=0 && boardmatrixAux[x+i][y+j]!=10 && matrix5x5[i][j]==10){// caso o elemento matrix5x5 (que guarda a pe�a+escudo) tenha escudo e o elemento do tabuleiro seja uma pe�a,
                        return 0;// retorna o valor 0
                    }
                }else{
                    if(boardmatrix[x+i-1][y+j-1]!=0 && boardmatrix[x+i-1][y+j-1]!=10 && matrix5x5[i][j]==10){// caso o elemento matrix5x5 (que guarda a pe�a+escudo) tenha escudo e o elemento do tabuleiro seja uma pe�a,
                        return 0;// retorna o valor 0
                    }
                }
            }
        }
    return 1;// retorna o valor 1 (n�o h� viola��o da restri��o)
    }

//--------------------------------------
    void InitBoardMatrix(int linhas, int colunas){ //Fun��o que atribui os valores iniciais do tabuleiro
        int i,j;
            for(i=0;i<linhas;i++){//percorre as linhas
                for(j=0;j<colunas;j++){//percorre as colunas
                        boardmatrix[i][j]=0;//atribui o valor 0 (�gua) a todos os elementos da matriz
                }
            }
            for(i=0;i<linhas+2;i++){//percorre as linhas
                for(j=0;j<colunas+2;j++){//percorre as colunas
                        boardmatrixAux[i][j]=0;//atribui o valor 0 (�gua) a todos os elementos da matriz auxiliar
                }
            }
    }

    void PrintBoard(int linhas,int colunas){ //Fun��o que imprime o tabuleiro
    int i,j,n;
    n=linhas;//n guarda o numero da linha
        for(i=0;i<linhas;i++){ // ciclo for que percorre as linhas do tabuleiro
                printf("%2.d ",n); // sempre que ocorre uma mudan�a de linha imprime o n�mero da linha correspondente
            for(j=0;j<colunas;j++){ // ciclo for que percorre as colunas do tabuleiro
                    if(boardmatrix[i][j]==0){
                    printf(" - ");              // caso o valor guardado seja 0 (�gua), imprime o caracter -
                    }if(boardmatrix[i][j]==1){
                    printf(" 1 ");              // caso o valor guardado seja 1 (pe�a 1), imprime o caracter 1
                    }if(boardmatrix[i][j]==2){
                    printf(" 2 ");              // caso o valor guardado seja 2 (pe�a 2), imprime o caracter 2
                    }if(boardmatrix[i][j]==3){
                    printf(" 3 ");              // caso o valor guardado seja 3 (pe�a 3), imprime o caracter 3
                    }if(boardmatrix[i][j]==4){
                    printf(" 4 ");              // caso o valor guardado seja 4 (pe�a 4), imprime o caracter 4
                    }if(boardmatrix[i][j]==5){
                    printf(" 5 ");              // caso o valor guardado seja 5 (pe�a 5), imprime o caracter 5
                    }if(boardmatrix[i][j]==6){
                    printf(" 6 ");              // caso o valor guardado seja 6 (pe�a 6), imprime o caracter 6
                    }if(boardmatrix[i][j]==7){
                    printf(" 7 ");              // caso o valor guardado seja 7 (pe�a 7), imprime o caracter 7
                    }if(boardmatrix[i][j]==8){
                    printf(" 8 ");              // caso o valor guardado seja 8 (pe�a 8), imprime o caracter 8
                    }
            }
            printf("\n");//line break
            n--;//n decrementa
        }
        printf("\n");//line break
        PrintfAlphabet(colunas);//chama a fun��o que imprime a numera��o alfab�tica do tabuleiro
    }

    void help_message(){// Fun��o respons�vel pela impress�o da mensagem de ajuda
    printf("Help menu\n\n-h ajuda para o utilizador\n-t dimens�es do tabuleiro (linha x coluna)\n-j modo de jogo (0 a 2)\n-p modo de posicionamento de pe�as pelo computador (1 a 2)\n-d modo de disparo de pe�as pelo computador (1 a 3)\n");
    printf("-1 n�mero de pe�as do tipo 1\n-2 n�mero de pe�as do tipo 2\n-3 n�mero de pe�as do tipo 3\n-4 n�mero de pe�as do tipo 4\n-5 n�mero de pe�as do tipo 5\n-5 n�mero de pe�as do tipo 5\n-6 n�mero de pe�as do tipo 6\n-7 n�mero de pe�as do tipo 7\n-8 n�mero de pe�as do tipo 8\n");
}

    int  main(int argc, char* argv[]){// Fun��o Main

        int s;
        int gopt='h';// incializa��o da vari�vel gopt
        int linhas=9,colunas=9;// atribui��o das dimens�es do tabuleiro predefinidas (9x9)
        int modo_jogo=0,modo_posicionamento=1,modo_disparo=1;// predefini��es dos modos j,p,d

        while((gopt=getopt(argc,argv,"t:j:p:d:1:2:3:4:5:6:7:8:h")) != -1){// enquanto a fun��o getopt n�o retornar -1,

            switch(gopt){// switch para a leitura dos argumentos na linha de comandos
                case 't':
                    sscanf(optarg,"%dx%d",&linhas,&colunas);// leitura das dimens�es do tabuleiro
                    break;
                case 'j':
                    sscanf(optarg,"%d",&modo_jogo);// leitura do modo de jogo
                    if(modo_jogo==2){modo_posicionamento=2;}
                    break;
                case 'p':
                    sscanf(optarg,"%d",&modo_posicionamento);// leitura do modo de posicionamento
                    break;
                case 'd':
                    sscanf(optarg,"%d",&modo_disparo);// leitura do modo de disparo
                    break;
                case '1':
                    sscanf(optarg,"%d",&n_pecas1);// leitura do n� de pe�as 1
                    break;
                case '2':
                    sscanf(optarg,"%d",&n_pecas2);// leitura do n� de pe�as 2
                    break;
                case '3':
                    sscanf(optarg,"%d",&n_pecas3);// leitura do n� de pe�as 3
                    break;
                case '4':
                    sscanf(optarg,"%d",&n_pecas4);// leitura do n� de pe�as 4
                    break;
                case '5':
                    sscanf(optarg,"%d",&n_pecas5);// leitura do n� de pe�as 5
                    break;
                case '6':
                    sscanf(optarg,"%d",&n_pecas6);// leitura do n� de pe�as 6
                    break;
                case '7':
                    sscanf(optarg,"%d",&n_pecas7);// leitura do n� de pe�as 7
                    break;
                case '8':
                    sscanf(optarg,"%d",&n_pecas8);// leitura do n� de pe�as 8
                    break;
                case 'h':
                    help_message(); //chamada � fun��o help_message para imprimir a mensagem de ajuda
                    exit(-1);// sai do programa com retorno -1
                    break;
            }
        }
        VerificacaoDadosInseridos(linhas,colunas);// Chama a fun��o que verifica a validade das dimens�es inseridas
        if(modo_jogo>2||modo_jogo<0){// se o modo de jogo selecionado for diferente de 1 e 2,
            printf(" *Modo de jogo inserido inv�lido\n");
            help_message();// chama a fun��o da mensagem de ajuda
            exit(-1);// sai do programa com retorno -1
        }
        if(modo_posicionamento>2||modo_posicionamento<1){// se o modo de posicionamento for diferente de 1 e 2,
           printf(" *Modo de posicionamento inv�lido\n");
           help_message();// chama a fun��o da mensagem de ajuda
           exit(-1);// sai do programa com retorno -1
        }
        if(modo_disparo>3||modo_disparo<1){// se o modo de disparo for diferente de 1, 2 ou 3,
            printf(" *Modo de posicionamento inv�lido\n");
            help_message();// chama a fun��o da mensagem de ajuda
            exit(-1);// sai do programa com retorno -1
        }
        if(modo_posicionamento==2){// se o modo de posicionamento for 2,
            s=MatrizesVazias(linhas,colunas);// guarda na vari�vel s a quantidade de matrizes vazias a colocar no modo p2
            if(NumPecas(s)==0){// caso o n�mero de pe�as colocado seja incorreto,
                printf(" *Numero de pe�as inserido incorreto\n");
                exit(-1);// sai do programa com retorno -1
            }
        }
        if(modo_jogo==0){// se o modo de jogo for 0,
            if(modo_posicionamento==1){// se o modo de posicionamento for 1,
                Modo_p1(linhas,colunas);// chama a fun��o respons�vel pelo modo p1
                PrintBoard(linhas,colunas);// chama a fun��o respons�vel pela impress�o do tabuleiro
            }
            if(modo_posicionamento==2){// se o modo de posicionamento for 2,
                Modo_p2(linhas,colunas);// chama a fun��o respons�vel pelo modo p2
                PrintBoard(linhas,colunas);// chama a fun��o respons�vel pela impress�o do tabuleiro
            }
        }
        if(modo_jogo==1){// se o modo de jogo for 1,
            if(modo_posicionamento==1){// se o modo de posicionamento for 1,
                Modo_p1(linhas,colunas);// chama a fun��o respons�vel pelo modo p1
                printf(" * ============================\n");
                printf(" * Modo do Jogo 1\n");
                printf(" * Insira as Coordenadas de Disparo\n");
                printf(" * ============================\n");
                printf("%dx%d %d %d %d %d %d %d %d %d \n",linhas,colunas,n_pecas1,n_pecas2,n_pecas3,n_pecas4,n_pecas5,n_pecas6,n_pecas7,n_pecas8);
                Modo_d1j1(linhas,colunas);// chama a fun��o respons�vel pelo modo d1 no posicionamento j1
                PrintBoard(linhas,colunas);// chama a fun��o respons�vel pela impress�o do tabuleiro
            }
            if(modo_posicionamento==2){// se o modo de posicionamento for 2,
                Modo_p2(linhas,colunas);// se o modo de posicionamento for 2,
                printf(" * ============================\n");
                printf(" * Modo do Jogo 1\n");
                printf(" * Insira as Coordenadas de Disparo\n");
                printf(" * ============================\n");
                printf("%dx%d %d %d %d %d %d %d %d %d \n",linhas,colunas,n_pecas1,n_pecas2,n_pecas3,n_pecas4,n_pecas5,n_pecas6,n_pecas7,n_pecas8);
                Modo_d1j1(linhas,colunas);// chama a fun��o respons�vel pelo modo d1 no modo j1
                PrintBoard(linhas,colunas);// chama a fun��o respons�vel pela impress�o do tabuleiro
            }
        }
        if(modo_jogo==2){// se o modo de jogo for 2,
            printf(" * ============================\n");
            printf(" * Modo do Jogo 2\n");
            printf(" * Crie um tabuleiro com as caracter�sticas indicadas\n");
            printf(" * Responda aos disparos do programa\n");
            printf(" * ============================\n");
            printf("%dx%d %d %d %d %d %d %d %d %d \n",linhas,colunas,n_pecas1,n_pecas2,n_pecas3,n_pecas4,n_pecas5,n_pecas6,n_pecas7,n_pecas8);

            if(modo_disparo==1){// se o modo de disparo for 1,
                Modo_p2(linhas,colunas);// chama a fun��o respons�vel pelo modo p2
                Modo_d1j2(linhas,colunas);// chama a fun��o respons�vel pelo modo d1 no modo j2
                PrintBoard(linhas,colunas);// chama a fun��o respons�vel pela impress�o do tabuleiro
            }
            if(modo_disparo==2){// se o modo de disparo for 2,
                Modo_p2(linhas,colunas);// chama a fun��o respons�vel pelo modo p2
                Modo_d2(linhas,colunas);// chama a fun��o respons�vel pelo modo d2
                PrintBoard(linhas,colunas);// chama a fun��o respons�vel pela impress�o do tabuleiro
            }
            if(modo_disparo==3){
                Modo_p2(linhas,colunas);// chama a fun��o respons�vel pelo modo p2
                Modo_d3(linhas,colunas);// chama a fun��o respons�vel pelo modo d3
                PrintBoard(linhas,colunas);// chama a fun��o respons�vel pela impress�o do tabuleiro
            }
        }

        return 0;
    }
