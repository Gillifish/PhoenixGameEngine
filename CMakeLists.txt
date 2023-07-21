cmake_minimum_required(VERSION 3.15)
project(example
  LANGUAGES CXX
  VERSION 1.0
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(dependencies)

target_include_directories(main PRIVATE src
                                        src/Engine
)

target_link_libraries(main PRIVATE sfml-window sfml-graphics sfml-system sfml-audio ImGui-SFML::ImGui-SFML)