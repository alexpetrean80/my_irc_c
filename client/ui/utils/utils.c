//
// Created by padfoot on 5/13/23.
//

#include "utils.h"
#include "../menu/menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


bool is_input_valid(char user_input) {
    return (user_input == 'Y' || user_input == 'y' || user_input == 'N' ||
            user_input == 'n');
}

bool is_input_yes(char user_input) {
    return user_input == 'y' || user_input == 'Y';
}

char read_user_input() {
    char user_input;
    do {
        user_input = (char) getchar();
    } while (!is_input_valid(user_input));
    return user_input;
}

bool check_should_save_user_info() {
    bool should_save = false;

    puts("Do you want the info to be stored for easy access in the future? (Y/n)");
    char user_input = read_user_input();
    if (is_input_yes(user_input)) {
        should_save = true;
        puts("Your user info will be saved at the end of the session.");
    }
    return should_save;
}

bool user_info_file_exists() {
    return 0 == access(USER_INFO_FILE_NAME, F_OK);
}

bool server_list_exists() {
    return 0 == access(SERVER_LIST_FILE_NAME, F_OK);
}


void handle_user_file_exists(UserInfo *user) {
    if (0 != read_user_info(user)) {
        perror("Cannot read user info.");
    }
}

void handle_user_name_does_not_exist(UserInfo *user, Options *opts) {
    puts("User info not stored. Who are you?");
    printf("Name: ");
    scanf("%s", user->name);

    opts->should_save_user_info = check_should_save_user_info();

}

void populate_user(UserInfo *user, Options *opts) {
    if (user_info_file_exists()) {
        handle_user_file_exists(user);
    } else {
        handle_user_name_does_not_exist(user, opts);
    }
}

unsigned int read_server_port() {
    unsigned int server_port = 0;
    bool ok = false;
    char input[MAX_LENGTH];
    char *endptr;
    errno = 0;
    do {
        if (NULL == fgets(input, sizeof(input), stdin)) {
            perror("Input error.");
            exit(EXIT_FAILURE);
        }
        server_port = (unsigned int) strtol(input, &endptr, 10);
        if (errno != 0 || endptr == input || *endptr != '\n') {
            perror("Port must be a number.");
        } else {
            ok = true;
        }
    } while (!ok);
    return server_port;
}

bool ask_user_to_connect() {
    puts("Do you want to connect automatically?");
    return read_user_input();
}

void ask_user_to_add_server(ServerList *server_list, UserInfo *user) {
    puts("You have no saved servers. Would you like to add one now? (Y/n)");
    char user_info = read_user_input();

    if (!is_input_yes(user_info)) {
        puts("Exiting...");
        exit(0);
    }

    char server_name[MAX_LENGTH];
    printf("Server alias:");
    if (NULL == fgets(server_name, MAX_LENGTH - 1, stdin)) {
        perror("Name too long.");
        exit(EXIT_FAILURE);
    }
    char server_ip[MAX_LENGTH];
    printf("Server IP:");
    if (NULL == fgets(server_ip, MAX_LENGTH - 1, stdin)) {
        perror("Name too long.");
        exit(EXIT_FAILURE);
    }
    printf("Server port:");
    unsigned int server_port = read_server_port();
    append_server_list(server_list, server_name, server_ip, server_port);

    bool should_connect = ask_user_to_connect();
    if (should_connect) {
        // handle server connection
    } else {
        run_menu(server_list, user, NULL);
    }
}


