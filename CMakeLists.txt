cmake_minimum_required(VERSION 3.16)
project(PiratePlatformer C)

set(CMAKE_C_STANDARD 23)

add_subdirectory(external/raylib)

add_executable(${PROJECT_NAME}
  src/main.c
)

target_link_libraries(${PROJECT_NAME}
  raylib
)

if (UNIX)
  target_link_libraries(${PROJECT_NAME} m pthread dl rt X11)
endif()

