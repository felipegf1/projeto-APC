#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TAM_CPF 15
#define TAM_CNPJ 15
#define TAM_NOME 100

typedef struct{
    int dia, mes, ano;
}DATA; 

typedef struct{
    char cnpj[TAM_CNPJ];
    char nome_usina[TAM_NOME];
    DATA data_inicio_operacao;
    float potencia;
}USINA;
 
typedef struct{
   char cnpj[TAM_CNPJ];
   char id_consumidor[TAM_CPF];
   DATA data_inicio_contrato;
   float potencia_contratada; 
}CONTRATO;  

typedef struct{
    char identificacao[TAM_CPF];
    char nome_pessoa[TAM_NOME];
}CONSUMIDOR; 

int validadata(int dia, int mes, int ano);
int validacpf(char cpf[]);
int validacnpj(char cpf[]);
void cadastrausina();
void cadastraconsumidor();
void contrato();
void consultausina();
void consultaconsumidor();

int main()
{    
    int n;
    do{
        menu_opcoes();
        printf("Escolha uma opcao: \n");
        scanf("%d", &n);
        switch(n){
        case 1:
        cadastrausina();
        break;

        case 2:
        cadastraconsumidor();
        break;
        
        case 3:
        contrato();
        break;

        case 4:
        consultausina();
        break;

        case 5:
        consultaconsumidor();
        break;

        case 6:
        excluiusina();
        break;
        
        case 7:
        excluiconsumidor();
        break; 

        case 8:
        
        break;

        default:
        printf("Opcao invalida.");      
        }

    } while(n != 8); 
    

    return 0;
}

void limpar_tela() {      // funcao para limpar a tela
    #ifdef _WIN32
        system("cls");
    #elif __linux__ 
        system("clear");
    #endif         
}

void limpar_buffer() {  // funcao para limpar o buffer 
    fflush (stdin);
}

void menu_opcoes(){  // funcao para printar o menu na tela 
    limpar_tela();
    printf("------------------------------------------------------------------\n");
    printf("1 - Cadastrar Usina\n");
    printf("2 - Cadastrar Consumidor\n");
    printf("3 - Cadastrar Contrato entre Consumidor e Usina\n");
    printf("4 - Consultar Usina Cadastrada\n");
    printf("5 - Consultar Consumidor Cadastrado\n");
    printf("6 - Excluir Usina\n");
    printf("7 - Excluir Consumidor\n");
    printf("8 - Encerrar Programa\n");
    printf("------------------------------------------------------------------\n");
}

