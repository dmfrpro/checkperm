#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include "argresolver.h"

void walk(char *abs_path, const char *user_name, const char *group_name) {
    if (strncmp(abs_path, "/proc", 5) == 0 || strncmp(abs_path, "/sys", 4) == 0)
        return;

    DIR *dir_stream = opendir(abs_path);

    if (dir_stream == NULL)
        return;

    struct dirent *dir_entry;
    struct stat file_stat;
    struct passwd *user;
    struct group *group;

    char entry_abs_path[MAX_STRING_SIZE];
    bool is_dir, is_usr_write_permissions, is_grp_write_permissions, is_available_for_all;


    while ((dir_entry = readdir(dir_stream)) != NULL) {
        if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0)
            continue;

        snprintf(entry_abs_path, sizeof(entry_abs_path), "%s/%s", abs_path, dir_entry->d_name);

        if (lstat(entry_abs_path, &file_stat) == -1 || S_ISLNK(file_stat.st_mode))
            continue;

        is_dir = S_ISDIR(file_stat.st_mode);

        user = getpwuid(file_stat.st_uid);
        group = getgrgid(file_stat.st_gid);

        is_usr_write_permissions = strcmp(user->pw_name, user_name) == 0 && (file_stat.st_mode & S_IWUSR);
        is_grp_write_permissions = strcmp(group->gr_name, group_name) == 0 && (file_stat.st_mode & S_IWGRP);
        is_available_for_all = file_stat.st_mode & S_IWOTH;

        if (is_usr_write_permissions || is_grp_write_permissions || is_available_for_all)
            printf("%c %s\n", is_dir ? 'd' : 'f', entry_abs_path);

        if (is_dir)
            walk(entry_abs_path, user_name, group_name);
    }
}

int main(int argc, const char **argv) {
    struct args_struct arguments;
    parse_args(&arguments, argc, argv);
    walk(arguments.target_dir, arguments.user_name, arguments.group_name);
}
