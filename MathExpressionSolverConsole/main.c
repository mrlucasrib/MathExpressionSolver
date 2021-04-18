#include <stdio.h>
#include "../MathExpressionSolverLib/expression_tree.h"

int main()
{
    ExpressionTree* etree =  parse_expr("5+5+4", 5);


    printf("Resultado: \n%f",evaluate(etree));
//    save_as_dot(etree, "/home/lucas/isso.txt");

    return 0;
}