int validadata(int dia, int mes, int ano) {  // funcao para validar a data 
    if((dia >= 1 && dia <= 31) && (mes >= 1 && mes <= 12)) {
        if((dia == 29 && mes == 2) && (((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0))) { // Ano bissexto
            return 1;
        }
        if(dia <= 28 && mes == 2) {
            return 1;
        }
        if((dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) {
            return 1;
        }
        if((dia <=31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes ==8 || mes == 10 || mes == 12)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

int validacpf(char cpf[]) {   //funcao para validar o cpf
    int soma, soma2, resto, resto2, cpf0, cpf1, cpf2, cpf3, cpf4, cpf5, cpf6, cpf7, cpf8, cpf9, cpf10;
    cpf0 = cpf[0] - '0';
    cpf1 = cpf[1] - '0';
    cpf2 = cpf[2] - '0';
    cpf3 = cpf[3] - '0';
    cpf4 = cpf[4] - '0';
    cpf5 = cpf[5] - '0';
    cpf6 = cpf[6] - '0';
    cpf7 = cpf[7] - '0';
    cpf8 = cpf[8] - '0';
    cpf9 = cpf[9] - '0';
    cpf10 = cpf[10] - '0';
    soma = (cpf0*10) + (cpf1*9) + (cpf2*8) + (cpf3*7) + (cpf4*6) + (cpf5*5) + (cpf6*4) + (cpf7*3) + (cpf8*2);
    resto = (soma*10) % 11;
    soma2 = (cpf0*11) + (cpf1*10) + (cpf2*9) + (cpf3*8) + (cpf4*7) + (cpf5*6) + (cpf6*5) + (cpf7*4) + (cpf8*3) + (cpf9*2);
    resto2 = (soma2*10) % 11;
    if((cpf0 == cpf1) && (cpf1 == cpf2) && (cpf2 == cpf3) && (cpf3 == cpf4) && (cpf4 == cpf5) && (cpf5 == cpf6) && (cpf6 == cpf7) && (cpf7 == cpf8)
    && (cpf8 == cpf9) && (cpf9 == cpf10)) {
        return 0;
    } else if((resto == cpf9) && (resto2 == cpf10)) {
        return 1;
    } else {
        return 0;
    }    
}

int validacnpj(char cnpj[]) {  //funcao para validar o cnpj
  int sm, i, r, num, mult;
  char dig13, dig14;


  sm = 0; mult = 2;
  for (i=11; i>=0; i--) {
    num = cnpj[i] - 48;	
			
    sm = sm + (num * mult);
    mult = mult + 1;
    if (mult == 10)
       mult = 2;
  }
  r = sm % 11;
  if ((r == 0) || (r == 1))
     dig13 = '0';
  else
     dig13 = (11 - r) + 48;


  sm = 0; mult = 2;
  for (i=12; i>=0; i--) {
    num = cnpj[i] - 48;
    sm = sm + (num * mult);
    mult = mult + 1;
    if (mult == 10)
       mult = 2;
  }
  r = sm % 11;
  if ((r == 0) || (r == 1))
     dig14 = '0';
  else
     dig14 = (11 - r) + 48;


  if ((dig13 == cnpj[12]) && (dig14 == cnpj[13]))
     return 1;
  else
     return 0;
}

void cadastrausina(){  // funcao para cadastrar a usina 
    limpar_tela();
    FILE* arquivo;         
    USINA usn;
    char copiacnpj[TAM_CNPJ];
    arquivo = fopen("usinas.dat", "rb");   //abertura do arquivo e verificaçao se ele existe 
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo");
    }else{
        limpar_buffer();
        printf("Informe o CNPJ da Usina: (apenas numeros)\n");
        scanf("%s", usn.cnpj);
        strcpy(copiacnpj, usn.cnpj);
        if((validacnpj(usn.cnpj) == 0 ) && (strlen(usn.cnpj) != 15)){       // cadastro e validacao de dados 
            do{ 
                limpar_tela();
                limpar_buffer();
                printf("CNPJ invalido, informe um CNPJ valido: \n");
                scanf("%s", usn.cnpj);
                limpar_buffer();
                strcpy(copiacnpj, usn.cnpj);

            }while((validacnpj(usn.cnpj) == 0 ) && (strlen(usn.cnpj) != 15));
        }
        
        fclose(arquivo);
        arquivo = fopen("usinas.dat", "rb"); 
        if(arquivo == NULL){
        printf("Problemas na abertura do arquivo");
        fclose(arquivo);

        }else{
            while(fread(&usn, sizeof(USINA), 1, arquivo)){        // verificacao se a usina ja esta cadastrada
                if(strcmp(usn.cnpj, copiacnpj) == 0){
                    printf("Essa usina ja esta cadastrada.");                                        
                    limpar_buffer();
                    getchar();
                    return;
                }
            }
            strcpy(usn.cnpj, copiacnpj);
            fclose(arquivo);
        }                
           
        limpar_tela();
        limpar_buffer();
        printf("Informe o Nome da Usina: \n");
        scanf("%[^\n]s", usn.nome_usina);
        limpar_tela();
        limpar_buffer();
        printf("Informe a data de unicio de operacao da Usina: \n");
        printf("Informe o dia: ");
        scanf("%d", &usn.data_inicio_operacao.dia);
        limpar_buffer();
        printf("Informe o mes: ");
        scanf("%d", &usn.data_inicio_operacao.mes);
        limpar_buffer();
        printf("Informe o ano: ");
        scanf("%d", &usn.data_inicio_operacao.ano);                 // cadastro e validacao de dados 
        limpar_buffer();
        
        if(validadata(usn.data_inicio_operacao.dia, usn.data_inicio_operacao.mes, usn.data_inicio_operacao.ano) == 0){
            do{
                limpar_tela();
                printf("Data invalida, informe uma data valida: \n");
                printf("Informe o dia: ");
                scanf("%d", &usn.data_inicio_operacao.dia);
                limpar_buffer();
                printf("Informe o mes: ");
                scanf("%d", &usn.data_inicio_operacao.mes);
                limpar_buffer();
                printf("Informe o ano: ");
                scanf("%d", &usn.data_inicio_operacao.ano);
                limpar_tela();
            }while(validadata(usn.data_inicio_operacao.dia, usn.data_inicio_operacao.mes, usn.data_inicio_operacao.ano) == 0);

        }
        printf("Informe a potencia estimada da Usina: \n");
        scanf("%f", &usn.potencia);
        limpar_buffer();
        if(usn.potencia <= 0){
            do{
                printf("Potencia invalida, Informe uma potencia maior do que 0: \n");   // cadastro e validacao de dados 
                scanf("%f", &usn.potencia);  
            }while(usn.potencia <= 0);
        }
    }
    arquivo = fopen("usinas.dat", "ab");
    if(arquivo == NULL){
        arquivo = fopen("usinas.dat", "wb");     // escrita de dados no arquivo 
    }else{
        fwrite(&usn, sizeof(USINA), 1, arquivo);
    }
    fclose(arquivo);
}

void cadastraconsumidor(){  // funcao parar cadastrar o consumidor 
    limpar_tela();
    FILE* arquivo;
    CONSUMIDOR csmd;
    char copiaid[TAM_CPF];
    arquivo = fopen("consumidores.dat", "ab");   //abertura do arquivo e verificaçao se ele existe 
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo");
    }else{
        limpar_buffer();
        printf("Informe a identificacao do consumidor: (apenas numeros)\n");
        scanf("%s", csmd.identificacao);
        strcpy(copiaid, csmd.identificacao);
        limpar_buffer();
        if (((validacpf(csmd.identificacao)==0) && (validacnpj(csmd.identificacao) == 0)) && (strlen(csmd.identificacao) != 15)){
            limpar_tela();
            printf("ID Invalida, informe uma ID valida");   // cadastro e validacao de dados 
            getchar();
            return;
        }
        fclose(arquivo);
        arquivo = fopen("consumidores.dat", "rb"); 
        if(arquivo == NULL){
        printf("Problemas na abertura do arquivo");
        fclose(arquivo);

        }else{
            while(fread(&csmd, sizeof(CONSUMIDOR), 1, arquivo)){
                if(strcmp(csmd.identificacao, copiaid) == 0){
                    printf("Essa consumidor ja esta cadastrado.");   // verificacao se o consumidor ja esta cadastrado                                  
                    limpar_buffer();
                    getchar();
                    return;
                }
            }
            strcpy(csmd.identificacao, copiaid);
            fclose(arquivo);
        }                
        limpar_tela();
        printf("Informe o nome do consumidor: \n");       // cadastro de dados 
        scanf("%[^\n]s", csmd.nome_pessoa);
        limpar_buffer();
    }
    arquivo = fopen("consumidores.dat", "ab");
    if(arquivo == NULL){
        arquivo = fopen("consumidores.dat", "wb");
    }else{
        fwrite(&csmd, sizeof(CONSUMIDOR), 1, arquivo);
    }
    fclose(arquivo);
}

void contrato(){  // funcao para cadastrar o contrato 
    FILE* arquivo;
    CONTRATO cnt;
    USINA usn;
    CONSUMIDOR csmd;
    int contador, contador2, contador3, contadorloop;
    float potencia_atual, copiapotencia;
    contador = 0;
    contador2 = 0;
    contador3 = 0;
    contadorloop = 0;
    potencia_atual = 0;
    copiapotencia = 0;
    char copiacnpj[TAM_CNPJ];
    char copiacpf[TAM_CPF];
    arquivo = fopen("contratos.dat", "rb");
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo");
    }else{
        limpar_tela();
        limpar_buffer();    
        printf("Informe o CNPJ da usina: \n");     // cadastro de dados 
        scanf("%s", cnt.cnpj);
        limpar_buffer();
        strcpy(copiacnpj, cnt.cnpj);
        
        fclose(arquivo);        
        arquivo = fopen("usinas.dat", "rb"); 
        if(arquivo == NULL){
            printf("Problemas na abertura do arquivo");
            fclose(arquivo);

        }else{
            while(fread(&usn, sizeof(USINA), 1, arquivo)){
                if(strcmp(usn.cnpj, copiacnpj) == 0){
                    contador++;
                    copiapotencia = usn.potencia;                                       
                }                        
            }            
            strcpy(cnt.cnpj, copiacnpj);
            fclose(arquivo);
        }
        if(contador == 0){
            printf("Essa usina nao esta cadastrada, cadastre ou informe um CNPJ cadastrado");   // verificacao se a usina esta cadastrada
            limpar_buffer();
            getchar();
            return;
        }
        if(contador != 0){
            limpar_tela();
            printf("Informe a data de inicio do contrato: \n");
            printf("Informe o dia: ");
            scanf("%d", &cnt.data_inicio_contrato.dia);
            limpar_buffer();
            printf("Informe o mes: ");
            scanf("%d", &cnt.data_inicio_contrato.mes);       // cadastro da data 
            limpar_buffer();
            printf("Informe o ano: ");
            scanf("%d", &cnt.data_inicio_contrato.ano);
            limpar_buffer();
            if(cnt.data_inicio_contrato.ano < usn.data_inicio_operacao.ano){
                printf("Data Invalida, Informe uma Data Valida (data do contrato anterior a criacao da usina)\n");  // verificacao se a data nao é anterior a criaçao da usina 
                getchar();
                return;
            }
            if(cnt.data_inicio_contrato.ano == usn.data_inicio_operacao.ano){
                if(cnt.data_inicio_contrato.mes < usn.data_inicio_operacao.mes){
                    printf("Data Invalida, Informe uma Data Valida (data do contrato anterior a criacao da usina)\n");
                    getchar();
                    return;    
                }
                if(cnt.data_inicio_contrato.mes == usn.data_inicio_operacao.mes){
                    if(cnt.data_inicio_contrato.dia < usn.data_inicio_operacao.dia){
                       printf("Data Invalida, Informe uma Data Valida (data do contrato anterior a criacao da usina)\n");
                        getchar();
                        return; 
                    }
                }
            }
        }
        limpar_tela();
        limpar_buffer();
        printf("Informe a potencia contratada: \n");
        scanf("%f", &cnt.potencia_contratada);
        potencia_atual = copiapotencia - cnt.potencia_contratada;     // cadastro da potencia 
        limpar_buffer();
        arquivo = fopen("usinas.dat", "rb");
            while(fread(&usn, sizeof(USINA), 1, arquivo)){
                if((strcmp(usn.cnpj,copiacnpj) == 0 )&&(usn.potencia < cnt.potencia_contratada)){      // verificacao se a potencia contratada esta disponivel             
                    printf("Potencia indisponivel, Consulte a Potencia Disponivel da Usina \n");
                    getchar();
                    return;
                }
            }
        fclose(arquivo);
        
        limpar_buffer();
        limpar_tela();
        printf("Informe a ID do consumidor: \n");    // cadastro do consumidor 
        scanf("%s", cnt.id_consumidor);
        limpar_buffer();
        strcpy(copiacpf, cnt.id_consumidor);
        
        fclose(arquivo);        
        arquivo = fopen("consumidores.dat", "rb"); 
        if(arquivo == NULL){
            printf("Problemas na abertura do arquivo");
            fclose(arquivo);

        }else{
            while(fread(&csmd, sizeof(CONSUMIDOR), 1, arquivo)){
                if(strcmp(csmd.identificacao, copiacpf) == 0){
                    contador2++;                 
                }                                        
            }
            strcpy(csmd.identificacao, copiacpf);
            fclose(arquivo);
        }                
        if(contador2 == 0){
            printf("Esse consumidor nao esta cadastrado, cadastre ou informe um cadastrado");  // verificacao se o consumidor esta cadastrado                                       
            limpar_buffer();
            getchar();
            return;
        }            
    }
     
    arquivo = fopen("usinas.dat", "rb+");
        while(fread(&usn, sizeof(USINA), 1, arquivo)){
            contadorloop++;
            if(strcmp(usn.cnpj, cnt.cnpj) == 0){   // loop para atualizar o valor da potencia...  
                usn.potencia = potencia_atual;                
                contador3++;
                break;                
            }
        }
        if(contador3 == 1){
            contadorloop--;
            fseek(arquivo, contadorloop*sizeof(USINA), SEEK_SET);  // e para atualizar o arquivo com a nova potencia 
            fwrite(&usn, sizeof(USINA), 1, arquivo);
            
        }
    fclose(arquivo);



    arquivo = fopen("contratos.dat", "ab");
    if(arquivo == NULL){
        arquivo = fopen("contratos.dat", "wb");
    }else{
        fwrite(&cnt, sizeof(CONTRATO), 1, arquivo);  
    }
    fclose(arquivo);
}

void consultausina(){ // funcao para consultar a usina
    limpar_tela();
    FILE* arquivo;
    USINA usn;
    CONTRATO cnt;
    char cnpj[TAM_CNPJ];
    int contador, contcontrato;
    contador = 0;
    contcontrato = 0;
    
    arquivo = fopen("usinas.dat", "rb");
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo");                 //abertura do arquivo e verificaçao se ele existe 
    }else{ 
        limpar_buffer();
        printf("Informe o CNPJ da usina que deseja consultar: \n");
        scanf("%s", cnpj);
        limpar_buffer();

        while(fread(&usn, sizeof(USINA), 1, arquivo)){
            if(strcmp(cnpj, usn.cnpj) == 0){
                contador++;
                limpar_buffer();
                limpar_tela();
                printf("Nome da Usina: %s\n", usn.nome_usina);     // saida dos dados da usina 
                printf("CNPJ da Usina: %s\n", usn.cnpj);
                printf("Data de Inicio de Operacao: %d/%d/%d\n", usn.data_inicio_operacao.dia, usn.data_inicio_operacao.mes, usn.data_inicio_operacao.ano);
                printf("Potencia Disponivel: %.2f MW\n",usn.potencia);
                limpar_buffer();

            }                   
        }
    fclose(arquivo);

    arquivo = fopen("contratos.dat", "rb");
        while(fread(&cnt, sizeof(CONTRATO), 1, arquivo)){
            if(strcmp(cnpj, cnt.cnpj) == 0 ){
                contcontrato++;
                limpar_buffer();
                printf("\nConsumidores vinculados: \n");       // listagem dos contratos vinculados 
                printf("Identificacao: %s\n", cnt.id_consumidor);  
                
            }
        }
    }
    fclose(arquivo);
    if(contador == 0){
        limpar_tela();
        printf("Usina nao cadastrada no sistema.\n");  // condicional para mostrar que a usina nao esta no sistema 
        getchar();
        return;
    }
    if(contcontrato == 0){
        printf("\nNenhum contrato vinculado\n");  //  condicional caso nao tenha nenhum contrato vinculado  
        getchar();
        return;
    }
    limpar_buffer();
    printf("\nPressione qualquer tecla para voltar ao menu.\n"); // retorno para o menu 
    getchar();

}

void consultaconsumidor(){ // funcao para consultar o consumidor        
    limpar_tela();
    FILE* arquivo;
    CONSUMIDOR csmd;
    CONTRATO cnt;
    char cpf[TAM_CPF];
    int contador, contcontrato;
    contador = 0;
    contcontrato = 0;
    arquivo = fopen("consumidores.dat", "rb");            //abertura do arquivo e verificaçao se ele existe 
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo");
    }else{
        limpar_buffer();
        printf("Informe a ID do consumidor que deseja consultar: \n");  // leita da identificacao do consumidor 
        scanf("%s", cpf);
        limpar_buffer();

        while(fread(&csmd, sizeof(CONSUMIDOR), 1, arquivo)){
            if(strcmp(cpf, csmd.identificacao) == 0){
                limpar_tela();
                contador++;
                printf("Nome do Consumidor: %s\n", csmd.nome_pessoa);  // saida dos dados do consumidor 
                printf("ID do Consumidor: %s\n", csmd.identificacao);
                limpar_buffer();                            
            }           
        }
    fclose(arquivo);

    arquivo = fopen("contratos.dat", "rb");    
        while(fread(&cnt, sizeof(CONTRATO), 1, arquivo)){
            if(strcmp(cpf, cnt.id_consumidor) == 0){
                limpar_buffer();
                printf("\nUsina vinculada:\n");   // verificacao se o consumidor tem um contrato vinculado 
                printf("CNPJ: %s\n", cnt.cnpj);                
                contcontrato++;
                limpar_buffer();
                
    
            }                             
        }

    }
    fclose(arquivo);
    if(contcontrato == 0 && contador != 0){
        printf("\nNenhum contrato vinculado\n");  // condicional caso nao tenha nenhum contrato vinculado 
        limpar_buffer();
        getchar();
        return;

    }

    if(contador == 0){
        limpar_tela();
        printf("Consumidor nao cadastrado no sistema.\n"); // condicional caso a entrada seja uma identificacao nao cadastrada
        limpar_buffer();
        getchar();
        return;
    }
    printf("\nAperte qualquer tecla para voltar ao menu.\n");
    getchar();
}

