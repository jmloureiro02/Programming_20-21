#ifndef COVID19_H_INCLUDED
#define COVID19_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>


#define FILE_HEADER "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count"

struct secundaria {
    char indicator[7];
    int weekly_count;
    char year_week[8];
    double rate_14_day;
    int cumulative_count;
    struct secundaria *nexts;
};

struct principal {
    char country[30];
    char country_code[4];
    char continent[8];
    int  linhas;
    int  ultimo;
    int population;
    struct secundaria *next;
    struct principal *link;
};

void ORDalfa(struct principal *head);

struct principal *troca(struct principal *left, struct principal *right);

void ORDpop(struct principal *head);

void ORDinf_dea(struct principal *head, char *data,char *ind);

void SELinf_dea(struct principal *head,char *ind);

void RESmin(struct principal *head,long long n);

void RESmax(struct principal *head, long long n);

void SELratio_inf_dea(struct principal *head,char *ind);

void RESdate1(struct principal *head, char *date);

void RESdate2(struct principal *head, char *date1, char *date2);

void freeAll(struct principal *head);

void Ler(struct principal *head, char *all, char *name);

void WriteFile(struct principal *head,char *headerr,char *name);

void Lerbin(struct principal *head,char *name);

void WriteFilebin(struct principal *head,char *name);

int Verificacao(char *string);

int VerificacaoPOP_Weekly(char *string);

int VerificacaoIND(char *string);

int colunas(char *string);

int Verificacaoyear(char *string);

int Verificacaorate(char *string);

int Verificacaocomu(char *string);

void ErrorMessage(struct principal *head);


#endif // COVID19_H_INCLUDED
