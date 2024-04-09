/******************************************************************************

                                PROJETO FINAL
                ..:: projeto Controle De Investimentos ::..

AUTORES
    Heloiza Martins da Silva RA: 2588412
    Lucas Crempe Fazan       RA: 2564505
    Mateus de Melo Camargo   RA: 2564548

DISCIPLINA E TURMA
    Engenhraia de Computação
    Algoritmos 1 - EC41A_C11

DOCENTE
    Francisco Pereira Júnior (Thesko)

INSTITUIÇÃO
    Universidade Tecnologica Federal do Paraná (UTFPR)
    Câmpus Cornélio Procóprio

BIBLIOTECAS UTILIZADAS
    <stdio.h>
        scanf
        printf
        fgets
        getchar
        sprintf
    
    <stdlib.h>
        qsort
        system
    
    <string.h>
        strlen
        strcmp
    
    <math.h>
        log10
        fabs
        labs
    
NOTAS
    As constantes:
        DATA_ATUAL_DIA,
        DATA_ATUAL_MES,
        DATA_ATUAL_ANO;
    servem como marcadores da data atual manuais, uma alternativa às funções contidas na bliblioteca <time.h>
    
    A função:
        converter_maiusculas();
    serve como alternativa às funções contidas na biblioteca <ctype.h> para manipulação de caracteres em strings
    
    Artigos que ajudaram a organizar o código e escrever os comentários que formam uma documentação simples:
        https://helpjuice.com/blog/software-documentation
        https://technicalwriterhq.com/documentation/software-documentation/how-to-write-software-documentation/
        https://guides.lib.berkeley.edu/how-to-write-good-documentation

*******************************************************************************/

//----- CONSTS/BIBLI -----//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CLIENTES      100
#define MAX_TRANSACOES    100
#define MAX_INVESTIMENTOS 30
#define MAX_LARGURA_TEXTO 50
#define MAX_LARGURA_CPF   15
#define MAX_LARGURA_ATIVO 01
#define DATA_ATUAL_ANO    2023
#define DATA_ATUAL_MES    06
#define DATA_ATUAL_DIA    27

//------------------------//

//----- STRUCTS -----//

/*
Struct Data
    int dia: O dia da data.
    int mes: O mês da data.
    int ano: O ano da data.

Struct Telefone
    int      ddd...: O código DDD do telefone.
    long int numero: O número do telefone.
    
Struct Cliente
    char     nome[MAX_LARGURA_TEXTO]: O nome do cliente.
    char     cpf[MAX_LARGURA_CPF]...: O CPF do cliente.
    Telefone fone...................: O telefone do cliente.
    Data     nascimento.............: A data de nascimento do cliente.

Struct Investimento
    char  emissor[MAX_LARGURA_TEXTO]: O emissor do investimento.
    char  ativo[MAX_LARGURA_ATIVO]..: O ativo do investimento.
    int   aplicacao_tipo............: O tipo de aplicação do investimento.
    float aplicacao_taxa............: A taxa de aplicação do investimento.

Struct Transacao
    int          id.............: O ID da transação (autoincremental).
    float        valor_aplicacao: O valor da aplicação.
    float        valor_resgate..: O valor do resgate (iniciar com 0.0).
    Cliente      cliente........: O cliente associado à transação.
    Investimento investimento...: O investimento associado à transação.
    Data         data_aplicacao.: A data de aplicação da transação (iniciar com 00/00/0000).
    Data         data_resgate...: A data de resgate da transação.
*/

typedef struct {
    int dia,
        mes,
        ano;
}Data;

typedef struct {
         int ddd;
    long int numero;
}Telefone;

typedef struct {
    char     nome[MAX_LARGURA_TEXTO],
             cpf [MAX_LARGURA_CPF];
    Telefone fone;
    Data     nascimento;
}Cliente;

typedef struct {
    char  emissor[MAX_LARGURA_TEXTO],
          ativo[MAX_LARGURA_ATIVO];
    int   aplicacao_tipo;
    float aplicacao_taxa;
}Investimento;

typedef struct {
    int          id; //autoincremental
    float        valor_aplicacao,
                 valor_resgate; //inicar com 0.0
    Cliente      cliente;
    Investimento investimento;
    Data         data_aplicacao; //iniciar com 00/00/0000
    Data         data_resgate;
}Transacao;

//-------------------//

//----- VARIAVEIS -----//

int          num_clientes        = 0,
             num_investimentos   = 0,
             num_transacoes      = 0,
             global_transacao_id = 0;
Cliente      clientes[MAX_CLIENTES];
Investimento investimentos[MAX_INVESTIMENTOS];
Transacao    transacoes[MAX_TRANSACOES];
//---------------------//

//----- FUNCOES -----//

/*
 * Centralizar Texto
 *
 * Criada pelo membro Mateus Camargo, importada de outro projeto, apenas o nome da função e dos parâmetros foram alterados para português)
 * Esta função centraliza uma string de texto em uma largura máxima definida.
 * Ela imprime a string na posição central, com margens iguais à esquerda e à direita.
 * A função também pode opcionalmente imprimir um separador acima e abaixo do texto.
 *
 * @param str   A string de texto a ser centralizada.
 * @param sep   Um valor inteiro indicando se um separador deve ser impresso:
 *                - 0: Não imprimir separador.
 *                - 1: Imprimir separador.
 */
