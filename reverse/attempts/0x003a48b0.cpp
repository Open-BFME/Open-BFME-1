// ?applyByName@Rva003A48B0Owner@@QAEXPBVAsciiString@@PAXH@Z
// partial score=0.7 date=2026-09-11
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc

extern const char Rva006A16B0Empty[];
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	char m_text[1];
};

class AsciiString
{
public:
	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? other.m_data->m_text : Rva006A16B0Empty;
		int selfLength = m_data ? m_data->m_length : 0;
		const char *selfText = m_data ? m_data->m_text : Rva006A16B0Empty;
		int result = memcmp(selfText, otherText,
			(unsigned int)(selfLength < otherLength ? selfLength : otherLength));
		return result ? result : selfLength - otherLength;
	}

	BfmeAsciiStringData *m_data;
};

class Rva003A48B0Entry
{
public:
	void applyValue(void *value);
	void applyMode3(void *, void *, void *, void *, int);
	void applyMode1(void *, int);
	void applyMode2(void *, int);

	char m_pad00[0xac];
	AsciiString m_name;
};

#pragma comment(linker, "/alternatename:?applyValue@Rva003A48B0Entry@@QAEXPAX@Z=?j_000079c3@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyMode3@Rva003A48B0Entry@@QAEXPAX000H@Z=?j_00017896@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyMode1@Rva003A48B0Entry@@QAEXPAXH@Z=?j_00024bea@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyMode2@Rva003A48B0Entry@@QAEXPAXH@Z=?j_00028835@@YAXXZ")

struct BfmeLivingWorldManagerA48
{
	char m_pad00[0x170];
	void *m_mode3a;
	void *m_mode3b;
	void *m_mode3c;
	void *m_mode3d;
	void *m_mode1;
	void *m_mode2;
};

extern BfmeLivingWorldManagerA48 *g_bfmeGameCW;

class Rva003A48B0Owner
{
public:
	void applyByName(const AsciiString *name, void *value, int mode);

	char m_pad00[0x48];
	Rva003A48B0Entry **m_begin;
	Rva003A48B0Entry **m_end;
};

void Rva003A48B0Owner::applyByName(
	const AsciiString *name, void *value, int mode)
{
	for (unsigned int i = 0; i < (unsigned int)(m_end - m_begin); ++i)
	{
		Rva003A48B0Entry *entry = m_begin[i];
		if (name->compare(entry->m_name) != 0)
			continue;

		entry->applyValue(value);
		if (mode == 3)
		{
			entry->applyMode3(g_bfmeGameCW->m_mode3a,
				g_bfmeGameCW->m_mode3b, g_bfmeGameCW->m_mode3c,
				g_bfmeGameCW->m_mode3d, 0);
		}
		else if (mode == 1)
		{
			entry->applyMode1(g_bfmeGameCW->m_mode1, 0);
		}
		else if (mode == 2)
		{
			entry->applyMode2(g_bfmeGameCW->m_mode2, 0);
		}
	}
}
