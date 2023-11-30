#include "calculadora.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX_SIZE 100


void initialize(Stack *stack) {
    stack->top = NULL;
}

void push(Stack *stack, const char *value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("falha na alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->data, value);
    newNode->next = stack->top;
    stack->top = newNode;
}

void pop(Stack *stack, char *value) {
    if (stack->top != NULL) {
        Node *temp = stack->top;
        strcpy(value, temp->data);
        stack->top = temp->next;
        free(temp);
    } else {
        printf("pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

int is_operator(const char *token) {
    const char *operators[] = {"+", "-", "*", "/", "log", "sen", "cos", "tan", "^"};
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); ++i) {
        if (strcmp(token, operators[i]) == 0) {
            return 1; // É um operador
        }
    }
    return 0; // Não é um operador
}

int get_next_token(const char *expression, int *index, char *token) {
    int i = 0;
    while (expression[*index] != '\0' && expression[*index] != ' ' && expression[*index] != '\n') {
        token[i++] = expression[(*index)++];
    }
    token[i] = '\0';
    // Avança para o próximo caractere não-espaço
    while (expression[*index] == ' ') {
        (*index)++;
    }
    return i; 
}

void print_stack(Stack *stack) {
    
    Node *current = stack->top;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void translatePostfixToInfix(const char *expression, char result[MAX_SIZE]) {
    Stack stack;
    initialize(&stack);

    int index = 0;
    char token[MAX_SIZE];

    while (get_next_token(expression, &index, token) > 0) {
        if (is_operator(token)) {
            if (strcmp(token, "sen") == 0 ||
                strcmp(token, "cos") == 0 || strcmp(token, "tan") == 0) {
                char operand[MAX_SIZE];
                char r[MAX_SIZE];
                pop(&stack, operand);
                sprintf(r, "%s(%s)", token, operand);
                push(&stack, r);
                
            } else if (strcmp(token, "^") == 0) {
                char base[MAX_SIZE];
                char operand[MAX_SIZE];
                char r[MAX_SIZE];
                pop(&stack, base);
                pop(&stack, operand);
                sprintf(r, "%s%s(%s)", base, token, operand);
                push(&stack, r);
                
            } else if (strcmp(token, "log") == 0) {
                char operand[MAX_SIZE];
                char r[MAX_SIZE];
                pop(&stack, operand);
                sprintf(r, "log(%s)", operand);
                push(&stack, r);
                
            } else {
                char operand2[MAX_SIZE], operand1[MAX_SIZE], r[MAX_SIZE];
                pop(&stack, operand2);
                pop(&stack, operand1);
                
                sprintf(r, "(%s %s %s)", operand1, token, operand2);
                
                push(&stack, r);
            }
        } else {
            
            push(&stack, token);
        }

        
    }

    
    result[0] = '\0';
    char temp[MAX_SIZE];
    while (stack.top != NULL) {
        pop(&stack, temp);
        strcat(result, temp);
        strcat(result, " ");
    }
    result[strlen(result) - 1] = '\0'; 
}







void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, double valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("falha na alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

double desempilhar(Pilha *pilha) {
    if (pilha->topo != NULL) {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;
    } else {
        printf("pilha vazia\n");
        exit(EXIT_FAILURE);
    }
}

double avaliarExpressaoPosfixada(const char *expressao) {
    Pilha pilha;
    inicializar(&pilha);

    char *endptr;
    double valor;
double base; 

    for (int i = 0; expressao[i] != '\0'; ++i) {
        if (isdigit(expressao[i]) || (expressao[i] == '-' && isdigit(expressao[i + 1]))) {
            valor = strtod(&expressao[i], &endptr);
            empilhar(&pilha, valor);
            i += endptr - &expressao[i] - 1;
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            continue;
        } else {
            double operando;
            switch (expressao[i]) {
                case '+':
                    empilhar(&pilha, desempilhar(&pilha) + desempilhar(&pilha));
                    break;
                case '-':
                    operando = desempilhar(&pilha);
                    empilhar(&pilha, desempilhar(&pilha) - operando);
                    break;
                case '*':
                    empilhar(&pilha, desempilhar(&pilha) * desempilhar(&pilha));
                    break;
                case '/':
                    operando = desempilhar(&pilha);
                    if (operando != 0.0) {
                        empilhar(&pilha, desempilhar(&pilha) / operando);
                    } else {
                        printf("erro na divisao por zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case '^':
                    operando = desempilhar(&pilha);
                    base = desempilhar(&pilha); 
                    empilhar(&pilha, pow(base, operando));
                    break;
                case 'l':
                    // Logaritmo 
                    operando = desempilhar(&pilha);
    empilhar(&pilha, log10(operando));
    i += 2; 
                    break;
                case 's':
                    // Seno
                    empilhar(&pilha, sin(desempilhar(&pilha)));
                    i += 2; 
                    break;
                case 'c':
                    // Cosseno
                    empilhar(&pilha, cos(desempilhar(&pilha)));
                    i += 2; 
                    break;
                case 't':
                    // Tangente
                    empilhar(&pilha, tan(desempilhar(&pilha)));
                    i += 2; 
                    break;
                default:
                    printf("operador invalido\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    if (pilha.topo == NULL) {
        printf("pilha vazia\n");
        exit(EXIT_FAILURE);
    }

    double resultado = desempilhar(&pilha);

    if (pilha.topo != NULL) {
        printf("pilha nao esta vazia apos a avaliacao\n");
        exit(EXIT_FAILURE);
    }

    return resultado;
}




