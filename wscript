#!/usr/bin/env python
# encoding: utf-8

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx unittest_gtest doxygen')

def configure(conf):
    conf.load('compiler_cxx unittest_gtest doxygen')

    conf.env.CXXFLAGS = ['-Wall', '-g3']

def build(bld):
    
    # Compile tests
    bld.program(
        features = 'gtest',
        source   = 'src/tests/circular_buffer_unittest.cc',
        includes = 'include',
        target   = 'circular_buffer_test',
    )

    # Generate documentation
    bld(features='doxygen', doxyfile='Doxyfile')
