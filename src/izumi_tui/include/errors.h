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

#ifndef ERRORS_H
#define ERRORS_H

#include <stdint.h>
#include <stdio.h>

enum errors_e {
    ERR_MAX_WINS, // TODO
    ERR_PANEL_NOT_FOUND, // TODO
    ERR_NO_PANELS, // TODO
    ERR_FILE_NOT_FOUND,
    ERR_FILE_NOT_A_FILE,
    ERR_FILE_WRONG_FORMAT, // TODO on parser
    ERR_CONFIG_NOT_FOUND,
    ERR_CONFIG_WRONG_FORMAT, // TODO
    ERR_FIND_NOT_FOUND,
    ERR_NEXT_NOT_FOUND,
    ERR_PREV_NOT_FOUND,
    ERR_WRONG_COMMAND,
    ERR_INCORRECT_ARGS,
    ERR_WRONG_ARG_VALUE,
    CORRECT
};

typedef enum errors_e errors;

static const char *error_messages[] = {
    "Too many windows",
    "Panel not found",
    "No panels",
    "File not found",
    "File is not a file",
    "File has wrong format",
    "Config option not found",
    "Config option has wrong format",
    "Find pattern not found",
    "Next pattern not found",
    "Previous pattern not found",
    "Wrong command",
    "Incorrect arguments",
    NULL
};

#endif
