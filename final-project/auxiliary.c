#include "Covid19.h"

/** \brief troca dois elementos de uma lista, trocando os seus ponteiros
 *
 * \param *left struct principal: ponteiro anterior
 * \param *right struct principal: ponteiro atual
 * \return *right struct principal
 *
 */
struct principal *troca(struct principal *left,struct principal *right){
    left -> link = right -> link;
    right -> link = left;
    return right;
}

/** \brief liberta toda a memoria alocada por listas
 *
 * \param *head struct principal: ponteiro para cabeca de lista
 * \return void
 *
 */
void freeAll(struct principal *head){
    struct principal *ptr,*Aux;
    struct secundaria *sec;

    ptr= head -> link;
    Aux = head;

    /*percorre os nos principais e secundarios libertando-os*/
    while(ptr != NULL)
    {
        sec= ptr -> next;

        while(sec != NULL)
        {
            ptr -> next = sec -> nexts;
            sec-> nexts = NULL;
            free(sec);
            sec = ptr -> next;
        }

        Aux -> link= ptr -> link;
        ptr -> link= NULL;
        free(ptr); // liberta a memoria apontar por ptr
        ptr= Aux -> link;
    }

    head -> link = NULL;
    free(head);
}

/** \brief Imprime mensagem de ajuda e liberta chama funcao freeAlll
 *
 * \param *head struct principal: ponteiro para cabeca de lista
 * \return void
 *
 */
void ErrorMessage(struct principal *head){
    fprintf(stderr,"\n\
        ==== SELECTING INPUT FILE ====\n\
        * -i filename.csv -> reads a comma separated value (csv) file\n\
        * -i filename.dat -> reads a binary file\n\n\
        ==== READING DATA ====\n\
        * -L all -> reads all data regardless of the continent\n\
        * -L *continent* -> reads the data from the continent you inserted\n\n\
        ==== SORTING DATA ====\n\
        * -S alfa -> sorts all countries alphabetically\n\
        * -S pop -> sorts all countries by their population in descending order\n\
        * -S inf *date* -> sorts all countries in descending order by the number of cases in a given date\n\
        * -S dea *date* -> sorts all countries in descending order by the number of deaths in a given date\n\n\
        ==== SELECTING DATA ====\n\
        * -D inf -> selects the week with the highest number of cases for each country\n\
        * -D dea -> selects the week with the highest number of deaths for each country\n\
        * -D racioinf *date* -> selects the week with the highest infection ratio per 100000 people.\n\
        * -D raciodea *date* -> selects the week with the highest death ratio per 100000 people.\n\n\
        ==== RESTRICTING DATA ====\n\
        * -P min *n thousand people* -> it will only show the countries that have a population higher than the number you inserted times 1000\n\
        * -P dea *n thousand people* -> it will only show the countries that have a population lower than the number you inserted times 1000\n\
        * -P date *yyyy-ww* -> it will only show data from the date you inserted\n\
        * -P date *yyyy-ww yyyy-ww* -> it will only show data from the dates that lie between those you inserted\n\n\
        ==== SELECTING OUTPUT FILE ====\n\
        * -o filename.csv -> writes a comma separated value (csv) file\n\
        * -o filename.dat -> writes a binary file\n\n\
    ");
    freeAll(head);
    exit(1);
}
