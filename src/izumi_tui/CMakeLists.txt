file(GLOB IZUMI_SRC "*.c")

find_package(Curses)
if(Curses_FOUND AND NOT TARGET Curses::Curses)
    add_library(Curses::Curses INTERFACE IMPORTED)
    set_target_properties(
    Curses::Curses
    PROPERTIES
        INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
    )

    include_directories("include/" "../libizumi/include/")

    add_executable(izumi-tui ${IZUMI_SRC})
    target_link_libraries(izumi-tui PRIVATE izumi Curses::Curses)
    
    set_target_properties(izumi-tui PROPERTIES OUTPUT_NAME izumi)
    
    install(TARGETS izumi-tui DESTINATION bin COMPONENT izumi)
    
    add_custom_target(run
        COMMAND ./izumi
        DEPENDS izumi-tui
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

else()
    message(WARNING "ncurses not found, not building client")
endif()



