cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# MSVC runtime library flags are selected by an abstraction
cmake_policy(SET CMP0091 NEW)

project(STUNTGP CXX)

include(CheckCXXSourceCompiles)
include(CMakeDependentOption)
include(CMakePushCheckState)
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/reccmp.cmake")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
option(ENABLE_CLANG_TIDY "Enable clang-tidy")
if (ENABLE_CLANG_TIDY)
  find_program(CLANG_TIDY_BIN NAMES "clang-tidy")
  set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_BIN}")
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_BIN}")
endif()

math(EXPR bits "8 * ${CMAKE_SIZEOF_VOID_P}")
message(STATUS "Building ${bits}-bit binaries")
if (NOT bits EQUAL 32)
  message(WARNING "Only 32-bit executables are supported")
endif()

set(MSVC_FOR_DECOMP FALSE)
if (MSVC)
  # Visual C++ 6.0.8168 -> cl version 12.00.8168
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "13.0")
    set(MSVC_FOR_DECOMP TRUE)
  endif()
endif()

function(add_cxx_warning WARNING)
  if(STUNTGP_WERROR)
    set(compiler_option "-Werror=${WARNING}")
  else()
    set(compiler_option "-W${WARNING}")
  endif()
  string(MAKE_C_IDENTIFIER "COMPILER_SUPPORTS${compiler_option}" varname)

  cmake_push_check_state(RESET)
  set(CMAKE_REQUIRED_FLAGS "${compiler_option} ")
  if(MSVC)
    string(APPEND CMAKE_REQUIRED_FLAGS "/WX")
  else()
    string(APPEND CMAKE_REQUIRED_FLAGS "-Werror")
  endif()
  check_cxx_source_compiles("int main() { return 0; }" ${varname})
  cmake_pop_check_state()

  if(${varname})
    add_compile_options(${compiler_option})
  endif()
endfunction()

message(STATUS "MSVC for decompilation: ${MSVC_FOR_DECOMP}")

option(STUNTGP_WERROR "Treat warnings as errors" OFF)
# option(STUNTGP_BUILD_APP "Build StuntGP_D3D.exe application" ON)
option(STUNTGP_USE_DX6 "Build with internal DirectX 6 SDK" ON)
option(STUNTGP_DECOMP_ASSERT "Assert struct size" ${MSVC_FOR_DECOMP})
cmake_dependent_option(STUNTGP_USE_DX6_LIBS "Build with internal DirectX 6 SDK Libraries" ON ISLE_USE_DX5 OFF)
# option(ISLE_INCLUDE_ENTROPY "Build with entropy.h" OFF)
# option(ISLE_ENTROPY_FILENAME "Entropy header filename" "entropy.h")

# add_cxx_warning(parentheses)


add_library(DirectX6::DirectX6 INTERFACE IMPORTED)
target_include_directories(DirectX6::DirectX6 INTERFACE "${PROJECT_SOURCE_DIR}/3rdparty/dx6/include")
if(STUNTGP_USE_DX6)
  target_link_directories(DirectX6::DirectX6 INTERFACE "${PROJECT_SOURCE_DIR}/3rdparty/dx6/lib")
endif()

# TODO
# function(add_lego_libraries NAME)


add_executable(STUNTGP_D3D WIN32
# TODO
  STUNTGP_D3D/main.cpp
  STUNTGP_D3D/uwu.cpp
)
reccmp_add_target(STUNTGP_D3D ID STUNTGP_D3D)


target_compile_definitions(STUNTGP_D3D PRIVATE STUNTGP_D3D_APP)

target_include_directories(STUNTGP_D3D PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/STUNTGP_D3D")
# Use internal DirectX 6 if required
target_link_libraries(STUNTGP_D3D PRIVATE $<$<BOOL:${STUNTGP_USE_DX6}>:DirectX6::DirectX6>)
target_link_libraries(STUNTGP_D3D PRIVATE ddraw dinput dsound winmm)


set_property(TARGET STUNTGP_D3D PROPERTY OUTPUT_NAME "StuntGP_D3D")
set_property(TARGET STUNTGP_D3D PROPERTY PREFIX "")
set_property(TARGET STUNTGP_D3D PROPERTY SUFFIX ".exe")


# Compiler flags
# TODO - this will be important for compiling with MSVC later than the original one
# if (MSVC)
# endif()



if (STUNTGP_DECOMP_ASSERT)
message(STATUS "Decomp asserts enabled")
target_compile_definitions(STUNTGP_D3D PRIVATE "ENABLE_DECOMP_ASSERTS")
endif()

if (MSVC_FOR_DECOMP)
    # These flags have been taken from the defaults for a Visual C++ 6.0 project (the compiler the
    # game was originally built with) and tweaked slightly to produce more debugging info for reccmp.
    # They ensure a recompilation that can be byte/instruction accurate to the original binaries.
    target_link_options(STUNTGP_D3D PRIVATE "/OPT:REF")
    # set_property(TARGET STUNTGP_D3D PROPERTY MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Release>:Release>")
    set_property(TARGET STUNTGP_D3D PROPERTY MSVC_RUNTIME_LIBRARY "$<$<CONFIG:Debug>:Debug>")


    # /Gr? fastcall or not
    # /ML - the only possible /M option
    # doesn't matter (So far) - /FD /Gy /GR /GB?, /ZI
    # disabled /Ge
    #  testing  /GNumber
  set(CMAKE_CXX_FLAGS "/Gr /ML /W3 /GX /G5 /c /D \"WIN32\" /D \"_WINDOWS\"") # G6???
  set(CMAKE_CXX_FLAGS_DEBUG "/Gm /ZI /Od /D \"_DEBUG\"")
  set(CMAKE_CXX_FLAGS_RELEASE "/EHs /O2 /D \"NDEBUG\"")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/EHs /Zp4 /Ox /Zi /D \"NDEBUG\"") #/ZI in debug
  set(CMAKE_CXX_FLAGS_MINSIZEREL "/Os /D \"NDEBUG\"")

  set(CMAKE_EXE_LINKER_FLAGS "/machine:I386")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/incremental:yes /debug /pdbtype:con")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/incremental:no")
  set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/incremental:no /debug /pdbtype:con")
  set(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL "/incremental:no")

  set(CMAKE_STATIC_LINKER_FLAGS "/machine:I386 /pdbtype:con")

  # TODO check if we need to bump this to 13, or simply ignore
  # Older MSVC versions don't support building in parallel.
  # Force non-parallel builds of isle and lego1 by putting them in a pool with 1 available job.
  if (CMAKE_CXX_COMPILER_ID VERSION_LESS 12)
    set_property(GLOBAL APPEND PROPERTY JOB_POOLS "msvc_stuntgp_d3d=1")
    set_property(TARGET STUNTGP_D3D PROPERTY JOB_POOL_COMPILE "msvc_config")
    set_property(TARGET STUNTGP_D3D PROPERTY JOB_POOL_LINK "msvc_config")
  endif()
endif()

# TODO
# find_program(CLANGFORMAT_BIN NAMES clang-format)

reccmp_configure()
