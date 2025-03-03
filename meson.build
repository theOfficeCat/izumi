project('Izumi', 'c',
  license: 'GPL-3.0-or-later',
  license_files: ['LICENSE'],
  version: run_command('cut', 'src/version.h', '-d ', '-f3').stdout().strip().strip('"'),
)

# Find a suitable shell
shell = find_program('sh')

# Locate sources
sources_command = run_command(shell, '-c', 'echo src/*.c', check: true)
sources = sources_command.stdout().strip().split(' ')

# Locate ncurses
ncurses = dependency('ncurses')

# Define build targets
executable('izumi', sources, dependencies: ncurses)
