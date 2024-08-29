# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles /data/home/emk/Coding/Trading_system/TradingSystem//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /data/home/emk/Coding/Trading_system/TradingSystem/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named test

# Build rule for target.
test: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test
.PHONY : test

# fast build rule for target.
test/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/build
.PHONY : test/fast

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/main.cpp.s
.PHONY : main.cpp.s

src/DataManager/DataManager.o: src/DataManager/DataManager.cpp.o
.PHONY : src/DataManager/DataManager.o

# target to build an object file
src/DataManager/DataManager.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataManager.cpp.o
.PHONY : src/DataManager/DataManager.cpp.o

src/DataManager/DataManager.i: src/DataManager/DataManager.cpp.i
.PHONY : src/DataManager/DataManager.i

# target to preprocess a source file
src/DataManager/DataManager.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataManager.cpp.i
.PHONY : src/DataManager/DataManager.cpp.i

src/DataManager/DataManager.s: src/DataManager/DataManager.cpp.s
.PHONY : src/DataManager/DataManager.s

# target to generate assembly for a file
src/DataManager/DataManager.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataManager.cpp.s
.PHONY : src/DataManager/DataManager.cpp.s

src/DataManager/DataReader.o: src/DataManager/DataReader.cpp.o
.PHONY : src/DataManager/DataReader.o

# target to build an object file
src/DataManager/DataReader.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataReader.cpp.o
.PHONY : src/DataManager/DataReader.cpp.o

src/DataManager/DataReader.i: src/DataManager/DataReader.cpp.i
.PHONY : src/DataManager/DataReader.i

# target to preprocess a source file
src/DataManager/DataReader.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataReader.cpp.i
.PHONY : src/DataManager/DataReader.cpp.i

src/DataManager/DataReader.s: src/DataManager/DataReader.cpp.s
.PHONY : src/DataManager/DataReader.s

# target to generate assembly for a file
src/DataManager/DataReader.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataReader.cpp.s
.PHONY : src/DataManager/DataReader.cpp.s

src/DataManager/DataWriter.o: src/DataManager/DataWriter.cpp.o
.PHONY : src/DataManager/DataWriter.o

# target to build an object file
src/DataManager/DataWriter.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataWriter.cpp.o
.PHONY : src/DataManager/DataWriter.cpp.o

src/DataManager/DataWriter.i: src/DataManager/DataWriter.cpp.i
.PHONY : src/DataManager/DataWriter.i

# target to preprocess a source file
src/DataManager/DataWriter.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataWriter.cpp.i
.PHONY : src/DataManager/DataWriter.cpp.i

src/DataManager/DataWriter.s: src/DataManager/DataWriter.cpp.s
.PHONY : src/DataManager/DataWriter.s

# target to generate assembly for a file
src/DataManager/DataWriter.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/DataManager/DataWriter.cpp.s
.PHONY : src/DataManager/DataWriter.cpp.s

src/FUTU/FutuEngine.o: src/FUTU/FutuEngine.cpp.o
.PHONY : src/FUTU/FutuEngine.o

# target to build an object file
src/FUTU/FutuEngine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/FUTU/FutuEngine.cpp.o
.PHONY : src/FUTU/FutuEngine.cpp.o

src/FUTU/FutuEngine.i: src/FUTU/FutuEngine.cpp.i
.PHONY : src/FUTU/FutuEngine.i

# target to preprocess a source file
src/FUTU/FutuEngine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/FUTU/FutuEngine.cpp.i
.PHONY : src/FUTU/FutuEngine.cpp.i

src/FUTU/FutuEngine.s: src/FUTU/FutuEngine.cpp.s
.PHONY : src/FUTU/FutuEngine.s

# target to generate assembly for a file
src/FUTU/FutuEngine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/FUTU/FutuEngine.cpp.s
.PHONY : src/FUTU/FutuEngine.cpp.s

