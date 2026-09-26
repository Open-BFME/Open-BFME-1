// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x008845D0, 576 bytes: WWDownload registry.cpp counterpart.
// BFME-specific product path and the independently matched lower setter
// at 0x00883FB0 establish this wrapper; native STLport handles string EH.

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <windows.h>

extern bool setUnsignedIntInRegistry(HKEY root, std::string path,
	std::string key, unsigned int val);

// ?SetUnsignedIntInRegistry@@YA_NV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@0I@Z
bool SetUnsignedIntInRegistry(std::string path, std::string key,
	unsigned int val)
{
	std::string fullPath =
		"SOFTWARE\\Electronic Arts\\EA Games\\The Battle for Middle-earth";
	fullPath.append(path);

	if (setUnsignedIntInRegistry(HKEY_LOCAL_MACHINE, fullPath, key, val))
		return true;

	return setUnsignedIntInRegistry(HKEY_CURRENT_USER, fullPath, key, val);
}
