SOURCES = []
OBJECTS = []

RASPI = 1
PREFIX = "arm-none-eabi-"

GCC = PREFIX + "g++"
AS = GCC
LD = PREFIX + "ld"
AR = PREFIX + "ar"
OBJCOPY = PREFIX + "objcopy"
OBJDUMP = PREFIX + "objdump"

INCLUDE_DIRS = ["-I " + String for String in INCLUDE_DIRS]
LIBS = [LIB_PATH + String for String in LIBS]

if (RASPI == 1):
	ARCH = "-march=armv6j -mtune=arm1176jzf-s -mfloat-abi=hard"
else:
	ARCH = "-march=armv7-a -mtune=cortex-a7 -mfloat-abi=hard"

AFLAGS = ARCH + " -g -DRASPPI=%s " % str(RASPI)
CFLAGS = ARCH + " -g -fno-exceptions -Wall -Wno-write-strings -fsigned-char -include " + ROOT_DIR + "Common/default.h -DRASPPI=%s -O " % str(RASPI)

def GetFiles(Directory, Pattern):
	for Root, Dirs, Files in os.walk(Directory):
		for BaseName in Files:
			if fnmatch.fnmatch(BaseName, Pattern):
				Name = os.path.join(Root, BaseName)
				yield Name		

def ExecCommand(Command):
	print(Command)
	return os.system(Command)

def ExecCommandCritical(Command, Return):
	if (ExecCommand(Command) != Return):
		exit(1)

def GetSources():
	global SOURCES
	
	SOURCES += GetFiles(SOURCE_DIR, '*.c')
	SOURCES += GetFiles(SOURCE_DIR, '*.S')

	for filename in SOURCES:
		Name = filename.rsplit("/", 1)[1]
		Name = Name.rsplit(".", 1)[0] + ".o"
		Name = BUILD_DIR + Name

		OBJECTS.append(Name)
		
def Compile():
	for I in range(0, len(SOURCES)):
		if (SOURCES[I].rsplit(".", 1)[1] == "c"):
			FLAGS = CFLAGS
		else:
			FLAGS = AFLAGS
	
		ExecCommandCritical(GCC + " " + FLAGS + " " + " ".join(INCLUDE_DIRS) + " -c -o " + OBJECTS[I] + " " + SOURCES[I], 0)

def StandardClean():
	ExecCommand("find . -name '*.o' -delete");