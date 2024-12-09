cmake_minimum_required(VERSION 3.10)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()


project(apitrace)

include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)
add_definitions(-D__psp2__)

set(SOURCES
    wrappers/glcaps.cpp
    wrappers/config.cpp
    wrappers/gltrace_arrays.cpp
    wrappers/gltrace_state.cpp
    wrappers/glmemshadow.hpp
    wrappers/glmemshadow.cpp
    wrappers/gltrace_unpack_compressed.hpp
    wrappers/gltrace_unpack_compressed.cpp
    wrappers/egltrace.cpp
    wrappers/glproc_gl.cpp
    dispatch/glproc.cpp
    helpers/glfeatures.cpp
    helpers/eglsize.cpp
    lib/os/os_posix.cpp
    lib/trace/trace_callset.cpp
    lib/trace/trace_dump.cpp
    lib/trace/trace_fast_callset.cpp
    lib/trace/trace_file.cpp
    lib/trace/trace_file_read.cpp
   lib/trace/trace_file_zlib.cpp
   lib/os/os_backtrace.cpp
    lib/trace/trace_file_brotli.cpp
    lib/trace/trace_file_snappy.cpp
    lib/trace/trace_format.hpp
    lib/trace/trace_model.cpp
    lib/trace/trace_parser.cpp
    lib/trace/trace_parser_flags.cpp
    lib/trace/trace_parser_loop.cpp
    lib/trace/trace_writer.cpp
    lib/trace/trace_writer_local.cpp
    lib/trace/trace_writer_model.cpp
    lib/trace/trace_profiler.cpp
    lib/trace/trace_option.cpp
    lib/trace/trace_ostream_snappy.cpp
   lib/trace/trace_ostream_zlib.cpp
   lib/highlight/highlight.cpp
   lib/guids/guids.cpp
    thirdparty/snappy/snappy-c.cc
    thirdparty/snappy/snappy-sinksource.cc
    thirdparty/snappy/snappy-stubs-internal.cc
    thirdparty/snappy/snappy.cc
)

include_directories(
dispatch
wrappers
helpers
lib/os
lib/trace
lib/highlight
lib/guids
compat
thirdparty/snappy
thirdparty/config/snappy/
thirdparty/brotli/c/include/
thirdparty/khronos/)

add_subdirectory(thirdparty)

add_library(apitrace ${SOURCES})

