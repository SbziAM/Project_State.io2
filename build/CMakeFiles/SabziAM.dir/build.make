# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amirmohammad/projects/Project_mabani

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amirmohammad/projects/Project_mabani/build

# Include any dependencies generated for this target.
include CMakeFiles/SabziAM.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SabziAM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SabziAM.dir/flags.make

CMakeFiles/SabziAM.dir/src/main.c.o: CMakeFiles/SabziAM.dir/flags.make
CMakeFiles/SabziAM.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amirmohammad/projects/Project_mabani/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SabziAM.dir/src/main.c.o"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/SabziAM.dir/src/main.c.o   -c /home/amirmohammad/projects/Project_mabani/src/main.c

CMakeFiles/SabziAM.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SabziAM.dir/src/main.c.i"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amirmohammad/projects/Project_mabani/src/main.c > CMakeFiles/SabziAM.dir/src/main.c.i

CMakeFiles/SabziAM.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SabziAM.dir/src/main.c.s"
	/bin/x86_64-linux-gnu-gcc-9 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amirmohammad/projects/Project_mabani/src/main.c -o CMakeFiles/SabziAM.dir/src/main.c.s

# Object files for target SabziAM
SabziAM_OBJECTS = \
"CMakeFiles/SabziAM.dir/src/main.c.o"

# External object files for target SabziAM
SabziAM_EXTERNAL_OBJECTS =

SabziAM: CMakeFiles/SabziAM.dir/src/main.c.o
SabziAM: CMakeFiles/SabziAM.dir/build.make
SabziAM: CMakeFiles/SabziAM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amirmohammad/projects/Project_mabani/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SabziAM"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SabziAM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SabziAM.dir/build: SabziAM

.PHONY : CMakeFiles/SabziAM.dir/build

CMakeFiles/SabziAM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SabziAM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SabziAM.dir/clean

CMakeFiles/SabziAM.dir/depend:
	cd /home/amirmohammad/projects/Project_mabani/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amirmohammad/projects/Project_mabani /home/amirmohammad/projects/Project_mabani /home/amirmohammad/projects/Project_mabani/build /home/amirmohammad/projects/Project_mabani/build /home/amirmohammad/projects/Project_mabani/build/CMakeFiles/SabziAM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SabziAM.dir/depend
