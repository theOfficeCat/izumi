# Izumi project

The izumi project englobes the `izumi_tui` instruction pipeline dump visualizer and its support library, `libizumi`.

This repository serves as a central hub for all the project components, providing a unified build system for them. Clone this repository if you want to easily setup a development environment or build all the components at once.

> [!Note]
> The library and the visualizer are still under development and things may break, specially if you are not careful when choosing the right versions for each one. If you are not actively developing Izumi, please use the `main` branch of this repository and its referenced submodule commits to ensure stability.

## Components
- [libizumi](https://github.com/Izumi-visualizer/libizumi):  a multi-format instruction pipeline dump parser library.
- [izumi_tui](https://github.com/Izumi-visualizer/izumi_tui):  a multi-format instruction pipeline dump TUI visualizer.


## Requirements

- `ncurses`
- `make` (build only)
- `autotools` (build from source only, not needed in distribution packages)
- `doxygen` (optional, for generating documentation)

## Building (and installing)

If you cloned the repository instead of downloading a distribution package,
start by generating the build system:

```sh
autoreconf --install
```

With the `configure` script available, you can follow the traditional mantra:

```sh
mkdir build && cd build       # Any path supported!
../configure
make
(sudo) make install
```

The `configure` script options are pretty limited in this repository, so you may want to individually build the different components if you need more control over the build process.

### Nix derivation

You can also use `nix` (flakes recommended):
```bash
nix run github:Izumi-visualizer/Izumi
```

## Visualizer usage

Use the installed `izumi` binary...
```sh
izumi path/to/file
```
... or use the `make` wrapper:
```sh
make run ARGS=path/to/file
```

> [!IMPORTANT]
> If sanitizers are enabled, an `AddressSanitizer:DEADLYSIGNAL` error can be raised randomly when starting the program. Just kill the program and try again. If it persists, please report it.

> [!NOTE]
> Some supported example files are on the `examples` directory. These are generated on the RISC-V core [Sargantana](https://github.com/bsc-loca/core_tile/).

See the [izumi_tui README](https://github.com/Izumi-visualizer/izumi_tui) for more information about the available commands and other features.

## Library usage

See the [libizumi README](https://github.com/Izumi-visualizer/libizumi).

## Screenshot

![Screenshot](.github/screenshot.png)

I know it's not the best looking tool, but it's a start (now it has colors :D).

---

![Izumi Konata](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fstatic.zerochan.net%2FIzumi.Konata.full.955876.jpg&f=1&nofb=1&ipt=11ebd39eb2229bec63db528410089c03d01dd9a541df01063ee5c809b6c69f58&ipo=images)
