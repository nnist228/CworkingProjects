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
CMAKE_SOURCE_DIR = /home/alex/Projects/C/HashTablesTask/rework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Projects/C/HashTablesTask/rework/build

# Include any dependencies generated for this target.
include CMakeFiles/WordsCounter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/WordsCounter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/WordsCounter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/WordsCounter.dir/flags.make

CMakeFiles/WordsCounter.dir/Tests.c.o: CMakeFiles/WordsCounter.dir/flags.make
CMakeFiles/WordsCounter.dir/Tests.c.o: ../Tests.c
CMakeFiles/WordsCounter.dir/Tests.c.o: CMakeFiles/WordsCounter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/WordsCounter.dir/Tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/WordsCounter.dir/Tests.c.o -MF CMakeFiles/WordsCounter.dir/Tests.c.o.d -o CMakeFiles/WordsCounter.dir/Tests.c.o -c /home/alex/Projects/C/HashTablesTask/rework/Tests.c

CMakeFiles/WordsCounter.dir/Tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordsCounter.dir/Tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/C/HashTablesTask/rework/Tests.c > CMakeFiles/WordsCounter.dir/Tests.c.i

CMakeFiles/WordsCounter.dir/Tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordsCounter.dir/Tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/C/HashTablesTask/rework/Tests.c -o CMakeFiles/WordsCounter.dir/Tests.c.s

CMakeFiles/WordsCounter.dir/forward_list.c.o: CMakeFiles/WordsCounter.dir/flags.make
CMakeFiles/WordsCounter.dir/forward_list.c.o: ../forward_list.c
CMakeFiles/WordsCounter.dir/forward_list.c.o: CMakeFiles/WordsCounter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/WordsCounter.dir/forward_list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/WordsCounter.dir/forward_list.c.o -MF CMakeFiles/WordsCounter.dir/forward_list.c.o.d -o CMakeFiles/WordsCounter.dir/forward_list.c.o -c /home/alex/Projects/C/HashTablesTask/rework/forward_list.c

CMakeFiles/WordsCounter.dir/forward_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordsCounter.dir/forward_list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/C/HashTablesTask/rework/forward_list.c > CMakeFiles/WordsCounter.dir/forward_list.c.i

CMakeFiles/WordsCounter.dir/forward_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordsCounter.dir/forward_list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/C/HashTablesTask/rework/forward_list.c -o CMakeFiles/WordsCounter.dir/forward_list.c.s

CMakeFiles/WordsCounter.dir/open_hash_struct.c.o: CMakeFiles/WordsCounter.dir/flags.make
CMakeFiles/WordsCounter.dir/open_hash_struct.c.o: ../open_hash_struct.c
CMakeFiles/WordsCounter.dir/open_hash_struct.c.o: CMakeFiles/WordsCounter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/WordsCounter.dir/open_hash_struct.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/WordsCounter.dir/open_hash_struct.c.o -MF CMakeFiles/WordsCounter.dir/open_hash_struct.c.o.d -o CMakeFiles/WordsCounter.dir/open_hash_struct.c.o -c /home/alex/Projects/C/HashTablesTask/rework/open_hash_struct.c

CMakeFiles/WordsCounter.dir/open_hash_struct.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordsCounter.dir/open_hash_struct.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/C/HashTablesTask/rework/open_hash_struct.c > CMakeFiles/WordsCounter.dir/open_hash_struct.c.i

CMakeFiles/WordsCounter.dir/open_hash_struct.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordsCounter.dir/open_hash_struct.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/C/HashTablesTask/rework/open_hash_struct.c -o CMakeFiles/WordsCounter.dir/open_hash_struct.c.s

CMakeFiles/WordsCounter.dir/hash_table_open.c.o: CMakeFiles/WordsCounter.dir/flags.make
CMakeFiles/WordsCounter.dir/hash_table_open.c.o: ../hash_table_open.c
CMakeFiles/WordsCounter.dir/hash_table_open.c.o: CMakeFiles/WordsCounter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/WordsCounter.dir/hash_table_open.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/WordsCounter.dir/hash_table_open.c.o -MF CMakeFiles/WordsCounter.dir/hash_table_open.c.o.d -o CMakeFiles/WordsCounter.dir/hash_table_open.c.o -c /home/alex/Projects/C/HashTablesTask/rework/hash_table_open.c

CMakeFiles/WordsCounter.dir/hash_table_open.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordsCounter.dir/hash_table_open.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/C/HashTablesTask/rework/hash_table_open.c > CMakeFiles/WordsCounter.dir/hash_table_open.c.i

