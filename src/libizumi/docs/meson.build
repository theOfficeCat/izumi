libizumi_docs_option = get_option('libizumi_docs').require(
  find_program('hotdoc', required: false).found(),
  error_message: 'Documentation can\'t be generated without hotdoc'
)

if libizumi_docs_option.allowed()
  hotdoc = import('hotdoc')
  assert(hotdoc.has_extensions('c-extension'))
  
  libizumi_docs = hotdoc.generate_doc('libizumi',
    project_version: meson.project_version(),
    sitemap: 'sitemap.txt',
    index: 'index.md',
    c_index: 'api.md',
    c_sources: [headers],
    c_include_directories: include_directories,
    fatal_warnings: true,
    build_by_default: true,
    install: true,
  )
  
  alias_target('libizumi_docs', libizumi_docs)
  
  xdg_open = find_program('xdg-open',
    required: false,
    disabler: true
  )
  run_target('open_libizumi_docs',
    command: [xdg_open, libizumi_docs.full_path() / 'html' / 'index.html'],
    depends: libizumi_docs,
  )
endif