# Generate config.h
conf_data = configuration_data()
conf_data.set_quoted('VERSION', meson.project_version())
configure_file(
  output: 'config.h',
  configuration: conf_data,
)