void centralizar_texto(char str[MAX_LARGURA_TEXTO], int sep) {
    
    //separator 1
    if (sep == 1) {
        for (int i = 0; i < MAX_LARGURA_TEXTO; i ++) {printf("-");}
    }
    
    //get header string size
    int len = strlen(str);

    //set margins for header string
    int margin      = MAX_LARGURA_TEXTO - len;
    int margin_left = margin / 2;
    
    //print header string in center
    printf("\n");
    for(int i = 0; i < margin_left; i ++) {printf(" ");}
    printf("%s", str);
    printf("\n");
    
    //separator 2
    if (sep == 1) {
        for(int i = 0; i < MAX_LARGURA_TEXTO; i ++) {printf("-");}
    }
}

/*
 * Separador de Texto para Identação
 *
 * Esta função imprime um separador horizontal para ajudar na identação de texto.
 * O comprimento do separador é definido pela constante MAX_LARGURA_TEXTO.
 */
void separador() {
    for (int i = 0; i < MAX_LARGURA_TEXTO; i ++) {printf("-");}
}

/*
 * Converter Letras Minúsculas para Maiúsculas
 *
 * Esta função converte todas as letras minúsculas de uma string em letras maiúsculas.
 * Ela modifica a string fornecida diretamente, substituindo as letras minúsculas pelas correspondentes maiúsculas.
 *
 * @param str   A string de entrada que será modificada.
 */
void converter_maiusculas(char *str) {
    int i = 0;
    
    /*
    poderiamos usar a biblioteca <ctype.h> com a função toupper()
    */
    
    //enquanto o caractere não for "\0", diminuir o valor numérico dele em 32, seguindo a tabela ASCII
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
        i ++;
    }
}

/*
 * Validar Data
 *
 * Esta função verifica se uma data fornecida é válida. Ela realiza uma série de verificações
 * para garantir que a data esteja dentro de limites aceitáveis.
 *
 * @param data  A estrutura de dados "Data" contendo os valores do dia, mês e ano.
 * @return      Um valor inteiro indicando a validade da data:
 *                - 1: Data válida.
 *                - 0: Data inválida.
 */
