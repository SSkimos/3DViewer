#include <check.h>
#include "../model/s21_parse_obj.h"
#include "../model/s21_affin_p.h"

START_TEST(affine_no_job) {
  data_t*obj = ParseCountObj("obj/cube.obj");
  affine_t* vector = InitAffine();
  int expected_code = 0;
  int my_code = -1;
  if (obj && vector) {
    my_code = MoveAndRotateModel(&obj, vector);
    RemoveObject(obj);
  }
  ck_assert_int_eq(expected_code, my_code);

}
END_TEST

START_TEST(affine_basic_scale) {

}
END_TEST

START_TEST(affine_rotate_xyz) {

}
END_TEST

Suite *affine_suite(void) {
  Suite* s;
  TCase *tc_core;
  s = suite_create("affine");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, affine_no_job);
  suite_add_tcase(s, tc_core);

  return s;
}