void excluiusina(){ // funcao para excluir usina 
FILE* arquivo1;
FILE* arquivonovo;
FILE* arquivocnt;
FILE* arquivocnt2;
USINA usn;
CONTRATO cnt;
char cnpj[TAM_CNPJ];

arquivo1 = fopen("usinas.dat", "rb");
arquivonovo = fopen("usinasnovo.dat", "wb");

if(arquivo1 == NULL || arquivonovo == NULL ){              //abertura do arquivo e verificaçao se ele existe 
    printf("Problemas na abertura do arquivo");
}else{
    limpar_tela();
    limpar_buffer();
    printf("Informe o CNPJ da usina a ser exluida: \n");  // entrada do dado da usina a ser excluida
    scanf("%s", cnpj);
    limpar_buffer();

    while(fread(&usn, sizeof(USINA), 1, arquivo1)){
        if(strcmp(cnpj, usn.cnpj) != 0){
            fwrite(&usn, sizeof(USINA), 1, arquivonovo); // escrita dos dados restantes no arquivo novo 
        }
    }    
}
fclose(arquivo1);
fclose(arquivonovo);
remove("usinas.dat");
rename("usinasnovo.dat", "usinas.dat");  // funcoes para excluir o arquivo antigo e renomear o novo 

arquivocnt = fopen("contratos.dat", "rb");
arquivocnt2 = fopen("contratosnovo.dat", "wb");

if(arquivocnt == NULL || arquivocnt2 == NULL ){
    printf("Problemas na abertura do arquivo"); 
}else{
    while(fread(&cnt, sizeof(CONTRATO), 1, arquivocnt)){
        if(strcmp(cnpj, cnt.cnpj) != 0){
            fwrite(&cnt, sizeof(CONTRATO), 1, arquivocnt2); // escrita dos dados restantes dos contratos vinculados para o arquivo novo 
        }
    }  
}
fclose(arquivocnt);
fclose(arquivocnt2);
remove("contratos.dat");         // funcoes para excluir o arquivo antigo e renomear o novo 
rename("contratosnovo.dat", "contratos.dat");

printf("\nUsina excluida");

getchar();
}

