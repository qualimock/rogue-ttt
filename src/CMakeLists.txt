add_executable(${PROJECT_NAME}
  main.cpp
  game/game.cpp
  game/game.hpp
  grid/grid.cpp
  grid/grid.hpp
  grid/cell.cpp
  grid/cell.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
