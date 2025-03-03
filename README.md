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

- ncurses
- meson (build only)
- ninja (build only, can be replaced by other meson backends)

## Building

Building with `meson` is recommended:

```bash
meson setup build
cd build
meson compile
```

But, if the classic `make` sequence is hard-wired in your brain, you can:

```bash
./configure
make
```

In both cases the binary will be found in `build/izumi`.

## Usage

```bash
$ cd build # if not done yet
$ ./izumi <input_file> [-p]
```

- `input_file`: The input file in Onikiri2-Kanata format
- `-p`: Print the data of the pipeline to the terminal before visualizing with
the ncurses frontend

## Screenshot

![Screenshot](.github/screenshot.jpg)

I know it's not the best looking tool, but it's a start (now it has colors :D).

---

![Izumi Konata](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fstatic.zerochan.net%2FIzumi.Konata.full.955876.jpg&f=1&nofb=1&ipt=11ebd39eb2229bec63db528410089c03d01dd9a541df01063ee5c809b6c69f58&ipo=images)
