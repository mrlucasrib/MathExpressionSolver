#include "expression_tree.h"
#include <malloc.h>

int NODE_ID = 0;

struct ExpressionTree {
    /**
     * @brief Valor do nó
     */
    char value;
    /**
     * @brief ID unico de cada nó gerado automaticamente para produção da figura
     * @private
     */
    int ID;
    /**
     * @brief Nós filhos
     */
    struct ExpressionTree *left, *right;
};

/**
 * @brief Encontra o caractere com menor precedencia a partir de uma cadeia de caracteres
 * @memberof ExpressionTree
 * @return Retorna ao item de menor precedencia.
 */
int get_lower_precedence(ExpressionTree *etree, char *expr, int start, int end);

/**
 * @brief Atribui um valor de precedencia a partir do caractere
 * @memberof ExpressionTree
 * @param c Caractere a ser avaliado
 * @return retorna um valor de 1 a 3 como a precedencia.
 */
int precedence(char c);

/**
 * @brief Função recursiva para fazer o parse da expressão
 * @memberof ExpressionTree
 * @param etree Arvore binaria a ser populada
 * @return Retorna 1 se não existir problemas.
 */
int parse(ExpressionTree *etree, char *expr, int start, int end) {
    int position = get_lower_precedence(etree, expr, start, end);
    if (position != -1) {
        etree->left = init_etree();
        etree->right = init_etree();
        parse(etree->left, expr, start, position - 1);
        parse(etree->right, expr, position + 1, end);
    }
    return 1;
}

int get_lower_precedence(ExpressionTree *etree, char *expr, int start, int end) {
    if (start == end) {
        etree->value = expr[start];
        return -1;
    }
    int p = start;

    for (int i = start + 1; i <= end; ++i)
        if (precedence(expr[p]) > precedence(expr[i]))
            p = i;
    etree->value = expr[p];
    return p;
}

int precedence(char c) {
    if (c == '-' || c == '+')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else
        return 3;
}

ExpressionTree *init_etree() {
    ExpressionTree *etree = malloc(sizeof(ExpressionTree));
    etree->left = NULL;
    etree->right = NULL;
    etree->ID = NODE_ID;
    NODE_ID++;
    return etree;
}


float evaluate(ExpressionTree *etree) {
    if (etree == NULL)
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

/**
 * @brief Cria a configuração inicial da linguagem de descrição de grafos
 * @param etree
 * @param f
 */
void generate_dot_config(ExpressionTree *etree, FILE *f) {
    if (etree == NULL)
        return;
    fprintf(f, "%d [label=\"%c\"]\n", etree->ID, etree->value);
    generate_dot_config(etree->left, f);
    generate_dot_config(etree->right, f);
}


void generate_dot(ExpressionTree *etree, FILE *f) {
    if (etree != NULL) {
        if (etree->left != NULL)
            fprintf(f, "%d -- %d\n", etree->ID, etree->left->ID);
        if (etree->right != NULL)
            fprintf(f, "%d -- %d\n", etree->ID, etree->right->ID);
        printf("\n");
        generate_dot(etree->left, f);
        generate_dot(etree->right, f);
    }
}

int save_as_dot(ExpressionTree *etree, char *filepath) {
    FILE *f = fopen(filepath, "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return -1;
    }
    fprintf(f, "graph G {\n");
    generate_dot_config(etree, f);
    generate_dot(etree, f);
    fprintf(f, "}");
    fclose(f);
    return 1;
}

ExpressionTree *parse_expr(char *expr, int size) {
    ExpressionTree *etree = init_etree();
    parse(etree, expr, 0, size - 1);
    return etree;
}

void free_mem_expressiontree(ExpressionTree *etree) {
    if (etree == NULL)
        return;
    free_mem_expressiontree(etree->left);
    free_mem_expressiontree(etree->right);
    free(etree);
}
