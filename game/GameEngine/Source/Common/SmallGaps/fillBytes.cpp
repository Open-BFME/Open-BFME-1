// ?fillBytes@@YAPAXPAXHI@Z
#include <string.h>
#pragma intrinsic(memset)
void* fillBytes(void* dst, int value, unsigned int count)
{
	return memset(dst, value, count);
}
