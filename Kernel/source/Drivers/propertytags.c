#include <Stdlib/memutil.h>
#include <Kernel/propertytags.h>
#include <Kernel/sysutils.h>
#include <Kernel/bcm2835.h>

bool PropertyTagsGetTag(uint32 TagId, void* Tag, unsigned TagSize, unsigned  RequestParmSize)
{
	unsigned BufferSize = sizeof(PropertyBuffer) + TagSize + sizeof(uint32);

	uint8 Buffer[BufferSize + 15];
	PropertyBuffer *PropBuffer = (PropertyBuffer*) (((uint32) Buffer + 15) & ~15);
	
	PropBuffer->BufferSize = BufferSize;
	PropBuffer->Code = CODE_REQUEST;
	
	MemoryCopy (Tag, PropBuffer->Tags, TagSize);
	
	PropertyTag* Header = (PropertyTag*) PropBuffer->Tags;
	Header->TagId = TagId;
	Header->ValueBufSize = TagSize - sizeof(PropertyTag);
	Header->ValueLength = RequestParmSize & ~VALUE_LENGTH_RESPONSE;

	uint32* EndTag = (uint32*) (PropBuffer->Tags + TagSize);
	*EndTag = PROPTAG_END;

	CleanDataCache ();
	DataSyncBarrier ();

	uint32 BufferAddress = GPU_MEM_BASE + (uint32) PropBuffer;
	if (MailBoxWriteRead(8, BufferAddress) != BufferAddress)
	{
		return false;
	}
	
	InvalidateDataCache ();
	DataSyncBarrier ();

	if (PropBuffer->Code != CODE_RESPONSE_SUCCESS)
	{
		return false;
	}
	
	if (!(Header->ValueLength & VALUE_LENGTH_RESPONSE))
	{
		return false;
	}
	
	Header->ValueLength &= ~VALUE_LENGTH_RESPONSE;
	if (Header->ValueLength == 0)
	{
		return false;
	}

	MemoryCopy(PropBuffer->Tags, Tag, TagSize);

	return true;
}
