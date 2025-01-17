# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-src")
  file(MAKE_DIRECTORY "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-src")
endif()
file(MAKE_DIRECTORY
  "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-build"
  "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-subbuild/pybind11-populate-prefix"
  "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-subbuild/pybind11-populate-prefix/tmp"
  "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-subbuild/pybind11-populate-prefix/src/pybind11-populate-stamp"
  "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-subbuild/pybind11-populate-prefix/src"
  "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-subbuild/pybind11-populate-prefix/src/pybind11-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-subbuild/pybind11-populate-prefix/src/pybind11-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/NULP/SEM 3/Coursework/Coursework/Coursework/build/_deps/pybind11-subbuild/pybind11-populate-prefix/src/pybind11-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
