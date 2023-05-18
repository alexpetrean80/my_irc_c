//
// Created by padfoot on 5/14/23.
//

#include "menu.h"
#include "../../options.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
  char *messages[6] = {"Menu:",           "", "1: Choose servers.",
                       "2: Change name.", "", "3: Exit."};
  for (unsigned short i = 0; i < 6; i++) {
    puts(messages[i]);
  }
}

void choose_servers() {}

void change_name() {}

void run_menu(server_list_t *server_list, user_info_t *user, Options *opts) {
  for (;;) {
    print_menu();
    char user_input = (char)getchar();
    switch (user_input) {
    case '1':
      choose_servers();
      break;
    case '2':
      change_name();
    case '3':
      free_server_list(server_list);
      if (opts->should_save_user_info) {
        puts(user->name);
        int err = store_user_info(user->name, user->ip_addr);
        if (err) {
          perror("Could not save user info.");
          exit(EXIT_FAILURE);
        }
      }
      exit(0);
    default:
      puts("Wrong answer.");
    }
  }
}
