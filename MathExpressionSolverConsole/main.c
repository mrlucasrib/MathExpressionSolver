#include <stdio.h>
#include "../MathExpressionSolverLib/calculator.h"
#include "../MathExpressionSolverLib/expression_tree.h"

int main()
{
    ExpressionTree* etree =  parse_by_path(NULL);

//    postfix_expression_tree(etree);

    printf("Hello World!\n%f",evaluate(etree));

    preOrdem_ArvBin(etree);
    return 0;
}
