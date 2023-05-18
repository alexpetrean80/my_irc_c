//
// Created by padfoot on 5/13/23.
//

#pragma once

#include <stdbool.h>
#include "../../server/server_list/server_list.h"

#include "../../options.h"
#include "user_info.h"

bool is_input_valid(char user_input);

bool is_input_yes(char user_input) ;

char read_user_input() ;

bool check_should_save_user_info() ;

bool user_info_file_exists();

bool server_list_exists();

void handle_user_file_exists(UserInfo *user);

void handle_user_name_does_not_exist(UserInfo *user, Options *opts);

void populate_user(UserInfo *user, Options *opts);

unsigned int read_server_port() ;

bool ask_user_to_connect();

void ask_user_to_add_server(ServerList *server_list, UserInfo *user);