# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.5\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Cutting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Cutting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Cutting.dir/flags.make

CMakeFiles/Cutting.dir/main.cpp.obj: CMakeFiles/Cutting.dir/flags.make
CMakeFiles/Cutting.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Cutting.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Cutting.dir\main.cpp.obj -c C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\main.cpp

CMakeFiles/Cutting.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cutting.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\main.cpp > CMakeFiles\Cutting.dir\main.cpp.i

CMakeFiles/Cutting.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cutting.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\main.cpp -o CMakeFiles\Cutting.dir\main.cpp.s

# Object files for target Cutting
Cutting_OBJECTS = \
"CMakeFiles/Cutting.dir/main.cpp.obj"

# External object files for target Cutting
Cutting_EXTERNAL_OBJECTS =

Cutting.exe: CMakeFiles/Cutting.dir/main.cpp.obj
Cutting.exe: CMakeFiles/Cutting.dir/build.make
Cutting.exe: CMakeFiles/Cutting.dir/linklibs.rsp
Cutting.exe: CMakeFiles/Cutting.dir/objects1.rsp
Cutting.exe: CMakeFiles/Cutting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Cutting.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Cutting.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Cutting.dir/build: Cutting.exe

.PHONY : CMakeFiles/Cutting.dir/build

CMakeFiles/Cutting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Cutting.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Cutting.dir/clean

CMakeFiles/Cutting.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\cmake-build-debug C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\cmake-build-debug C:\Users\Comarch\Desktop\studia\genetyczne\projekt\Cutting\cmake-build-debug\CMakeFiles\Cutting.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Cutting.dir/depend

