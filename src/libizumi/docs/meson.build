# Meson options
libizumi_docs_option = get_option('libizumi_docs').require(
  find_program('hotdoc', required: false).found(),
  error_message: 'Documentation can\'t be generated without hotdoc',
)

doc_tests_option = get_option('doc_tests').require(
  find_program('gtkdoc-scan', required: false).found(),
  error_message: 'Documentation tests require gtk-doc to be installed',
).require(
  find_program('gtkdoc-mkdb', required: false).found(),
  error_message: 'Documentation tests require gtk-doc to be installed',
)

summary({
  'libizumi_docs': libizumi_docs_option.allowed(),
  'doc_tests': doc_tests_option.allowed()},
  section: 'Configuration options'
)

if libizumi_docs_option.allowed()
  hotdoc = import('hotdoc')
  assert(hotdoc.has_extensions('c-extension'))
  
  # Build documentation
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
  
  # Open documentation
  xdg_open = find_program('xdg-open',
    required: false,
    disabler: true
  )
  run_target('open_libizumi_docs',
    command: [xdg_open, libizumi_docs.full_path() / 'html' / 'index.html'],
    depends: libizumi_docs,
  )
endif

# Documentation tests
if doc_tests_option.allowed()
  run_target('libizumi_undocumented',
    command: list_undocumented_items
  )
  
  test('libizumi_undocumented', list_undocumented_items[0],
    args: [list_undocumented_items[1], '--test'],
    env: {
      'MESON_SOURCE_ROOT': meson.project_source_root(),
      'MESON_SUBDIR': meson.current_source_dir(),
    },
    
  )
endif