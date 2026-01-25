cmake_minimum_required(VERSION 4.0)
project("KernManager")

include_directories(include/)

add_executable(${PROJECT_NAME} src/main.c src/args.c src/actions.c)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libargp.a)
    target_include_directories(${PROJECT_NAME} PRIVATE opt/homebrew/include/)
endif()
