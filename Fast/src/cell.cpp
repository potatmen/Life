#include "../include/cell.h"
void Cell::changeNewState(bool val) { newState = val; }

void Cell::changeCurState() { curState = newState; }

void Cell::setState(bool val) { curState = val; }

bool Cell::getCurState() const { return curState; }
