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
CMAKE_SOURCE_DIR = /data/home/emk/Coding/Trading_system/TradingSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/home/emk/Coding/Trading_system/TradingSystem

# Include any dependencies generated for this target.
include CMakeFiles/test.exe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test.exe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.exe.dir/flags.make

CMakeFiles/test.exe.dir/main.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/main.cpp.o: main.cpp
CMakeFiles/test.exe.dir/main.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.exe.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/main.cpp.o -MF CMakeFiles/test.exe.dir/main.cpp.o.d -o CMakeFiles/test.exe.dir/main.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/main.cpp

CMakeFiles/test.exe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/main.cpp > CMakeFiles/test.exe.dir/main.cpp.i

CMakeFiles/test.exe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/main.cpp -o CMakeFiles/test.exe.dir/main.cpp.s

CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o: src/DataManager/DataManager.cpp
CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o -MF CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o.d -o CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataManager.cpp

CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataManager.cpp > CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.i

CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataManager.cpp -o CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.s

CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o: src/DataManager/DataReader.cpp
CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o -MF CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o.d -o CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataReader.cpp

CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataReader.cpp > CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.i

CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataReader.cpp -o CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.s

CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o: src/DataManager/DataWriter.cpp
CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o -MF CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o.d -o CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataWriter.cpp

CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataWriter.cpp > CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.i

CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/DataManager/DataWriter.cpp -o CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.s

CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o: src/FUTU/FutuEngine.cpp
CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o -MF CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o.d -o CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/FUTU/FutuEngine.cpp

CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/FUTU/FutuEngine.cpp > CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.i

CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/FUTU/FutuEngine.cpp -o CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.s

CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o: src/Helper/logger.cpp
CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o -MF CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o.d -o CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/Helper/logger.cpp

CMakeFiles/test.exe.dir/src/Helper/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/Helper/logger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/Helper/logger.cpp > CMakeFiles/test.exe.dir/src/Helper/logger.cpp.i

CMakeFiles/test.exe.dir/src/Helper/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/Helper/logger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/Helper/logger.cpp -o CMakeFiles/test.exe.dir/src/Helper/logger.cpp.s

CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o: src/Interface/IEngine.cpp
CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o -MF CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o.d -o CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/IEngine.cpp

CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/IEngine.cpp > CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.i

CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/IEngine.cpp -o CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.s

CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o: src/Interface/IMessenger.cpp
CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o -MF CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o.d -o CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/IMessenger.cpp

CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/IMessenger.cpp > CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.i

CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/IMessenger.cpp -o CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.s

CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o: CMakeFiles/test.exe.dir/flags.make
CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o: src/Interface/datastruture.cpp
CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o: CMakeFiles/test.exe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o -MF CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o.d -o CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o -c /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/datastruture.cpp

CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/datastruture.cpp > CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.i

CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /data/home/emk/Coding/Trading_system/TradingSystem/src/Interface/datastruture.cpp -o CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.s

# Object files for target test.exe
test_exe_OBJECTS = \
"CMakeFiles/test.exe.dir/main.cpp.o" \
"CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o" \
"CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o" \
"CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o" \
"CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o" \
"CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o" \
"CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o" \
"CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o" \
"CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o"

# External object files for target test.exe
test_exe_EXTERNAL_OBJECTS =

test.exe: CMakeFiles/test.exe.dir/main.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/DataManager/DataManager.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/DataManager/DataReader.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/DataManager/DataWriter.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/FUTU/FutuEngine.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/Helper/logger.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/Interface/IEngine.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/Interface/IMessenger.cpp.o
test.exe: CMakeFiles/test.exe.dir/src/Interface/datastruture.cpp.o
test.exe: CMakeFiles/test.exe.dir/build.make
test.exe: /home/emk/vcpkg/installed/x64-linux/debug/lib/libjsoncpp.a
test.exe: CMakeFiles/test.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.exe.dir/build: test.exe
.PHONY : CMakeFiles/test.exe.dir/build

CMakeFiles/test.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.exe.dir/clean

CMakeFiles/test.exe.dir/depend:
	cd /data/home/emk/Coding/Trading_system/TradingSystem && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/home/emk/Coding/Trading_system/TradingSystem /data/home/emk/Coding/Trading_system/TradingSystem /data/home/emk/Coding/Trading_system/TradingSystem /data/home/emk/Coding/Trading_system/TradingSystem /data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles/test.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.exe.dir/depend

