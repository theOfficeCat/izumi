file(GLOB LIBIZUMI_SRC "*.c")

include_directories("include/")

add_library(izumi STATIC ${LIBIZUMI_SRC})

# documentation
if (NOT NODOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
            set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
            set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
            configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

            add_custom_target(docs ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Building documentation"
                VERBATIM
            )

            add_custom_target(open_libizumi_docs
                COMMAND xdg-open index.html
                DEPENDS docs
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/html/
            )
    else()
        message(WARNING Doxygen not found)
    endif()
endif()

