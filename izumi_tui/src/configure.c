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

#include "configure.h"
#include "command_tree.h"
#include "window.h"

#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *get_config_path() {
    char *path = malloc(PATH_MAX);
    if (path == NULL) return NULL;

    const char *home = getenv("HOME");

    if (home == NULL) {
        free(path);
        return NULL;
    }

    strcpy(path, home);

    if (strlen(path) + strlen("/.config/izumi/config") > PATH_MAX) {
        free(path);
        return NULL;
    }

    strcat(path, "/.config/izumi/config");

    return path;
}

char **read_config_file(char *path) {
    FILE *file = fopen(path, "r");
    free(path);
    if (file == NULL) return NULL;

    char **commands = malloc(10 * sizeof(char *)); // Initial allocation for 10 commands
    int command_count = 0;

    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file) != -1) {
        // Remove trailing newline character
        size_t line_length = strlen(line);
        if (line_length > 0 && line[line_length - 1] == '\n') {
            line[line_length - 1] = '\0';
        }

        // Ignore empty lines and comments
        if (line[0] == '\0' || line[0] == '#') continue;

        // Allocate memory for the command
        commands[command_count] = malloc((line_length + 1) * sizeof(char));
        if (commands[command_count] == NULL) {
            for (int i = 0; i < command_count; i++) {
                free(commands[i]);
            }
            free(commands);
            return NULL; // Memory allocation failed
            //fprintf(stderr, "Error: Memory allocation failed\n");
            //exit(1);
        }

        strcpy(commands[command_count], line);
        command_count++;

        // Resize the array if necessary
        if (command_count % 10 == 0) {
            commands = realloc(commands, (command_count + 10) * sizeof(char *));
            if (commands == NULL) {
                for (int i = 0; i < command_count; i++) {
                    free(commands[i]);
                }
                free(commands);

                return NULL; // Memory reallocation failed

                //fprintf(stderr, "Error: Memory reallocation failed\n");
                //exit(1);
            }
        }
    }

    free(line);
    fclose(file);

    // Resize the array to the actual number of commands
    commands = realloc(commands, (command_count + 1) * (sizeof(char *) + 1));
    if (commands == NULL) {
        for (int i = 0; i < command_count; i++) {
            free(commands[i]);
        }
        free(commands);
        return NULL; // Memory reallocation failed
        //fprintf(stderr, "Error: Memory reallocation failed\n");
        //exit(1);
    }

    // Null-terminate the array
    commands[command_count] = NULL;
    return commands;
}

bool execute_config_commands(ApplicationData *app_data, char **commands) {
    if (commands == NULL) return false;

    for (int i = 0; commands[i] != NULL; i++) {
        char *command = commands[i];

        if (app_data->command != NULL) {
            free(app_data->command);
        }

        app_data->command = malloc(strlen(command) + 1);
        if (app_data->command == NULL) {
            for (int j = 0; commands[j] != NULL; j++) {
                free(commands[j]);
            }
            free(commands);
            return false; // Memory allocation failed
        }
        strcpy(app_data->command, command);

        // Execute the command
        run_command(app_data);
    }

    for (int j = 0; commands[j] != NULL; j++) {
        free(commands[j]);
    }
    free(commands);

    return true;
}
