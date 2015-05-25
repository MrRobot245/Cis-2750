#ifndef A1TEST_A1TEST_H
#define A1TEST_A1TEST_H

/* File name to use for writing temporary files */
#define TEST_FILENAME "TEMP"

/* Default value to use for PM_create */
#define DEFAULT_CREATE_VAL 1

/* Default character to use as a comment */
#define DEFAULT_COMMENT '#'

/* Maximum difference threshold when comparing REAL_TYPE values */
#define REAL_THRESHOLD 1.0

/*
 * ASSERT
 * A simple macro. Return 1 if cond evaluates to false.
 * Used by test cases to exit if condition is false.
 */
#define ASSERT(cond) if (!(cond)) return 1

/* Test framework methods */
FILE *file_with_contents(char *contents);
int fork_test(int (*fn)());
void run_test(int (*fn)(), char *fn_name);

/* Main functionality tests */
int test_pm_create_destroy();
int test_pm_create_destroy_twice();
int test_pm_create_destroy_large_size();

/* PM_manage optional value tests */
int test_pm_manage_int_optional();
int test_pm_manage_real_optional();
int test_pm_manage_boolean_optional();
int test_pm_manage_string_optional();
int test_pm_manage_list_optional();

/* PM_manage required value tests */
int test_pm_manage_int_required();
int test_pm_manage_real_required();
int test_pm_manage_boolean_required();
int test_pm_manage_string_required();
int test_pm_manage_list_required();

/* PM_parseFrom optional value tests */
int test_pm_parse_int_optional();
int test_pm_parse_real_optional();
int test_pm_parse_boolean_optional();
int test_pm_parse_string_optional();
int test_pm_parse_list_optional();
int test_pm_parse_all_optional();

/* PM_parseFrom missing optional value tests */
int test_pm_parse_int_optional_missing();
int test_pm_parse_real_optional_missing();
int test_pm_parse_boolean_optional_missing();
int test_pm_parse_string_optional_missing();
int test_pm_parse_list_optional_missing();
int test_pm_parse_all_optional_missing();

/* PM_parseFrom required value tests */
int test_pm_parse_int_required();
int test_pm_parse_real_required();
int test_pm_parse_boolean_required();
int test_pm_parse_string_required();
int test_pm_parse_list_required();
int test_pm_parse_all_required();

/* Comment tests */
int test_comment();
int test_comment_only();
int test_comment_inline();
int test_comment_multiple();
int test_comment_non_default();
int test_comment_before_semicolon();
int test_comment_before_value();
int test_comment_before_equals();

/* Parse error tests */
int test_parse_error_no_semicolon();
int test_parse_error_no_required_value();
int test_parse_error_no_equals();
int test_parse_error_double_equals();
int test_parse_error_wrong_type();
int test_parse_error_multiple_values();

/* Whitespace tests */
int test_whitespace_more();
int test_whitespace_less();
int test_whitespace_none();
int test_whitespace_multiline();

/* INT_TYPE tests */
int test_int_zero();
int test_int_negative();
int test_int_multiples();

/* REAL_TYPE tests */
int test_real_no_decimal();
int test_real_multiples();

/* BOOLEAN_TYPE tests */
int test_boolean_false();
int test_boolean_multiples();

/* STRING_TYPE tests */
int test_string_spaces();
int test_string_line_break();
int test_string_single_quotes();
int test_string_number();
int test_string_multiples();

/* LIST_TYPE tests */
int test_list_empty();
int test_list_many_values();
int test_list_spaces();
int test_list_no_spaces();
int test_list_line_breaks();
int test_list_multiples();

#endif  /* A1TEST_A1TEST_H */
