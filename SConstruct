import os

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
	#'-isystem/usr/include/freetype2',
	'-O3',
	'-mtune=native',
	#'-g'
	]

# this is a little hack to use the path variable of
# the user. I do this so the gcc wrapper colorgcc is used.
env = {
	'PATH' : os.environ['PATH'],
	'TERM' : os.environ['TERM'],
	'HOME' : os.environ['HOME']
}

debug_env = Environment( ENV = env)
debug_env.AppendUnique(CCFLAGS=flags)
debug_env.Program('dotdemo', file_list, LIBS=libs)



#release_env = Environment(ENV = env)
#release_env.AppendUnique(CCFLAGS=flags + ['-03'])
#release_env.Program('boardball', file_list, LIBS=libs)
#
#Default(release_env)
