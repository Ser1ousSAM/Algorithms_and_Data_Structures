# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list

# Include any dependencies generated for this target.
include CMakeFiles/LList.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LList.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LList.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LList.dir/flags.make

CMakeFiles/LList.dir/LList.cpp.o: CMakeFiles/LList.dir/flags.make
CMakeFiles/LList.dir/LList.cpp.o: LList.cpp
CMakeFiles/LList.dir/LList.cpp.o: CMakeFiles/LList.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LList.dir/LList.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LList.dir/LList.cpp.o -MF CMakeFiles/LList.dir/LList.cpp.o.d -o CMakeFiles/LList.dir/LList.cpp.o -c /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list/LList.cpp

CMakeFiles/LList.dir/LList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LList.dir/LList.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list/LList.cpp > CMakeFiles/LList.dir/LList.cpp.i

CMakeFiles/LList.dir/LList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LList.dir/LList.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list/LList.cpp -o CMakeFiles/LList.dir/LList.cpp.s

# Object files for target LList
LList_OBJECTS = \
"CMakeFiles/LList.dir/LList.cpp.o"

# External object files for target LList
LList_EXTERNAL_OBJECTS =

LList: CMakeFiles/LList.dir/LList.cpp.o
LList: CMakeFiles/LList.dir/build.make
LList: CMakeFiles/LList.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LList"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LList.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LList.dir/build: LList
.PHONY : CMakeFiles/LList.dir/build

CMakeFiles/LList.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LList.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LList.dir/clean

CMakeFiles/LList.dir/depend:
	cd /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list /home/gleb/Desktop/University/Algorithms_and_Data_Structures/list/new_list/CMakeFiles/LList.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LList.dir/depend

