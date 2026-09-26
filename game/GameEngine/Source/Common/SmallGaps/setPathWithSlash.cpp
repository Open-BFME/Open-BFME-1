// ?setPathWithSlash@@YAXPBD@Z
extern "C" char* __cdecl strcpy(char*, const char*);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" char* __cdecl strcat(char*, const char*);
#pragma intrinsic(strcpy, strlen, strcat)
extern char Rva009C8600Path[];
void setPathWithSlash(const char* path)
{
	strcpy(Rva009C8600Path, path);
	int n = strlen(Rva009C8600Path);
	if (n > 0 && Rva009C8600Path[n - 1] != '\\' && Rva009C8600Path[n - 1] != '/')
		strcat(Rva009C8600Path, "\\");
}
