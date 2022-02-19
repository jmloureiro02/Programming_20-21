#include "Covid19.h"

/** \brief ordena alfabeticamente todos os elementos da lista principal, atraves do algoritmo bubble sort
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \return void
 *
 */
void ORDalfa(struct principal *head){
    int trocas = 1;
    struct principal *left, *right, *Head, aux_struct;

    Head = &aux_struct;
    Head -> link = head;
    if((head != NULL) && (head -> link != NULL)){
        while(trocas){ // enquanto se realizar trocas
            trocas = 0;
            left = Head;
            right = Head -> link;
            while(right -> link != NULL){
                if(strcmp(right -> country,right -> link -> country) > 0){ // caso o no seguinte seja alfabeticamente menor que o anterior,
                    left -> link = troca(right,right -> link); // troca
                    trocas = 1;
                }
                left = right;
                if(right -> link != NULL){
                    right = right -> link;
                }
            }
        }
    }
    right = head -> link;
}

/** \brief ordena descrescentemente todos os paises pela sua populacao, atraves do algoritmo bubble sort
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \return void
 *
 */
void ORDpop(struct principal *head){
    int trocas = 1;
    struct principal *left, *right, *Head, aux_struct;

    Head = &aux_struct;
    Head = head;
    if(head != NULL){
        while(trocas){ // enquanto realizar trocas
            trocas = 0;
            left = Head;
            right = Head -> link;
            while(right -> link != NULL){

                if(right->population == right ->link-> population){ // caso a populacao seja a mesma, verifica o segundo criterio

                            if(strcmp(right -> country,right -> link -> country) > 0){ // caso o no seguinte seja alfabeticamente menor que o anterior,
                             left -> link = troca(right,right -> link); // troca
                            trocas = 1;
                         }

                        }

                else if((right -> population) < (right -> link -> population)){ // caso a populacao seguinte seja maior que a anterior,
                    left -> link = troca(right,right -> link); // troca
                    trocas = 1;
                }

                left = right;
                if(right -> link != NULL){
                    right = right -> link;
                }
            }
        }
    }
    right = head -> link;
}

/** \brief ordena descrescentemente todos os paises pelo seu numero de infetados ou mortes numa determinada semana, atraves do algoritmo bubble sort
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *data char: semana selecionada
 * \param *ind char: indicador que seleciona se estamos a ordenar por mortes ou por casos
 * \return void
 *
 */
void ORDinf_dea(struct principal *head, char *data, char *ind){
    int trocas = 1;
    struct principal *left, *right, *Head, aux_struct;
    struct secundaria *ptr,*ptr1;
    int j,k;

    Head = &aux_struct;
    Head  = head;
    if((head != NULL) && (head -> link != NULL)){
        while(trocas){ // enquanto se realizar trocas
            trocas = 0;
            left = Head;
            right = Head -> link;
            while(right -> link != NULL){
                    ptr = right->next;
                    ptr1 = right -> link -> next;
                    j=0;
                    k=0;
                    while(ptr  !=NULL){ // percorre os nos secundarios e verifica se existe algum no com a data indicada e com o indicador ind especificado
                        if( strcmp(ptr->indicator,ind)==0 && strcmp(ptr->year_week,data)==0 ){
                            j++;
                            break;
                        }
                        ptr = ptr -> nexts;
                    }

                    while(ptr1  !=NULL){ // percorre os nos secundarios e verifica se existe algum no com a data indicada e com o indicador ind especificado
                        if( strcmp(ptr1->indicator,ind)==0 && strcmp(ptr1->year_week,data)==0 ){
                            k++;
                            break;
                        }
                        ptr1 = ptr1 -> nexts;
                    }

                        if(j>0 && k>0){ // caso existam nos com data e indicador correto:
                            if((ptr->weekly_count) == (ptr1 -> weekly_count)){

                                if(strcmp(right -> country,right -> link -> country) > 0){
                                    left -> link = troca(right,right -> link);
                                    trocas = 1;
                                }
                            }

                            if((ptr->weekly_count) < (ptr1 -> weekly_count)){
                                left -> link = troca(right,right -> link);
                                trocas = 1;


                            }
                        } else if(k==0 && j>0){ // caso exista so um dos nos a verificar tenha data e indicador correto:
                            if((ptr->weekly_count) == 0){

                                if(strcmp(right -> country,right -> link -> country) > 0){
                                    left -> link = troca(right,right -> link);
                                    trocas = 1;
                                }
                            }

                            if((ptr->weekly_count) < 0){
                                left -> link = troca(right,right -> link);
                                trocas = 1;

                            }

                        } else if(j==0 && k>0){ // caso exista so um dos nos a verificar tenha data e indicador correto:

                            if( 0 == (ptr1 -> weekly_count)){

                                if(strcmp(right -> country,right -> link -> country) > 0){
                                    left -> link = troca(right,right -> link);
                                    trocas = 1;
                                }

                            }

                            if( 0 < (ptr1 -> weekly_count)){
                                left -> link = troca(right,right -> link);
                                trocas = 1;
                            }

                        } else if (j==0 && k==0){  // caso nenhum dos nos a verificar tenha data e indicador correto:

                            if(strcmp(right -> country,right -> link -> country) > 0){
                                left -> link = troca(right,right -> link);
                                trocas = 1;
                            }
                        }

                    left = right;
                    if(right -> link != NULL){
                        right = right -> link;
                    }
            }
        }
    }
    right = head -> link;
}

