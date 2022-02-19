#include "Covid19.h"

/** \brief le o ficheiro .csv indicado e insere a informacao lida em listas, principais para cada pais e dados fixos, secundarias para dados variaveis
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *all char: indicador proveniente da linhas de comandos que indica os dados a ler
 * \param *name char: nome do ficheiro .csv a ler
 * \return void
 *
 */
void Ler(struct principal *head ,char *all,char *name){
    FILE *file = NULL;
    struct secundaria *sec = NULL;
    struct principal *ptr1 = NULL;
    struct principal *ptr = NULL;
    struct secundaria *sec1= NULL;
    char string1[200];
    char string2[200];
    char string3[200];
    char *Cou_C, *con, *ind, *year_week, *popu, *week, *rate,*comu;
     char *token, *token1, *token2, *token3,*token4,*token5, *token6, *token7,*token8,*token9;
    int j=0,i=0,m=0;
    char c;


    if((file = fopen(name,"r"))==NULL){
        ErrorMessage(head);
    }



    while((c = getc(file)) != EOF){

        fseek(file,-1,SEEK_CUR);
            i=0;
            memset(string1, 0, sizeof(string1));
            while((c = getc(file)) !='\n'){
                string1[i] = c;
                i++;
            }
            memset(string2, 0, sizeof(string2));
            strcpy(string2,string1);
            strcpy(string3,string1);
            token1 = strtok(string1,",");
            token2 = strtok(NULL,",");
            token3 = strtok(NULL,",");
            token4 = strtok(NULL,",");
            token5 = strtok(NULL,",");
            token6 = strtok(NULL,",");
            token7 = strtok(NULL,",");
            token8 = strtok(NULL,",");
            /* verifica se os dados que esta a ler estao corretos*/
            if(  (token9 = strtok(NULL,","))!=NULL){

             if(  m>=1 && (Verificacao(token1)>0 || Verificacao(token2)>0 || Verificacao(token3)>0 || colunas(string2)!=8 || VerificacaoPOP_Weekly(token4)>0 || VerificacaoIND(token5)>0 || VerificacaoPOP_Weekly(token6)>0  || Verificacaoyear(token7)>0 ||  Verificacaorate(token8)>0 || Verificacaocomu(token9)>0 ) ){
               fprintf(stderr,"-1 Erro de Leitura ...");
               fclose(file);
               freeAll(head);
               exit(-1);
           }


             } else{

                    if(  m>=1 && (Verificacao(token1)>0 || Verificacao(token2)>0 || Verificacao(token3)>0 || colunas(string2)!=8 || VerificacaoPOP_Weekly(token4)>0 || VerificacaoIND(token5)>0 || VerificacaoPOP_Weekly(token6)>0  || Verificacaoyear(token7)>0 || Verificacaocomu(token8)>0) ){
                        fprintf(stderr,"-1 Erro de Leitura ...");
                        fclose(file);
                        freeAll(head);
                        exit(-1);
               }

             }


            /* Verfica se os dados que está a ler, corresponde a opçcao -L que o user escolheu */
            if(m>=1 && (strcmp(token3,all)==0 || strcmp("all",all)==0) ){

            j=0;
            ptr1=head;
            /* verifica se existe algum no princiapal com o pais da linha que esta a ler, se existe da break no while e j=1
            Caso exsita, coloca os dados variaveis num no secundario, e liga-o ao ultimo no secundario dessa lista principal
            Caso nao exista, cria um no princiapal para este pais e cria um secundario que vai ligar ao no principal */
            while(ptr1->link != NULL){
                ptr1 = ptr1 -> link;

                if(strcmp(token1,ptr1->country)==0){
                    j=1;
                    break;
                }
            }
            if( j==1 ){
                sec1 = ptr1 -> next;
                while(sec1->nexts!=NULL){
                    sec1= sec1->nexts;
                }
                token = strtok(string2,",");
                Cou_C = strtok(NULL,",");
                con = strtok(NULL,",");
                popu = strtok(NULL,",");
                ind = strtok(NULL,",");
                week = strtok(NULL,",");
                year_week = strtok(NULL,",");
                rate = strtok(NULL,",");

                sec= (struct secundaria*) calloc(1,sizeof(struct secundaria));

                sec1 -> nexts = sec;
                strcpy(sec -> indicator,ind);
                sec -> weekly_count = atoi(week);
                strcpy(sec -> year_week,year_week);
                sec -> rate_14_day = atof(rate);
                if(  (comu = strtok(NULL,","))!=NULL){
                    sec ->cumulative_count = atoi(comu);
                } else {
                    sec -> cumulative_count = sec ->rate_14_day;
                    sec -> rate_14_day = 0;

                }


            }else if( j==0 ){


                token = strtok(string2,",");
                Cou_C = strtok(NULL,",");
                con = strtok(NULL,",");
                popu = strtok(NULL,",");
                ind = strtok(NULL,",");
                week = strtok(NULL,",");
                year_week = strtok(NULL,",");
                rate = strtok(NULL,",");



                ptr= (struct principal*) calloc(1,sizeof(struct principal));

                ptr1 -> link = ptr;
                strcpy(ptr -> country,token);
                strcpy(ptr -> country_code,Cou_C);
                strcpy(ptr -> continent,con);
                ptr -> population = atof(popu);

                sec= (struct secundaria*) calloc(1,sizeof(struct secundaria));
                ptr -> next = sec;

                strcpy(sec -> indicator,ind);
                sec -> weekly_count = atoi(week);
                strcpy(sec -> year_week,year_week);
                sec -> rate_14_day = atof(rate);
                if(  (comu = strtok(NULL,","))!=NULL){
                    sec ->cumulative_count = atoi(comu);
                } else {
                    sec -> cumulative_count = sec ->rate_14_day;
                    sec -> rate_14_day = 0;

                }

            }
        }
        m++;
    }


    fclose(file);
}

