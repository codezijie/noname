#include <iostream>

#include "init.h"

int main(int args, char **argv) {
  InitApp(args, argv);

  DeleteApp();
  return 0;
}