/** \brief seleciona para cada pais a semana com mais infetados ou mortes
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *ind char: indicador que seleciona se estamos a selecionar mortes ou casos
 * \return void
 *
 */
void SELinf_dea(struct principal *head,char *ind){
    int max = -1,j=0,m=0;
    char semana[8];
    struct secundaria *ptr2,*aux2;
    struct principal *ptr1,*AuxP;
    ptr1 = head -> link;
    AuxP = head;

    while(ptr1 !=NULL){
            max = -1;
            ptr2 = ptr1 -> next;
            //ciclo que procura o maximo de infetados num no
            j=0;
            while(ptr2 != NULL){
                if(ptr2 -> weekly_count > max && (strcmp(ptr2 -> indicator,ind) == 0)){
                    max = ptr2 -> weekly_count;
                    strcpy(semana, ptr2 -> year_week);
                    j++;
                } else if( ptr2 -> weekly_count == max && (strcmp(ptr2 ->year_week,semana) > 0) && (strcmp(ptr2 -> indicator,ind) == 0)){
                    strcpy(semana, ptr2 -> year_week);
                }


                ptr2 = ptr2 -> nexts;

            }
            ptr2 =  ptr1 -> next;// reinicia o ponteiro secundario
            m=0;
            // ciclo que elimina os nos secundarios caso estes nao correspondam ao maximo guardado em max
            while(ptr2  != NULL){
                if(ptr2 -> weekly_count == max && (strcmp(ptr2 -> indicator,ind) == 0) && (strcmp(ptr2 ->year_week,semana) == 0)){
                        aux2 = ptr2;
                        m++;
                        aux2 = ptr1 -> next;
                        ptr2 = ptr2 -> nexts;
                }   else if(m==0){
                    ptr1 -> next = ptr2 -> nexts;
                    ptr2 -> nexts = NULL;
                    free(ptr2);
                    ptr2 = ptr1 -> next;
                } else if(m>0){
                    aux2 -> nexts = ptr2 -> nexts;
                    ptr2-> nexts = NULL;
                    free(ptr2);
                    ptr2 = aux2 -> nexts;
                }

            }
        if(j==0){

             AuxP -> link = ptr1 -> link;
            ptr1 -> link = NULL;
            free(ptr1);

        } else{
        AuxP = ptr1;
        ptr1= ptr1 -> link;
        }
    }

}

/** \brief seleciona para cada pais a semana com maior racio de infetados ou maior racio de mortes
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *ind char: indicador que seleciona se estamos a slecionar racio de mortes ou racio de casos
 * \return void
 *
 */
void SELratio_inf_dea(struct principal *head,char *ind){
    double max = -1,j=0,m=0;
    char semana[8];
    struct secundaria *ptr2,*aux2=NULL;
    struct principal *ptr1,*AuxP;
    ptr1 = head -> link;
    AuxP = head;

    while(ptr1 !=NULL){
            max = -1;
            ptr2 = ptr1 -> next;
            j=0;
            //ciclo que procura o maximo de racio de infetados no nó
            while(ptr2 != NULL){
                if(ptr2 -> rate_14_day > max && (strcmp(ptr2 -> indicator,ind) == 0)){
                    max = ptr2 -> rate_14_day;
                     strcpy(semana, ptr2 -> year_week);
                    j++;
                } else if( ptr2 -> rate_14_day == max && (strcmp(ptr2 ->year_week,semana) > 0) && (strcmp(ptr2 -> indicator,ind) == 0)){
                    strcpy(semana, ptr2 -> year_week);
                }
                ptr2 = ptr2 -> nexts;
            }
            ptr2 =  ptr1 -> next;// reinicia o ponteiro secundario
            m=0;
            // ciclo que elimina os nos secundarios caso estes nao correspondam ao maximo guardado em max
            while(ptr2  != NULL){
                if(ptr2 -> rate_14_day == max && (strcmp(ptr2 -> indicator,ind) == 0) && (strcmp(ptr2 ->year_week,semana) == 0) ){
                        aux2 = ptr2;
                        m++;
                        aux2 = ptr1 -> next;
                        ptr2 = ptr2 -> nexts;
                }   else if(m==0){
                    ptr1 -> next = ptr2 -> nexts;
                    ptr2 -> nexts = NULL;
                    free(ptr2);
                    ptr2 = ptr1 -> next;
                } else if(m>0){
                    aux2 -> nexts = ptr2 -> nexts;
                    ptr2-> nexts = NULL;
                    free(ptr2);
                    ptr2 = aux2 -> nexts;
                }
            }
        if(j==0){
            AuxP -> link = ptr1 -> link;
            ptr1 =AuxP -> link;
            free(ptr1);
        } else{
            AuxP = ptr1;
            ptr1= ptr1 -> link;
        }
    }
}

