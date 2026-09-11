// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern bool getStringFromRegistry(HKEY root, std::string path,
	std::string key, std::string &val);

// ?GetStringFromRegistry@@YA_NV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@0AAV12@@Z
bool GetStringFromRegistry(std::string path, std::string key,
	std::string &val)
{
	std::string fullPath =
		"SOFTWARE\\Electronic Arts\\EA Games\\The Battle for Middle-earth";

	fullPath.append(path);
	if (getStringFromRegistry(HKEY_LOCAL_MACHINE,
		fullPath.c_str(), key.c_str(), val))
	{
		return true;
	}

	return getStringFromRegistry(HKEY_CURRENT_USER,
		fullPath.c_str(), key.c_str(), val);
}
