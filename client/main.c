#include "options.h"
#include "server/server_list/server_list.h"
#include "ui/menu/menu.h"
#include "ui/utils/utils.h"
#include <stdio.h>
#include "../lib/user_info/user_info.h"

int main() {
  puts("Hello, welcome to my irc.");
  puts("Retrieving user info...");

  user_info_t user;
  server_list_t *server_list;
  Options opts;
  opts.should_save_user_info = false;

  populate_user(&user, &opts);
  if (server_list_exists()) {
    server_list = read_server_list_from_file();
  } else {
    server_list = init_server_list();
  }

  if (0 == server_list->size) {
    ask_user_to_add_server(server_list, 0);
  } else {
    run_menu(server_list, &user, &opts);
  }

  return 0;
}
