#!/usr/bin/python
import os
import fnmatch
import sys

ROOT_DIR = "../../../"
COMMON_DIR = ROOT_DIR + "Common/"
SOURCE_DIR = "source/"
BUILD_DIR = "build/"
INCLUDE_DIRS = ["include/", ROOT_DIR + "Stdlib/include", ROOT_DIR + "Userland/API/include"]
LIB_PATH = COMMON_DIR
LIBS = ["libgcc.a", "stdlib.a", "siwkapi.a"]

PROGRAM_NAME = "Snake"

os.chdir(sys.path[0])
exec(open(ROOT_DIR + "defs.py").read())

def Make():	
	StandardClean()
	GetSources()
	Compile()
	
	ExecCommandCritical(LD + " --whole-archive --no-undefined " + " ".join(OBJECTS) + " " + " ".join(LIBS) + " -o " + BUILD_DIR + PROGRAM_NAME + ".elf -T program.ld", 0)
	ExecCommandCritical(OBJDUMP + " -D " + BUILD_DIR + PROGRAM_NAME + ".elf > " + PROGRAM_NAME + ".lst", 0)
	ExecCommandCritical(OBJCOPY + " " + BUILD_DIR + PROGRAM_NAME + ".elf -O binary " + PROGRAM_NAME + ".bin", 0)
	ExecCommandCritical(COMMON_DIR + "siwkasign " + PROGRAM_NAME + ".bin " + COMMON_DIR + "Programs/" + PROGRAM_NAME + ".swx " + PROGRAM_NAME + "", 0)
	
	exit(0);
	
Make()


