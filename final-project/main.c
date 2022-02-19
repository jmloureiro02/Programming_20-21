#include "Covid19.h"


int main(int argc, char *argv[]){

    struct principal *head = NULL;
    head =(struct principal*) calloc(1,sizeof(struct principal));

    int opt=0;
    int i_flag=0  , S_flag=0 , D_flag=0 , P_flag=0 , o_flag=0, Bin_flag=0;
    char *i_value=NULL, *L_value="all", *S_value[2]={NULL}, *D_value=NULL, *P_value[3]={NULL}, *o_value=NULL;
    char *eptr;
    char input_compare[5]="0";
    char output_compare[5];
    long long P_population = 0;
    int i=0,j=0;


    S_value[0]="alfa";

    while ( (opt = getopt(argc, argv, "i:L:S:D:P:o:")) != -1 )
    {
        switch(opt)
        {
        case 'i':
            i_flag=1;
            i_value = optarg;
            break;
        case 'L':
            L_value = optarg;
            break;
        case 'S':
            S_flag=1;
            optind--;
            for(i=0;optind< argc && *argv[optind]!= '-'; optind++, i++)
                S_value[i]=argv[optind];
            break;
        case 'D':
            D_flag=1;
            D_value= optarg;
            break;
        case 'P':
            P_flag=1;
            optind--;
            for(i=0; optind<argc && *argv[optind]!= '-'; optind++, i++)
                P_value[i]= argv[optind];
            break;
        case 'o':
            o_flag=1;
            o_value=optarg;
            break;
        }
    }

    if((P_value[0]==NULL && P_flag==1) || (P_value[0]!=NULL && P_value[1]==NULL && P_flag==1) ||(D_value==NULL && D_flag==1)){
        ErrorMessage(head);
    }

    //leitura
    if(i_flag==1){
        for( i = 0; i_value[i+1] != '\0' ; i++);
        input_compare[3] = i_value[i];
        input_compare[2] = i_value[i-1];
        input_compare[1] = i_value[i-2];
        input_compare[0] = i_value[i-3];

        printf("Input File: %s\n",i_value);
        printf("Reading Data: -L %s\n",L_value);

        if(strcmp(input_compare,".dat")==0){
            Bin_flag = 1;
            Lerbin(head,i_value);
        }else if(strcmp(input_compare,".csv")==0){
            if(strcmp(L_value,"all")==0){
                Ler(head,"all",i_value);
            }else if(strcmp(L_value,"Africa")==0 || strcmp(L_value,"Europe")==0 || strcmp(L_value,"Oceania")==0 || strcmp(L_value,"America")==0 || strcmp(L_value,"Asia")==0){
                Ler(head,L_value,i_value);
            }else{
                ErrorMessage(head);
            }
        }else{
            ErrorMessage(head);
        }
    }else{
        ErrorMessage(head);
    }

    //selecoes
    if(D_flag==1 && Bin_flag == 0){
        printf("Selecting Data: -D %s\n",D_value);
       if(strcmp(D_value,"inf")==0){
            SELinf_dea(head,"cases");
        }else if(strcmp(D_value,"dea")==0){
            SELinf_dea(head,"deaths");
        }else if(strcmp(D_value,"racioinf")==0){
            SELratio_inf_dea(head,"cases");
        }else if(strcmp(D_value,"raciodea")==0){
            SELratio_inf_dea(head,"deaths");
        }else{
			ErrorMessage(head);
		}
    }else if(D_flag==1 && Bin_flag == 1){
        ErrorMessage(head);
    }

    //restricoes
    if(P_flag==1 && Bin_flag == 0){
        printf("Restricting Data: -P %s %s %s\n",P_value[0],P_value[1],P_value[2]);
        if(strcmp(P_value[0],"min")==0){
            P_population = strtoll(P_value[1],&eptr,10);
            RESmin(head,P_population);
        }else if(strcmp(P_value[0],"max")==0){
            P_population = strtoll(P_value[1],&eptr,10);
            RESmax(head,P_population);
        }else if(strcmp(P_value[0],"date")==0 && P_value[2]==NULL){
            RESdate1(head,P_value[1]);
        } else if(strcmp(P_value[0],"dates")==0 && P_value[2]!=NULL){
            RESdate2(head,P_value[1],P_value[2]);
        } else {
            ErrorMessage(head);
        }
    }else if(P_flag==1 && Bin_flag == 1){
        ErrorMessage(head);
    }

    //ordenacoes
    if(S_flag==1 && Bin_flag == 0){
        printf("Sorting Data: -S %s %s \n",S_value[0],S_value[1]);
        if(strcmp(S_value[0],"alfa")==0){
            ORDalfa(head);
        }else if(strcmp(S_value[0],"pop")==0){
            ORDpop(head);
        }else if(strcmp(S_value[0],"inf")==0){
            ORDinf_dea(head,S_value[1],"cases");
        }else if(strcmp(S_value[0],"dea")==0){
            ORDinf_dea(head,S_value[1],"deaths");
        }else{
			ErrorMessage(head);
		}
    }else if(S_flag==1 && Bin_flag == 1){
        ErrorMessage(head);
    }

    // Escrita de Ficheiros

    if(o_flag==1){
        for( j = 0; o_value[j] != '\0' ; j++);
        output_compare[4] = '\0';
        output_compare[3] = o_value[j-1];
        output_compare[2] = o_value[j-2];
        output_compare[1] = o_value[j-3];
        output_compare[0] = o_value[j-4];
        printf("Output File: %s\n\n",o_value);

        if(strcmp(output_compare,".dat")==0){
            WriteFilebin(head,o_value);
        }else if(strcmp(output_compare,".csv")==0){
            WriteFile(head,FILE_HEADER,o_value);
        }else{
            ErrorMessage(head);
        }
    }else{
        ErrorMessage(head);
    }


    //liberta memoria
    freeAll(head);

    return 0;
}
