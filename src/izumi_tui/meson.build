# Locate sources
sources_command = run_command([locate_sources, '*.c'], check: true)
sources = files(sources_command.stdout().strip().split('\n'))

# Find required ncurses headers
curses_headers_command = run_command([list_curses_includes, sources], check: true)
curses_headers = curses_headers_command.stdout().strip().split('\n')

# Locate ncurses and ensure all required headers are available
message(
  'Determined the project to require the following curses headers:',
  curses_headers,
)
curses = compiler.find_library('curses', has_headers: curses_headers)

subdir('include')

include_directories = include_directories('include')

# Define build target
executable('izumi',
  sources,
  dependencies: [curses, libizumi],
  include_directories: include_directories,
  install: true
)