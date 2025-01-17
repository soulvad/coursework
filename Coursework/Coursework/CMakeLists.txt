cmake_minimum_required(VERSION 3.14)
project(chess_module)

# Встановіть стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Завантажити pybind11 за допомогою FetchContent
include(FetchContent)
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(pybind11)

# Додати всі файли проєкту
set(SOURCES
    Game.cpp
    Pieces.cpp
    ChessBot.cpp
    module.cpp  # Ваш основний файл для Python-розширення
)

# Створити Python-розширення
pybind11_add_module(chess_module ${SOURCES})

# Укажіть заголовкові файли
target_include_directories(chess_module PRIVATE ${CMAKE_SOURCE_DIR})
