/******************************************************************************

                           PROJETO PESSOAL DE FIXAÇÃO EM C
                ..:: controle de pedidos de restaurante/cantina ::..

AUTOR
    Mateus de Melo Camargo
    https://github.com/mateusmcamargo

DATA 
    06/06/2023
    
NOTAS

*******************************************************************************/

//Libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h> 

//Constants
#define  PRODUCT_NUMBER    12
#define  ORDER_SIZE        30
#define  IDENT_SIZE        3
#define  MAX_WIDTH         33
#define  NOONE             -4
#define  PRODUCT_ALIGN_BIG 6
#define  PRODUCT_ALIGN_SMA 7

//order number (will be increased by one at the end of the main function)
int order_number = 1;

//value of order and day
float value_total = 0, value_total_of_day = 0;

float value_array[PRODUCT_NUMBER]             =         {
0,                  //0
3,                  //1  - Pao de queijo
6,                  //2  - Achocolatado
2,                  //3  - Pacoca
5,                  //4  - Coca-cola lata
8,                  //5  - Coca-cola 600
12,                 //6  - Coca-cola 2lt
12.5,               //7  - Suco natural
6.5,                //8  - Salgado assado
6.5,                //9  - Salgado frito
8,                  //10 - Ruffles media
20,               //11 - Refeicao
};

//PRODUCT_NUMBER = number of itens + 1. eg: for 10 itens, PRODUCT_NUMBER = 11
char product_array[PRODUCT_NUMBER][MAX_WIDTH] =         {
" "             ,   //0
"Pao de queijo" ,   //1  - Pão de queijo
"Achocolatado"  ,   //2  - Achocolatado
"Pacoca"        ,   //3  - Pacoca
"Coca-cola lata",   //4  - Coca-cola lata
"Coca-cola 600" ,   //5  - Coca-cola 600
"Coca-cola 2lt" ,   //6  - Coca-cola 2lt
"Suco natural"  ,   //7  - Suco natural
"Salgado assado",   //8  - Salgado assado
"Salgado frito" ,   //9  - Salgado frito
"Ruffles media" ,   //10 - Ruffles media
"Refeicao"      ,   //11 - Refeicao
};

