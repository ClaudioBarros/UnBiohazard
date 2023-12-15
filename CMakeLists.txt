# CMakeList.txt : CMake project for unbiohazard, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("unbiohazard")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/lib)

#set compiler preprocessor definitions
add_compile_definitions(PROJECT_DIR=${CMAKE_SOURCE_DIR})

# 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED) 

# Add source to this project's executable.

set(SRC_FILES
    "Main.cpp"
    "State.cpp"
    "Game.cpp"
    "Vec2.cpp"
    "Rect.cpp"
    "Sprite.cpp"
    "Sprite2.cpp"
    "Music.cpp"
    "GameObject.cpp"
    "Sound.cpp"
    "TileSet.cpp"
    "TileMap.cpp"
    "Helper.cpp"
    "Resources.cpp"
    "InputManager.cpp"
    "Camera.cpp"
    "CameraFollower.cpp"
    "Collider.cpp"
    "Timer.cpp"
    "Player.cpp"
    "Wall.cpp"
    "Pigeon.cpp"
    "Hitbox.cpp"
    "Reitora.cpp"
    "Gato.cpp"
    "Bullet.cpp"
    "Sarue.cpp"
    )

add_executable (unbiohazard ${SRC_FILES})

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(unbiohazard PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(unbiohazard PRIVATE SDL2::SDL2 SDL2_Image SDL2_Mixer)

set_property(TARGET unbiohazard PROPERTY CXX_STANDARD 11)

# TODO: Add tests and install targets if needed.
