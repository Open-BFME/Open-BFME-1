// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This file is the BFME WWDownload registry-string primitive.  The matching
** source is the GeneralsMD WWDownload registry.cpp twin.
*/

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// ?getStringFromRegistry@@YA_NPAXV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@1AAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z
bool getStringFromRegistry(HKEY root, std::string path, std::string key,
	std::string &val)
{
	HKEY handle;
	unsigned char buffer[256];
	unsigned long size = 256;
	unsigned long type;
	int returnValue;

	if ((returnValue = RegOpenKeyEx(root, path.c_str(), 0, KEY_READ, &handle)) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueEx(handle, key.c_str(), NULL, &type,
			(unsigned char *)&buffer, &size);
		RegCloseKey(handle);
	}

	if (returnValue == ERROR_SUCCESS)
	{
		val = (char *)buffer;
		return true;
	}

	return false;
}
