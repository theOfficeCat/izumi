# Locate private headers
include_files_command = run_command(locate_sources, '*.h', check: true)
include_files = files(include_files_command.stdout().strip().split('\n'))

subdir('izumi')