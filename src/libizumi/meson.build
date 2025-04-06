# Locate sources
sources_command = run_command(locate_sources, '*.c', check: true)
sources = files(sources_command.stdout().strip().split('\n'))

subdir('include')

include_directories = include_directories('include')

# Define build target
libizumi = static_library('libizumi',
  sources,
  include_directories: include_directories
)

# Declare a dependency for the frontends
libizumi = declare_dependency(
  sources: public_include_files,
  link_with: libizumi,
  include_directories: include_directories,
)