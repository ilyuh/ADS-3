// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int prior(char pr) {
  switch (pr) {
  case '(': return 0;
  case ')': return 1;
  case '+': return 2;
  case '-': return 2;
  case '*': return 3;
  case '/': return 3;
  default: return -1;
  }
}

std::string infx2pstfx(std::string inf) {
  char top = 0;
  TStack<char> stack;
  std::string str;
  for (int i = 0; i < inf.length(); i++) {
      int p;
      p = prior(inf[i]);
      if (p > -1) {
          if ((p == 0 || p > prior(top) ||
                stack.isEmpty()) && inf[i] != ')') {
          if (stack.isEmpty())
              top = inf[i];
          stack.push(inf[i]);
          } else if (inf[i] == ')') {
              while (stack.get() != '(') {
                  str.push_back(stack.get());
                  str.push_back(' ');
                  stack.pop();
              }
              stack.pop();
              if (stack.isEmpty())
                  top = 0;
          } else {
              while (!stack.isEmpty() && prior(stack.get()) >= p) {
                  str.push_back(stack.get());
                  str.push_back(' ');
                  stack.pop();
              }
              if (stack.isEmpty())
                  top = inf[i];
              stack.push(inf[i]);
          }
      } else {
          str.push_back(inf[i]);
          str.push_back(' ');
      }
  }
  while (!stack.isEmpty()) {
      str.push_back(stack.get());
      str.push_back(' ');
      stack.pop();
  }
  str.erase(str.end() - 1, str.end());
  return str;
}

int calculate(char operand, int num1, int num2) {
  switch (operand) {
  case '+': return num1 + num2;
    break;
  case '-': return num1 - num2;
    break;
  case '*': return num1 * num2;
    break;
  case '/': return num1 / num2;
    break;
  }
}

int eval(std::string pst) {
TStack<int> stack;
  int result = 0, i = 0;
  char x = pst[i];
  while (x) {
      if (x >= '0' && x <= '9') {
          int insertInt = 0;
          int dec = 1;
          while (x != ' ') {
              insertInt += (x - 48) * dec;
              dec *= 10;
              x = pst[++i];
          }
          stack.push(insertInt);
      } else {
          char operate = x;
          i++;
          int num2 = stack.get();
          stack.pop();
          int num1 = stack.get();
          stack.pop();
          int result = calculate(operate, num1, num2);
          stack.push(result);
      }
      if (i < pst.size())
          x = pst[++i];
      else
          x = 0;
  }
  result = stack.get();
  stack.pop();
  return result;
}
