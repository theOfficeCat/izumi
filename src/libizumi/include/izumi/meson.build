# Generate public header files from the private ones
public_include_files = []
foreach include_file : include_files
  basename = fs.name(include_file)
  
  public_include_files += custom_target(basename,
    output: basename,
    input: include_file,
    command: [gen_public_header, '@INPUT@', '@OUTPUT@'],
  )
endforeach