//ident
void printf_ident(const char* format, ...)              {
    for(int i = 0; i < IDENT_SIZE; i ++) {printf(" ");}
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

//separator
void separator()                                        {
    for(int i = 0; i < IDENT_SIZE; i ++) {printf(" ");}
    for (int i = 0; i < MAX_WIDTH; i ++) {printf("-");}
}

//centralize text
void center(char str[MAX_WIDTH], int sep)               {
    
    //separator 1
    if (sep == 1) {
        for(int i = 0; i < IDENT_SIZE; i ++) {printf(" ");}
        for (int i = 0; i < MAX_WIDTH; i ++) {printf("-");}
    }
    
    //get header string size
    int len = strlen(str);

    //set margins for header string
    int margin      = MAX_WIDTH - len;
    int margin_left = margin / 2;
    
    //print header string in center
    printf("\n");
    for(int i = 0; i < margin_left; i ++) {printf(" ");}
    for(int i = 0; i < IDENT_SIZE; i ++) {printf(" ");}
    printf("%s", str);
    printf("\n");
    
    //separator 2
    if (sep == 1) {
        for(int i = 0; i < IDENT_SIZE; i ++) {printf(" ");}
        for(int i = 0; i < MAX_WIDTH; i ++) {printf("-");}
    }
}

//ident to a certain distance to the right
void align_right(char str[MAX_WIDTH], int margin_right) {
    
    //get string size
    int len = strlen(str);
    
    //print string aligned
    for(int i = 0; i < margin_right; i ++) {printf(" ");}
    printf("%s", str);
    //printf("\n");
}

//new line
void nl(int quant)                                      {
    for(int i = 0; i < quant; i ++) {printf("\n");}
}

//clear last line of input
void clear_line()                                       {
    //move cursor to last line
    printf("\033[A");
    //delete the line
    printf("\033[K");
}

//post shitf data print
int end_of_shift()                                      {

    system("clear");
    nl(1);
    
    //header
    char header_end[MAX_WIDTH] = "FIM DE EXPEDIENTE";
    center(header_end, 1);
    
    nl(2);
    
    //data
    printf_ident("Numero de pedidos: %d\n", order_number);
    printf_ident("Faturamento total: R$ %.2f\n", value_total_of_day);
   
}

//main function
int main()                                              {

//----- PRINT PRODUCTS -----//

    char input_header[MAX_WIDTH] = "NUTREBEM";
    center(input_header, 1);
    
    nl(2);

    //printf_ident("Produtos cadastrados:\n");
    int j = 0;
    for (int i = 0; i < PRODUCT_NUMBER; i ++) {
        //print product code
        if (j > 0) {
            if (j <= 9) {
                printf_ident("|Cod %d.: ", j);
            } else {
                printf_ident("|Cod %d: ", j);
            }
            //print product name
            printf("%14s|\n", product_array[i]);
        }
            
        j ++;
    }
    
    nl(2);
    
    printf_ident("*Digite o código de cada produto\n");
    printf_ident("consumido seguido de 'ENTER'\n\n");
    printf_ident("*Digite '0' para terminar");
    
    nl(2);

    //----- END OF PRINT PRODUCTS -----//
    
    
    
    
    //----- GET ORDER DATA -----//

    int loop_var                 = 0,
        order                    = NOONE,
        order_array[ORDER_SIZE]  = {0},
        order_size_control       = 0;

    memset(order_array, 0, sizeof(order_array));

    //order input loop
    while (loop_var < ORDER_SIZE) {
        for(int i = 0; i < IDENT_SIZE; i ++) {printf(" ");}
        scanf("%d", &order);
        if (order == 0) {break;}
        order_array[loop_var] = order;
        loop_var ++;
        order_size_control ++;
        if (order < PRODUCT_NUMBER) {
            printf_ident("'%s' adicionado", product_array[order]);
        } else {
            printf_ident("Produto nao existente");
        }
        nl(2);
    } system("clear");

    //----- END OF GET ORDER DATA -----//
    
    
    
    
    //----- REAL TIME -----//

    setenv("TZ", "America/Sao_Paulo", 1);
    tzset();
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    
    //----- END OF REAL TIME -----//
    
    
    
    
    //----- HEADER -----//
    
    char header_header[MAX_WIDTH] = "CUPOM NAO FISCAL - NUTREBEM";
    center(header_header, 1);

    //----- END OF HEADER -----//
   
   
    nl(2);
    
    
    //----- DATA -----//
    
    //date and hour
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M", timeinfo);
    
    printf_ident("Data....: %s\n", buffer);           //date and hour
    printf_ident("Cantina.: NUTREBEM Fundamental\n"); //shop
    printf_ident("Terminal: TEST_LAB22_01");          //terminal
    
    //----- END OF DATA -----//
    
    
    nl(2);
    
    
    //----- ORDER -----//
    
    //header
    char order_header[MAX_WIDTH];
    char consumption [MAX_WIDTH] = "Consumo:";
    
    //convert 'int' to 'string'
    sprintf(order_header, "*** Pedido %d ***", order_number);
    
    center(order_header, 1);

    nl(1);

    center(consumption, 0);
    
    nl(1);
    
    printf_ident("Quant:  Prod:           Val:\n");
    nl(1);
    
    int count  = 0;
    
    for(int target = 0; target < ORDER_SIZE; target ++) {
        
        char product_name[MAX_WIDTH]  = "",
             product_price[MAX_WIDTH] = "";
           
        //print products and calculate order cost  
        void print_order(int align_price_right) {
            
            if (count > 0) {
                //print number of itens
                printf_ident("%d", count);
                
                //print produt ID (name)
                if (count > 9) {align_right(product_array[target], PRODUCT_ALIGN_BIG);}
                else           {align_right(product_array[target], PRODUCT_ALIGN_SMA);}
                
                //print total price
                strcpy(product_price, "");
                sprintf(product_price, "R$ %.2f\n", value_array[target] * count);
                align_right(product_price, align_price_right);
                
                value_total += value_array[target] * count;
            }
        }
        
        for (int i = 0; i < ORDER_SIZE; i++) {
                if (order_array[i] == target) {
                    count  ++;
                }
            }
        
        //print_order(int align_price_right);    
        switch(target) {
            case 1:  print_order(3); break; //1  - Pão de queijo
            case 2:  print_order(4); break; //2  - Achocolatado
            case 3:  print_order(10);break; //3  - Pacoca
            case 4:  print_order(2); break; //4  - Coca-cola lata
            case 5:  print_order(3); break; //5  - Coca-cola 600
            case 6:  print_order(3); break; //6  - Coca-cola 2lt
            case 7:  print_order(4); break; //7  - Suco natural
            case 8:  print_order(2); break; //8  - Salgado assado
            case 9:  print_order(3); break; //9  - Salgado frito
            case 10: print_order(3); break; //10 - Ruffles media
            case 11: print_order(8); break; //10 - Refeicao
            
            default: //Produt do not exists
                if (target != 0 && count >= 1) {
                    printf_ident("AVISO:  PRODUTO '%d' NAO EXISTE\n", target);
                }
            break;
        }
        
        count = 0;
    }

    //----- END OF ORDER -----//
   
    
    nl(1);

    printf_ident("Total: R$ %.2f\n", value_total);
    value_total_of_day += value_total;

    nl(1); 

    for(int i = 0; i < IDENT_SIZE; i ++) {printf(" ");}
    for(int i = 0; i < MAX_WIDTH; i ++) {printf("-");}
    
    
    //----- RESTART FUNCTION -----//

    order_size_control = 0;
    int end_function = NOONE;
    
    nl(1);
    
    char conclude_header[MAX_WIDTH] = "PEDIDO CONCLUIDO";
    center(conclude_header, 0);
    
    nl(1);
  
    //start new order
    void start_new_order()                                  {
        system("clear");
        order_number++;
        value_total = 0;
        main();
    }
    
    //decide on what to do at the end of an order
    void end_decision()                                     {
        
        separator();
        nl(1);
        printf_ident("*Para iniciar um novo pedido:\n");
        printf_ident("digite '1'\n\n");
        printf_ident("*Para finalizar o turno......:\n");
        printf_ident("digite '0'\n");
        
        for(int i = 0; i < IDENT_SIZE; i++) {
            printf(" ");
        }
        int end_function = NOONE;
        scanf("%d", &end_function);
        
        clear_line();
        nl(1);
    
        if (end_function == 1) {
            start_new_order();
        } else if (end_function == 0) {
            separator();
            nl(1);
            printf_ident("Tem certeza que deseja\n");
            printf_ident("finalizar o dia?\n\n");
            printf_ident("*Para nao: digite 0\n");
            printf_ident("*Para sim: digite 1\n");
    
            int decision = NOONE;
            
            for(int i = 0; i < IDENT_SIZE; i++) {
                printf(" ");
            }
            
            scanf("%d", &decision);
            
            if (decision == 0) {
                clear_line();
                nl(1);
                end_decision();
            } else if (decision == 1) {
                end_of_shift();
            }
        }
    }

    
    end_decision();

    //----- END OF RESTART FUNCTION -----//
}