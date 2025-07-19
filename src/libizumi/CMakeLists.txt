file(GLOB LIBIZUMI_SRC "*.c")
file(GLOB LIBIZUMI_HEADERS "include/*.h")

include_directories("include/")

add_library(izumi STATIC ${LIBIZUMI_SRC})

add_subdirectory(docs)

