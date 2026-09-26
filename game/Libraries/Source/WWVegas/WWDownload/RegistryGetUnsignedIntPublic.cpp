// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <windows.h>

extern bool getUnsignedIntFromRegistry(HKEY root, std::string path,
	std::string key, unsigned int &val);

// ?GetUnsignedIntFromRegistry@@YA_NV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@0AAI@Z
bool GetUnsignedIntFromRegistry(std::string path, std::string key,
	unsigned int &val)
{
	std::string fullPath =
		"SOFTWARE\\Electronic Arts\\EA Games\\The Battle for Middle-earth";

	fullPath.append(path);
	if (getUnsignedIntFromRegistry(HKEY_LOCAL_MACHINE,
		fullPath.c_str(), key.c_str(), val))
	{
		return true;
	}

	return getUnsignedIntFromRegistry(HKEY_CURRENT_USER,
		fullPath.c_str(), key.c_str(), val);
}
