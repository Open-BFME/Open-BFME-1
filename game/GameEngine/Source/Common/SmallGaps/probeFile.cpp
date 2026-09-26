// ?probeFile@@YAXPBDPAH@Z
__declspec(dllimport) void* __cdecl bfmeFopenVIF(const char* name, const char* mode);
__declspec(dllimport) void __cdecl bfmeFreeUXB(void* file);
void probeFile(const char* name, int* status)
{
	void* file = bfmeFopenVIF(name, "w");
	*status = (file != 0) ? 0 : 10;
	bfmeFreeUXB(file);
}
