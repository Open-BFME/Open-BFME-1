// ?j_000250d6@Glo012F1024Item@@QAEXXZ
// partial score=0.32 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /Oy /Ireference/shims/stringinline
// ?j_000250d6@Glo012F1024Item@@QAEXXZ
// Guarded 0x28-byte record walk at +0x14. Named by bfmeEnter calling
// j_000250d6. String temporaries are destroyed immediately after the
// empty-check, matching retail's nested-scope dtors.

#include "StringInline.h"

struct ICoord2D
{
	int x;
	int y;
};

struct Rva003BDA10Pair
{
	int first;
	int second;
};

class Rec003AD560
{
public:
	AsciiString getAt18(void);
	AsciiString getAt08(void);
	AsciiString getAt04(void);
	AsciiString getAt0C(void);
	ICoord2D *getCoord(ICoord2D *);

	char m_pad00[0x1C];
	unsigned char m_flag1C;	// +0x1C
	unsigned char m_flag1D;	// +0x1D
	char m_pad1E[0x02];
	Rva003BDA10Pair m_pair;	// +0x20
};

#pragma comment(linker, "/alternatename:?getAt18@Rec003AD560@@QAE?AVAsciiString@@XZ=?j_0001c792@@YAXXZ")
#pragma comment(linker, "/alternatename:?getAt08@Rec003AD560@@QAE?AVAsciiString@@XZ=?j_0002b3e6@@YAXXZ")
#pragma comment(linker, "/alternatename:?getAt04@Rec003AD560@@QAE?AVAsciiString@@XZ=?j_000279b7@@YAXXZ")
#pragma comment(linker, "/alternatename:?getAt0C@Rec003AD560@@QAE?AVAsciiString@@XZ=?j_0004959e@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCoord@Rec003AD560@@QAEPAUICoord2D@@PAU2@Z=?j_0003c3d0@@YAXXZ")

class Rec003AD560Vector
{
public:
	unsigned int bfmeSize(void) const { return m_end - m_begin; }

	Rec003AD560 *m_begin;
	Rec003AD560 *m_end;
};

class Glo012F1028Sub
{
};

class Glo012F1028Type
{
public:
	char m_head[0x28];
	Glo012F1028Sub *m_sub;
	void runInt(int value);
	void addPair(ICoord2D pair, const AsciiString *first, unsigned char flag,
		const AsciiString *second);
	void call36264(AsciiString *first, AsciiString *second, Rva003BDA10Pair *pair);
	void call1713E(Rva003BDA10Pair *pair, AsciiString *name, ICoord2D *pos);
};

#pragma comment(linker, "/alternatename:?runInt@Glo012F1028Type@@QAEXH@Z=?j_0003e531@@YAXXZ")
#pragma comment(linker, "/alternatename:?addPair@Glo012F1028Type@@QAEXUICoord2D@@PBVAsciiString@@E1@Z=?j_00033186@@YAXXZ")
#pragma comment(linker, "/alternatename:?call36264@Glo012F1028Type@@QAEXPAVAsciiString@@0PAURva003BDA10Pair@@@Z=?j_00036264@@YAXXZ")
#pragma comment(linker, "/alternatename:?call1713E@Glo012F1028Type@@QAEXPAURva003BDA10Pair@@PAVAsciiString@@PAUICoord2D@@@Z=?j_0001713e@@YAXXZ")

extern Glo012F1028Type *Glo012F1028;

static bool bfmeNonempty(const AsciiString &s)
{
	const char *data = *(const char **)&s;
	if (data == 0)
		return false;
	return *(const unsigned short *)(data + 4) != 0;
}

class Glo012F1024Item
{
public:
	void j_000250d6(void);

private:
	char m_head[0x14];
	Rec003AD560Vector m_recs;	// +0x14
};

void Glo012F1024Item::j_000250d6(void)
{
	Glo012F1028Type *global = Glo012F1028;
	if (global->m_sub == 0)
		return;

	for (unsigned int index = 0; index < m_recs.bfmeSize(); ++index)
	{
		Rec003AD560 *record = m_recs.m_begin + index;
		bool hasFirst;
		{
			AsciiString first = record->getAt18();
			hasFirst = bfmeNonempty(first);
		}
		if (hasFirst)
		{
			if (record->m_flag1D != 0)
			{
				AsciiString second = record->getAt08();
				global->runInt((int)&second);
			}
			else
			{
				AsciiString second = record->getAt08();
				char flag = record->m_flag1C;
				AsciiString again = record->getAt18();
				ICoord2D coord;
				global->addPair(*record->getCoord(&coord), &again, flag, &second);
			}
		}
		else
		{
			bool hasFallback;
			{
				AsciiString fallback = record->getAt04();
				hasFallback = bfmeNonempty(fallback);
			}
			if (hasFallback)
			{
				AsciiString name = record->getAt0C();
				AsciiString again = record->getAt04();
				global->call36264(&again, &name, &record->m_pair);
			}
			else
			{
				AsciiString name = record->getAt0C();
				ICoord2D pos;
				global->call1713E(&record->m_pair, &name, record->getCoord(&pos));
			}
		}
	}
}
