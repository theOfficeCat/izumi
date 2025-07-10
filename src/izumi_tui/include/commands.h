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
#include "window.h"

CommandNoArgsCallback panelcmd_j_cb;
CommandNoArgsCallback panelcmd_k_cb;

const Command PANEL_COMMANDS[] = {
    CMD_NO_ARGS("j", panelcmd_j_cb),
    CMD_NO_ARGS("k", panelcmd_k_cb),
};

CommandNoArgsCallback newpanel_cb;
CommandArglistCallback closepanel_cb;
CommandNoArgsCallback closeallpanels_cb;
CommandFixedArglistCallback open_cb;
CommandArglistCallback set_cb;
CommandNoArgsCallback panelsync_cb;
CommandNoArgsCallback paneldesync_cb;
CommandFixedArglistCallback findpc_cb;
CommandFixedArglistCallback findinst_cb;
CommandNoArgsCallback next_cb;
CommandNoArgsCallback prev_cb;
CommandArglistCallback reload_cb;
CommandNoArgsCallback quit_cb;

const Command COMMANDS[] = {
    CMD_ALIAS("n", "newpanel"),
    CMD_NO_ARGS("newpanel", newpanel_cb),
    CMD_ALIAS("c", "closepanel"),
    CMD_ARGLIST("closepanel", closepanel_cb),
    CMD_ALIAS("ca", "closeallpanels"),
    CMD_NO_ARGS("closeallpanels", closeallpanels_cb),
    CMD_ALIAS("o", "open"),
    CMD_FIXED_ARGLIST("open", 1, open_cb),
    CMD_SUBCOMMAND("panelcmd", PANEL_COMMANDS),
    CMD_ARGLIST("set", set_cb),
    CMD_NO_ARGS("panelsync", panelsync_cb),
    CMD_NO_ARGS("paneldesync", paneldesync_cb),
    CMD_FIXED_ARGLIST("findpc", 1, findpc_cb),
    CMD_FIXED_ARGLIST("findinst", 1, findinst_cb),
    CMD_NO_ARGS("next", next_cb),
    CMD_NO_ARGS("prev", prev_cb),
    CMD_ALIAS("r", "reload"),
    CMD_ARGLIST("reload", reload_cb),
    CMD_ALIAS("q", "quit"),
    CMD_NO_ARGS("quit", quit_cb),
};

#endif
