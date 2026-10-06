// cl: /DNDEBUG /MD /EHsc
#include <string.h>
#include "Rva0093DD20Copy.h"

void __cdecl Rva0093DD20Copy(unsigned char *destination,
	const unsigned char *source)
{
	if (destination != 0)
	{
		unsigned short key;
		memcpy(&key, source, sizeof(key));
		memcpy(destination, &key, sizeof(key));
		unsigned int value;
		memcpy(&value, source + 4, sizeof(value));
		memcpy(destination + 4, &value, sizeof(value));
	}
}
