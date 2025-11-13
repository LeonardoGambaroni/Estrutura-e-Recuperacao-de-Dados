#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Node {
    char data;        
    double value;     
    struct Node *left;
    struct Node *right;
} Node;

double evaluateExpression(Node *currentNode) {
    if (currentNode == NULL) {
        
        return 0.0;
    }
    
    if (currentNode->left == NULL && currentNode->right == NULL) {
        return currentNode->value;
    }
    
    double leftVal = evaluateExpression(currentNode->left);
    double rightVal = evaluateExpression(currentNode->right);

    switch (currentNode->data) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/':
            if (rightVal == 0.0) {
                fprintf(stderr, "Erro: divisão por zero na árvore de expressão.\n");
                return NAN; 
            }
            return leftVal / rightVal;
        default:
            fprintf(stderr, "Erro: operador desconhecido '%c'.\n", currentNode->data);
            return NAN;
    }
}

Node* makeOperatorNode(char op, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = op;
    node->value = 0.0;
    node->left = left;
    node->right = right;
    return node;
}

Node* makeValueNode(double val) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) { perror("malloc"); exit(EXIT_FAILURE); }
    node->data = '\0';
    node->value = val;
    node->left = node->right = NULL;
    return node;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    
    Node* n5 = makeValueNode(5.0);
    Node* n2 = makeValueNode(2.0);
    Node* times = makeOperatorNode('*', n5, n2);

    Node* n3 = makeValueNode(3.0);

    Node* plus = makeOperatorNode('+', n3, times);

    double result = evaluateExpression(plus);
    if (!isnan(result))
        printf("Resultado: %.6g\n", result); 

    freeTree(plus);
    return 0;
}