CMakeFiles/WordsCounter.dir/hash_table_open.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordsCounter.dir/hash_table_open.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/C/HashTablesTask/rework/hash_table_open.c -o CMakeFiles/WordsCounter.dir/hash_table_open.c.s

CMakeFiles/WordsCounter.dir/hash_table_list.c.o: CMakeFiles/WordsCounter.dir/flags.make
CMakeFiles/WordsCounter.dir/hash_table_list.c.o: ../hash_table_list.c
CMakeFiles/WordsCounter.dir/hash_table_list.c.o: CMakeFiles/WordsCounter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/WordsCounter.dir/hash_table_list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/WordsCounter.dir/hash_table_list.c.o -MF CMakeFiles/WordsCounter.dir/hash_table_list.c.o.d -o CMakeFiles/WordsCounter.dir/hash_table_list.c.o -c /home/alex/Projects/C/HashTablesTask/rework/hash_table_list.c

CMakeFiles/WordsCounter.dir/hash_table_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordsCounter.dir/hash_table_list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/C/HashTablesTask/rework/hash_table_list.c > CMakeFiles/WordsCounter.dir/hash_table_list.c.i

CMakeFiles/WordsCounter.dir/hash_table_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordsCounter.dir/hash_table_list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/C/HashTablesTask/rework/hash_table_list.c -o CMakeFiles/WordsCounter.dir/hash_table_list.c.s

CMakeFiles/WordsCounter.dir/hash.c.o: CMakeFiles/WordsCounter.dir/flags.make
CMakeFiles/WordsCounter.dir/hash.c.o: ../hash.c
CMakeFiles/WordsCounter.dir/hash.c.o: CMakeFiles/WordsCounter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/WordsCounter.dir/hash.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/WordsCounter.dir/hash.c.o -MF CMakeFiles/WordsCounter.dir/hash.c.o.d -o CMakeFiles/WordsCounter.dir/hash.c.o -c /home/alex/Projects/C/HashTablesTask/rework/hash.c

CMakeFiles/WordsCounter.dir/hash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/WordsCounter.dir/hash.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alex/Projects/C/HashTablesTask/rework/hash.c > CMakeFiles/WordsCounter.dir/hash.c.i

CMakeFiles/WordsCounter.dir/hash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/WordsCounter.dir/hash.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alex/Projects/C/HashTablesTask/rework/hash.c -o CMakeFiles/WordsCounter.dir/hash.c.s

# Object files for target WordsCounter
WordsCounter_OBJECTS = \
"CMakeFiles/WordsCounter.dir/Tests.c.o" \
"CMakeFiles/WordsCounter.dir/forward_list.c.o" \
"CMakeFiles/WordsCounter.dir/open_hash_struct.c.o" \
"CMakeFiles/WordsCounter.dir/hash_table_open.c.o" \
"CMakeFiles/WordsCounter.dir/hash_table_list.c.o" \
"CMakeFiles/WordsCounter.dir/hash.c.o"

# External object files for target WordsCounter
WordsCounter_EXTERNAL_OBJECTS =

WordsCounter: CMakeFiles/WordsCounter.dir/Tests.c.o
WordsCounter: CMakeFiles/WordsCounter.dir/forward_list.c.o
WordsCounter: CMakeFiles/WordsCounter.dir/open_hash_struct.c.o
WordsCounter: CMakeFiles/WordsCounter.dir/hash_table_open.c.o
WordsCounter: CMakeFiles/WordsCounter.dir/hash_table_list.c.o
WordsCounter: CMakeFiles/WordsCounter.dir/hash.c.o
WordsCounter: CMakeFiles/WordsCounter.dir/build.make
WordsCounter: CMakeFiles/WordsCounter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable WordsCounter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WordsCounter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/WordsCounter.dir/build: WordsCounter
.PHONY : CMakeFiles/WordsCounter.dir/build

CMakeFiles/WordsCounter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/WordsCounter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/WordsCounter.dir/clean

CMakeFiles/WordsCounter.dir/depend:
	cd /home/alex/Projects/C/HashTablesTask/rework/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Projects/C/HashTablesTask/rework /home/alex/Projects/C/HashTablesTask/rework /home/alex/Projects/C/HashTablesTask/rework/build /home/alex/Projects/C/HashTablesTask/rework/build /home/alex/Projects/C/HashTablesTask/rework/build/CMakeFiles/WordsCounter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/WordsCounter.dir/depend

