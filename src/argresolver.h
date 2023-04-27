#ifndef CHECKPERM_ARGRESOLVER_H
#define CHECKPERM_ARGRESOLVER_H

#include <string.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 255

#define SHORT_OPTION_USER_NAME   "-u"
#define SHORT_OPTION_GROUP_NAME  "-g"
#define SHORT_OPTION_TARGET_DIR  "-p"

#define FULL_OPTION_USER_NAME    "--user-name"
#define FULL_OPTION_GROUP_NAME   "--group-name"
#define FULL_OPTION_TARGET_DIR   "--target-dir"

#define is_user_name(arg)                                               \
    strcmp(SHORT_OPTION_USER_NAME, (arg)) == 0 ||                       \
    strcmp(FULL_OPTION_USER_NAME, (arg)) == 0

#define is_group_name(arg)                                              \
    strcmp(SHORT_OPTION_GROUP_NAME, (arg)) == 0 ||                      \
    strcmp(FULL_OPTION_GROUP_NAME, (arg)) == 0

#define is_target_dir(arg)                                              \
    strcmp(SHORT_OPTION_TARGET_DIR, (arg)) == 0 ||                      \
    strcmp(FULL_OPTION_TARGET_DIR, (arg)) == 0

struct args_struct {
    char user_name[MAX_STRING_SIZE];
    char group_name[MAX_STRING_SIZE];
    char target_dir[MAX_STRING_SIZE];
};

bool parse_args(struct args_struct *arguments,
                int argc,
                const char *argv[MAX_STRING_SIZE]);

#endif // CHECKPERM_ARGRESOLVER_H
