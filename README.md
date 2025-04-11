# Izumi

Izumi is an instruction pipeline visualizer for Onikiri2-Kanata format based on [shioyadan/Konata](https://github.com/shioyadan/Konata).

> [!Note]
> The tool is still under development and may not work properly with full
> features of the format.

## Supported features

- Instruction

    Only support for file identificator
- Stage
- Line on left
- End of stage (for multiple cycle stages/stalling the pipeline)
- End of instruction

## Requierments

- `ncurses`
- `meson` (build only) *[version >=1.2.0]*
- `ninja` (build only, can be replaced by other meson backends)
- `python3` (build only)

## Building (and installing)

Building with `meson` is recommended:

```bash
meson setup build
cd build
meson compile
meson install
```
> [!IMPORTANT]
> meson needs to be available as root for `meson install`

But, if the classic `make` sequence is hard-wired in your brain, you can:

```bash
./configure
make
make install
```

You can also use `nix` (flakes recommended):
```bash
nix run github:theOfficeCat/Izumi
```
## Usage

```bash
$ make run # If you want to test before installing
$ izumi (path/to/file)
```

> [!IMPORTANT]
> In some cases an `AddressSanitizer:DEADLYSIGNAL` error can be raised randomly when starting the program. Just kill the program and try again. If it persists, please report it.

> [!NOTE]
> Some example files supported are on `examples` directory. These are generated on the RISC-V core [Sargantana](https://github.com/bsc-loca/core_tile/).

### Commands

| Command | Description |
|---------|-------------|
| `:q`    | Quit        |
| `:quit` | Quit        |
| `:open (path)`    | Open a file on the current panel |
| `:findpc 0x(address)` | Search and go to the first appearance of the address |
| `:findinst (instruction)` | Search and go to the first appearance of the instruction |
| `:next` | Next appearance of the last search |
| `:prev` | Previous appearance of the last search |
| `:newpanel` | Create a new panel |
| `:panelcmd j` | Select next panel |
| `:panelcmd k` | Select previous panel |
| `:closepanel` | Close focused panel |
| `:closepanel (index)` | Close selected panel |
| `:closeallpanels` | Close all panels |
| `:set bar_offset (amount)` | Set offset of the vertical bar (not persistent) |
| `:set stage_width (amount)` | Set width of the stage on the pipeline visualizer (not persistent) |
| `:panelsync` | Sync movement of all the panels |
| `:paneldesync` | Desync movement of all the panels |


### Keybindings

| Key | Description |
|-----|-------------|
| `n` | Next appearance of the last search |
| `N` | Previous appearance of the last search |
| `j` | Move down |
| `KEY_DOWN` | Move down |
| `k` | Move up |
| `KEY_UP` | Move up |

## Screenshot

![Screenshot](.github/screenshot.png)

I know it's not the best looking tool, but it's a start (now it has colors :D).

---

![Izumi Konata](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fstatic.zerochan.net%2FIzumi.Konata.full.955876.jpg&f=1&nofb=1&ipt=11ebd39eb2229bec63db528410089c03d01dd9a541df01063ee5c809b6c69f58&ipo=images)
