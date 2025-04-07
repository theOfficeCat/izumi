# Locate sources
sources_command = run_command(locate_sources, '*.c', check: true)
sources = files(sources_command.stdout().strip().split('\n'))

include_directories = include_directories('include')

# Define build target
libizumi = static_library('libizumi',
  sources,
  include_directories: include_directories,
  build_by_default: false,
)

# Declare a dependency for the frontends
libizumi = declare_dependency(
  objects: libizumi.extract_all_objects(),
  include_directories: include_directories,
)