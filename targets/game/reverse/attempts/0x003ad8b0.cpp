// ?j_0001eb9b@Glo012F1024Item@@QAEXXZ
// partial score=0.52 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /Oy /Ireference/shims/stringinline
// ?j_0001eb9b@Glo012F1024Item@@QAEXXZ
// Walks 0x30-byte records at +0x20 and dispatches addItem plus the
// living-world triple-string call. Getters stay out of line (ILT aliases)
// so the caller keeps the 32-byte accessor REL32s.

#include "StringInline.h"

struct Rva003C1C50Coord
{
	Rva003C1C50Coord(const Rva003C1C50Coord &);
	int x;
	int y;
};

class Rec003AD8B0
{
public:
	AsciiString getDesc(void);
	AsciiString getAscii(void);
	AsciiString getLabel(void);
	AsciiString getSecond(void);
	AsciiString getName(void);
	Rva003C1C50Coord getCoord(void);
	AsciiString get0C(void);
	AsciiString get1C(void);

	char m_pad00[0x18];
	unsigned char m_flag;		// +0x18
	unsigned char m_enabled;	// +0x19
	char m_pad1A[0x12];
	unsigned char m_final;		// +0x2C
	char m_pad2D[0x03];
};

#pragma comment(linker, "/alternatename:?getDesc@Rec003AD8B0@@QAE?AVAsciiString@@XZ=?j_0000556f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getAscii@Rec003AD8B0@@QAE?AVAsciiString@@XZ=?j_000357c4@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLabel@Rec003AD8B0@@QAE?AVAsciiString@@XZ=?j_00022ead@@YAXXZ")
#pragma comment(linker, "/alternatename:?getSecond@Rec003AD8B0@@QAE?AVAsciiString@@XZ=?j_0002ce67@@YAXXZ")
#pragma comment(linker, "/alternatename:?getName@Rec003AD8B0@@QAE?AVAsciiString@@XZ=?j_00032029@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCoord@Rec003AD8B0@@QAE?AURva003C1C50Coord@@XZ=?j_00048027@@YAXXZ")
#pragma comment(linker, "/alternatename:?get0C@Rec003AD8B0@@QAE?AVAsciiString@@XZ=?j_0001de99@@YAXXZ")
#pragma comment(linker, "/alternatename:?get1C@Rec003AD8B0@@QAE?AVAsciiString@@XZ=?j_0002c971@@YAXXZ")

class Glo012F1028Type
{
public:
	bool addItem(const AsciiString &name, const AsciiString &secondName,
		const Rva003C1C50Coord &coord, char flag, char enabled,
		const AsciiString &label, const AsciiString &ascii,
		const AsciiString &description, char finalFlag);
};

#pragma comment(linker, "/alternatename:?addItem@Glo012F1028Type@@QAE_NABVAsciiString@@0ABURva003C1C50Coord@@DD000D@Z=?j_0001c03a@@YAXXZ")

class Glo012F1024Type
{
public:
	void j_000493a5(const AsciiString &a, const AsciiString &b,
		const AsciiString &c);
};

#pragma comment(linker, "/alternatename:?j_000493a5@Glo012F1024Type@@QAEXABVAsciiString@@00@Z=?j_000493a5@@YAXXZ")

extern Glo012F1028Type *Glo012F1028;
extern Glo012F1024Type *TheLivingWorldCampaignManager;

class Rec003AD8B0Vector
{
public:
	unsigned int bfmeSize(void) const { return m_end - m_begin; }

	Rec003AD8B0 *m_begin;
	Rec003AD8B0 *m_end;
};

class Glo012F1024Item
{
public:
	void j_0001eb9b(void);

private:
	char m_head[0x20];
	Rec003AD8B0Vector m_recs;	// +0x20
};

void Glo012F1024Item::j_0001eb9b(void)
{
	for (unsigned int index = 0; index < m_recs.bfmeSize(); ++index)
	{
		Rec003AD8B0 *record = m_recs.m_begin + index;
		AsciiString description = record->getDesc();
		AsciiString ascii = record->getAscii();
		AsciiString label = record->getLabel();
		AsciiString second = record->getSecond();
		AsciiString name = record->getName();
		AsciiString *savedName = &name;
		char finalFlag = record->m_final;
		char enabled = record->m_enabled;
		char flag = record->m_flag;
		Glo012F1028->addItem(*savedName, second, record->getCoord(),
			flag, enabled, label, ascii, description, finalFlag);

		AsciiString extra0c = record->get0C();
		AsciiString nameAgain = record->getName();
		AsciiString extra1c = record->get1C();
		TheLivingWorldCampaignManager->j_000493a5(extra1c, nameAgain, extra0c);
	}
}
