// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Iinputs/reference/shims/sweep

#include "PreRTS.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

bool Use_Non_Blocking_Mode(void)
{
	HKEY regKey;
	LONG regRetval;
	DWORD bufsiz = 0;
	DWORD type = 0;
	DWORD nonBlockingValue = 0;

	regRetval = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Westwood\\Earth And Beyond Beta 2", 0, KEY_READ, &regKey);
	if (regRetval != ERROR_SUCCESS)
		return true;

	bufsiz = sizeof(nonBlockingValue);
	type = REG_DWORD;
	regRetval = RegQueryValueEx(regKey, "UseNonBlockingFTP", 0, &type, (BYTE *)&nonBlockingValue, &bufsiz);

	RegCloseKey(regKey);

	if (regRetval != ERROR_SUCCESS || type != REG_DWORD)
		return true;

	return nonBlockingValue != 0;
}
