import os
import sys


libs = [
	'SDL2',
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
	'Demo.cpp'
]

flags = [
	'-std=c++0x',
	'-Wall',
]

vars = Variables()
vars.Add('O_SIZE', 'Set to 1 to optimize for size', 0)

if ARGUMENTS.get('debug', 0):
	flags.extend(['-g'])
elif ARGUMENTS.get('oSize', 0):
	flags.extend(['-Os', '-fomit-frame-pointer'])
else:
	flags.extend(['-O3', '-mtune=native'])

# this is a little hack to use the path variable of
# the user. I do this so the gcc wrapper colorgcc is used.
env = {
	'PATH' : os.environ['PATH'],
	'TERM' : os.environ['TERM'],
	'HOME' : os.environ['HOME']
}

env = Environment( 
	ENV = env,
	variables=vars,
	CPPDEFINES={'O_SIZE': '${O_SIZE}'}
)
env.AppendUnique(CCFLAGS=flags)
env.Program('dotdemo', file_list, LIBS=libs)

