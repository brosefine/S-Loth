# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/anny/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/anny/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/173.4548.31/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anny/Dokumente/Projects/untitled

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anny/Dokumente/Projects/untitled/cmake-build-debug

# Include any dependencies generated for this target.
include apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/depend.make

# Include the progress variables for this target.
include apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/progress.make

# Include the compile flags for this target's objects.
include apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/flags.make

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o: apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/flags.make
apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o: ../apps/s-loth_main/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anny/Dokumente/Projects/untitled/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o"
	cd /home/anny/Dokumente/Projects/untitled/cmake-build-debug/apps/s-loth_main && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/s-loth_main_app.dir/main.cpp.o -c /home/anny/Dokumente/Projects/untitled/apps/s-loth_main/main.cpp

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/s-loth_main_app.dir/main.cpp.i"
	cd /home/anny/Dokumente/Projects/untitled/cmake-build-debug/apps/s-loth_main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anny/Dokumente/Projects/untitled/apps/s-loth_main/main.cpp > CMakeFiles/s-loth_main_app.dir/main.cpp.i

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/s-loth_main_app.dir/main.cpp.s"
	cd /home/anny/Dokumente/Projects/untitled/cmake-build-debug/apps/s-loth_main && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anny/Dokumente/Projects/untitled/apps/s-loth_main/main.cpp -o CMakeFiles/s-loth_main_app.dir/main.cpp.s

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.requires:

.PHONY : apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.requires

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.provides: apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.requires
	$(MAKE) -f apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/build.make apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.provides.build
.PHONY : apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.provides

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.provides.build: apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o


# Object files for target s-loth_main_app
s__loth_main_app_OBJECTS = \
"CMakeFiles/s-loth_main_app.dir/main.cpp.o"

# External object files for target s-loth_main_app
s__loth_main_app_EXTERNAL_OBJECTS =

bin/s-loth_main: apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o
bin/s-loth_main: apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/build.make
bin/s-loth_main: lib/libs-loth_source.so
bin/s-loth_main: /usr/lib/x86_64-linux-gnu/libglut.so
bin/s-loth_main: /usr/lib/x86_64-linux-gnu/libXmu.so
bin/s-loth_main: /usr/lib/x86_64-linux-gnu/libXi.so
bin/s-loth_main: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/s-loth_main: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/s-loth_main: /usr/lib/x86_64-linux-gnu/libGL.so
bin/s-loth_main: /usr/lib/libSOIL.a
bin/s-loth_main: /usr/lib/x86_64-linux-gnu/libGLEW.so
bin/s-loth_main: apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anny/Dokumente/Projects/untitled/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/s-loth_main"
	cd /home/anny/Dokumente/Projects/untitled/cmake-build-debug/apps/s-loth_main && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/s-loth_main_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/build: bin/s-loth_main

.PHONY : apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/build

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/requires: apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/main.cpp.o.requires

.PHONY : apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/requires

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/clean:
	cd /home/anny/Dokumente/Projects/untitled/cmake-build-debug/apps/s-loth_main && $(CMAKE_COMMAND) -P CMakeFiles/s-loth_main_app.dir/cmake_clean.cmake
.PHONY : apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/clean

apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/depend:
	cd /home/anny/Dokumente/Projects/untitled/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anny/Dokumente/Projects/untitled /home/anny/Dokumente/Projects/untitled/apps/s-loth_main /home/anny/Dokumente/Projects/untitled/cmake-build-debug /home/anny/Dokumente/Projects/untitled/cmake-build-debug/apps/s-loth_main /home/anny/Dokumente/Projects/untitled/cmake-build-debug/apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : apps/s-loth_main/CMakeFiles/s-loth_main_app.dir/depend
