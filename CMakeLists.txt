cmake_minimum_required(VERSION 3.20)

project(izumi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -fsanitize=address,undefined")

file(STRINGS ".version" VERSION)
add_compile_definitions(VERSION="${VERSION}")

add_subdirectory(src)

# packaging
set(CPACK_PACKAGE_VENDOR "ARFNET")
set(CPACK_PACKAGE_CONTACT "arf20@arf20.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "arf20")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An instruction pipeline visualizer for Onikiri2-Kanata format based on Konata.")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")
set(CPACK_SOURCE_GENERATOR "TGZ;ZIP")
set(CPACK_GENERATOR "DEB;TGZ;ZIP")

execute_process(COMMAND dpkg-query --showformat='${Version}' --show libc6 OUTPUT_VARIABLE LIBC_VER)
execute_process(COMMAND dpkg-query --showformat='${Version}' --show libncurses6 OUTPUT_VARIABLE LIBNCURSES_VER)

set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEB_COMPONENT_INSTALL YES)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= ${LIBC_VER}), libncurses6 (>= ${LIBNCURSES_VER})")

include(CPack)


