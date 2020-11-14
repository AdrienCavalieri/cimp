#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../../src/data/picture.h"

START_TEST(test_create_picture_from_image) {
    struct picture *p = create_picture_from_image("./tux.png");

    ck_assert(p != NULL);

    destroy_picture(p);

} END_TEST

START_TEST(test_create_picture) {
    struct picture *p = create_picture(800, 600);

    ck_assert(p != NULL);
    ck_assert_int_eq(get_picture_width(p), 800);
    ck_assert_int_eq(get_picture_height(p), 600);

    destroy_picture(p);

} END_TEST

START_TEST(test_get_picture_width) {
    struct picture *p = create_picture_from_image("./tux.png");

    ck_assert_int_eq(get_picture_width(p), 287);

    destroy_picture(p);

} END_TEST

START_TEST(test_get_picture_height) {
    struct picture *p = create_picture_from_image("./tux.png");

    ck_assert_int_eq(get_picture_height(p), 301);

    destroy_picture(p);

} END_TEST

START_TEST(test_get_picture_format) {
    struct picture *p = create_picture_from_image("./tux.png");

    ck_assert(get_picture_format(p) == PNG);

    destroy_picture(p);

} END_TEST

START_TEST(test_get_picture_path) {
    struct picture *p = create_picture_from_image("./tux.png");

    ck_assert_str_eq(get_picture_path(p), "./tux.png");

    destroy_picture(p);

} END_TEST

Suite* picture_suite (void) {
    TCase *tc_constructors, *tc_getters;
    Suite *s;

    tc_constructors = tcase_create("Constructors");
    tcase_add_test(tc_constructors, test_create_picture_from_image);
    tcase_add_test(tc_constructors, test_create_picture);

    tc_getters = tcase_create("Getters");
    tcase_add_test(tc_getters, test_get_picture_width);
    tcase_add_test(tc_getters, test_get_picture_height);
    tcase_add_test(tc_getters, test_get_picture_format);
    tcase_add_test(tc_getters, test_get_picture_path);

    s = suite_create("Picture");
    suite_add_tcase(s, tc_constructors);
    suite_add_tcase(s, tc_getters);

    return s;
}

int main() {
    int failures;

    Suite *s;
    SRunner *sr;

    s = picture_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    failures = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
