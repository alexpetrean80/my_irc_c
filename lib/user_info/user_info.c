#include "user_info.h"

short read_user_info(UserInfo *user) {
    FILE *fd;
    // retrieve userinfo file
    fd = fopen(USER_INFO_FILE_NAME, "r");
    if (fd == NULL) {
        return -1;
    }

    char user_name[MAX_LENGTH];

    fgets(user->name, MAX_LENGTH - 1, fd);
    fgets(user->ip_addr, MAX_LENGTH - 1, fd);
    fclose(fd);

    return 0;
}

short store_user_info(char *user_name, char *ip_addr) {
    FILE *fd;
    // retrieve userinfo file
    fd = fopen(USER_INFO_FILE_NAME, "w");

    if (fd == NULL) {
        return -1;
    }
    fputs(user_name, fd);
    fputs(ip_addr, fd);
    fclose(fd);

    return 0;
}
