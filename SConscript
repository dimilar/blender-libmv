#!/usr/bin/python

# NOTE: This file is automatically generated by bundle.sh script
#       If you're doing changes in this file, please update template
#       in that script too

import sys
import os

Import('env')

defs = []
incs = '.'

if env['WITH_BF_LIBMV']:
    defs.append('GOOGLE_GLOG_DLL_DECL=')
    defs.append('WITH_LIBMV')

    src = env.Glob("libmv-capi.cc")
    src += env.Glob('libmv/image/*.cc')
    src += env.Glob('libmv/multiview/*.cc')
    src += env.Glob('libmv/numeric/*.cc')
    src += env.Glob('libmv/simple_pipeline/*.cc')
    src += env.Glob('libmv/tracking/*.cc')
    src += env.Glob('third_party/fast/*.c')
    src += env.Glob('third_party/gflags/*.cc')

    incs += ' ../Eigen3 third_party/ceres/include'
    incs += ' ' + env['BF_PNG_INC']
    incs += ' ' + env['BF_ZLIB_INC']

    if env['OURPLATFORM'] in ('win32-vc', 'win32-mingw', 'linuxcross', 'win64-vc', 'win64-mingw'):
        incs += ' ./third_party/glog/src/windows ./third_party/glog/src/windows/glog'
        if env['OURPLATFORM'] in ('win32-vc', 'win64-vc'):
            incs += ' ./third_party/msinttypes'

        src += ['./third_party/glog/src/logging.cc', './third_party/glog/src/raw_logging.cc', './third_party/glog/src/utilities.cc', './third_party/glog/src/vlog_is_on.cc']
        src += ['./third_party/glog/src/windows/port.cc']
    else:
        src += env.Glob("third_party/glog/src/*.cc")
        incs += ' ./third_party/glog/src'
else:
    src = env.Glob("libmv-capi_stub.cc")

env.BlenderLib ( libname = 'extern_libmv', sources=src, includes=Split(incs), defines=defs, libtype=['extern', 'player'], priority=[20,137] )

if env['WITH_BF_LIBMV']:
    SConscript(['third_party/SConscript'])
