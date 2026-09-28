// ?copyBytes@@YAPAXPAXPBXH@Z
#include <string.h>
#pragma intrinsic(memcpy)
void* copyBytes(void* dst, const void* src, int count)
{
	return memcpy(dst, src, count);
}
