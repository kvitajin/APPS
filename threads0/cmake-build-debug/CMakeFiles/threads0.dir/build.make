# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/kvitajin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kvitajin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.4892.24/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kvitajin/CLionProjects/vsb/apps/threads0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kvitajin/CLionProjects/vsb/apps/threads0/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/threads0.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/threads0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threads0.dir/flags.make

CMakeFiles/threads0.dir/main.cpp.o: CMakeFiles/threads0.dir/flags.make
CMakeFiles/threads0.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kvitajin/CLionProjects/vsb/apps/threads0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threads0.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threads0.dir/main.cpp.o -c /home/kvitajin/CLionProjects/vsb/apps/threads0/main.cpp

CMakeFiles/threads0.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threads0.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kvitajin/CLionProjects/vsb/apps/threads0/main.cpp > CMakeFiles/threads0.dir/main.cpp.i

CMakeFiles/threads0.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threads0.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kvitajin/CLionProjects/vsb/apps/threads0/main.cpp -o CMakeFiles/threads0.dir/main.cpp.s

# Object files for target threads0
threads0_OBJECTS = \
"CMakeFiles/threads0.dir/main.cpp.o"

# External object files for target threads0
threads0_EXTERNAL_OBJECTS =

threads0: CMakeFiles/threads0.dir/main.cpp.o
threads0: CMakeFiles/threads0.dir/build.make
threads0: CMakeFiles/threads0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kvitajin/CLionProjects/vsb/apps/threads0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable threads0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threads0.dir/build: threads0

.PHONY : CMakeFiles/threads0.dir/build

CMakeFiles/threads0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threads0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threads0.dir/clean

CMakeFiles/threads0.dir/depend:
	cd /home/kvitajin/CLionProjects/vsb/apps/threads0/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kvitajin/CLionProjects/vsb/apps/threads0 /home/kvitajin/CLionProjects/vsb/apps/threads0 /home/kvitajin/CLionProjects/vsb/apps/threads0/cmake-build-debug /home/kvitajin/CLionProjects/vsb/apps/threads0/cmake-build-debug /home/kvitajin/CLionProjects/vsb/apps/threads0/cmake-build-debug/CMakeFiles/threads0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threads0.dir/depend

