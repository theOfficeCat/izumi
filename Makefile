# This is just a wrapper arround the meson build system


# Directories
source_dir = $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
build_dir = $(source_dir)/build

# Check if configure was run
ifeq ($(shell meson configure $(build_dir) >/dev/null 2>&1 || echo fail),fail)
$(error "Invalid state: Run the configure script ($(source_dir)/configure) before building!")
endif

# Commands
meson_compile_cmd = meson compile -C $(build_dir)
meson_run_cmd     = ninja run     -C $(build_dir) # Running through meson breaks stdin/stdout
meson_test_cmd    = meson test    -C $(build_dir)
meson_install_cmd = meson install -C $(build_dir)
meson_clean_cmd   = meson clean   -C $(build_dir)

# Compilation target
.PHONY: default
default:
	$(meson_compile_cmd) $(MAKECMDGOALS)

# Special targets
run:
	$(meson_run_cmd)

test:
	$(meson_test_cmd)

install:
	$(meson_install_cmd)

clean:
	$(meson_compile_cmd) --clean

# Pass remaining targets to 'meson compile'
%:
	$(meson_compile_cmd) $@

