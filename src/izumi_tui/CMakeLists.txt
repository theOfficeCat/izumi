file(GLOB IZUMI_SRC "*.c")

include_directories("include/" "../libizumi/include/")

add_executable(izumi-tui ${IZUMI_SRC})
target_link_libraries(izumi-tui PRIVATE izumi Curses::Curses)

set_target_properties(izumi-tui PROPERTIES OUTPUT_NAME izumi)

# run target?

