cmake_minimum_required(VERSION 3.15)
project(LastName_FirstName)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(headers)
include_directories(src)

add_executable(LastName_FirstName
        headers/Blinky.h
        headers/Clyde.h
        headers/Constants.h
        headers/Draw.h
        headers/Game.h
        headers/Ghost.h
        headers/Inky.h
        headers/Pinky.h
        headers/Player.h
        headers/Position.h
        headers/SimpleTimer.h
        headers/View.h
        headers/SimpleConio.h
        src/Blinky.cpp
        src/Clyde.cpp
        src/Constants.cpp
        src/Draw.cpp
        src/Game.cpp
        src/Ghost.cpp
        src/Inky.cpp
        src/LastName_FirstName.cpp
        src/Pinky.cpp
        src/Player.cpp
        src/Position.cpp
        src/SimpleTimer.cpp
        src/View.cpp
        src/SimpleConio.cpp)
