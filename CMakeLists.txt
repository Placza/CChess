cmake_minimum_required(VERSION 3.15)
project(MyRaylibGame C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opcija 1: Koristi lokalni raylib kao submodul
add_subdirectory(raylib)

# Opcija 2: Ako imaš sistemski instalirani raylib, zakomentiraj gornju liniju i odkomentiraj ovu:
# find_package(raylib REQUIRED)

# Automatski dodaj sve .c fajlove iz src/ direktorija
file(GLOB_RECURSE SOURCES "src/*.c")

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Linkuj raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Include direktoriji - automatski uključuje sve .h fajlove iz src/
target_include_directories(${PROJECT_NAME} PRIVATE src inc)

# Linux specific libraries
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m pthread dl rt X11)
endif()


