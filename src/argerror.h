#ifndef CHECKPERM_ARGERROR_H
#define CHECKPERM_ARGERROR_H

#define ARGUMENTS_NUMBER 7

static void perror_with_message(const char *fmt, ...);

static void perror_invalid_argument(const char *arg_name, const char *value);

void perror_invalid_argc(int expected_argc, int actual_argc);

void perror_invalid_option(const char *option);

void perror_argument_not_given(const char *option);

void perror_invalid_user_name(const char *value);

void perror_invalid_group_name(const char *value);

void perror_invalid_target_dir(const char *value);

#endif // CHECKPERM_ARGERROR_H
