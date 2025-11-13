#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char itens[100];
    int topo;
} Pilha;

void inicializar(Pilha *p) {
    p->topo = -1;
}

bool estaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, char c) {
    if (p->topo < 99) {
        p->itens[++p->topo] = c;
    }
}

char pop(Pilha *p) {
    if (!estaVazia(p)) {
        return p->itens[p->topo--];
    }
    return '\0'; 
}

bool verificarExpressao(char exp[]) {
    Pilha p;
    inicializar(&p);

    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if (c == '(' || c == '[' || c == '{') {
            push(&p, c);
        }

        else if (c == ')' || c == ']' || c == '}') {
            if (estaVazia(&p)) {
                return false;
            }

            char topo = pop(&p);

            if ((c == ')' && topo != '(') ||
                (c == ']' && topo != '[') ||
                (c == '}' && topo != '{')) {
                return false; 
            }
        }
    }

    return estaVazia(&p);
}

int main() {
    char exp1[] = "{[(2+3)*5] + (4/2)}";
    char exp2[] = "{[(2+3)*5{] + (4/2)}";

    printf("Expressao 1: %s -> %s\n", exp1,
           verificarExpressao(exp1) ? "Expressao valida" : "Expressao invalida");
    printf("Expressao 2: %s -> %s\n", exp2,
           verificarExpressao(exp2) ? "Expressao valida" : "Expressao invalida");

    return 0;
}
