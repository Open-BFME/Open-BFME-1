// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) int __cdecl _strnicmp(
	const char *left,
	const char *right,
	unsigned int count);

// ?bfmeSkipLevelPrefix@@YAPBDPBD@Z
const char *__cdecl bfmeSkipLevelPrefix(const char *path)
{
	if (path == 0)
		return 0;

	if (_strnicmp(path, "_level", 6) == 0) {
		path += 6;
		while (*path != 0 && *path != '/' && *path != '.')
			++path;
		if (*path != 0)
			++path;
	}

	return path;
}
