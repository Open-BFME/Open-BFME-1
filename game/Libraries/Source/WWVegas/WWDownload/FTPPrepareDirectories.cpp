// cl: /DNDEBUG /MD /EHs-c-
// WWDownload FTP.CPP Prepare_Directories body.

extern "C" __declspec(dllimport) char *__cdecl strchr(const char *, int);
extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *, const char *, unsigned int);
extern "C" void *__cdecl memset(void *, int, unsigned int);
extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *, const char *, ...);
extern "C" __declspec(dllimport) int __stdcall CreateDirectoryA(
	const char *, void *);

bool Prepare_Directories(const char *rootdir, const char *filename)
{
	char tempstr[256];
	char newdir[256];

	const char *cptr = filename;
	while (cptr = strchr(cptr, '\\'))
	{
		memset(tempstr, 0, 256);
		strncpy(tempstr, filename, cptr - filename);
		sprintf(newdir, "%s\\%s", rootdir, tempstr);
		if (!CreateDirectoryA(newdir, 0))
			return false;
		cptr++;
	}
	return true;
}
