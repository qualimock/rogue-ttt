add_executable(${PROJECT_NAME}
  main.cpp
  Game/Game.cpp
  Game/Game.hpp
  Grid/IGrid.cpp
  Grid/IGrid.hpp
  Grid/BaseGrid.cpp
  Grid/BaseGrid.hpp
  Grid/DraggableGrid.cpp
  Grid/DraggableGrid.hpp
  Grid/Map.cpp
  Grid/Map.hpp
  Grid/CombatGrid.cpp
  Grid/CombatGrid.hpp
  GridManager/GridManager.cpp
  GridManager/GridManager.hpp
  Entity/Entity.cpp
  Entity/Entity.hpp
  Entity/Actor/Actor.cpp
  Entity/Actor/Actor.hpp
  Entity/Actor/TTTCell.cpp
  Entity/Actor/TTTCell.hpp
  Entity/Actor/Wall.cpp
  Entity/Actor/Wall.hpp
  Entity/Actor/Door.cpp
  Entity/Actor/Door.hpp
  Entity/Character/Character.cpp
  Entity/Character/Character.hpp
  Entity/Character/Player.cpp
  Entity/Character/Player.hpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