/** \brief restringe a lista a paises com mais de n mil habitantes
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param n long long: numero de mil habitantes
 * \return void
 *
 */
void RESmin(struct principal *head,long long n){
    long long min = n*1000;

    struct principal *auxP, *ptr1;
    struct secundaria *auxS,*auxS1;
    ptr1 = head -> link;
    auxP = head;

    while(ptr1 != NULL){

        if((ptr1 -> population) < min){ // se a populacao for inferior ao minimo n, elimina os nos secundarios e o principal
            auxP -> link = ptr1 -> link;
            ptr1 -> link = NULL;
            auxS = ptr1 ->next;
            while(auxS != NULL){ // ciclo que elimina nos secundarios
                 auxS1 = auxS -> nexts;
                 auxS -> nexts = NULL;
                free(auxS);
                auxS = auxS1;
            }
            free(ptr1);
            ptr1 = auxP -> link;

        } else{
            auxP = ptr1;
            ptr1 = ptr1 -> link;
        }
    }
}

/** \brief restringe a lista a paises com menos de n mil habitantes
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param n long long: numero de mil habitantes
 * \return void
 *
 */
void RESmax(struct principal *head, long long n){
    long long max = n*1000;


    struct principal *auxP, *ptr1;
    struct secundaria *auxS,*auxS1;
    ptr1 = head -> link;
    auxP = head;

    while(ptr1 != NULL){

        if((ptr1 -> population) > max){ // se a populacao for superior ao maximo n, elimina os nos secundarios e o principal
            auxP -> link = ptr1 -> link;
            ptr1 -> link = NULL;
            auxS = ptr1 ->next;
            while(auxS != NULL){ // ciclo que elimina nos secundarios
                 auxS1 = auxS -> nexts;
                 auxS -> nexts = NULL;
                free(auxS);
                auxS = auxS1;

            }
            free(ptr1);
            ptr1 = auxP -> link;

        } else{
            auxP = ptr1;
            ptr1 = ptr1 -> link;

        }


    }

}

/** \brief restringe a lista a dados da semana indicada
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *date char : semana indicada
 * \return void
 *
 */
void RESdate1(struct principal *head,char *date){
    struct secundaria *ptr2, *aux2;
    struct principal *ptr1,*aux;
    int j=0,k=0;

    ptr1 = head -> link;
    aux = head;

    while(ptr1 != NULL){
        ptr2 = ptr1 -> next;
        aux2 = ptr1 -> next;
        k=0;j=0;
        while(ptr2 != NULL){

            if( strcmp(ptr2 -> year_week,date) != 0){ // se a semana a ler é diferente da pretendida, elimina o no
                if(j==0){
                ptr1->next = ptr2 -> nexts;
                aux2= ptr1 -> next;
                free(ptr2);
                ptr2 = ptr1->next;
                }else{
                aux2  -> nexts = ptr2 -> nexts;
                free(ptr2);
                ptr2 = aux2 -> nexts;
                }
            } else {
                aux2 = ptr2;
                 j++;
                 k++;
                  ptr2 = ptr2 -> nexts;
            }
        }
        if(k==0){

            aux -> link= ptr1 -> link;
            ptr1 -> link = NULL;
            free(ptr1);
            ptr1= aux -> link;
        } else{
            aux = ptr1;
            ptr1 = ptr1 -> link;
        }
    }
}

/** \brief restringe a lista a dados entree duas semanas indicadas
 *
 * \param *head struct principal: ponteiro para cabeca de lista principal
 * \param *date1 char : primeira semana indicada
 * \param *date2 char : segunda semana indicada
 * \return void
 *
 */
void RESdate2(struct principal *head,char *date1, char *date2){
    struct secundaria *ptr2, *aux2;
    struct principal *ptr1, *aux;
    int j=0,k=0;
    char *Aux;

    if(strcmp(date1,date2)>0)
    {
        Aux=date1;
        date1=date2;
        date2=Aux;
    }

    ptr1 = head -> link;
    aux = head;

    while(ptr1 != NULL){

        ptr2 = ptr1 -> next;

        j=0;
        k=0;
        while(ptr2 != NULL){

            if( strcmp(ptr2 -> year_week,date1) <0 || strcmp(ptr2 -> year_week,date2)>0  ){// se a semana a ler nao estiver no intervalo pretendido, elimina o no
                if(j==0){
                    ptr1->next = ptr2 -> nexts;
                    aux2= ptr1 -> next;
                    free(ptr2);
                    ptr2 = ptr1->next;
                }else {
                    aux2  -> nexts = ptr2 -> nexts;
                    free(ptr2);
                    ptr2 = aux2 -> nexts;
                }
            } else {
                aux2 = ptr2;
                j++;
                k++;
                ptr2 = ptr2 -> nexts;
            }
        }
         if(k==0){
            aux -> link= ptr1 -> link;
            ptr1 -> link = NULL;
            free(ptr1);
            ptr1= aux -> link;
        } else if (k>0){
            aux = ptr1;
            ptr1 = ptr1 -> link;
        }
    }
}
