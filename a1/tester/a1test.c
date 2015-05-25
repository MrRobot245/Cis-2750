#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ParameterManager.h"
#include "a1test.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET "\x1b[0m"

int num_tests = 0;
int num_tests_suite = 0;
int num_success = 0;
int num_success_suite = 0;

int test_pm_create_destroy() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_create_destroy_twice() {
        ParameterManager *pm1, *pm2;
        ASSERT(pm1 = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(pm2 = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_destroy(pm1));
        ASSERT(PM_destroy(pm2));
        return 0;
}

int test_pm_create_destroy_large_size() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(100));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_int_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_real_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_boolean_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_string_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_list_optional() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 0));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_int_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_real_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_boolean_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_string_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_manage_list_required() {
        ParameterManager *pm;
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_destroy(pm));
        return 0;
}

int test_pm_parse_int_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_real_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 3.3;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT((PM_getValue(pm, "name").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_boolean_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = true;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").bool_val == true);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_string_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"string\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_list_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_all_optional() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = 1;\n"
                "name2 = 3.3;\n"
                "name3 = true;\n"
                "name4 = \"string\";\n"
                "name5 = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(5));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 0));
        ASSERT(PM_manage(pm, "name2", REAL_TYPE, 0));
        ASSERT(PM_manage(pm, "name3", BOOLEAN_TYPE, 0));
        ASSERT(PM_manage(pm, "name4", STRING_TYPE, 0));
        ASSERT(PM_manage(pm, "name5", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_hasValue(pm, "name3"));
        ASSERT(PM_hasValue(pm, "name4"));
        ASSERT(PM_hasValue(pm, "name5"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT((PM_getValue(pm, "name2").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_getValue(pm, "name3").bool_val == true);
        ASSERT(PM_getValue(pm, "name4").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name4").str_val, "string") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name5").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_int_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_real_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_boolean_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_string_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_list_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_all_optional_missing() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(5));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 0));
        ASSERT(PM_manage(pm, "name2", REAL_TYPE, 0));
        ASSERT(PM_manage(pm, "name3", BOOLEAN_TYPE, 0));
        ASSERT(PM_manage(pm, "name4", STRING_TYPE, 0));
        ASSERT(PM_manage(pm, "name5", LIST_TYPE, 0));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(!PM_hasValue(pm, "name1"));
        ASSERT(!PM_hasValue(pm, "name2"));
        ASSERT(!PM_hasValue(pm, "name3"));
        ASSERT(!PM_hasValue(pm, "name4"));
        ASSERT(!PM_hasValue(pm, "name5"));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_int_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_real_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 3.3;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT((PM_getValue(pm, "name").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_boolean_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = true;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").bool_val == true);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_string_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"string\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_list_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_pm_parse_all_required() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = 1;\n"
                "name2 = 3.3;\n"
                "name3 = true;\n"
                "name4 = \"string\";\n"
                "name5 = { \"string\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(5));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", REAL_TYPE, 1));
        ASSERT(PM_manage(pm, "name3", BOOLEAN_TYPE, 1));
        ASSERT(PM_manage(pm, "name4", STRING_TYPE, 1));
        ASSERT(PM_manage(pm, "name5", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_hasValue(pm, "name3"));
        ASSERT(PM_hasValue(pm, "name4"));
        ASSERT(PM_hasValue(pm, "name5"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT((PM_getValue(pm, "name2").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT(PM_getValue(pm, "name3").bool_val == true);
        ASSERT(PM_getValue(pm, "name4").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name4").str_val, "string") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name5").list_val));
        ASSERT(strcmp(str, "string") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "#Comment\n"
                "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_only() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "#Comment";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(DEFAULT_CREATE_VAL));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_inline() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1; #Comment";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_multiple() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1; #Comment #Comment";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_non_default() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "$Comment\n"
                "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, '$'));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_before_semicolon() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1 #Comment\n"
                ";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_before_value() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = #Comment\n"
                "1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_comment_before_equals() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name #Comment\n"
                "= 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_no_semicolon() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_no_required_value() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_no_equals() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_double_equals() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name == 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_wrong_type() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_parse_error_multiple_values() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 1 2;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 0));
        ASSERT(!PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_whitespace_more() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "   name   =   1   ;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_whitespace_less() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1=1;\n"
                "name2=2;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(2));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT(PM_getValue(pm, "name2").int_val == 2);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_whitespace_none() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1=1;name2=2;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(2));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT(PM_getValue(pm, "name2").int_val == 2);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_whitespace_multiline() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name =\n"
                "\n     "
                "1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_int_zero() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 0;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_int_negative() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = -1;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").int_val == -1);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_int_multiples() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = 1;\n"
                "name2 = 2;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(2));
        ASSERT(PM_manage(pm, "name1", INT_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", INT_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").int_val == 1);
        ASSERT(PM_getValue(pm, "name2").int_val == 2);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_real_no_decimal() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = 3;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", REAL_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT((PM_getValue(pm, "name").real_val - 3) <= REAL_THRESHOLD);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_real_multiples() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = 3.3;\n"
                "name2 = 4.4;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(2));
        ASSERT(PM_manage(pm, "name1", REAL_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", REAL_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT((PM_getValue(pm, "name1").real_val - 3.3) <= REAL_THRESHOLD);
        ASSERT((PM_getValue(pm, "name2").real_val - 4.4) <= REAL_THRESHOLD);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_boolean_false() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = false;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", BOOLEAN_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").bool_val == false);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_boolean_multiples() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = true;\n"
                "name2 = false;";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(2));
        ASSERT(PM_manage(pm, "name1", BOOLEAN_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", BOOLEAN_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").bool_val == true);
        ASSERT(PM_getValue(pm, "name2").bool_val == false);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_spaces() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"   string   \";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "   string   ") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_line_break() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"string\nmore\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "string\nmore") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_single_quotes() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"'string'\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "'string'") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_number() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = \"123\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name").str_val, "123") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_string_multiples() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = \"string1\";\n"
                "name2 = \"string2\";";
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(2));
        ASSERT(PM_manage(pm, "name1", STRING_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", STRING_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name1").str_val, "string1") == 0);
        ASSERT(PM_getValue(pm, "name2").str_val != NULL);
        ASSERT(strcmp(PM_getValue(pm, "name2").str_val, "string2") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_list_empty() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = {};";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        str = PL_next(PM_getValue(pm, "name").list_val);
        ASSERT(str == NULL);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_list_many_values() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = { \"string1\", \"string2\", \"string3\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string1") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string2") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string3") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_list_spaces() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = {   \"string1\"   ,   \"string2\"   };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string1") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string2") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_list_no_spaces() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = {\"string1\",\"string2\"};";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string1") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string2") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_list_line_breaks() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name = {\"string1\",\n"
                "\"string2\",\n"
                "\"string3\"\n"
                "};";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(1));
        ASSERT(PM_manage(pm, "name", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name"));
        ASSERT(PM_getValue(pm, "name").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string1") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string2") == 0);
        ASSERT(str = PL_next(PM_getValue(pm, "name").list_val));
        ASSERT(strcmp(str, "string3") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

int test_list_multiples() {
        ParameterManager *pm;
        FILE *fp;
        char *contents = "name1 = { \"string1\" };\n"
                "name2 = { \"string2\" };";
        char *str;
        fp = file_with_contents(contents);
        ASSERT(pm = PM_create(2));
        ASSERT(PM_manage(pm, "name1", LIST_TYPE, 1));
        ASSERT(PM_manage(pm, "name2", LIST_TYPE, 1));
        ASSERT(PM_parseFrom(pm, fp, DEFAULT_COMMENT));
        ASSERT(PM_hasValue(pm, "name1"));
        ASSERT(PM_hasValue(pm, "name2"));
        ASSERT(PM_getValue(pm, "name1").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name1").list_val));
        ASSERT(strcmp(str, "string1") == 0);
        ASSERT(PM_getValue(pm, "name2").list_val != NULL);
        ASSERT(str = PL_next(PM_getValue(pm, "name2").list_val));
        ASSERT(strcmp(str, "string2") == 0);
        ASSERT(PM_destroy(pm));
        fclose(fp);
        return 0;
}

FILE *file_with_contents(char *contents) {
        FILE *fp = fopen(TEST_FILENAME, "w");
        fprintf(fp, contents);
        fclose(fp);
        return fopen(TEST_FILENAME, "r");
}

int fork_test(int (*fn)()) {
        int test_val;
        int status;
        pid_t proc_id;

        /* Test runs in forked child process. */
        proc_id = fork();
        if (proc_id == 0) {
                test_val = (*fn)();
                exit(test_val);
        } else if (proc_id > 0) {
                wait(&status);
                return status;  /* In the event of a segfault, status will be non-zero. */
        } else {
                fprintf(stderr, "[a1test] Failed to fork test process. Exiting.\n");
                exit(1);
        }
}

void run_test(int (*fn)(), char *fn_name) {
        num_tests++;
        num_tests_suite++;
        printf("[a1test][TEST]: %s ", fn_name);
        fflush(stdout);
        if (fork_test(fn)) {
                printf(ANSI_COLOR_RED "[FAILURE]\n" ANSI_COLOR_RESET);
        } else {
                num_success++;
                num_success_suite++;
                printf(ANSI_COLOR_GREEN "[SUCCESS]\n" ANSI_COLOR_RESET);
        }
}

int main(int argc, char **argv) {
        /* Main functionality tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: Main functionality tests" ANSI_COLOR_RESET "\n");
        run_test(test_pm_create_destroy, "test_pm_create_destroy");
        run_test(test_pm_create_destroy_twice, "test_pm_create_destroy_twice");
        run_test(test_pm_create_destroy_large_size, "test_pm_create_destroy_large_size");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);
        

        /* PM_manage optional value tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: PM_manage optional value tests" ANSI_COLOR_RESET "\n");
        run_test(test_pm_manage_int_optional, "test_pm_manage_int_optional");
        run_test(test_pm_manage_real_optional, "test_pm_manage_real_optional");
        run_test(test_pm_manage_boolean_optional, "test_pm_manage_boolean_optional");
        run_test(test_pm_manage_string_optional, "test_pm_manage_string_optional");
        run_test(test_pm_manage_list_optional, "test_pm_manage_list_optional");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* PM_manage required value tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: PM_manage required value tests" ANSI_COLOR_RESET "\n");
        run_test(test_pm_manage_int_required, "test_pm_manage_int_required");
        run_test(test_pm_manage_real_required, "test_pm_manage_real_required");
        run_test(test_pm_manage_boolean_required, "test_pm_manage_boolean_required");
        run_test(test_pm_manage_string_required, "test_pm_manage_string_required");
        run_test(test_pm_manage_list_required, "test_pm_manage_list_required");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* PM_parseFrom optional value tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: PM_parseFrom optional value tests" ANSI_COLOR_RESET "\n");
        run_test(test_pm_parse_int_optional, "test_pm_parse_int_optional");
        run_test(test_pm_parse_real_optional, "test_pm_parse_real_optional");
        run_test(test_pm_parse_boolean_optional, "test_pm_parse_boolean_optional");
        run_test(test_pm_parse_string_optional, "test_pm_parse_string_optional");
        run_test(test_pm_parse_list_optional, "test_pm_parse_list_optional");
        run_test(test_pm_parse_all_optional, "test_pm_parse_all_optional");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* PM_parseFrom missing optional value tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: PM_parseFrom missing optional value tests" ANSI_COLOR_RESET "\n");
        run_test(test_pm_parse_int_optional_missing, "test_pm_parse_int_optional_missing");
        run_test(test_pm_parse_real_optional_missing, "test_pm_parse_real_optional_missing");
        run_test(test_pm_parse_boolean_optional_missing, "test_pm_parse_boolean_optional_missing");
        run_test(test_pm_parse_string_optional_missing, "test_pm_parse_string_optional_missing");
        run_test(test_pm_parse_list_optional_missing, "test_pm_parse_list_optional_missing");
        run_test(test_pm_parse_all_optional_missing, "test_pm_parse_all_optional_missing");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* PM_parseFrom required value tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: PM_parseFrom required value tests" ANSI_COLOR_RESET "\n");
        run_test(test_pm_parse_int_required, "test_pm_parse_int_required");
        run_test(test_pm_parse_real_required, "test_pm_parse_real_required");
        run_test(test_pm_parse_boolean_required, "test_pm_parse_boolean_required");
        run_test(test_pm_parse_string_required, "test_pm_parse_string_required");
        run_test(test_pm_parse_list_required, "test_pm_parse_list_required");
        run_test(test_pm_parse_all_required, "test_pm_parse_all_required");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* Comment tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: Comment tests" ANSI_COLOR_RESET "\n");
        run_test(test_comment, "test_comment");
        run_test(test_comment_only, "test_comment_only");
        run_test(test_comment_inline, "test_comment_inline");
        run_test(test_comment_multiple, "test_comment_multiple");
        run_test(test_comment_non_default, "test_comment_non_default");
        run_test(test_comment_before_semicolon, "test_comment_before_semicolon");
        run_test(test_comment_before_value, "test_comment_before_value");
        run_test(test_comment_before_equals, "test_comment_before_equals");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* Parse error tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: Parse error tests" ANSI_COLOR_RESET "\n");
        run_test(test_parse_error_no_semicolon, "test_parse_error_no_semicolon");
        run_test(test_parse_error_no_required_value, "test_parse_error_no_required_value");
        run_test(test_parse_error_no_equals, "test_parse_error_no_equals");
        run_test(test_parse_error_double_equals, "test_parse_error_double_equals");
        run_test(test_parse_error_wrong_type, "test_parse_error_wrong_type");
        run_test(test_parse_error_multiple_values, "test_parse_error_multiple_values");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* Whitespace tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: Whitespace tests" ANSI_COLOR_RESET "\n");
        run_test(test_whitespace_more, "test_whitespace_more");
        run_test(test_whitespace_less, "test_whitespace_less");
        run_test(test_whitespace_none, "test_whitespace_none");
        run_test(test_whitespace_multiline, "test_whitespace_multiline");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);
        
        /* INT_TYPE tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: INT_TYPE tests" ANSI_COLOR_RESET "\n");
        run_test(test_int_zero, "test_int_zero");
        run_test(test_int_negative, "test_int_negative");
        run_test(test_int_multiples, "test_int_multiples");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* REAL_TYPE tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: REAL_TYPE tests" ANSI_COLOR_RESET "\n");
        run_test(test_real_no_decimal, "test_real_no_decimal");
        run_test(test_real_multiples, "test_real_multiples");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* BOOLEAN_TYPE tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: BOOLEAN_TYPE tests" ANSI_COLOR_RESET "\n");
        run_test(test_boolean_false, "test_boolean_false");
        run_test(test_boolean_multiples, "test_boolean_multiples");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* STRING_TYPE tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: STRING_TYPE tests" ANSI_COLOR_RESET "\n");
        run_test(test_string_spaces, "test_string_spaces");
        run_test(test_string_line_break, "test_string_line_break");
        run_test(test_string_single_quotes, "test_string_single_quotes");
        run_test(test_string_number, "test_string_number");
        run_test(test_string_multiples, "test_string_multiples");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        /* LIST_TYPE tests */
        num_tests_suite = 0;
        num_success_suite = 0;
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: LIST_TYPE tests" ANSI_COLOR_RESET "\n");
        run_test(test_list_empty, "test_list_empty");
        run_test(test_list_many_values, "test_list_many_values");
        run_test(test_list_spaces, "test_list_spaces");
        run_test(test_list_no_spaces, "test_list_no_spaces");
        run_test(test_list_line_breaks, "test_list_line_breaks");
        run_test(test_list_multiples, "test_list_multiples");
        printf(ANSI_COLOR_YELLOW "[a1test][TEST SUITE]: %d/%d tests succeeded " ANSI_COLOR_RESET "\n\n", num_success_suite, num_tests_suite);

        printf(ANSI_COLOR_YELLOW "[a1test] Total: %d/%d tests succeeded." ANSI_COLOR_RESET "\n", num_success, num_tests);
        unlink(TEST_FILENAME);
        return 0;
}
