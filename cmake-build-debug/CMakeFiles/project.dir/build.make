# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/57/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/57/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amin/Desktop/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amin/Desktop/project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project.dir/flags.make

CMakeFiles/project.dir/src/init.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/init.c.o: ../src/init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Desktop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/project.dir/src/init.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/project.dir/src/init.c.o   -c /home/amin/Desktop/project/src/init.c

CMakeFiles/project.dir/src/init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/src/init.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Desktop/project/src/init.c > CMakeFiles/project.dir/src/init.c.i

CMakeFiles/project.dir/src/init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/src/init.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Desktop/project/src/init.c -o CMakeFiles/project.dir/src/init.c.s

CMakeFiles/project.dir/src/logic.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/logic.c.o: ../src/logic.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Desktop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/project.dir/src/logic.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/project.dir/src/logic.c.o   -c /home/amin/Desktop/project/src/logic.c

CMakeFiles/project.dir/src/logic.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/src/logic.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Desktop/project/src/logic.c > CMakeFiles/project.dir/src/logic.c.i

CMakeFiles/project.dir/src/logic.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/src/logic.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Desktop/project/src/logic.c -o CMakeFiles/project.dir/src/logic.c.s

CMakeFiles/project.dir/src/main.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Desktop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/project.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/project.dir/src/main.c.o   -c /home/amin/Desktop/project/src/main.c

CMakeFiles/project.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Desktop/project/src/main.c > CMakeFiles/project.dir/src/main.c.i

CMakeFiles/project.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Desktop/project/src/main.c -o CMakeFiles/project.dir/src/main.c.s

CMakeFiles/project.dir/src/physics.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/physics.c.o: ../src/physics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Desktop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/project.dir/src/physics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/project.dir/src/physics.c.o   -c /home/amin/Desktop/project/src/physics.c

CMakeFiles/project.dir/src/physics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/src/physics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Desktop/project/src/physics.c > CMakeFiles/project.dir/src/physics.c.i

CMakeFiles/project.dir/src/physics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/src/physics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Desktop/project/src/physics.c -o CMakeFiles/project.dir/src/physics.c.s

CMakeFiles/project.dir/src/simple_snake.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/simple_snake.c.o: ../src/simple_snake.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Desktop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/project.dir/src/simple_snake.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/project.dir/src/simple_snake.c.o   -c /home/amin/Desktop/project/src/simple_snake.c

CMakeFiles/project.dir/src/simple_snake.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/src/simple_snake.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Desktop/project/src/simple_snake.c > CMakeFiles/project.dir/src/simple_snake.c.i

CMakeFiles/project.dir/src/simple_snake.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/src/simple_snake.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Desktop/project/src/simple_snake.c -o CMakeFiles/project.dir/src/simple_snake.c.s

CMakeFiles/project.dir/src/view.c.o: CMakeFiles/project.dir/flags.make
CMakeFiles/project.dir/src/view.c.o: ../src/view.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amin/Desktop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/project.dir/src/view.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/project.dir/src/view.c.o   -c /home/amin/Desktop/project/src/view.c

CMakeFiles/project.dir/src/view.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/project.dir/src/view.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/amin/Desktop/project/src/view.c > CMakeFiles/project.dir/src/view.c.i

CMakeFiles/project.dir/src/view.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/project.dir/src/view.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/amin/Desktop/project/src/view.c -o CMakeFiles/project.dir/src/view.c.s

# Object files for target project
project_OBJECTS = \
"CMakeFiles/project.dir/src/init.c.o" \
"CMakeFiles/project.dir/src/logic.c.o" \
"CMakeFiles/project.dir/src/main.c.o" \
"CMakeFiles/project.dir/src/physics.c.o" \
"CMakeFiles/project.dir/src/simple_snake.c.o" \
"CMakeFiles/project.dir/src/view.c.o"

# External object files for target project
project_EXTERNAL_OBJECTS =

project: CMakeFiles/project.dir/src/init.c.o
project: CMakeFiles/project.dir/src/logic.c.o
project: CMakeFiles/project.dir/src/main.c.o
project: CMakeFiles/project.dir/src/physics.c.o
project: CMakeFiles/project.dir/src/simple_snake.c.o
project: CMakeFiles/project.dir/src/view.c.o
project: CMakeFiles/project.dir/build.make
project: CMakeFiles/project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amin/Desktop/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project.dir/build: project

.PHONY : CMakeFiles/project.dir/build

CMakeFiles/project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project.dir/clean

CMakeFiles/project.dir/depend:
	cd /home/amin/Desktop/project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amin/Desktop/project /home/amin/Desktop/project /home/amin/Desktop/project/cmake-build-debug /home/amin/Desktop/project/cmake-build-debug /home/amin/Desktop/project/cmake-build-debug/CMakeFiles/project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project.dir/depend

