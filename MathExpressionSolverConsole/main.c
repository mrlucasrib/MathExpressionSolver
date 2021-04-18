#include <stdio.h>
#include "../MathExpressionSolverLib/expression_tree.h"

int main(int agrc, char *argv[]) {
    ExpressionTree *etree = parse_expr("5+5+4", 5);
    printf("Resultado: \n%.2f\n", evaluate(etree));
    free_mem_expressiontree(etree);
    return 0;
}
