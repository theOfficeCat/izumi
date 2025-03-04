project('Izumi', 'c',
  license: 'GPL-3.0-or-later',
  license_files: ['LICENSE'],
  version: '0.0.1',
  meson_version: '>= 1.1.0',
)

conf_data = configuration_data()
conf_data.set_quoted('VERSION', meson.project_version())
configure_file(
  output: 'config.h',
  configuration: conf_data,
)

# Find a suitable shell
shell = find_program('sh')

# Locate sources
sources_command = run_command(shell, '-c', 'echo src/*.c', check: true)
sources = sources_command.stdout().strip().split(' ')

# Locate ncurses
ncurses = dependency('ncurses')

# Define build targets
executable('izumi', sources, dependencies: ncurses, install: true)
