cmake_minimum_required(VERSION 3.16)
project(PiratePlatformer C)

set(CMAKE_C_STANDARD 23)

add_subdirectory(external/raylib)

add_executable(${PROJECT_NAME}
  src/main.c
  src/game.c 
  src/game.h 
  src/level.c 
  src/level.h
  src/resources.h
  src/resources.c
  src/files.c
  src/files.h
  src/tile.c
  src/tile.h
  src/map.c
  src/map.h
  src/entity.c 
  src/entity.h
  src/paths.h
  src/camera.c 
  src/camera.h
  src/background.c 
  src/background.h
  src/audio.c
  src/audio.h
  src/ui.c
  src/ui.h
)

target_link_libraries(${PROJECT_NAME}
  raylib
)

if (UNIX)
  target_link_libraries(${PROJECT_NAME} m pthread dl rt X11)
endif()

