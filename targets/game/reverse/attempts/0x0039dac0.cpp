// ?appendNames@Rva0039DAC0Owner@@QAEXPAVBFMERetailAsciiString@@@Z
// partial score=0.4 date=2026-09-28
#include <string.h>
// cl: /DNDEBUG /MD /EHsc
//
// Address-derived at retail RVA 0x0039DAC0. Pool/index/bound idiom from landed
// AttributeHandleStandInDestructor.cpp (index at this+0, pool at 0x012F1000,
// 0x88 stride via magic 0x78787879); string text idiom from BfmeConv1589.cpp
// (empty fallback, length at data+4, text at data+8); record has the string at
// +0x20; vectors at +0x18/+0x30; kind mask at +0x48; names from g_bfmeTableEJ.

template <typename T>
class StringBase
{
public:
	void concat(const T *text, int length);
};

extern char Rva006A16B0Empty[];

class BFMERetailAsciiString
{
public:
	void concat(const char *text, int length)
	{
		((StringBase<char> *)this)->concat(text, length);
	}

	void *m_data;
};

struct Rva0039DAC0Record
{
	char m_pad[0x20];
	BFMERetailAsciiString m_name;		// +0x20
};

struct Rva0039DAC0Entry
{
	char m_pad00[0x18];
	Rva0039DAC0Record **m_firstStart;	// +0x18
	Rva0039DAC0Record **m_firstFinish;	// +0x1C
	char m_pad20[0x10];
	Rva0039DAC0Record **m_secondStart;	// +0x30
	Rva0039DAC0Record **m_secondFinish;	// +0x34
	char m_pad38[0x10];
	unsigned int m_kindMask[6];		// +0x48
	char m_pad60[0x24];			// +0x60
	int m_useCount;				// +0x84
};

struct Rva0039DAC0Pool
{
	Rva0039DAC0Entry *m_start;		// +0x00
	Rva0039DAC0Entry *m_finish;		// +0x04
};

extern Rva0039DAC0Pool TheBfmeAttributePool;	// 0x012F1000
extern const char *g_bfmeTableEJ[];		// 0x012AA068

class Rva0039DAC0Owner
{
public:
	void appendNames(BFMERetailAsciiString *out);

private:
	int m_handle;				// +0x00
};

// ?appendNames@Rva0039DAC0Owner@@QAEXPAVBFMERetailAsciiString@@@Z
void Rva0039DAC0Owner::appendNames(BFMERetailAsciiString *out)
{
	if (m_handle >= TheBfmeAttributePool.m_finish - TheBfmeAttributePool.m_start)
		return;
	if (m_handle == -1)
		return;

	Rva0039DAC0Entry *entry = &TheBfmeAttributePool.m_start[m_handle];

	for (Rva0039DAC0Record **it = entry->m_firstStart; it != entry->m_firstFinish; ++it)
	{
		char *data = (char *)(*it)->m_name.m_data;
		int length = data != 0 ? *(unsigned short *)(data + 4) : 0;
		const char *text = data != 0 ? data + 8 : Rva006A16B0Empty;
		out->concat(text, length);
	}

	for (Rva0039DAC0Record **it = entry->m_secondStart; it != entry->m_secondFinish; ++it)
	{
		char *data = (char *)(*it)->m_name.m_data;
		int length = data != 0 ? *(unsigned short *)(data + 4) : 0;
		const char *text = data != 0 ? data + 8 : Rva006A16B0Empty;
		out->concat(text, length);
	}

	for (int kind = 0; kind < 181; ++kind)
	{
		if ((entry->m_kindMask[kind >> 5] & (1 << (kind & 31))) != 0)
		{
			const char *name = g_bfmeTableEJ[kind];
			if (name != 0)
			{
				const char *end = name;
				while (*end != 0)
					++end;
				out->concat(name, (int)(end - name));
			}
		}
	}
}
