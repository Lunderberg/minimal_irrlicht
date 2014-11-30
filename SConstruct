# -*- python -*-

import os

# Define a recursive install builder, to be used later.
def RecursiveInstall(env, target, src):
    if isinstance(src,str):
        try:
            src = File(src)
        except TypeError:
            src = Dir(src)

    try:
        root_items = []
        for src_list in src:
            try:
                root_items.extend(src_list)
            except TypeError:
                root_items.append(src_list)
    except TypeError:
        root_items = [src]

    for root_item in root_items:
        unsearched = [root_item]
        base_dir = os.path.split(str(root_item))[0]
        #Recursive search
        while unsearched:
            current = unsearched.pop()
            if current.isdir():
                unsearched.extend(Glob(str(current)+'/*'))
            else:
                dir_initial, filename = os.path.split(str(current))
                dir_relative = dir_initial[len(str(base_dir)):].strip('/')
                output_dir = (os.path.join(str(target),dir_relative)
                              if dir_relative else str(target))
                env.InstallAs(os.path.join(output_dir,current.name),current)

def TOOL_RECURSIVE_INSTALL(env):
    env.AddMethod(RecursiveInstall)

env = Environment(tools=['default',
                         TOOL_RECURSIVE_INSTALL],
                  ENV=os.environ)
env.Append(CPPPATH=['/usr/local/include'])

# More readable output
if not ARGUMENTS.get('VERBOSE'):
    env['CXXCOMSTR'] = 'Compiling C++ object $TARGETS'
    env['CCCOMSTR'] = 'Compiling C object $TARGETS'
    env['ARCOMSTR'] = 'Packing static library $TARGETS'
    env['RANLIBCOMSTR'] = 'Indexing static library $TARGETS'
    env['SHCCCOMSTR'] = 'Compiling shared C object $TARGETS'
    env['SHCXXCOMSTR'] = 'Compiling shared C++ object $TARGETS'
    env['LINKCOMSTR'] = 'Linking $TARGETS'
    env['SHLINKCOMSTR'] = 'Linking shared $TARGETS'

# Command-line adjustments
optimize = ARGUMENTS.get('OPTIMIZE')
if not optimize:
    optimize = 3
if optimize!='0':
    env.Append(CPPFLAGS=['-O{}'.format(optimize)])

if ARGUMENTS.get('RELEASE'):
    env.Append(CPPDEFINES=['NDEBUG'])
    env.Append(CPPFLAGS=['-s'])
else:
    env.Append(CPPFLAGS=['-g'])

if ARGUMENTS.get('PROFILE'):
    env.Append(CPPFLAGS=['-pg','-g'])
    env.Append(LINKFLAGS=['-pg'])


# System specific changes
win32 = env.Clone()
win64 = env.Clone()
linux = env.Clone()

#Define the working directory
win32['SYS'] = 'win32'
win64['SYS'] = 'win64'
linux['SYS'] = 'linux'

#Define the compilers, using C++11
win32.Replace(CC='i686-w64-mingw32-gcc')
win32.Replace(CXX='i686-w64-mingw32-g++')
win32.Replace(LINK='i686-w64-mingw32-g++')
win32.Append(CXXFLAGS=['-std=c++0x'])
win64.Replace(CC='x86_64-w64-mingw32-gcc')
win64.Replace(CXX='x86_64-w64-mingw32-g++')
win64.Replace(LINK='x86_64-w64-mingw32-g++')
win64.Append(CXXFLAGS=['-std=c++0x'])
linux.Replace(LINK='g++')
linux.Append(CXXFLAGS=['-std=c++11'])

#Define the appropriate file formats
win32.Replace(SHLIBPREFIX='')
win32.Replace(SHLIBSUFFIX='.dll')
win32.Replace(PROGSUFFIX='.exe')
win32.Append(LINKFLAGS='-static')
win64.Replace(SHLIBPREFIX='')
win64.Replace(SHLIBSUFFIX='.dll')
win64.Replace(PROGSUFFIX='.exe')
win64.Append(LINKFLAGS='-static')

#Location of boost static libraries
linux.Append(LIBS=['pthread',
                   File('/usr/local/lib/libboost_system.a'),
                   File('/usr/local/lib/libboost_serialization.a'),
                   ])
win32.Append(LIBPATH=['/usr/local/boost-w32/lib'])
win32.Append(LIBS=['boost_system-mt-s','ws2_32','wsock32','boost_serialization-mt-s'])
win64.Append(LIBPATH=['/usr/local/boost-w64/lib'])
win64.Append(LIBS=['boost_system-mt-s','ws2_32','wsock32','boost_serialization-mt-s'])

#Threading library
linux.Append(LIBS=['pthread'])


for env in [win32,win64,linux]:
    env['ENV']['CC'] = env['CC']
    env['ENV']['CXX'] = env['CXX']
    build_dir = os.path.join('build',env['SYS'])
    exe = SConscript('SConscript',
                     variant_dir=build_dir,
                     src_dir='.',
                     exports=['env'])
    inst_dir = env['SYS']
    Execute(Mkdir(env['SYS']))
    env.RecursiveInstall(inst_dir,exe)
    if os.path.exists('resources'):
        env.RecursiveInstall(inst_dir,'resources')
    Clean('.',env['SYS'])

Clean('.','build')
