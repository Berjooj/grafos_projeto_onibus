cmake_minimum_required(VERSION 3.5.0)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(grafos_projeto_onibus VERSION 0.1.0 LANGUAGES C)

set(SOURCES
	main.c
	dependencies/cJSON/cJSON.c
)

include_directories(cJSON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(main ${SOURCES})
