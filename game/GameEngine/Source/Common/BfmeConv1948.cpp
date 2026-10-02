#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class HAnimClass;

HAnimClass *Get_HAnim(const char *name);

extern const char g_bfmeEmptyAscii[];

struct BfmeStrDataERC
{
	int m_bfmeRefERC;
	unsigned short m_bfmeLenERC;
	unsigned short m_bfmePadERC;
	char m_bfmeTextERC[1];
};

class BfmeStrERC
{
public:
	const char *bfmeTextERC() const
	{
		return m_bfmeDataERC ? m_bfmeDataERC->m_bfmeTextERC : g_bfmeEmptyAscii;
	}

	int bfmeLenERC() const
	{
		return m_bfmeDataERC ? m_bfmeDataERC->m_bfmeLenERC : 0;
	}

	BfmeStrDataERC *m_bfmeDataERC;
};

void __stdcall bfmeAnimERC(BfmeStrERC *name, void *owner, HAnimClass **out)
{
	if (owner == 0)
		return;

	AsciiString full = *(const AsciiString *)name;

	full.StringBase<char>::concat(".", 1);
	full.StringBase<char>::concat(name->bfmeTextERC(), name->bfmeLenERC());

	*out = Get_HAnim(((const BfmeStrERC *)&full)->bfmeTextERC());
}
