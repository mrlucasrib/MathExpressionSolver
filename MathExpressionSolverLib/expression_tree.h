#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
typedef struct Node ExpressionTree;

int parse(ExpressionTree*etree, char *expr, int start, int end);

ExpressionTree* init_etree();

float evaluate(ExpressionTree*);

int save_as_gv(ExpressionTree*);

void postfix_expression_tree(ExpressionTree *raiz);
void preOrdem_ArvBin(ExpressionTree *raiz);
#endif // EXPRESSION_TREE_H
