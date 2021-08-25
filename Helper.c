#include <stdbool.h>
#include "Operator.h"
#include "Helper.h"

bool is_redundant(const enum Operator node_to_expand_operator, const enum Operator op) {
    switch (node_to_expand_operator) /* according to Korf's paper (see references) */ {
    case L:
    case L2:
    case Li:
        return op == L || op == L2 || op == Li;

    case U:
    case U2:
    case Ui:
        return op == U || op == U2 || op == Ui;

    case F:
    case F2:
    case Fi:
        return op == F || op == F2 || op == Fi;

    case R:
    case R2:
    case Ri:
        return (op == R || op == R2 || op == Ri) || (op == L || op == L2 || op == Li);

    case D:
    case D2:
    case Di:
        return (op == D || op == D2 || op == Di) || (op == U || op == U2 || op == Ui);

    case B:
    case B2:
    case Bi:
        return (op == B || op == B2 || op == Bi) || (op == F || op == F2 || op == Fi);

    default: // node_to_expand is the root
        return false;
    }
}
