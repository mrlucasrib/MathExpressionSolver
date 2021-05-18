#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H
typedef struct ExpressionTree ExpressionTree;

/**
 * @brief Cria e popula uma arvore com a expressão fornecida
 * @memberof ExpressionTree
 * @param expr Uma string contendo a expressão sem espaços
 * @param size Tamanho da string
 * @return retorna a arvore criada a partir da expressão
 */
ExpressionTree *parse_expr(char *expr, int size);

/**
 * @brief Inicializa a arvore
 * @memberof ExpressionTree
 * @return Retorna a uma arvore sem nós
 */
ExpressionTree *init_etree();

/**
 * @brief Faz a resolução da expressão
 * @memberof ExpressionTree
 * @param etree ExpressionTree vazia
 * @return retorna o ExpressionTree equivalente a expressão.
 */
float evaluate(ExpressionTree *etree);

/**
 * @brief Salva a arvore em um formato para geração do grafo
 * @memberof ExpressionTree
 * @param etree A arvore de expressão
 * @param filepath Local onde será salvo o arquivo
 * @return 1 se ok 0 se não ok
 */
int save_as_dot(ExpressionTree *etree, char *filepath);

/**
 * @brief Libera a memoria da ExpressionTree
 * @memberof ExpressionTree
 * @param etree Arvore binaria a ser liberada
 */
void free_mem_expressiontree(ExpressionTree* etree);

#endif // EXPRESSION_TREE_H
