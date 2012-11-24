#!/usr/bin/env python
# encoding: utf-8

APPLICATION_NAME='circular_buffer'

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx unittest_gtest doxygen')

def configure(conf):
    conf.load('compiler_cxx unittest_gtest doxygen')
    conf.env.CXXFLAGS += [ '-Wall', '-g', '-O3']

def build(bld):
    
    TESTS_PATTERN   = 'src/**/tests/**.cc'

    # Compile tests
    bld.program(
        features = 'gtest',
        source   = bld.path.ant_glob([TESTS_PATTERN]),
        includes = 'include',
        target   = APPLICATION_NAME+'_test',
    )

    # Generate documentation
    bld(features='doxygen', doxyfile='Doxyfile')
