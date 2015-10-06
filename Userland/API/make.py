#!/usr/bin/python
import os
import fnmatch
import sys

ROOT_DIR = "../../"
COMMON_DIR = ROOT_DIR + "Common/"
SOURCE_DIR = "source/"
BUILD_DIR = "build/"
INCLUDE_DIRS = ["include/", ROOT_DIR + "Stdlib/include"]
LIB_PATH = COMMON_DIR
LIBS = []

OUTPUT_NAME = "siwkapi"

os.chdir(sys.path[0])
exec(open(ROOT_DIR + "defs.py").read())

def Make():	
	StandardClean()
	GetSources()
	Compile()
	
	ExecCommandCritical(AR + " cr " + ROOT_DIR + "Common/" + OUTPUT_NAME + ".a " + " ".join(OBJECTS), 0)
	
	exit(0);
	
Make()


