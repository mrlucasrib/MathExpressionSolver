#ifndef CALCULATOR_H
#define CALCULATOR_H
/**
 * @brief Modelo para o trabalho pratico
 * Escreva aqui as definições das funções que irá utilizar.
 */
#include "expression_tree.h"

int dothis();
ExpressionTree* parse_by_path(char* filepath);
float evaluate(ExpressionTree*);
//int save_as_gv(ExpressionTree*, char* path);


#endif // CALCULATOR_H
