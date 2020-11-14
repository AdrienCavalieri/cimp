#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../../src/data/color.h"

START_TEST(test_color_create){
	struct color *c;
	c=create_color(0,25,50,100);
	unsigned char tab[4];
	get_rgba(c,&tab[0],&tab[1],&tab[2],&tab[3]);
	ck_assert_int_eq(tab[0],0);
	ck_assert_int_eq(tab[1],25);
	ck_assert_int_eq(tab[2],50);
	ck_assert_int_eq(tab[3],100);
	destroy_color(c);
}
END_TEST

START_TEST(test_color_create_hex){
	struct color *c;
	c=create_color_hex(0x00193264);
	unsigned char tab[4];
	get_rgba(c,&tab[0],&tab[1],&tab[2],&tab[3]);
	ck_assert_int_eq(tab[0],0);
	ck_assert_int_eq(tab[1],25);
	ck_assert_int_eq(tab[2],50);
	ck_assert_int_eq(tab[3],100);
	destroy_color(c);
}
END_TEST

START_TEST(test_equalsColor){
	struct color *c,*t;
	c=create_color(0,25,50,100);
	t=create_color(0,0,0,0);
	ck_assert_int_eq(equalsColor(c,t),0);
	ck_assert_int_eq(equalsColor(c,c),1);
	destroy_color(c);
	destroy_color(t);
}
END_TEST

Suite* color_suite (void) {
    TCase *tc_create;
    TCase *tc_equals;
    Suite *s;

    tc_create = tcase_create("Create");
    tcase_add_test(tc_create, test_color_create);
    tcase_add_test(tc_create, test_color_create_hex);

    tc_equals=tcase_create("Equals");
    tcase_add_test(tc_equals, test_equalsColor);

    s=suite_create("Color");
    suite_add_tcase(s,tc_create);
    suite_add_tcase(s,tc_equals);

    return s;
}

int main() {
    int failures;

    Suite *s;
    SRunner *sr;

    s = color_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    failures = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
