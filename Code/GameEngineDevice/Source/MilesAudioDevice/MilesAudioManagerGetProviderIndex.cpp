// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// MilesAudioManager::getProviderIndex, ported from
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

class AsciiString
{
public:
	BfmeAsciiStringData *m_data;
	int compare(const AsciiString &other) const
	{
		const AsciiString *self = this;
		const AsciiString *that = &other;
		int thatLength = that->m_data ? that->m_data->length : 0;
		const char *thatText = that->m_data ? &that->m_data->data[0] : (const char *)"";
		int selfLength = self->m_data ? self->m_data->length : 0;
		const char *selfText = self->m_data ? &self->m_data->data[0] : (const char *)"";
		int count = selfLength < thatLength ? selfLength : thatLength;
		int result = memcmp(selfText, thatText, count);
		if (result != 0)
			return result;
		return selfLength - thatLength;
	}
};

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
		if (providerName.compare(m_provider3D[i].name) == 0)
			return i;
	}

	return 0xffffffff;
}
