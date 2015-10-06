#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

typedef struct
{
	uint32 Width;
	uint32 Height;
	uint32 VirtualWidth;
	uint32 VirtualHeight;
	uint32 Pitch;
	uint32 BitDepth;
	uint32 X;
	uint32 Y;
	char* Pointer;
	uint32 Size;
} FramebufferDescription;

namespace Framebuffer
{
	extern FramebufferDescription Description __attribute__ ((__aligned__(64)));
	
	void Setup();
	FramebufferDescription* GetDescription();
}

#endif
