project('tapuwu','cpp')

sources = ['src/main.cc','lib/MediaManager.cc','lib/WindowManager.cc','lib/Util.cc','lib/Object.cc','lib/sha256.cc']

sdl2 = dependency('sdl2')
zlib = dependency('zlib')
sdl2_image = dependency('SDL2_image')
inc = include_directories('include')

executable('tapuwu',sources,include_directories: inc,dependencies:[sdl2,sdl2_image,zlib])