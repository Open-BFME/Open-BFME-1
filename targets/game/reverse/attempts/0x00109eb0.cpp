// ?GetRegistryUseLocalUserMaps@@YA_NXZ
// partial score=0.96 date=2026-09-04
// ?GetRegistryUseLocalUserMaps@@YA_NXZ
// Started from reverse/attempts/0x00109eb0.cpp; first probe lever: guard assignment shape.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_downloadmanager /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

bool GetUnsignedIntFromRegistry(AsciiString path, AsciiString key, unsigned int &val);

bool GetRegistryUseLocalUserMaps(void)
{
	static int value = -1;
	if (value < 0)
	{
		unsigned int registryValue;
		value = GetUnsignedIntFromRegistry("", "UseLocalUserMaps", registryValue)
			? registryValue
			: 1;
	}

	return value != 0;
}
