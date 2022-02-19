#include "Covid19.h"

/** \brief verifica, para uma string, a existencia de caracteres para alem de espacos, letras maisuculas e letras minusculas
 *
 * \param *string char: string a analisar
 * \return return j int: numero de caracteres nao pertendidos
 *
 */
int Verificacao(char *string){
int k=0;;
int i=0,j=0;
    k=strlen(string);
    for(i=0;k>i; i++){
        /* verificar se a string esta entre os valores 65-90 e 97-122, que traduzidos correspondem, as letra A-Z e a-z
        e ainda verifica a possiblidade de haver um espaços, sendo que este corresponde a 32 na tabela de ASCII */
        if( (string[i]>=65 && string[i]<=90) ||  (string[i]>=97 && string[i]<=122) || string[i]==32){

        } else {
            j++;
        }
    }
    return j;
}

/** \brief verifica, para uma string, a existencia de caracteres que nao sejam algarismos
 *
 * \param *string char: string a analisar
 * \return return j int: numero de caracteres nao pertendidos
 *
 */
int VerificacaoPOP_Weekly(char *string){
int k=0;;
int i=0,j=0;
    k=strlen(string);
    for(i=0;k>i; i++){
        /* verificar se a string esta entre os valores 48 e 57, valores que traduzido atraves de tabela de ASCII  correspondem a valores de 0-9 */
        if( string[i]>=48 && string[i]<=57){
        } else {
            j++;
        }
    }
    return j;
}

/** \brief verifica, para uma string, se esta contem os indicadores "deaths" ou "cases"
 *
 * \param *string char: string a analisar
 * \return return int: 0 se for igual a "cases" ou "mortes", 1 se for diferente
 *
 */
int VerificacaoIND(char *string){
    if( strcmp(string,"deaths")==0 || strcmp(string,"cases")==0){
        return 0;
    } else {
        return 1;
    }
}

/** \brief conta o numero de virgulas numa determinada string (numero de colunas - 1 num ficheiro csv)
 *
 * \param *string char: string a analisar
 * \return return j int: retorna o numero de virgulas contabilizadas
 *
 */
int colunas(char *string){

int k=0;;
int i=0,j=0;
    k=strlen(string);
    for(i=0;k>i; i++){
        /* verificar se a string tem virgulas, sendo que as virgulas na tabela de ASCII corresponde ao numero 44 */
        if( string[i]==44){
            j++;
        }
    }
    return j;

}

/** \brief verifica, para uma string, se esta apresenta-se no formato yyyy-ww (data)
 *
 * \param *string char: string a analisar
 * \return return j int : retorna o numero de caracteres nao pertendidos
 *
 */
int Verificacaoyear(char *string){
int k=0;;
int i=0,j=0;
    k=strlen(string);
    for(i=0;k>i; i++){
    /* verificar se a string tem "-" no carater 5 da string  , sendo que este corresponde ao numero 45 na tabela de ASCI
    e para os restantes carater da string verificar se estao entre os valores 48 e 57 da tabela de ASCII que corresponder ao numeros de 0-9*/
        if( string[4]==45){

        } else if (string[4]!=45){
            j++;
        }

        if( string[i]>=48 && string[i]<=57  && i!=4){
        } else if (i!=4){
            j++;
        }
    }
    return j;
}

/** \brief conta o numero de caracteres que nao correspondem a algarismos
 *
 * \param *string char: string a analisar
 * \return return j int: retorna o numero de caracteres nao pertendidos
 *
 */
int Verificacaorate(char *string){

int k=0;;
int i=0,j=0,m=0,n=0;
    k=strlen(string);
    for(i=0;k>i; i++){
        /* verificar se a string tem pontos finais , sendo que este corresponde ao numero 46 na tabela de ASCI */
        if( string[i]!=46){

        } else {

            m++;
            n=i;
        }
    }

    if(m==0){ // se nao houver pontos

         for(i=0;k>i; i++){
         /* verificamos se a string esta entre os valores 48 e 57, valores que traduzido atraves de tabela de ASCII  correspondem a valores de 0-9 */
        if( string[i]>=48 && string[i]<=57){
        } else {
            j++;
        }
    }
    }
    if(m==1){ // se houver so um ponto
        for(i=0;k>i; i++){
        /* verificamos se a string esta 0-9 */
            if( string[i]>=48 && string[i]<=57  && i!=n){
            } else if (i!=n){
                j++;
            }
        }
    } else if(m>1) {
        j++;
    }
    return j;
}

/** \brief conta o numero de caracteres que nao correspondem a algarismos
 *
 * \param *string char: string a analisar
 * \return return j int: retorna o numero de caracteres nao pertendidos
 *
 */
int Verificacaocomu(char *string){
int k=0;;
int i=0,j=0;
    k=strlen(string);
    for(i=0;k-1>i; i++){
        /* verificar se a string esta entre os valores 48 e 57, valores que traduzido atraves de tabela de ASCII  correspondem a valores de 0-9 */
        if( string[i]>=48 && string[i]<=57){
        } else {
            j++;
        }
    }
    return j;
}
