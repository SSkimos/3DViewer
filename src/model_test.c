#include <check.h>

#include <stdio.h>
#include <stdlib.h>
#include "tests/suites.h"

int main() {
  Suite* affine = affine_suite();
  Suite* load = load_suite();
  SRunner* runner = srunner_create(affine);
  srunner_add_suite(runner, load);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

