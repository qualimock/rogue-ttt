project('rogue-ttt', 'cpp',
        version: '2.1',
        meson_version: '>=0.55.0',
        license: 'MIT')

deps = [dependency('sfml-all'), dependency('gl')]

subdir('src')
subdir('include')

imgui_sources = ['include/imgui/imgui.cpp',
                 'include/imgui/imgui_demo.cpp',
                 'include/imgui/imgui_draw.cpp',
                 'include/imgui/imgui_tables.cpp',
                 'include/imgui/imgui_widgets.cpp',
                 'include/imgui-sfml/imgui-SFML.cpp']

exe = executable('rogue-ttt',
                 'src/main.cpp',
                 'src/grid/grid.cpp',
                 'src/grid/grid.hpp',
                 'src/game/game.cpp',
                 'src/game/game.hpp',
                 imgui_sources,
                 dependencies: deps,
                 include_directories: include_directories('.', 'include/imgui', 'include/imgui-sfml'))
