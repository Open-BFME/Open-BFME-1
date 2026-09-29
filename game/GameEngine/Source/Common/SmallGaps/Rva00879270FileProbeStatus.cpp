// Retail 0x00879270 opens the path in update mode and reports status 0
// on success or 13 on failure. No caller proves a more specific identity.
__declspec(dllimport) void *__cdecl bfmeFopenVIF(const char *name,
	const char *mode);

void *Rva00879270FileProbeStatus(const char *name, int *status)
{
	void *file = bfmeFopenVIF(name, "w+");
	*status = (file != 0) ? 0 : 13;
	return file;
}
