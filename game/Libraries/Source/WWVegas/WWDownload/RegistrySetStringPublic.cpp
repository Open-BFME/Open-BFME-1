// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** BFME's public WWDownload registry wrapper, ported from the bundled
** GeneralsMD registry.cpp twin.  The product-name literal is BFME-specific.
*/

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern bool setStringInRegistry(HKEY root, std::string path,
	std::string key, std::string val);

// ?SetStringInRegistry@@YA_NV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@00@Z
bool SetStringInRegistry(std::string path, std::string key, std::string val)
{
	std::string fullPath =
		"SOFTWARE\\Electronic Arts\\EA Games\\The Battle for Middle-earth";
	fullPath.append(path);

	if (setStringInRegistry(HKEY_LOCAL_MACHINE, fullPath, key, val))
		return true;

	return setStringInRegistry(HKEY_CURRENT_USER, fullPath, key, val);
}
