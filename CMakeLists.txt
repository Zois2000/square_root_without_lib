cmake_minimum_required(VERSION 3.20)
project(square_root_without_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# GCC/Clang warning options
# ------------------------------------------------------------------------------
option(MP_WERROR "Treat warnings as errors" OFF)
option(MP_PEDANTIC "Enable -Wpedantic" ON)
option(MP_VERY_NOISY "Enable extra noisy warnings" OFF)

function(mp_enable_strict_warnings target)
  if(NOT (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    message(FATAL_ERROR "mp_enable_strict_warnings(): GCC/Clang only. Compiler=${CMAKE_CXX_COMPILER_ID}")
  endif()

  target_compile_options(${target} PRIVATE
    -Wall -Wextra $<$<BOOL:${MP_PEDANTIC}>:-Wpedantic>
    -Wshadow -Wconversion -Wsign-conversion
    -Wcast-align -Wcast-qual -Wold-style-cast
    -Woverloaded-virtual -Wnon-virtual-dtor -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2 -Wformat-security -Wformat-signedness
    -Wimplicit-fallthrough -Wmisleading-indentation -Wundef
    -Wswitch -Wswitch-enum -Wswitch-default
    -Wuninitialized -Winit-self
    -Wredundant-decls -Wmissing-declarations -Wmissing-include-dirs
    -Wwrite-strings -Wextra-semi -Wzero-as-null-pointer-constant
    -Warray-bounds -Wvla
    -Wuseless-cast -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wfloat-equal
    -Wodr
    $<$<BOOL:${MP_WERROR}>:-Werror>
    $<$<CXX_COMPILER_ID:GNU>:
      -Walloca -Wtrampolines -Wstrict-overflow=5 -Wstringop-overflow=4 -Wstringop-truncation
      -Wbidi-chars=any -Wformat-overflow=2 -Wformat-truncation=2 -Wshift-overflow=2
    >
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
      -Wthread-safety -Wextra-semi-stmt -Wdocumentation -Wweak-vtables
      -Wexit-time-destructors -Wglobal-constructors -Wrange-loop-analysis
    >
    $<$<BOOL:${MP_VERY_NOISY}>:-Wc++98-compat -Wc++98-compat-pedantic -Wpadded -Wpacked>
  )
endfunction()

# ------------------------------------------------------------------------------
# Hinzufügen der Bibliothek und des Hauptprogramms
# ------------------------------------------------------------------------------



# Füge cpga_calculation.cpp zum Hauptprogramm hinzu
# Füge cgpa_i_o.cpp zum Hauptprogramm hinzu
# Füge main.cpp zum Hauptprogramm hinzu
add_executable(app
  src/main.cpp
)

mp_enable_strict_warnings(app)

# ------------------------------------------------------------------------------
# Tests (falls vorhanden)
# ------------------------------------------------------------------------------
include(CTest)
if(BUILD_TESTING AND EXISTS "${CMAKE_SOURCE_DIR}/test/CMakeLists.txt")
  add_subdirectory(test)
endif()
