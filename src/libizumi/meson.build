# Locate sources
sources_command = run_command(locate_sources, '*.c', check: true)
sources = files(sources_command.stdout().strip().split('\n'))

include_directories = include_directories('include', is_system: true)

# Define build target
libizumi = static_library('libizumi',
  sources,
  include_directories: include_directories,
  implicit_include_directories: false,
  name_prefix: '',
  build_by_default: false,
)

# Declare a dependency for the frontends
libizumi = declare_dependency(
  objects: libizumi.extract_all_objects(),
  include_directories: include_directories,
)