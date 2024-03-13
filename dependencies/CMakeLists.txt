include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY "https://github.com/SFML/SFML"
  GIT_TAG 69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
)

add_subdirectory(sfml)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG 277ae93c41314ba5f4c7444f37c4319cdf07e8cf
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG de565ac8f2b795dedc0307b60830cb006afd2ecd
)

add_subdirectory(imgui-sfml)
