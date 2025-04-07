project(
  'Izumi',
  'c',
  license: 'GPL-3.0-or-later',
  license_files: ['LICENSE'],
  version: files('.version'),
  meson_version: '>=1.2.0',
  default_options: [
    'b_sanitize=address,undefined',
    'warning_level=2',
  ],
)

# Get some required environment programs
compiler = meson.get_compiler('c')

subdir('build-tools')
subdir('src')

# Warn if sanitizers are activated in a release build
if (get_option('buildtype') == 'release' and get_option('b_sanitize') != 'none')
  warning('A release build with sanitizers ON has been configured!')
  message('', 'To improve performance, reconfigure with the -Db_sanitize=none flag.')
endif
