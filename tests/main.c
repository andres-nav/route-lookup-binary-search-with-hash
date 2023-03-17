#define MINIUNIT_MAIN
#include "miniunit.h"

int main(int argc, char *argv[]) {
  test_case("Testinggg", {
    expect("thi sis a description", 1 == 1);
    expect("thi sis a error", 1 == 2);
  });

  return 0;
}
