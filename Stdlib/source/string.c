#include <Stdlib/string.h>
#include <Stdlib/memutil.h>
#include <stdarg.h>

size_t StringGetLength(String String)
{
	size_t Count = 0;
	
	while (String[++Count] != '\0');
	
	return Count;
}

void StringCopy(String SourceString, void* Destination)
{
	MemoryCopy((void*)SourceString, Destination, StringGetLength(SourceString) + 1); 
}

int StringEqual(String String1, String String2)
{
	size_t Length1 = StringGetLength(String1);
	size_t Length2 = StringGetLength(String2);
	
	if (Length1 == Length2)
	{
		for (size_t i = 0; i < Length1; ++i)
		{
			if (String1[i] != String2[i])
				return 0;
		}
		
		return 1;
	}
	
	return 0;
}

String StringConcat(String String1, String String2)
{
	size_t Length1 = StringGetLength(String1);
	size_t Length2 = StringGetLength(String2);
	
	StringCopy(String2, String1 + Length1);
	String1[Length1 + Length2] = '\0';
	
	return String1;
}

String StringFormat(String Destination, String Pattern, ...)
{
	va_list Arguments;
	va_start(Arguments, Pattern);
	
	int PIndex = 0;
	int DIndex = 0;
	
	char NumberBuffer[30];
	
	while (Pattern[PIndex] != '\0')
	{
		if (Pattern[PIndex] == '%')
		{	
			String CurrentString = 0;
			++PIndex;
			
			if (Pattern[PIndex] == '%')
			{
				Destination[DIndex] = '%';
			}
			else
			{
				if (Pattern[PIndex] == 's')
				{
					CurrentString = va_arg(Arguments, char*);
				}
				else if (Pattern[PIndex] == 'u')
				{
					CurrentString = StringConvertUnsignedLong(NumberBuffer, (uint64_t)va_arg(Arguments, uint32_t));
				}
				else if (Pattern[PIndex] == 'i')
				{
					CurrentString = StringConvertLong(NumberBuffer, (int64_t)va_arg(Arguments, int32_t));
				}
				else if (Pattern[PIndex] == 'x')
				{
					CurrentString = StringConvertHex(NumberBuffer, va_arg(Arguments, uint64_t));		
				}
				else if (Pattern[PIndex] == 'X')
				{
					CurrentString = StringUpper(StringConvertHex(NumberBuffer, va_arg(Arguments, uint64_t)));		
				}
			
				StringCopy(CurrentString, Destination + DIndex);
				DIndex += StringGetLength(CurrentString) - 1;
			}
		}
		else
		{
			Destination[DIndex] = Pattern[PIndex];
		}
		
		++PIndex;
		++DIndex;
	}
	
	va_end(Arguments);
	 
	return Destination;
}

String StringConvertLong(String Buffer, int64_t Value)
{
	char *p;
	int flg = 0;
	
	if( Value < 0 ) { flg++; Value = -Value; }
	
	p = StringConvertUnsignedLong(Buffer, Value);
	if(flg) *--p = '-';
	return p;
}

String StringConvertUnsignedLong(String Buffer, uint64_t Value)
{
	char *p;
		 
	p = Buffer+21;
	*--p = '\0';
		 
	do
	{
		*--p = '0' + Value%10;
		Value/=10;
	}
	while(Value);
	
	return p;
}

String StringConvertHex(String Buffer, int64_t Value)
{
	static char HEX[] = "0123456789abcdef";
	char *p;
		 
	p = Buffer+21;
	*--p = '\0';
	
	do
	{
		*--p = HEX[Value % 16];
		Value/=16;
	}
	while(Value);
	
	return p;
}

String StringUpper(String Buffer)
{
	int Index = 0;

	while (Buffer[Index] != '\0')
	{
		if (Buffer[Index] >= 97 && Buffer[Index] <= 122)
			Buffer[Index] = Buffer[Index] - 32;
	
		++Index;
	}
	
	return Buffer;
}

String StringLower(String Buffer)
{
	int Index = 0;

	while (Buffer[Index] != '\0')
	{
		if (Buffer[Index] >= 65 && Buffer[Index] <= 90)
			Buffer[Index] = Buffer[Index] + 32;
	
		++Index;
	}
	
	return Buffer;
}
