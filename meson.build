project('Izumi', 'c',
  license: 'GPL-3.0-or-later',
  license_files: ['LICENSE'],
  version: '0.0.1',
  meson_version: '>=1.2.0',
  default_options: [
    'b_sanitize=address, undefined',
    ],
)

fs = import('fs')

compiler = meson.get_compiler('c')

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

# Find required ncurses headers
curses_headers = []

foreach source : sources
  source_code = fs.read(source)
  source_code = source_code.splitlines()

  foreach line : source_code
    line = line.strip()

    if not (line.startswith('#include') and 'curses' in line)
      continue
    endif

    header = line.replace('#include', '').strip().strip('<>').strip()

    if header not in curses_headers
      curses_headers += header
    endif
  endforeach
endforeach

# Locate ncurses and ensure all required headers are available
curses = dependency('curses')
message('Determined the project to require the following curses headers:', curses_headers)
foreach header : curses_headers
  compiler.has_header(header, dependencies: curses, required: true)
endforeach

# Define build targets
executable('izumi', sources, dependencies: curses, install: true)