int validar_data(Data data) {
    int dias_por_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    //VERIFICAR A DATA POR COMPLETO
    if (data.ano >= 1900 && data.ano <= DATA_ATUAL_ANO) {
        if (data.mes >= 1 && data.mes <= 12) {
            if (data.ano < DATA_ATUAL_ANO || (data.ano == DATA_ATUAL_ANO && data.mes <= DATA_ATUAL_MES)) {
                if (data.dia >= 1 && data.dia <= dias_por_mes[data.mes - 1]) {
                    
                    //verificar se o ano é bissexto
                    if (data.mes == 2 && data.dia == 29) {
                        if ((data.ano % 4 == 0 && data.ano % 100 != 0) || (data.ano % 400 == 0)) {
                            return 1;
                        }
                        else {
                            return 0;
                        }
                    }
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

/*
 * Validar Data Futura
 *
 * Esta função verifica se uma data fornecida representa uma data futura válida.
 * Ela realiza uma série de verificações para garantir que a data esteja dentro dos limites aceitáveis,
 * considerando apenas anos a partir de 1900 como futuros.
 *
 * @param data  A estrutura de dados "Data" contendo os valores do dia, mês e ano.
 * @return      Um valor inteiro indicando a validade da data futura:
 *                - 1: Data futura válida.
 *                - 0: Data futura inválida.
 */
int validar_data_futura(Data data) {
    int dias_por_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    //VERIFICAR A DATA POR COMPLETO
    if (data.ano >= 1900) {
        if (data.mes >= 1 && data.mes <= 12) {
            if (data.dia >= 1 && data.dia <= dias_por_mes[data.mes - 1]) {
                
                //verificar se o ano é bissexto
                if (data.mes == 2 && data.dia == 29) {
                    if ((data.ano % 4 == 0 && data.ano % 100 != 0) || (data.ano % 400 == 0)) {
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
                return 1;
            }
        }
    }
    
    return 0;
}

/*
 * Validar Telefone
 *
 * Esta função verifica se um número de telefone fornecido é válido.
 * Ela realiza uma série de verificações para garantir que o número de telefone
 * esteja dentro dos limites aceitáveis, considerando o código de área (DDD) e a quantidade de dígitos.
 *
 * @param telefone   A estrutura de dados "Telefone" contendo o DDD e o número de telefone.
 * @return           Um valor inteiro indicando a validade do número de telefone:
 *                     - 1: Número de telefone válido.
 *                     - 0: Número de telefone inválido.
 */
int validar_telefone(Telefone telefone) {
    
    //variáveis que guardam a quantidade de dígitos e o primeiro número respectivamente
    int digitos  = (int) log10(fabs(telefone.numero)) + 1;
    int primeiro = telefone.numero;
    
    //dividir por 10 até sobrar apenas um número (primeiro dígito)
    while (labs(primeiro >= 10)) {
        primeiro = primeiro / 10;
    }

    //checagem
    if(telefone.ddd >= 11 && telefone.ddd <= 91) {
        if (digitos == 8) {
            return 1;
        } else if (digitos == 9 && primeiro == 9) {
                return 1;
            } else {
                return 0;
            }
    } else {
        return 0;
    }
}

/*
 * Validar CPF
 *
 * Esta função verifica se um número de CPF fornecido é válido.
 * Ela realiza uma série de cálculos e verificações para garantir que o CPF
 * esteja dentro das regras de validação.
 *
 * @param cpf   A string contendo o número de CPF a ser validado.
 * @return      Um valor inteiro indicando a validade do CPF:
 *                - 1: CPF válido.
 *                - 0: CPF inválido.
 */
int validar_cpf(char cpf[MAX_LARGURA_CPF]) {
    int soma  = 0,
        resto = 0;
 
    for(int i = 0; i < 9; i ++) {
        soma += (cpf[i] - '0') * (10 - i);
    }

    resto = soma % 11;
   
    //condicao invalida 1
    if (resto < 2) {
        
        if (cpf[9] != '0') {
            return 0;
        }
    } else {
        if (cpf[9] - '0' != 11 - resto) {
            return 0;
        }
    }

    soma = 0;

    for (int i = 0; i < 10; i ++) {
        soma += (cpf[i] - '0') * (11 - i);
    }

    resto = soma % 11;
    
    //condicao invalida 2
    if (resto < 2) {
        if (cpf[10] != '0') {
            return 0;
        }
    } else {
        if (cpf[10] - '0' != 11 - resto) {
            return 0;
        }
    }

    return 1;
}

/*
 * Comparar Clientes
 *
 * Esta função é usada como um critério de comparação para ordenar clientes em uma lista.
 * Ela compara os nomes de dois clientes e retorna o resultado da comparação usando a função strcmp.
 *
 * @param cliente1   O ponteiro para o primeiro cliente a ser comparado.
 * @param cliente2   O ponteiro para o segundo cliente a ser comparado.
 * @return           Um valor inteiro indicando a ordem dos clientes:
 *                     - Negativo se o nome do cliente1 for menor que o nome do cliente2.
 *                     - Zero se os nomes dos clientes forem iguais.
 *                     - Positivo se o nome do cliente1 for maior que o nome do cliente2.
 */
int comparar_clientes(const void* cliente1, const void* cliente2) {
    Cliente* c1 = (Cliente*)cliente1;
    Cliente* c2 = (Cliente*)cliente2;
    return strcmp(c1 -> nome, c2 -> nome);
}

/*
 * Comparar CPF
 *
 * Esta função busca um cliente por CPF em uma lista de clientes.
 * Ela compara o CPF fornecido com os CPFs dos clientes na lista.
 *
 * @param cpf            A string contendo o CPF a ser comparado.
 * @return               Um valor inteiro indicando o resultado da comparação:
 *                         - 1: O CPF foi encontrado na lista de clientes.
 *                         - 0: O CPF não foi encontrado na lista de clientes.
 */
int comparar_cpf(char cpf[MAX_LARGURA_CPF]) {
    
    //buscar o cliente por CPF
    for (int i = 0; i < num_clientes; i ++) {
        if (strcmp(cpf, clientes[i].cpf) == 0) {
            return 1;
        }
    }
    
    return 0;
}

/*
 * Comparar Código
 *
 * Esta função busca um código de investimento em uma lista de investimentos.
 * Ela compara o código fornecido com os códigos dos investimentos na lista.
 *
 * @param codigo         O código de investimento a ser comparado.
 * @return               Um valor inteiro indicando o resultado da comparação:
 *                         - 1: O código foi encontrado na lista de investimentos.
 *                         - 0: O código não foi encontrado na lista de investimentos.
 */
int comparar_codigo(int codigo) {
    
    for (int i = 0; i < num_investimentos; i ++) {
        if (codigo == i) {
            return 1;
        }
    }
    
    return 0;
}

/*
 * Listar Clientes
 *
 * Esta função lista os clientes ordenados pelo nome.
 * Ela utiliza a função qsort para ordenar os clientes antes de apresentá-los.
 *
 * @param clientes         Um array de clientes a serem listados.
 * @param num_clientes     O número total de clientes na lista.
 */
void listar_clientes(Cliente* clientes, int num_clientes) {

    // Ordenar os clientes pelo nome usando a função qsort
    qsort(clientes, num_clientes, sizeof(Cliente), comparar_clientes);

    char titulo_listar_clientes[MAX_LARGURA_TEXTO] = "LISTA DE CLIENTES";
    centralizar_texto(titulo_listar_clientes, 1);

    //Apresentar a lista de clientes ordenados pelo nome
    for (int i = 0; i < num_clientes; i++) {
        
        printf("\n");
        printf("Nome......: %s",         clientes[i].nome);
        printf("Telefone..: (%02d) %ld\n", clientes[i].fone.ddd, clientes[i].fone.numero);
        printf("CPF.......: %s",         clientes[i].cpf);
        printf("Nascimento: %02d/%02d/%d\n", clientes[i].nascimento.dia, clientes[i].nascimento.mes, clientes[i].nascimento.ano);
    }
    
    printf("\n");
}

/*
 * Listar Montante
 *
 * Esta função calcula e lista o montante total por tipo de investimento.
 * Ela percorre as transações e acumula os valores de aplicação para cada tipo de investimento.
 * 
 * Em seguida, apresenta o montante por tipo de investimento.
 */
void listar_montante() {
    
    //titulo
    char titulo_montante[MAX_LARGURA_TEXTO] = "MONTANTE";
    centralizar_texto(titulo_montante, 1);
    
    printf("\n");
    
    //variaveis
    float montante_1 = 0,
          montante_2 = 0,
          montante_3 = 0;

    //somatória
    for (int i = 0; i < num_transacoes; i++) {
        if (transacoes[i].investimento.aplicacao_tipo == 1) {
            montante_1 += transacoes[i].valor_aplicacao; 
        }
        
        if (transacoes[i].investimento.aplicacao_tipo == 2) {
            montante_2 += transacoes[i].valor_aplicacao; 
        }
        
        if (transacoes[i].investimento.aplicacao_tipo == 3) {
            montante_3 += transacoes[i].valor_aplicacao; 
        }
    }
    
    //Apresentar o montante por tipo de investimento
    printf("LCI/LCA: \033[32mR$%.2f\033[0m\n", montante_1);
    printf("CDB....: \033[32mR$%.2f\033[0m\n", montante_2);
    printf("Fundos.: \033[32mR$%.2f\033[0m\n", montante_3);
    
    printf("\n");
}

/*
 * Listar Investimentos
 *
 * Esta função lista os investimentos disponíveis.
 * Ela percorre o array de investimentos e apresenta as informações de cada investimento.
 *
 * @param investimentos       Um array de investimentos a serem listados.
 * @param num_investimentos   O número total de investimentos na lista.
 */
void listar_investimentos(Investimento* investimentos, int num_investimentos) {

    char titulo_listar_investimentos[MAX_LARGURA_TEXTO] = "----- LISTA DE INVESTIMENTOS -----";
    centralizar_texto(titulo_listar_investimentos, 0);

    //Apresentar a lista de clientes ordenados pelo nome
    for (int i = 0; i < num_investimentos; i++) {
        
        printf("\n");
        
        printf("Codigo do investimento: %d\n", i);
        
        switch(investimentos[i].aplicacao_tipo) {
            case 1:printf("Tipo de investimento..: LCI/LCA\n");break;
            case 2:printf("Tipo de investimento..: CDB\n");    break;
            case 3:printf("Tipo de investimento..: Fundos\n"); break;
        }
        
        printf("Instituicao financeira: %s",   investimentos[i].emissor);
        printf("Taxa de rendimentos...: %.1f\n", investimentos[i].aplicacao_taxa);
        
        if (investimentos[i].ativo[0] = 'S') {
            printf("Ativo.................: SIM\n");
        } else if (investimentos[i].ativo[0] = 'N') {
            printf("Ativo.................: NAO\n");
        } 
        
        char titulo_listar_investimentos_2[MAX_LARGURA_TEXTO] = "-----";
        centralizar_texto(titulo_listar_investimentos_2, 0);
        
        printf("\n");
    }
}

/*
 * Apresentar Cliente
 *
 * Esta função busca e apresenta as informações de um cliente pelo seu CPF.
 * Ela percorre o array de clientes e procura por um cliente que tenha o CPF correspondente.
 * Se encontrar, imprime as informações do cliente.
 *
 * @param cpf   O CPF do cliente a ser apresentado.
 * @return      Retorna 1 se o cliente foi encontrado e apresentado, caso contrário retorna 0.
 */
int apresentar_cliente(char cpf[MAX_LARGURA_CPF]) {

    int j = 0;
    
    //buscar o cliente por CPF
    for (int i = 0; i < num_clientes; i ++) {
        if (strcmp(cpf, clientes[i].cpf) == 0) {
            //imprimir titulo
            char titulo_cliente_cadastrado[MAX_LARGURA_TEXTO] = "----- CLIENTE CADASTRADO -----";
            centralizar_texto(titulo_cliente_cadastrado, 0);
            
            //imprimir cliente
            printf("\n");
            printf("Nome....: %s",           clientes[i].nome);
            printf("Telefone: (%02d) %ld\n", clientes[i].fone.ddd, clientes[i].fone.numero);
        }
    }
    
    if (j <= 0) {
        //caso cliente não exista
        return 0;
    }
    
    printf("\n");

}

/*
 * Apresentar Extrato
 *
 * Esta função busca e apresenta o extrato de investimentos de um cliente pelo seu CPF.
 * Ela percorre o array de clientes e procura por um cliente que tenha o CPF correspondente.
 * Se encontrar, imprime as informações do cliente e seus investimentos.
 *
 * @param cpf   O CPF do cliente cujo extrato deve ser apresentado.
 */
void apresentar_extrato(char cpf[MAX_LARGURA_CPF]) {

    int j = 0;
    
    //buscar o cliente por CPF
    for (int i = 0; i < num_clientes; i ++) {
        if (strcmp(cpf, clientes[i].cpf) == 0) {
            j ++;
            //imprimir titulo
            char titulo_cliente_cadastrado[MAX_LARGURA_TEXTO] = "----- Cliente cadastrado -----";
            centralizar_texto(titulo_cliente_cadastrado, 0);
            printf("\n");
            
            //imprimir cliente
            printf("Nome....: %s",           clientes[i].nome);
            printf("Telefone: (%02d) %ld\n", clientes[i].fone.ddd, clientes[i].fone.numero);
            
            //imprimir titulo
            char titulo_cliente_cadastrado_2[MAX_LARGURA_TEXTO] = "----- Investimentos cadastrados -----";
            centralizar_texto(titulo_cliente_cadastrado_2, 0);
            printf("\n");
            
            for (int i = 0; i < num_transacoes; i ++) {
                if (strcmp(cpf, transacoes[i].cliente.cpf) == 0) {
                    
                    printf("ID da transacao..: %d\n",       transacoes[i].id);
                    printf("Instituicao......: %s",         transacoes[i].investimento.emissor);
                    printf("Valor investido..: \033[32mR$%.2f\033[0m\n",   transacoes[i].valor_aplicacao);
                    printf("Data de aplicacao: %02d/%02d/%d\n", transacoes[i].data_aplicacao.dia, transacoes[i].data_aplicacao.mes, transacoes[i].data_aplicacao.ano);
                    printf("Data de resgate..: %02d/%02d/%d\n", transacoes[i].data_resgate.dia,   transacoes[i].data_resgate.mes,   transacoes[i].data_resgate.ano);
                    
                    printf("Valor Esperado...: \033[32mR$%.2f\033[0m\n", transacoes[i].valor_resgate);
                    
                    printf("\n");
                }
            }
        }
    }
    
    if (j <= 0) {
        //caso cliente não exista
        printf("\n");
        printf("ERRO: CLIENTE NAO CADASTRADO\n");
    }
    
    printf("\n");

}

//-------------------// 

//----- FUNCAO PRINCIPAL -----//

/*
 * Função Principal
 *
 * Esta função aplica todo o código anterrior.
 * Ela apresenta um menu ao usuario, com 6 opções + opção de sair.
 */
int main()         {
    
    //Criação de variáveis das structs
    int seletor_menu = 0;

    do {
        char titulo_titulo[MAX_LARGURA_TEXTO] = "CONTROLE DE INVESTIMENTOS";
        centralizar_texto(titulo_titulo, 1);
        
        char titulo_investimento[MAX_LARGURA_TEXTO] = "Selecione o que deseja fazer:\n";
        centralizar_texto(titulo_investimento, 0);
        
        printf("Digite '1' para Cadastrar Clientes\n");
        printf("Digite '2' para Cadastrar Investimentos\n");
        printf("Digite '3' para Fazer Aplicacoes/Transacoes\n");
        printf("Digite '4' para Extrato do cliente\n");
        printf("Digite '5' para Montante de investimentos\n");
        printf("Digite '6' para Lista de clientes ordenados\n");
        printf("Digite '0' para Sair\n");
        
        printf("\n");
        
        scanf("%d", &seletor_menu);
        getchar();
        
        printf("\n");
        
        switch(seletor_menu) {
            
            //cadastrar clientes
            case 1:
                system("clear");
                if (num_clientes <= MAX_CLIENTES) {
                    Cliente novo_cliente;

                    //titulo (identação)
                    char titulo_cadastro_clientes[MAX_LARGURA_TEXTO] = "CADASTRO DE CLIENTES";
                    centralizar_texto(titulo_cadastro_clientes, 1);
                    printf("\n");
                    
                    //receber o nome do cliente
                    int i = 0;
                    do {
                        if (i <= 0) {
                            printf("Digite o nome completo:\n");
                            i ++;
                        } else {printf("\033[31mNome invalido, digite novamente:\033[0m\n");}
                        
                        fgets(novo_cliente.nome, MAX_LARGURA_TEXTO, stdin);
                        //converter o nome para letras maíusculas
                        converter_maiusculas(novo_cliente.nome);
                        printf("\n");
                    } while (novo_cliente.nome[0] == '\0' || novo_cliente.nome[0] == '\n');           
                    
                    //receber o nascimento
                    i = 0;
                    do {
                        if (i <= 0) {
                            printf("Digite a data de nascimento em dd/mm/aaaa\n");
                            i ++;
                        } else {printf("\033[31mData invalida, digite novamente:\033[0m\n");}
                        
                        scanf("%d/%d/%d", &novo_cliente.nascimento.dia, &novo_cliente.nascimento.mes, &novo_cliente.nascimento.ano);
                        getchar();
                        printf("\n");  
                    } while (validar_data(novo_cliente.nascimento) != 1);
                    
                    //receber o telefone
                    i = 0;
                    do {
                        if (i <= 0) {
                            printf("Digite o DDD e o numero de telefone em XX-XXXXXXXXX\n");
                            i ++;
                        } else {printf("\033[31mDDD ou numero invalidos, digite novamente:\033[0m\n");}
                        
                        scanf("%d-%ld", &novo_cliente.fone.ddd, &novo_cliente.fone.numero);
                        getchar();
                        printf("\n");
                    } while (validar_telefone(novo_cliente.fone) != 1);
                    
                    //receber o cpf
                    i = 0;
                    do {
                        if (i <= 0) {
                            printf("Digite o CPF sem espaços nem simbolos:\n");
                            i ++;
                        } else {printf("\033[31mCPF invalido, digite novamente:\033[0m\n");}
                        
                        fgets(novo_cliente.cpf, MAX_LARGURA_CPF, stdin);
                        printf("\n");
                    } while (validar_cpf(novo_cliente.cpf) != 1);
                    
                    printf("\n");
                    printf("\033[32m***Novo cliente cadastrado com sucesso\033[0m\n");
                        
                    clientes[num_clientes] = novo_cliente;
                    num_clientes ++;
                    
                } else {
                    printf("\n");
                    printf("\033[31m***ERRO: LIMITE DE CLIENTES ATINGIDO\033[0m\n");
                }
            break;
            
            //cadastrar investimentos
            case 2:
                system("clear");
                if (num_investimentos <= MAX_INVESTIMENTOS) {
                    Investimento novo_investimento;
                    
                    //PREENCHER DADOS
                
                    //titulo (identação)
                    char titulo_cadastro_investimento[MAX_LARGURA_TEXTO] = "CADASTRO DE INVESTIMENTOS";
                    centralizar_texto(titulo_cadastro_investimento, 1);
                    
                    //receber tipo de aplicacao
                    char titulo_investimento_tipo[MAX_LARGURA_TEXTO] = "Tipo de aplicacao:";
                    centralizar_texto(titulo_investimento_tipo, 0);
                    printf("\n");
                    
                    //receber o tipo de aplicacao
                    int i = 0;
                    do {
                        if (i <= 0) {
                            printf("Digite '1' para LCI/LCA\n");
                            printf("Digite '2' para CDB\n");
                            printf("Digite '3' para Fundos\n");
                            i ++;
                        } else {printf("\033[31mTipo de aplicacao invalida, digite novamente:\033[0m\n");}
                        
                        scanf("%d", &novo_investimento.aplicacao_tipo);
                        getchar();
                        printf("\n");  
                    } while (novo_investimento.aplicacao_tipo != 1 && novo_investimento.aplicacao_tipo != 2 && novo_investimento.aplicacao_tipo != 3);
                    
                    //receber a instituição financeira
                    i = 0;
                    do {
                        if (i <= 0) {
                            printf("Informe a instituição financeira:\n");
                            i ++;
                        } else {printf("\033[31mNome invalido, digite novamente:\033[0m\n");}
                        
                        fgets(novo_investimento.emissor, MAX_LARGURA_TEXTO, stdin);
                        //converter o nome para letras maíusculas
                        converter_maiusculas(novo_investimento.emissor);
                        printf("\n");
                    } while (novo_investimento.emissor[0] == '\0' || novo_investimento.emissor[0] == '\n');
                    
                    //receber a taxa
                    i = 0;
                    do {
                        if (i <= 0) {
                            printf("Informe a taxa anual de rendimentos:\n");
                            i ++;
                        } else {printf("\033[31mTaxa invalida, digite novamente:\033[0m\n");}
                        
                        scanf("%f", &novo_investimento.aplicacao_taxa);
                        getchar();
                        printf("\n");  
                    } while (novo_investimento.aplicacao_taxa <= 0);
                    
                    //receber informação sobre o ativo
                    i = 0;
                    do {
                        if (i <= 0) {
                            printf("Investimento ativo? [S]im ou [N]ão:\n");
                            i ++;
                        } else {printf("\033[31mCaractere invalido, digite novamente:\033[0m\n");}
                        
                        scanf("%s", novo_investimento.ativo);
                        //converter para letras maiusculas
                        converter_maiusculas(novo_investimento.ativo);
                        getchar();
                        printf("\n");
                    } while (novo_investimento.ativo[0] != 'S' && novo_investimento.ativo[0] != 'N');

                    printf("\n");
                    printf("\033[32m***Novo investimento cadastrado com sucesso\033[0m\n");     
                    
                    investimentos[num_investimentos] = novo_investimento;
                    num_investimentos++;
                } else {
                    printf("\n");
                    printf("\033[31m***ERRO: LIMITE DE INVESTIMENTOS ATINGIDO\033[0m\n");
                }

            break;
            
            //fazer aplicações/transações
            case 3:
                system("clear");
                if (num_transacoes <= MAX_TRANSACOES) {
                    if (num_clientes > 0 && num_investimentos > 0) {
                        Transacao nova_transacao;
                        int codigo                   = -4;
                        nova_transacao.valor_resgate = 0;
                        char cpf_busca[MAX_LARGURA_CPF];
                        int cliente_cadastrado = 0;
                        
                        //PREENCHER DADOS
                        
                        //titulo (identação)
                        char titulo_cadastro_transacao[MAX_LARGURA_TEXTO] = "CADASTRO DE TRANSACOES";
                        centralizar_texto(titulo_cadastro_transacao, 1);
                        
                        //buscar cliente
                        int i = 0;
                        do {
                            if (i <= 0) {
                                char titulo_cadastro_transacao_2[MAX_LARGURA_TEXTO] = "Busca por CPF";
                                centralizar_texto(titulo_cadastro_transacao_2, 0);
                                printf("\n");
                                printf("Digite o CPF sem espaços nem simbolos:\n");
                                i ++;
                            } else {printf("\033[31mCPF nao cadastrado, digite novamente:\033[0m\n");}
                            
                            //recebe o cpf e joga na funcao
                            fgets(cpf_busca, MAX_LARGURA_CPF, stdin);
                            
                            //cadastra na transação o cliente correspondente ao CPF recebido
                            for (int i = 0; i < num_clientes; i ++) {
                                if (strcmp(cpf_busca, clientes[i].cpf) == 0) {
                                    nova_transacao.cliente = clientes[i];
                                    apresentar_cliente(cpf_busca);
                                }
                            }
                            printf("\n");
                    } while (comparar_cpf(cpf_busca) != 1);
                        
                        //subtitulo
                        char titulo_cadastro_transacao_3[MAX_LARGURA_TEXTO];
                        sprintf(titulo_cadastro_transacao_3, "Transaçao %d", num_transacoes);
                        
                        //apresenta os investimentos disponíveis
                        listar_investimentos(investimentos, num_investimentos);
                        
                        //recebe o codigo do investimento
                        i = 0;
                        do {
                            if (i <= 0) {
                                printf("Digite o codigo corresponde ao investimento:\n");
                                i ++;
                            } else {printf("\033[31mCodigo nao cadastrado, digite novamente:\033[0m\n");}
                            
                            scanf("%d", &codigo);
                            getchar();
                            printf("\n");
                        } while (comparar_codigo(codigo) != 1);
                        
                        //cadastra na transação o investimento correspondente ao codigo recebido
                        for (int i = 0; i < num_investimentos; i ++) {
                            if (codigo == i) {
                                nova_transacao.investimento = investimentos[i];
                            }
                        }
                        
                        //recebe o valor
                        i = 0;
                        do {
                            if (i <= 0) {
                                printf("Digite o valor do investimento em R$:\n");
                                i ++;
                            } else {printf("\033[31mValor inválido, digite novamente:\033[0m\n");}
                            
                            scanf("%f", &nova_transacao.valor_aplicacao);
                            getchar();
                            printf("\n");
                        } while (nova_transacao.valor_aplicacao <= 0);
                        
                        //recebe a data de aplicacao
                        i = 0;
                        do {
                            if (i <= 0) {
                                printf("Digite a data da aplicacao em dd/mm/aaaa:\n");
                                i ++;
                            } else {printf("\033[31mData invalida, digite novamente:\033[0m\n");}
                            
                            scanf("%d/%d/%d", &nova_transacao.data_aplicacao.dia, &nova_transacao.data_aplicacao.mes, &nova_transacao.data_aplicacao.ano);
                            getchar();
                            printf("\n");
                        } while (validar_data(nova_transacao.data_aplicacao) != 1);

                        //recebe a data de resgate
                        i = 0;
                        do {
                            if (i <= 0) {
                                printf("Digite a data esperada do resgate em dd/mm/aaaa:\n");
                                i ++;
                            } else {printf("\033[31mData invalida, digite novamente:\033[0m\n");}
                            
                            scanf("%d/%d/%d", &nova_transacao.data_resgate.dia, &nova_transacao.data_resgate.mes, &nova_transacao.data_resgate.ano);
                            getchar();
                            printf("\n");
                        } while (validar_data_futura(nova_transacao.data_resgate) != 1);

                        printf("\033[32m***Novo investimento cadastrado com sucesso\033[0m\n");
                        //printf("Cliente associado.....: %s",     nova_transacao.cliente.nome);
                        //printf("Investimento associado: %d, %s", codigo, nova_transacao.investimento.emissor);
                        printf("\n");
                        
                        /*
                         * Calcula a taxa de Imposto de Renda de Pessoa Física (IRPF) com base no tempo de investimento.
                         *
                         * @param tempo_investido O tempo de investimento em dias.
                         * @return A taxa de IRPF correspondente ao tempo de investimento.
                         */
                        float calcular_imposto_irpf(float tempo_investido) {
                            if (tempo_investido <= 180) {
                                return 22.5;
                            } else if (tempo_investido <= 360) {
                                return 20;
                            } else if (tempo_investido <= 720) {
                                return 17.5;
                            } else {
                                return 15;
                            }
                        } 
                        
                        /*
                         * Calcula o valor de resgate de um investimento com base nas datas de aplicação e resgate,
                         * valor investido, taxa de rendimento e tipo de investimento.
                         *
                         * @param data_aplicacao     A data de aplicação do investimento.
                         * @param data_resgate       A data de resgate do investimento.
                         * @param valor_investido    O valor inicialmente investido.
                         * @param taxa_rendimento    A taxa de rendimento do investimento.
                         * @param tipo_investimento  O tipo de investimento (1: LCI/LCA, 2: CDB, 3: Fundos).
                         * @return O valor de resgate do investimento.
                         */
                        float calcular_valor_resgate(Data data_aplicacao, Data data_resgate, float valor_investido, float taxa_rendimento, int tipo_investimento) {
                            
                            float dias_investidos = 0;
                        
                            dias_investidos += (data_resgate.dia - data_aplicacao.dia);
                            dias_investidos += (data_resgate.mes - data_aplicacao.mes) * 30;
                            dias_investidos += (data_resgate.ano - data_aplicacao.ano) * 360;
                        
                            float tempo_investido_anos = dias_investidos / 360;
                            
                            // Cálculo do valor do resgate
                            float valor_resgate = valor_investido;
                        
                            if (tipo_investimento == 1) {
                                // LCI/LCA isento de imposto
                                valor_resgate += valor_investido * (taxa_rendimento / 100) * tempo_investido_anos;
                            } else if (tipo_investimento == 2) {
                                // CDB com imposto de renda
                                float lucro               = valor_investido * (taxa_rendimento / 100) * tempo_investido_anos;
                                float taxa_irpf           = calcular_imposto_irpf(dias_investidos);
                                float imposto             = lucro * (taxa_irpf / 100);
                                valor_resgate            += lucro - imposto;
                            } else if (tipo_investimento == 3) {
                                // Fundos com taxa de administração e imposto de renda
                                float lucro               = valor_investido * (taxa_rendimento / 100) * tempo_investido_anos;
                                float taxa_administracao  = lucro / 100;
                                float taxa_irpf           = calcular_imposto_irpf(dias_investidos);
                                float imposto             = lucro * (taxa_irpf / 100);
                                valor_resgate            += lucro - (taxa_administracao + imposto);
                            }
                        
                            return valor_resgate;
                        }
                        
                        //gera o ID da transação
                        global_transacao_id ++;
                        nova_transacao.id = global_transacao_id;
                        
                        //calcula o valor de resgate
                        nova_transacao.valor_resgate = calcular_valor_resgate(nova_transacao.data_aplicacao, nova_transacao.data_resgate,
                        nova_transacao.valor_aplicacao, nova_transacao.investimento.aplicacao_taxa, nova_transacao.investimento.aplicacao_tipo);
                        
                        transacoes[num_transacoes] = nova_transacao;
                        num_transacoes++;
                    } else {
                        printf("\n");
                        printf("\033[31m***ERRO: NENHUM CLIENTE OU INVESTIMENTO CADASTRADOS\033[0m\n");                          
                    }
                } else {
                    printf("\n");
                    printf("\033[31m***ERRO: LIMITE DE TRANSACOES ATINGIDO\033[0m\n");                    
                }
            break;
            
            //extrato do cliente
            case 4:
                system("clear");
                if (num_clientes > 0 && num_transacoes > 0) {
                    char cpf_busca[MAX_LARGURA_CPF];
                    
                        //buscar cliente
                        int i = 0;
                        do {
                            if (i <= 0) {
                                char titulo_busca[MAX_LARGURA_TEXTO] = "BUSCA POR CPF";
                                centralizar_texto(titulo_busca, 1);
                                printf("\n");
                                printf("Digite o CPF sem espaços nem simbolos:\n");
                                i ++;
                            } else {printf("\033[31mCPF nao cadastrado, digite novamente:\033[0m\n");}
                            
                            //recebe o cpf e joga na funcao
                            fgets(cpf_busca, MAX_LARGURA_CPF, stdin);
                            
                            //cadastra na transação o cliente correspondente ao CPF recebido
                            for (int i = 0; i < num_clientes; i ++) {
                                if (strcmp(cpf_busca, clientes[i].cpf) == 0) {
                                    apresentar_extrato(cpf_busca);
                                }
                            }
                        } while (comparar_cpf(cpf_busca) != 1);                
                } else {
                    printf("\n");
                    printf("\033[31m***ERRO: NENHUMA TRANSAÇÃO CADASTRADA\033[0m\n");             
                }
            break;
            
            //montante de investimentos
            case 5:
                system("clear");
                if (num_investimentos > 0) {
                    listar_montante();
                } else {
                    printf("\n");
                    printf("\033[31m***ERRO: NENHUM INVESTIMENTO CADASTRADO\033[0m\n");                       
                }            
            break;
            
            //lista de clientes ordenados
            case 6:
                system("clear");
                if (num_clientes > 0) {
                    listar_clientes(clientes, num_clientes);
                } else {
                    printf("\n");
                    printf("\033[31m***ERRO: NENHUM CLIENTE CADASTRADO\033[0m\n");                       
                }
            break;
        }

    } while (seletor_menu != 0);
    
    return 0;
}

//----------------------------//
