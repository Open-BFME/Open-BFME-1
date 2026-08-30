// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) char * __cdecl strrchr(const char *text, int character);

// ?bfmePathLeafAfterMarker@@YAPBDPBD@Z
const char *__cdecl bfmePathLeafAfterMarker(const char *path)
{
	if (path == 0)
		return 0;

	const char *marker = strrchr(path, '~');
	if (marker != 0)
		return marker + 1;

	marker = strrchr(path, '/');
	if (marker != 0)
		return marker + 1;

	return path;
}
