/*
 * This file is part of Izumi.
 *
 * Izumi is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Izumi is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Izumi. If not, see <https://www.gnu.org/licenses/>.
 */
 
#ifndef COMMAND_TREE_H
#define COMMAND_TREE_H

#include <stdbool.h>
#include <stdio.h>

#include "window.h"

bool run_command(ApplicationData *app_data);

struct Command_s;
typedef struct Command_s Command;

enum CommandType_e {
    COMMAND_TYPE_ARGLIST,
    COMMAND_TYPE_FIXED_ARGLIST,
    COMMAND_TYPE_SUBCOMMAND,
    COMMAND_TYPE_ALIAS,
};

typedef enum CommandType_e CommandType;

typedef bool(CommandArglistCallback)(ApplicationData *app_data, int argc, const char * const argv[]);

struct CommandArglist_s {
    CommandArglistCallback * callback;
};

typedef struct CommandArglist_s CommandArglist;

typedef bool(CommandFixedArglistCallback)(ApplicationData *app_data, const char * const argv[]);

struct CommandFixedArglist_s {
    int argc;
    CommandFixedArglistCallback * callback;
};

typedef struct CommandFixedArglist_s CommandFixedArglist;

struct CommandSubcommand_s {
    const Command * const subcommands;
    const size_t subcommands_length;
};

typedef struct CommandSubcommand_s CommandSubcommand;

struct CommandAlias_s {
    const char * const real_cmd;
};

typedef struct CommandAlias_s CommandAlias;

struct Command_s {
    const char * const cmd;
    CommandType type;
    union {
        CommandArglist arglist;
        CommandFixedArglist fixed_arglist;
        CommandSubcommand subcommand;
        CommandAlias alias;
    };
};

#define CMD_ARGLIST(cmd, callback)             { cmd, COMMAND_TYPE_ARGLIST, { .arglist = { callback } } }
#define CMD_FIXED_ARGLIST(cmd, argc, callback) { cmd, COMMAND_TYPE_FIXED_ARGLIST, { .fixed_arglist = { argc, callback } } }
#define CMD_SUBCOMMAND(cmd, subcommands)       { cmd, COMMAND_TYPE_SUBCOMMAND, { .subcommand = { subcommands, sizeof(subcommands) / sizeof(subcommands[0]) } } }
#define CMD_ALIAS(cmd, real_cmd)               { cmd, COMMAND_TYPE_ALIAS, { .alias = { real_cmd } } }

#endif
