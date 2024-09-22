#include <check.h>
#include <stdlib.h>  // for malloc, free
#include <stdio.h>   // for printf
#include "ft_split.h"  // Your ft_split function declaration

// Unicode symbols
#define GREEN_CHECK "\xEF\x81\x98"
#define RED_EXCLAMATION "\xEF\x81\xB1"  // \uF071 (Nerd Font exclamation)
#define GREEN_CIRCLE "\xF0\x9F\x9F\xA2"  // 🟢
#define RED_CIRCLE "\xF0\x9F\x94\xB4"  // 🔴

// Test Case 1: Simple Split
START_TEST(test_simple_split)
{
    char **result = ft_split("hello world", ' ');
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result[0], "hello");
    ck_assert_str_eq(result[1], "world");
    ck_assert_ptr_null(result[2]);

    // Free allocated memory
    for (int i = 0; result[i] != NULL; i++)
        free(result[i]);
    free(result);
}
END_TEST

// Test Case 2: Multiple Delimiters
START_TEST(test_multiple_delimiters)
{
    char **result = ft_split("one,,two,,,three", ',');
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result[0], "one");
    ck_assert_str_eq(result[1], "two");
    ck_assert_str_eq(result[2], "three");
    ck_assert_ptr_null(result[3]);

    // Free allocated memory
    for (int i = 0; result[i] != NULL; i++)
        free(result[i]);
    free(result);
}
END_TEST

// Test Case 3: Empty String
START_TEST(test_empty_string)
{
    char **result = ft_split("", ',');
    ck_assert_ptr_nonnull(result);
    ck_assert_ptr_null(result[0]);
    free(result);
}
END_TEST

// Test Case 4: No Delimiter Found
START_TEST(test_no_delimiter)
{
    char **result = ft_split("nodelem", ',');
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result[0], "nodelem");
    ck_assert_ptr_null(result[1]);

    // Free allocated memory
    free(result[0]);
    free(result);
}
END_TEST

// Test Case 5: NULL String Input
START_TEST(test_null_input)
{
    char **result = ft_split(NULL, ',');
    ck_assert_ptr_null(result);
}
END_TEST

// Creating the Test Suite
Suite *ft_split_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("ft_split");
    tc_core = tcase_create("Core");

    // Add test cases to the test suite
    tcase_add_test(tc_core, test_simple_split);
    tcase_add_test(tc_core, test_multiple_delimiters);
    tcase_add_test(tc_core, test_empty_string);
    tcase_add_test(tc_core, test_no_delimiter);
    tcase_add_test(tc_core, test_null_input);

    suite_add_tcase(s, tc_core);

    return s;
}

// Test Runner (Main function)
int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = ft_split_suite();
    sr = srunner_create(s);

    // Disable forking for accurate result handling
    srunner_set_fork_status(sr, CK_NOFORK);

    srunner_run_all(sr, CK_NORMAL);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    // Print results with colored icons
    if (number_failed == 0)
    {
        printf("%s %s All tests passed\n", GREEN_CIRCLE, GREEN_CHECK);
    }
    else
    {
        printf("%s %s %d test(s) failed\n", RED_CIRCLE, RED_EXCLAMATION, number_failed);
    }

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
