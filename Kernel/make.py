#!/usr/bin/python
import os
import fnmatch
import sys

ROOT_DIR = "../"
COMMON_DIR = ROOT_DIR + "Common/"
SOURCE_DIR = "source/"
BUILD_DIR = "build/"
INCLUDE_DIRS = ["include/", ROOT_DIR + "Stdlib/include"]
LIB_PATH = COMMON_DIR
LIBS = ["libuspi.a", "stdlib.a", "libgcc.a", "stdlib.a"]

OUTPUT_NAME = "kernel"

os.chdir(sys.path[0])
exec(open(ROOT_DIR + "defs.py").read())

def Make():	
	StandardClean()
	GetSources()
	Compile()
	
	ExecCommandCritical(LD + " --no-undefined " + " ".join(OBJECTS) + " " + " ".join(LIBS) + " -o " + BUILD_DIR + OUTPUT_NAME + ".elf -T " + OUTPUT_NAME + ".ld", 0)
	ExecCommandCritical(OBJDUMP + " -D " + BUILD_DIR + OUTPUT_NAME + ".elf > " + OUTPUT_NAME + ".lst", 0)
	ExecCommandCritical(OBJCOPY + " " + BUILD_DIR + OUTPUT_NAME + ".elf -O binary " + COMMON_DIR + OUTPUT_NAME + ".img", 0)
	
	exit(0);
	
Make()


