file(GLOB LIBIZUMI_SRC "*.c")

include_directories("include/")

add_library(izumi STATIC ${LIBIZUMI_SRC})

# docs?

