cmake_minimum_required(VERSION 3.10)
project(Bootcamp
        DESCRIPTION "C++ Bootcamp for 15-445/645"
        LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION MATCHES "^15.")
    message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
  else()
    message(WARNING "!! We recommend that you use clang-15 for this bootcamp. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, a different version.")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  message(STATUS "You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
else()
  message(WARNING "!! We recommend that you use clang-15 for this bootcamp. You're using ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}, which is not clang.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Clang on Linux defaults to -fno-standalone-debug ("limited" debug info), which
# omits the full type layout that libstdc++'s gdb pretty-printers rely on. The
# result is that std::string / std::vector locals fail to display in a debugger
# (e.g. the VS Code Variables pane shows errors or nothing). Emitting complete
# debug info in Debug builds fixes it. Harmless on AppleClang (already the
# default) and skipped on GCC, which does not accept the flag.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options($<$<CONFIG:Debug>:-fstandalone-debug>)
endif()

# Compiling move semantics/references executables
add_executable(references src/references.cpp)
add_executable(move_semantics src/move_semantics.cpp)
add_executable(move_constructors src/move_constructors.cpp)

# Compiling templates executables
add_executable(templated_functions src/templated_functions.cpp)
add_executable(templated_classes src/templated_classes.cpp)

# Compiling C++ STL executables
add_executable(vectors src/vectors.cpp)
add_executable(sets src/sets.cpp)
add_executable(unordered_maps src/unordered_maps.cpp)
add_executable(unique_ptr src/unique_ptr.cpp)
add_executable(shared_ptr src/shared_ptr.cpp)
add_executable(mutex src/mutex.cpp)
add_executable(scoped_lock src/scoped_lock.cpp)
add_executable(condition_variable src/condition_variable.cpp)
add_executable(rwlock src/rwlock.cpp)

# Compiling misc executables
add_executable(wrapper_class src/wrapper_class.cpp)
add_executable(iterator src/iterator.cpp)
add_executable(auto src/auto.cpp)
add_executable(namespaces src/namespaces.cpp)
add_executable(objects src/objects.cpp)

# Compiling bootcamp demo code
add_executable(s24_my_ptr src/spring2024/s24_my_ptr.cpp)
add_executable(bootcamp1 src/bootcamp1.cpp)
add_executable(bootcamp2 src/bootcamp2.cpp)
