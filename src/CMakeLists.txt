set(LEXER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Attributes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Error.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/LexemString.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Lexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Lexer/Table.cpp
)

set(
    PARSER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Parser/tree.cpp
)

set(GENERATOR_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Generator/generator.cpp
)

set(LIB_SOURCES
    ${LEXER_SOURCES}
    ${PARSER_SOURCES}
    ${GENERATOR_SOURCES}

)

add_library(${LIB_NAME} ${LIB_SOURCES})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)