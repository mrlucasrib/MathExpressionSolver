#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
typedef struct Node ExpressionTree;

ExpressionTree *parse_expr(char *expr, int size);

ExpressionTree *init_etree();

float evaluate(ExpressionTree *);

int save_as_dot(ExpressionTree *, char *filepath);

#endif // EXPRESSION_TREE_H
