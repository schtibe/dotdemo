import os
import sys


libs = [
	'SDL',
	'GL',
	'GLU',
	'boost_system',
	'GLEW'
]

file_list = [
	'main.cpp',
	'engine/Engine.cpp',
	'engine/EventHandler.cpp',
	'engine/Camera.cpp',
	'engine/Shader.cpp',
	'Demo.cpp',
	'Dot.cpp'
]

flags = [
	'-std=c++0x',
	'-Wall',
]

if len(sys.argv) > 1:
	if sys.argv[1] == 'debug':
		flags.extend(['-g'])
else:
	flags.extend(['-O3', '-mtune=native'])

# this is a little hack to use the path variable of
# the user. I do this so the gcc wrapper colorgcc is used.
env = {
	'PATH' : os.environ['PATH'],
	'TERM' : os.environ['TERM'],
	'HOME' : os.environ['HOME']
}

env = Environment( ENV = env)
env.AppendUnique(CCFLAGS=flags)
env.Program('dotdemo', file_list, LIBS=libs)