/** \brief escreve um ficheiro .dat com o nome indicado, recorrendo a leitura de listas para o fazer
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *name char: nome do ficheiro .dat a escrever
 * \return void
 *
 */
void WriteFilebin(struct principal *head,char *name){
    FILE*file=NULL;
    struct principal *ptr1,*aux;
    struct secundaria *ptr2;
    int n=0;

    if((file = fopen(name,"wb"))==NULL){
        printf("Nao foi possivel abrir o ficheiro de output ");
        exit(1);
    }
    ptr1=head-> link;
    aux = head;
    /*while responsavel por calcular, para cada no principal, a quantidade de nos secundarios, colocando este valor no paramentro "linhas"
    da lista principal  */
    while( ptr1 !=NULL){
        n=0;
        ptr2 = ptr1 -> next;
        while(ptr2 !=NULL){

            n++;


            ptr2= ptr2 -> nexts;
        }
        ptr1->linhas = n;
        ptr1 -> ultimo = 0;
        aux= ptr1;
        ptr1=ptr1 -> link;

    }
    aux -> ultimo=1; // coloca na lista o valor o 1, no parametro "ultimo", para quando formos a ler binario sabermos que este no se trata do ultimo

    /* Escrve no ficheiro binario, o no principal, e logo de seguida os seus,respetivos, nos secundario, e assim sucessicavemnte  */
    ptr1 = head-> link;
    while( ptr1!=NULL ){

        fwrite(ptr1,sizeof(struct principal),1,file);

        ptr2 = ptr1 -> next;
        while(ptr2 !=NULL){
            fwrite(ptr2,sizeof(struct secundaria),1,file);

            ptr2 = ptr2 -> nexts;
        }

        ptr1 = ptr1 -> link;
    }


fclose(file);
}

/** \brief escreve um ficheiro .csv com o nome indicado, recorrendo a leitura de listas para o fazer
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *headerr cha: header de cada ficheiro .csv (primeira linha de cada coluna)
 * \param *name char: nome do ficheiro .csv a escrever
 * \return void
 *
 */
void WriteFile(struct principal *head,char *headerr,char *name){
    FILE*file=NULL;
    struct principal *ptr1;
    struct secundaria *ptr2;

    if((file = fopen(name,"w"))==NULL){
        printf("Nao foi possivel abrir o ficheiro de output ");
        exit(1);}

fprintf(file,"%s\n",headerr);

    // PRINT dos dados no ficheiro
    ptr1 = head -> link ;
    while(ptr1 != NULL){
        ptr2 =  ptr1 -> next;
        while(ptr2 != NULL){
             fprintf(file,"%s,%s,%s,%d,%s,%d,%s,%f,%d\n",ptr1->country,ptr1->country_code,ptr1->continent,ptr1->population,ptr2->indicator,ptr2->weekly_count,ptr2->year_week,ptr2->rate_14_day,ptr2->cumulative_count);
            ptr2 = ptr2 -> nexts;
        }
    ptr1 = ptr1 -> link;
    }
    fclose(file);
}

/** \brief le o ficheiro .dat indicado e insere a informacao lida em listas, principais para cada pais e dados fixos, secundarias para dados variaveis
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *name char: nome do ficheiro .dat a ler
 * \return void
 *
 */
void Lerbin(struct principal *head,char *name){
FILE*file=NULL;
int p = 0 ;
int k=0,i=0;
struct principal *ptr,*ptr1;
struct secundaria *sec,*sec1;

if((file = fopen(name,"rb"))==NULL){
        printf("Nao foi possivel abrir o ficheiro");
        exit(1);
    }

do {


ptr =(struct principal*) calloc(1,sizeof(struct principal));
fread(ptr,sizeof(struct principal),1,file);
        if(k==0){   // se for o primeiro ciclo a head apontar para o proximo no e igual ao ptr

        head -> link = ptr;
        ptr1 = head-> link;

        }

        if( k>=1){ // depois de executar o primeiro ciclo, o ultimo no principal aponta para o no que alocamos neste ciclo, e sempre assim sucissavamente
            ptr1 -> link = ptr;
            ptr1 = ptr1 -> link;


        }

        p=0; i=0;
        while(p<ptr1->linhas){
            p++;



        sec1 =(struct secundaria*) calloc(1,sizeof(struct secundaria));
        fread(sec1,sizeof(struct secundaria),1,file);
        if(i==0){ // se for o primeiro no secundario, este fica ligado ao no principal em questao
            ptr1 -> next = sec1;
            sec1 -> nexts = NULL;
            sec = ptr1 -> next ;
        }
        if(i>0){ // se nao for o primeiro no secundario, estes ficam ligados ao ultimo no secundario em questao
            sec ->nexts = sec1;
            sec=sec -> nexts;

        }

        i++;
        }
        k++;

    }while(ptr1->ultimo !=1);

fclose(file);
}
