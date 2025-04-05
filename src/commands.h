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

#ifndef COMMANDS_H
#define COMMANDS_H

#include "command_tree.h"

CommandFixedArglistCallback panelcmd_j_cb;
CommandFixedArglistCallback panelcmd_k_cb;

const Command PANEL_COMMANDS[] = {
    CMD_FIXED_ARGLIST("j", 0, panelcmd_j_cb),
    CMD_FIXED_ARGLIST("k", 0, panelcmd_k_cb),
};

CommandFixedArglistCallback newpanel_cb;
CommandFixedArglistCallback open_cb;
CommandFixedArglistCallback set_cb;
CommandFixedArglistCallback panelsync_cb;
CommandFixedArglistCallback paneldesync_cb;
CommandFixedArglistCallback findpc_cb;
CommandFixedArglistCallback findinst_cb;
CommandFixedArglistCallback quit_cb;

const Command COMMANDS[] = {
    CMD_ALIAS("n", "newpanel"),
    CMD_FIXED_ARGLIST("newpanel", 0, newpanel_cb),
    CMD_ALIAS("o", "open"),
    CMD_FIXED_ARGLIST("open", 1, open_cb),
    CMD_SUBCOMMAND("panelcmd", PANEL_COMMANDS),
    CMD_FIXED_ARGLIST("set", 2, set_cb),
    CMD_FIXED_ARGLIST("panelsync", 0, panelsync_cb),
    CMD_FIXED_ARGLIST("paneldesync", 0, paneldesync_cb),
    CMD_FIXED_ARGLIST("findpc", 1, findpc_cb),
    CMD_FIXED_ARGLIST("findinst", 1, findinst_cb),
    CMD_ALIAS("q", "quit"),
    CMD_FIXED_ARGLIST("quit", 0, quit_cb),
};

#endif
