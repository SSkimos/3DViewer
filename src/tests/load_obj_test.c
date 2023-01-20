#include <check.h>

#include "../model/s21_affin_p.h"
#include "../model/s21_parse_obj.h"

START_TEST(basic_load) {
  data_t *obj = LoadObjFile("obj/lamp.obj");
  ck_assert_ptr_nonnull(obj);
  RemoveObject(obj);
}

END_TEST

Suite *load_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("obj");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, basic_load);
  suite_add_tcase(s, tc_core);

  return s;
}
