#ifndef CALCULADORA_H
#define CALCULADORA_H
#define MAX_SIZE 100

typedef struct No {
    double dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;


typedef struct Node {
    char data[MAX_SIZE];
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void initialize(Stack *stack);
void push(Stack *stack, const char *value);
void pop(Stack *stack, char *value);
int is_operator(const char *token);
int get_next_token(const char *expression, int *index, char *token);
void print_stack(Stack *stack);
void translatePostfixToInfix(const char *expression, char result[MAX_SIZE]);
void inicializar(Pilha *pilha);
void empilhar(Pilha *pilha, double valor);
double desempilhar(Pilha *pilha);
double avaliarExpressaoPosfixada(const char *expressao);

#endif

