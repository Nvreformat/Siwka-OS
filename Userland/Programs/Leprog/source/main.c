#include <Siwka/graphics.h>

void* Main() 
{
	Graphics::PutString("SEEEEEEEEEEEEEEEEE", 0, 0, 0);
	
	int a = 78;
	int b = 0;
	
	for (int I = 0; I < 100000000; I++)
	{
		a = a * b;	
	}
	
	return 0;
}