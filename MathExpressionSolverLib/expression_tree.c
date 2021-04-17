#include "expression_tree.h"

#include <malloc.h>

struct Node{
    char value;
    struct Node *left, *right;
};
int get_lower_precedence(ExpressionTree*etree, char*expr, int start, int end);
int precedence(char c);

int parse(ExpressionTree*etree, char *expr, int start, int end)
{
    int position = get_lower_precedence(etree, expr, start, end);
    if(position != -1){
        etree->left = init_etree();
        etree->right = init_etree();
        parse(etree->left, expr, start, position-1);
        parse(etree->right, expr, position+1, end);
    }
    return 1;
}

int get_lower_precedence(ExpressionTree*etree, char*expr, int start, int end){
    if(start == end){
        etree->value = expr[start];
        return -1;
    }
    int p = start;

    for (int i = start+1; i <= end ; ++i )
        if(precedence(expr[p]) > precedence(expr[i]))
            p = i;
    etree->value = expr[p];
    return p;
}
int precedence(char c){
    if(c == '-' || c == '+')
        return 1;
    else if(c == '*' || c == '/')
        return 2;
    else
        return 3;
}

ExpressionTree* init_etree(){
    ExpressionTree* etree = malloc(sizeof (ExpressionTree));
    etree->left = NULL;
    etree->right = NULL;
    return etree;
}

void postfix_expression_tree(ExpressionTree *raiz)
{

    if(raiz == NULL)
    {
        return;
    }
    if(raiz != NULL)
    {
        postfix_expression_tree(raiz->left);
        postfix_expression_tree(raiz->right);
        printf("%c\n",raiz->value);
    }
}


float evaluate(ExpressionTree *etree)
{
    if(etree == NULL)
        return 0;
    int x = evaluate(etree->left);
    int y = evaluate(etree->right);
    switch (etree->value) {
    case '/':
        return x / y;
    case '*':
        return x * y;
    case '+':
        return x + y;
    case '-':
        return x - y;
    default:
        return etree->value - '0';
    }
}

void preOrdem_ArvBin(ExpressionTree *raiz){
    ExpressionTree*aux = raiz;
    while(aux != NULL){
        printf("%c -- %c\n",raiz->value, raiz->left->value);
        printf("%c -- %c\n",raiz->value, raiz->right->value);
        aux = aux->left;
    }
    while(aux != NULL){
        printf("%c -- %c\n",raiz->value, raiz->left->value);
        printf("%c -- %c\n",raiz->value, raiz->right->value);
        aux = aux->right;
    }
        return;
//    if(raiz != NULL){
//        preOrdem_ArvBin(raiz->left);
//        preOrdem_ArvBin(raiz->right);
//    }
}
