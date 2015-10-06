#!/usr/bin/python

import os
import sys

print("Compiling Standard Library")
if (os.system("./Stdlib/make.py > /dev/null") != 0):
	exit(0)
	
print("Compiling Userland/API")
if (os.system("./Userland/API/make.py > /dev/null") != 0):
	exit(0)
	
print("Compiling Userland/Programs/Init")
if (os.system("./Userland/Programs/Init/make.py > /dev/null") != 0):
	exit(0)
	
print("Compiling Userland/Programs/Leprog")
if (os.system("./Userland/Programs/Leprog/make.py > /dev/null") != 0):
	exit(0)
	
print("Compiling Userland/Programs/Snake")
if (os.system("./Userland/Programs/Snake/make.py > /dev/null") != 0):
	exit(0)
	
print("Compiling Kernel")

if (os.system("./Kernel/make.py > /dev/null") == 0 and len(sys.argv) > 1):
	if (sys.argv[1] == "-t"):
		os.system("qemu-system-arm -kernel Common/kernel.img -initrd Common/kernel.img -cpu arm1176 -m 512 -M raspi")
	elif (sys.argv[1] == "-w"):
		os.system("sudo ./etherboot Common/kernel.img")
		
	
