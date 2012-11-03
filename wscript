#!/usr/bin/env python
# encoding: utf-8

APPLICATION_NAME='circular_buffer'

VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_REVISION = 1


VERSION=str(VERSION_MAJOR)+'.'+str(VERSION_MINOR)+'.'+str(VERSION_REVISION)

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx unittest_gtest doxygen')

def configure(conf):
    conf.load('compiler_cxx unittest_gtest doxygen')

    conf.define('VERSION', VERSION)
    conf.define('APPLICATION_NAME', APPLICATION_NAME)

    conf.write_config_header('config.h')


def build(bld):
    
    SOURCES_PATTERN = 'src/**.cc'
    TESTS_PATTERN   = 'src/**/tests/**.cc'

    # Compile library
    bld.stlib(
        features    = 'cxx',
        source      = [
                        'src/circular_buffer.cc',
                      ],
        includes    = 'include .',
        target=APPLICATION_NAME)

    # Compile tests
    bld.program(
        features = 'gtest',
        source   = bld.path.ant_glob([TESTS_PATTERN]),
        includes = 'include',
        use      = APPLICATION_NAME,
        target   = APPLICATION_NAME+'_test',
    )

    # Generate documentation
    bld(features='doxygen', doxyfile='Doxyfile')
