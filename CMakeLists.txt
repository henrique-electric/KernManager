cmake_minimum_required(VERSION 4.0)
project("KernManager")


add_executable(${PROJECT_NAME} main.c)
if(APPLE)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/libargp.a)
    target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
endif()
