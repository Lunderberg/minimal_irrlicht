# -*- python -*-

Import('env')

env.Append(CPPPATH=['#/include'])

env.Append(CPPPATH=['#/irrlicht-1.8.1/include'])
if env['SYS'] == 'linux':
    env.Append(LIBS=['GL','Xxf86vm','Xext','X11','Xcursor'])
else:
    env.Append(LIBS=['gdi32','opengl32','d3dx9_43','winmm'])
irrlicht = SConscript('irrlicht-1.8.1/SConscript',exports=['env'])

output = []
for src in Glob('*.cc'):
    prog = env.Program([src,Glob('src/*.cc'),irrlicht])
    output.append(prog)

Return('output')
