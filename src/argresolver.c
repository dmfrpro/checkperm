#include <regex.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "argresolver.h"
#include "argerror.h"

bool parse_args(struct args_struct *arguments, int argc, const char *argv[MAX_STRING_SIZE]) {
    if (argc != ARGUMENTS_NUMBER)
        perror_invalid_argc(ARGUMENTS_NUMBER - 1, argc - 1);

    bool got_user_name = false;
    bool got_group_name = false;
    bool got_target_dir = false;

    // TODO: Resolve problems with user and group name regex. According to /etc/adduser.conf
    //  user and group names in Ubuntu follow the same regex as user names and may contain
    //  '$' char at the end. However, I got failure on creating group with name "group$"
    //  (without quotes), and user with name "a$". Moreover, useradd does not check any
    //  restrictions. For now, it accepts users and groups without '$' in their names.
    regex_t name_regex;
    regcomp(&name_regex, "^[a-z][-a-z0-9]{0,31}$", REG_EXTENDED);

    for (int i = 1; i < argc; i += 2) {
        if (is_user_name(argv[i])) {
            if (!got_user_name) {
                got_user_name = true;

                if (regexec(&name_regex, argv[i + 1], 0, NULL, 0))
                    perror_invalid_user_name(argv[i + 1]);

                strncpy(arguments->user_name, argv[i + 1], MAX_STRING_SIZE);
            }

        } else if (is_group_name(argv[i])) {
            if (!got_group_name) {
                got_group_name = true;

                if (regexec(&name_regex, argv[i + 1], 0, NULL, 0))
                    perror_invalid_group_name(argv[i + 1]);

                strncpy(arguments->group_name, argv[i + 1], MAX_STRING_SIZE);
            }

        } else if (is_target_dir(argv[i])) {
            if (!got_target_dir) {
                got_target_dir = true;

                if (access(argv[i + 1], F_OK) == -1)
                    perror_invalid_target_dir(argv[i + 1]);

                char *abs_path = malloc(sizeof(char) * MAX_STRING_SIZE);
                realpath(argv[i + 1], abs_path);

                strncpy(arguments->target_dir, abs_path, MAX_STRING_SIZE);
                free(abs_path);
            }
        } else
            perror_invalid_option(argv[i]);
    }

    if (!got_user_name)
        perror_argument_not_given("user_name");

    if (!got_group_name)
        perror_argument_not_given("group_name");

    if (!got_target_dir)
        perror_argument_not_given("target_dir");

    return true;
}
