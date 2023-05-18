//
// Created by padfoot on 5/13/23.
//

#pragma once

#include <stdbool.h>
#include "../../server/server_list/server_list.h"

#include "../../options.h"
#include "../../../lib/user_info/user_info.h"

bool is_input_valid(char user_input);

bool is_input_yes(char user_input) ;

char read_user_input() ;

bool check_should_save_user_info() ;

bool user_info_file_exists();

bool server_list_exists();

void handle_user_file_exists(user_info_t *user);

void handle_user_name_does_not_exist(user_info_t *user, Options *opts);

void populate_user(user_info_t *user, Options *opts);

unsigned int read_server_port() ;

bool ask_user_to_connect();

void ask_user_to_add_server(server_list_t *server_list, user_info_t *user);
