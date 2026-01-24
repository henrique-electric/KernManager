cmake_minimum_required(VERSION 4.0)
project("KernManager")


add_executable(${PROJECT_NAME} main.c)
if(APPLE)
    target_link_libraries(${PROJECT_NAME} ./libargp.a)
endif()
