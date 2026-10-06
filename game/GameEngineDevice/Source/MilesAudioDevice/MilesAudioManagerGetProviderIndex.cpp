// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
// MilesAudioManager::getProviderIndex, ported from
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

#include "ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

struct ProviderInfo
{
	AsciiString name;
	unsigned int id;
	int isValid;
};

enum { MAXPROVIDERS = 64 };

class MilesAudioManager
{
public:
	virtual unsigned int getProviderIndex(const AsciiString &providerName) const;

private:
	char m_pad[0x650];
	ProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
};

unsigned int MilesAudioManager::getProviderIndex(const AsciiString &providerName) const
{
	for (unsigned int i = 0; i < m_providerCount; ++i) {
		if (providerName.StringBase<char>::compare(m_provider3D[i].name) == 0)
			return i;
	}

	return 0xffffffff;
}
