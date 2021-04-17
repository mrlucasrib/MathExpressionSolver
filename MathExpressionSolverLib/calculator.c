#include <stdio.h>
#include "expression_tree.h"
// Apenas teste
int dothis()
{
    printf("\nHello\n");
    return 99;
}



ExpressionTree *parse_by_path(char *filepath)
{
    char txt[] = "5+7+3*5";
    ExpressionTree* etree = init_etree();
    parse(etree, txt, 0, 6);
    return etree;
}
