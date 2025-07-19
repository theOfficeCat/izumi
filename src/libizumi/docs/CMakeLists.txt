find_program(HOTDOC_CMD hotdoc)

add_custom_target(izumi-docs
    COMMAND ${HOTDOC_CMD} init
        --init-dir ${CMAKE_CURRENT_BINARY_DIR}/hotdoc/
        --project-name "${PROJECT_NAME}"
        --project-version "${VERSION}"
        --sitemap "sitemap.txt"
        --index "index.md"
        --c-index "${CMAKE_CURRENT_SOURCE_DIR}/api.md"
        --c-sources ${LIBIZUMI_SRC} ${LIBIZUMI_HEADERS}
        --c-include-directories "../include/" -vv
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/sitemap.txt ${CMAKE_CURRENT_BINARY_DIR}/hotdoc/
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/*.md ${CMAKE_CURRENT_BINARY_DIR}/hotdoc/markdown_files/
    COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/hotdoc/ && ${HOTDOC_CMD} run -vv
)

if (HOTDOC_CMD)
    add_dependencies(izumi izumi-docs)
else()
    message(WARNING "hotdoc not found - not building documentation")
endif()

