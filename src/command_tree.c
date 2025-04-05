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

#include <ctype.h>
#include <string.h>

#include "command_tree.h"
#include "commands.h"

int command_arg_count(const char * const command) {
    int argc = 0;
    bool on_whitespace = true; // This allows us to ignore leading whitespace

    for (int i = 0; command[i] != '\0'; ++i) {
        bool on_whitespace_before = on_whitespace;
        on_whitespace = isspace(command[i]);

        // This handles repeated whitespace
        if (on_whitespace && !on_whitespace_before) ++argc;
    }

    // This handles trailing whitespace
    if (on_whitespace) --argc;

    return argc;
}

void split_command_arguments(char * const command, int argc, char ** const argv) {
    char * command_iter = command;

    for (int i = 0; i < argc+1; ++i) {
        // Skip leading whitespace
        while (isspace(*command_iter)) ++command_iter;

        // Save the command or argument start
        argv[i] = command_iter;

        // Skip to trailing whitespace or string end
        while (*command_iter != '\0' && !isspace(*command_iter)) ++command_iter;

        // Replace the whitespace with a null character to split the string
        *command_iter = '\0';

        // Skip the inserted null character. If this was the last null character
        // the pointer will be dangling, but argc will protect us from reading it.
        ++command_iter;
    }
}

bool traverse_command_tree(ApplicationData *app_data, const Command * const commands, size_t commands_length, const char * const command_name, int argc, const char * const * const argv) {
    for (unsigned int i = 0; i < commands_length; ++i) {
        if (strcmp(command_name, commands[i].cmd) != 0) continue;
        const Command * const command = commands + i;
        
        switch (command->type) {
        case COMMAND_TYPE_ARGLIST:
            return command->arglist.callback(app_data, argc, argv);
        case COMMAND_TYPE_FIXED_ARGLIST:
            if (argc != command->fixed_arglist.argc) return false;
            return command->fixed_arglist.callback(app_data, argv);
        case COMMAND_TYPE_SUBCOMMAND:
            if (argc == 0) return false;
            return traverse_command_tree(app_data, command->subcommand.subcommands, command->subcommand.subcommands_length, argv[0], argc - 1, argv + 1);
        case COMMAND_TYPE_ALIAS:
            return traverse_command_tree(app_data, command + 1, commands_length - i - 1, command->alias.real_cmd, argc, argv);
        }
    }
    
    // If we arrive here, nothing has matched
    return false;
}

bool run_command(ApplicationData *app_data) {
    char command[strlen(app_data->command) + 1];
    strcpy(command, app_data->command);

    int argc = command_arg_count(command);

    char * argv[argc+1]; // Contains the command, we later get rid of it
    split_command_arguments(command, argc, argv);

    const char * command_name = argv[0];
    const char * const * const command_argv = (const char * const * const) argv + 1;
    
    return traverse_command_tree(app_data, COMMANDS, sizeof(COMMANDS) / sizeof(COMMANDS[0]), command_name, argc, command_argv);
}
