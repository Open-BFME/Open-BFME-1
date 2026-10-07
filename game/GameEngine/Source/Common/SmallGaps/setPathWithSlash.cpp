// ?setPathWithSlash@@YAXPBD@Z
extern "C" char* __cdecl strcpy(char*, const char*);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" char* __cdecl strcat(char*, const char*);
#pragma intrinsic(strcpy, strlen, strcat)
// The 256-byte path prefix at retail VA 0x0134CB50 (.bss, up to
// TheArchiveFileSystem at 0x0134CC50); FileSystem_openFile.cpp reads it.
char byte_134CB50[256];
void setPathWithSlash(const char* path)
{
	strcpy(byte_134CB50, path);
	int n = strlen(byte_134CB50);
	if (n > 0 && byte_134CB50[n - 1] != '\\' && byte_134CB50[n - 1] != '/')
		strcat(byte_134CB50, "\\");
}