src/Helper/logger.o: src/Helper/logger.cpp.o
.PHONY : src/Helper/logger.o

# target to build an object file
src/Helper/logger.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Helper/logger.cpp.o
.PHONY : src/Helper/logger.cpp.o

src/Helper/logger.i: src/Helper/logger.cpp.i
.PHONY : src/Helper/logger.i

# target to preprocess a source file
src/Helper/logger.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Helper/logger.cpp.i
.PHONY : src/Helper/logger.cpp.i

src/Helper/logger.s: src/Helper/logger.cpp.s
.PHONY : src/Helper/logger.s

# target to generate assembly for a file
src/Helper/logger.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Helper/logger.cpp.s
.PHONY : src/Helper/logger.cpp.s

src/Interface/IEngine.o: src/Interface/IEngine.cpp.o
.PHONY : src/Interface/IEngine.o

# target to build an object file
src/Interface/IEngine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/IEngine.cpp.o
.PHONY : src/Interface/IEngine.cpp.o

src/Interface/IEngine.i: src/Interface/IEngine.cpp.i
.PHONY : src/Interface/IEngine.i

# target to preprocess a source file
src/Interface/IEngine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/IEngine.cpp.i
.PHONY : src/Interface/IEngine.cpp.i

src/Interface/IEngine.s: src/Interface/IEngine.cpp.s
.PHONY : src/Interface/IEngine.s

# target to generate assembly for a file
src/Interface/IEngine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/IEngine.cpp.s
.PHONY : src/Interface/IEngine.cpp.s

src/Interface/IMessenger.o: src/Interface/IMessenger.cpp.o
.PHONY : src/Interface/IMessenger.o

# target to build an object file
src/Interface/IMessenger.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/IMessenger.cpp.o
.PHONY : src/Interface/IMessenger.cpp.o

src/Interface/IMessenger.i: src/Interface/IMessenger.cpp.i
.PHONY : src/Interface/IMessenger.i

# target to preprocess a source file
src/Interface/IMessenger.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/IMessenger.cpp.i
.PHONY : src/Interface/IMessenger.cpp.i

src/Interface/IMessenger.s: src/Interface/IMessenger.cpp.s
.PHONY : src/Interface/IMessenger.s

# target to generate assembly for a file
src/Interface/IMessenger.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/IMessenger.cpp.s
.PHONY : src/Interface/IMessenger.cpp.s

src/Interface/datastruture.o: src/Interface/datastruture.cpp.o
.PHONY : src/Interface/datastruture.o

# target to build an object file
src/Interface/datastruture.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/datastruture.cpp.o
.PHONY : src/Interface/datastruture.cpp.o

src/Interface/datastruture.i: src/Interface/datastruture.cpp.i
.PHONY : src/Interface/datastruture.i

# target to preprocess a source file
src/Interface/datastruture.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/datastruture.cpp.i
.PHONY : src/Interface/datastruture.cpp.i

src/Interface/datastruture.s: src/Interface/datastruture.cpp.s
.PHONY : src/Interface/datastruture.s

# target to generate assembly for a file
src/Interface/datastruture.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Interface/datastruture.cpp.s
.PHONY : src/Interface/datastruture.cpp.s

src/Strategy/StrategyEngine.o: src/Strategy/StrategyEngine.cpp.o
.PHONY : src/Strategy/StrategyEngine.o

# target to build an object file
src/Strategy/StrategyEngine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/StrategyEngine.cpp.o
.PHONY : src/Strategy/StrategyEngine.cpp.o

src/Strategy/StrategyEngine.i: src/Strategy/StrategyEngine.cpp.i
.PHONY : src/Strategy/StrategyEngine.i

# target to preprocess a source file
src/Strategy/StrategyEngine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/StrategyEngine.cpp.i
.PHONY : src/Strategy/StrategyEngine.cpp.i

