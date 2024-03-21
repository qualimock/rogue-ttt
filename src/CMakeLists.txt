add_executable(${PROJECT_NAME}
  main.cpp
  Game/Game.cpp
  Game/Game.hpp
  Grid/Grid.cpp
  Grid/Grid.hpp
  Grid/Cell.cpp
  Grid/Cell.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
