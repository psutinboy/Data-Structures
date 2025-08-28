/*
  This file shows only what I added to make the program work.
  It includes the convertToPostfix function with simple comments.
*/

void convertToPostfix() {
  // create a stack to hold operators
  ArrStack *s = newStack();
  // j is the index where we write into the postfix string
  int j = 0;

  // go through each character in the input infix expression
  for (int i = 0; i < length; i++) {
    char ch = infix[i];

    // skip spaces and tabs
    if (ch == ' ' || ch == '\t')
      continue;

    // if the character is a letter (variable) or a digit, copy it to postfix
    if (isLetter(ch) || (ch >= '0' && ch <= '9')) {
      postfix[j++] = ch;
    }
    // if it's an opening parenthesis, push it on the stack
    else if (ch == '(') {
      push(s, ch);
    }
    // if it's a closing parenthesis, pop until we see '('
    else if (ch == ')') {
      while (!isEmpty(s) && peek(s) != '(') {
        postfix[j++] = pop(s);
      }
      // remove the '(' from the stack
      if (!isEmpty(s) && peek(s) == '(')
        pop(s);
    }
    // otherwise it is an operator: + - * / ^
    else {
      // find current operator precedence: ^ highest, then * /, then + -
      int pCur = (ch == '+' || ch == '-')   ? 1
                 : (ch == '*' || ch == '/') ? 2
                 : (ch == '^')              ? 3
                                            : 0;

      // while the top of the stack has an operator with higher precedence,
      // or the same precedence (and current op is not '^' because '^' is
      // right-associative), pop it to postfix
      while (!isEmpty(s) && peek(s) != '(') {
        char topOp = peek(s);
        int pTop = (topOp == '+' || topOp == '-')   ? 1
                   : (topOp == '*' || topOp == '/') ? 2
                   : (topOp == '^')                 ? 3
                                                    : 0;

        if (pTop > pCur || (pTop == pCur && ch != '^')) {
          postfix[j++] = pop(s);
        } else {
          break;
        }
      }

      // push the current operator
      push(s, ch);
    }
  }

  // pop any remaining operators from the stack
  while (!isEmpty(s)) {
    postfix[j++] = pop(s);
  }

  // add string terminator to postfix
  postfix[j] = '\0';

  // free the operator stack
  // You should use destroyStack(s) here instead of just free(s) because
  // destroyStack not only frees the ArrStack struct itself, but also frees the
  // dynamically allocated memory for the stack array inside the struct. If you
  // only called free(s), you would leak the memory allocated for s->stack.
  // destroyStack(s) properly frees all memory.
  destroyStack(s);
}
