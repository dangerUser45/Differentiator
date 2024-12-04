#include <math.h>
#include "Diff_Common.h"
#include "Eval.h"

val_t Eval (node* node)
{
    if (!node) return 0;
    if (node -> type == NUM)
        return node -> val;

    if (node -> type == VAR)
        return _Global_X;

    if (node -> type = OP)
        switch ((int) node -> val)
        {
            case ADD: 
            return Eval (node -> left) 
                 + Eval (node -> right);

            case SUB: 
            return Eval (node -> left) 
                 - Eval (node -> right);

            case MUL: 
            return Eval (node -> left)
                 * Eval (node -> right);

            case DIV:
            return Eval (node -> left)
                 / Eval (node -> right);

            case COS:
            return cos (Eval (node -> left));

            case SIN:
            return sin (Eval (node -> left));

            case TAN:
            return tan (Eval (node -> left));

            case POW: 
            return pow (Eval (node -> left), Eval (node -> right));

            case LN: 
            return log(Eval(node -> left));

            case LOG:
            return log(Eval(node -> left)) / log(Eval(node -> right));

            case EXP:
            return exp(Eval (node -> left));
        }
    return 0;
}
