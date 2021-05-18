#include <stdio.h>
#include "../MathExpressionSolverLib/expression_tree.h"
#define MAX_EXPRESSION 20


int main() {
    int size;
    char expr[MAX_EXPRESSION];
    printf("Insira o numero de caracteres da sua expressão (sem espaços): ");
    scanf("%d", &size);

    printf("Insira sua expressão (sem espaços): ");
    scanf("%s", expr);

    ExpressionTree *etree = parse_expr(expr, size);
    printf("Resultado: \n%.2f\n", evaluate(etree));
    free_mem_expressiontree(etree);
    return 0;
}
