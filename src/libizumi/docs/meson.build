hotdoc = import('hotdoc')

assert(hotdoc.has_extensions('c-extension'))

hotdoc.generate_doc('libizumi',
  project_version: meson.project_version(),
  sitemap: 'sitemap.txt',
  index: 'index.md',
  c_index: 'index.md',
  c_sources: [headers],
  c_include_directories: include_directories,
)