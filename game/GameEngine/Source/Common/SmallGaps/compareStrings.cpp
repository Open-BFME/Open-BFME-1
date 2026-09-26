// ?compareStrings@@YAHPBD0@Z
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)
int compareStrings(const char* a, const char* b)
{
	return strcmp(a, b);
}
