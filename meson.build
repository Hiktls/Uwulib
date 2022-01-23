project('tapuwu','cpp')

sources = ['src/main.cc','lib/MediaManager.cc','lib/WindowManager.cc','lib/Util.cc','lib/GameObject.cc','lib/Texture.cc','lib/Text.cc','lib/sha256.cc']

sdl2 = dependency('sdl2')
zlib = dependency('zlib')
sdl2_image = dependency('SDL2_image')
sdl2_ttf = dependency('SDL2_ttf')
inc = include_directories('include')

executable('tapuwu',sources,include_directories: inc,dependencies:[sdl2,sdl2_image,sdl2_ttf,zlib])