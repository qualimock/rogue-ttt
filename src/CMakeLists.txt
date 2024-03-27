add_executable(${PROJECT_NAME}
  main.cpp
  Game/Game.cpp
  Game/Game.hpp
  Grid/IGrid.cpp
  Grid/IGrid.hpp
  Grid/Map.cpp
  Grid/Map.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