src/Strategy/StrategyEngine.s: src/Strategy/StrategyEngine.cpp.s
.PHONY : src/Strategy/StrategyEngine.s

# target to generate assembly for a file
src/Strategy/StrategyEngine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/StrategyEngine.cpp.s
.PHONY : src/Strategy/StrategyEngine.cpp.s

src/Strategy/TestStrategy.o: src/Strategy/TestStrategy.cpp.o
.PHONY : src/Strategy/TestStrategy.o

# target to build an object file
src/Strategy/TestStrategy.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/TestStrategy.cpp.o
.PHONY : src/Strategy/TestStrategy.cpp.o

src/Strategy/TestStrategy.i: src/Strategy/TestStrategy.cpp.i
.PHONY : src/Strategy/TestStrategy.i

# target to preprocess a source file
src/Strategy/TestStrategy.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/TestStrategy.cpp.i
.PHONY : src/Strategy/TestStrategy.cpp.i

src/Strategy/TestStrategy.s: src/Strategy/TestStrategy.cpp.s
.PHONY : src/Strategy/TestStrategy.s

# target to generate assembly for a file
src/Strategy/TestStrategy.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/TestStrategy.cpp.s
.PHONY : src/Strategy/TestStrategy.cpp.s

src/Strategy/TradeUtil.o: src/Strategy/TradeUtil.cpp.o
.PHONY : src/Strategy/TradeUtil.o

# target to build an object file
src/Strategy/TradeUtil.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/TradeUtil.cpp.o
.PHONY : src/Strategy/TradeUtil.cpp.o

src/Strategy/TradeUtil.i: src/Strategy/TradeUtil.cpp.i
.PHONY : src/Strategy/TradeUtil.i

# target to preprocess a source file
src/Strategy/TradeUtil.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/TradeUtil.cpp.i
.PHONY : src/Strategy/TradeUtil.cpp.i

src/Strategy/TradeUtil.s: src/Strategy/TradeUtil.cpp.s
.PHONY : src/Strategy/TradeUtil.s

# target to generate assembly for a file
src/Strategy/TradeUtil.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/src/Strategy/TradeUtil.cpp.s
.PHONY : src/Strategy/TradeUtil.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/DataManager/DataManager.o"
	@echo "... src/DataManager/DataManager.i"
	@echo "... src/DataManager/DataManager.s"
	@echo "... src/DataManager/DataReader.o"
	@echo "... src/DataManager/DataReader.i"
	@echo "... src/DataManager/DataReader.s"
	@echo "... src/DataManager/DataWriter.o"
	@echo "... src/DataManager/DataWriter.i"
	@echo "... src/DataManager/DataWriter.s"
	@echo "... src/FUTU/FutuEngine.o"
	@echo "... src/FUTU/FutuEngine.i"
	@echo "... src/FUTU/FutuEngine.s"
	@echo "... src/Helper/logger.o"
	@echo "... src/Helper/logger.i"
	@echo "... src/Helper/logger.s"
	@echo "... src/Interface/IEngine.o"
	@echo "... src/Interface/IEngine.i"
	@echo "... src/Interface/IEngine.s"
	@echo "... src/Interface/IMessenger.o"
	@echo "... src/Interface/IMessenger.i"
	@echo "... src/Interface/IMessenger.s"
	@echo "... src/Interface/datastruture.o"
	@echo "... src/Interface/datastruture.i"
	@echo "... src/Interface/datastruture.s"
	@echo "... src/Strategy/StrategyEngine.o"
	@echo "... src/Strategy/StrategyEngine.i"
	@echo "... src/Strategy/StrategyEngine.s"
	@echo "... src/Strategy/TestStrategy.o"
	@echo "... src/Strategy/TestStrategy.i"
	@echo "... src/Strategy/TestStrategy.s"
	@echo "... src/Strategy/TradeUtil.o"
	@echo "... src/Strategy/TradeUtil.i"
	@echo "... src/Strategy/TradeUtil.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

