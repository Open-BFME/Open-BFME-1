// Open-BFME5 conversions.

extern "C" unsigned int __cdecl strlen(const char *text);

extern "C" __declspec(dllimport) int __stdcall AIL_enumerate_3D_providers(int *next,
	int *provider, char **name);

class BfmeStrVSK
{
public:
	void bfmeSetVSK(const char *text, int length);
	char *m_bfme00;
};

struct BfmeProvVSK
{
	BfmeStrVSK m_bfme00;
	int m_bfme04;
	int m_bfme08;
};

class BfmeAudioVSK
{
public:
	void bfmeEnumVSK();
	char m_bfmePad000[0x654];
	BfmeProvVSK m_bfme654[0x40];
	int m_bfme954;
};

void BfmeAudioVSK::bfmeEnumVSK()
{
	int next;
	char *name;
	unsigned int count;
	BfmeProvVSK *entry;

	next = 0;
	entry = m_bfme654;

	for (count = 0; count < 0x40; ++count, ++entry)
	{
		int length;

		if (AIL_enumerate_3D_providers(&next, &entry->m_bfme04, &name) == 0)
			break;

		if (name != 0)
			length = strlen(name);
		else
			length = 0;

		entry->m_bfme00.bfmeSetVSK(name, length);
	}

	m_bfme954 = count;
}
