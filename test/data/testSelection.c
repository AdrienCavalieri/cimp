#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../../src/data/selection.h"

START_TEST(test_selection_getters){
	struct selection* s;
	s=create_selection(100,200);
	int minx,miny,maxx,maxy;
	get_select_bounds(s,&minx,&miny,&maxx,&maxy);
	ck_assert_int_eq(get_selection_width(s),100);
	ck_assert_int_eq(get_selection_height(s),200);
	ck_assert_int_eq(minx,100);
	ck_assert_int_eq(miny,200);
	ck_assert_int_eq(maxx,-1);
	ck_assert_int_eq(maxy,-1);

	destroy_selection(s);
}
END_TEST

START_TEST(test_selection_selection){
	struct selection* s;
	s=create_selection(800,600);
	select_pixel(s,157,268);
	ck_assert_int_eq(is_selected(s,157,268),1);
	unselect(s,157,268);
	ck_assert_int_eq(is_selected(s,157,268),0);

	destroy_selection(s);
}
END_TEST

Suite* selection_suite (void) {
    TCase *tc_getters, *tc_selection;
    Suite *s;

    tc_getters=tcase_create("Getters");
    tcase_add_test(tc_getters,test_selection_getters);

	tc_selection=tcase_create("Selection");
    tcase_add_test(tc_selection,test_selection_selection);

    s=suite_create("Selection");
    suite_add_tcase(s,tc_getters);
	suite_add_tcase(s,tc_selection);

    return s;
}

int main() {
    int failures;

    Suite *s;
    SRunner *sr;

    s = selection_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    failures = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}