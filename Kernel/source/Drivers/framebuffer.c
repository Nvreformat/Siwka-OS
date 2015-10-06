#include <Kernel/framebuffer.h>
#include <Kernel/mailbox.h>

namespace Framebuffer
{
	FramebufferDescription Description __attribute__ ((__aligned__(64))) = {0};
	
	void Setup()
	{
		Description.Width = 1920;
		Description.Height = 1080;
		Description.VirtualWidth = 1920;
		Description.VirtualHeight = 1080;
		Description.Pitch = 0;
		Description.BitDepth = 24;
		Description.X = 0;
		Description.Y = 0;
		Description.Pointer = 0;
		Description.Size = 0;

		MailBoxWriteRead(1, (uint32)(&Description) | 0x40000000);
	}
	
	FramebufferDescription* GetDescription()
	{
		return &Description;
	}
}