void excluiconsumidor(){    // funcao para excluir o consumidor 
FILE* arquivo1;
FILE* arquivonovo;
FILE* arquivocnt;
FILE* arquivocnt2;
CONSUMIDOR csmd;
CONTRATO cnt;
char cpf[TAM_CPF];

arquivo1 = fopen("consumidores.dat", "rb");
arquivonovo = fopen("consumidoresnovo.dat", "wb");

if(arquivo1 == NULL || arquivonovo == NULL ){                 //abertura do arquivo e verificaçao se ele existe 
    printf("Problemas na abertura do arquivo");
}else{
    limpar_tela();
    limpar_buffer();
    printf("Informe a ID do consumidor a ser excluido: \n");  // entrada da identificacao do consumidor a ser excluido 
    scanf("%s", cpf);
    limpar_buffer();

    while(fread(&csmd, sizeof(CONSUMIDOR), 1, arquivo1)){
        if(strcmp(cpf, csmd.identificacao) != 0){
            fwrite(&csmd, sizeof(CONSUMIDOR), 1, arquivonovo);  // escrita dos dados restantes no arquivo novo 
        }
    }    
}

fclose(arquivo1);
fclose(arquivonovo);
remove("consumidores.dat");               // funcoes para excluir o arquivo antigo e renomear o novo 
rename("consumidoresnovo.dat", "consumidores.dat");

arquivocnt = fopen("contratos.dat", "rb");
arquivocnt2 = fopen("contratosnovo.dat", "wb");

if(arquivocnt == NULL || arquivocnt2 == NULL ){
    printf("Problemas na abertura do arquivo");
}else{
    while(fread(&cnt, sizeof(CONTRATO), 1, arquivocnt)){
        if(strcmp(cpf, cnt.id_consumidor) != 0){
            fwrite(&cnt, sizeof(CONTRATO), 1, arquivocnt2);   // escrita dos dados restantes dos contratos vinculados para o arquivo novo 
        }
    }  
}
fclose(arquivocnt);
fclose(arquivocnt2);
remove("contratos.dat");                 // funcoes para excluir o arquivo antigo e renomear o novo 
rename("contratosnovo.dat", "contratos.dat");

printf("\nConsumidor excluido");

getchar();
}