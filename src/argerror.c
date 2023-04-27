#include <stdlib.h>
#include <error.h>
#include <stdio.h>
#include <stdarg.h>

#include "argerror.h"

#define VARARGS_BUF_SIZE 512

static void perror_with_message(const char *fmt, ...) {
    va_list varargs;
    char buf[VARARGS_BUF_SIZE];

    va_start(varargs, fmt);
    vsnprintf(buf, sizeof(buf), fmt, varargs);
    error(EXIT_FAILURE, 0, "%s", buf);
    va_end(varargs);
}

static void perror_invalid_argument(const char *arg_name, const char *value) {
    perror_with_message("Invalid argument %s: %s\n", arg_name, value);
}

void perror_invalid_option(const char *option) {
    perror_with_message("Invalid option %s\n", option);
}

void perror_invalid_argc(int expected_argc, int actual_argc) {
    perror_with_message("Expected %d arguments, got %d\n", expected_argc, actual_argc);
}

void perror_argument_not_given(const char *option) {
    perror_with_message("Expected: %s, but were not given\n", option);
}

void perror_invalid_user_name(const char *value) {
    perror_invalid_argument("user_name", value);
}

void perror_invalid_group_name(const char *value) {
    perror_invalid_argument("group_name", value);
}

void perror_invalid_target_dir(const char *value) {
    perror_invalid_argument("target_dir", value);
}

