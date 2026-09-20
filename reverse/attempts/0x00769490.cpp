// ?invoke@Rva00769490Owner@@QAEXPAURva00769490Arg1@@PAV?$_Rb_tree@PAURva0013FA60Target@@PAU1@U?$_Identity@PAURva0013FA60Target@@@_STL@@U?$less@PAURva0013FA60Target@@@3@V?$allocator@PAURva0013FA60Target@@@3@@_STL@@PBVAsciiString@@H@Z
// partial score=0.27 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: anonymous carved body at 0x00769490 (429 bytes). Caller and
// owning class are unproven (only reached through an ILT thunk from the
// 970-byte sibling at 0x007710F0, which shares the same room-loop/tree/
// broadcast shape at a larger scale -- also unlanded). Retail:
//   for each record in [this+0x2c, this+0x30) stride 0x38:
//     build key = "a*" + (arg3 string, if non-empty) + "."
//     combined = <record name at +8> + key            (StringBase<char> ops;
//         ??0GameSpyGroupRoom@@QAE@ABV0@@Z / ?concat@?$StringBase@D@@... /
//         ??H@YA?AVAsciiString@@V0@ABV0@@Z are ICF aliases of the same
//         StringBase<char> bodies -- see reverse/symbols.csv 0x00887B60 /
//         0x00887D60 / 0x0000FE52->0x000D1860)
//     text = combined.m_data ? combined.m_data+8 : bfmeGoEMEb(&EmptyLiteral)
//     if (tree->insert_unique((Key)text).second) arg1->+0x10 = 1
//   then broadcast (arg1,arg2) to:
//     this+0x44 (single target, if non-null) via the ICF-shared
//       BfmeShadowPart::bfmeSetSize broadcaster (0x00022D86 -> 0x00428250,
//       see Code/GameEngine/Source/GameClient/Shadow_setSize.cpp -- the real
//       bytes are a generic "for each list member call vtbl+0xc" walk, NOT
//       Shadow sizing; reused here for its shape only)
//     this+0x50 linked list, node+0x1c holds a BfmeShadowPartClient*,
//       called directly through vtable slot 3 (+0xc)
//     this+0x54..0x58 and this+0x60..0x64 contiguous arrays (stride 0x14),
//       element+0x10 holds a BfmeShadowPart*, broadcast through the same
//       ICF-shared helper
//
// Field offsets are proven from the disassembly; the class name, arg1/arg2/
// arg3 identities and the 4th (stack-popped, ret 0x10) parameter are not --
// the 4th slot is never read in the body (a dead incoming argument).

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

template<class T> class StringBase
{
public:
	StringBase(const T *s);
	StringBase(const StringBase &s);
	~StringBase();
	void concat(const T *s);
	void concat(const T *s, int n);
	void releaseBuffer();

	const T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
	AsciiString(const AsciiString &s) : StringBase<char>(s) {}
	~AsciiString() { releaseBuffer(); }
};

class GameSpyGroupRoom : public StringBase<char>
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &s) : StringBase<char>(s) {}
	~GameSpyGroupRoom() { releaseBuffer(); }
};

AsciiString operator+(AsciiString a, const AsciiString &b);

extern "C" void *bfmeGoEMEb(void *a);

class BfmeShadowPartClient
{
public:
	virtual void _bfme_slot0();
	virtual void _bfme_slot1();
	virtual void _bfme_slot2();
	virtual void bfmeSetSize(float width, float height);
};

class BfmeShadowPart
{
public:
	void bfmeSetSize(float width, float height);
};

struct Rva0013FA60Target;

typedef Rva0013FA60Target *Rva00769490Key;

typedef _STL::_Rb_tree<Rva00769490Key, Rva00769490Key,
	_STL::_Identity<Rva00769490Key>, _STL::less<Rva00769490Key>,
	_STL::allocator<Rva00769490Key> > Rva0013FA60Tree;

struct Rva00769490Arg1
{
	unsigned char m_pad[0x10];
	unsigned char m_flag;
};

struct Rva00769490ShadowNode
{
	Rva00769490ShadowNode *m_next;
	unsigned char m_pad[0x14];
	BfmeShadowPartClient *m_client;
};

struct Rva00769490SlotRecord
{
	unsigned char m_pad[0x10];
	BfmeShadowPart *m_part;
};

struct Rva00769490Room
{
	unsigned char m_pad[8];
	GameSpyGroupRoom m_name;
	unsigned char m_tail[0x38 - 0xc];
};

class Rva00769490Owner
{
public:
	void invoke(Rva00769490Arg1 *arg1, Rva0013FA60Tree *arg2,
		const AsciiString *arg3, int arg4);

private:
	unsigned char m_pad0[0x2c];
	Rva00769490Room *m_roomBegin;
	Rva00769490Room *m_roomEnd;
	unsigned char m_pad1[0x44 - 0x34];
	BfmeShadowPart *m_broadcastTarget;
	unsigned char m_pad2[0x50 - 0x48];
	Rva00769490ShadowNode *m_sentinel;
	Rva00769490SlotRecord *m_slotsABegin;
	Rva00769490SlotRecord *m_slotsAEnd;
	unsigned char m_pad3[0x60 - 0x5c];
	Rva00769490SlotRecord *m_slotsBBegin;
	Rva00769490SlotRecord *m_slotsBEnd;
};

void Rva00769490Owner::invoke(Rva00769490Arg1 *arg1, Rva0013FA60Tree *arg2,
	const AsciiString *arg3, int /*arg4*/)
{
	for (Rva00769490Room *room = m_roomBegin; room != m_roomEnd; ++room)
	{
		AsciiString key("a*");

		if (arg3->m_data)
		{
			unsigned short len = *(const unsigned short *)(arg3->m_data + 4);
			if (len)
				key.concat(arg3->m_data + 8, (int)(unsigned int)len);
		}
		key.concat(".");

		GameSpyGroupRoom nameCopy(room->m_name);
		AsciiString combined = operator+(*(AsciiString *)&nameCopy, key);

		const char *text = combined.m_data
			? combined.m_data + 8
			: (const char *)bfmeGoEMEb((void *)0x0107388Bu);

		if (arg2->insert_unique((Rva00769490Key)text).second)
			arg1->m_flag = 1;
	}

	if (m_broadcastTarget)
		m_broadcastTarget->bfmeSetSize(*(float *)&arg1, *(float *)&arg2);

	for (Rva00769490ShadowNode *node = m_sentinel->m_next; node != m_sentinel;
		node = node->m_next)
	{
		BfmeShadowPartClient *client = node->m_client;
		if (client)
			client->bfmeSetSize(*(float *)&arg1, *(float *)&arg2);
	}

	for (Rva00769490SlotRecord *slot = m_slotsABegin; slot != m_slotsAEnd;
		++slot)
	{
		BfmeShadowPart *part = slot->m_part;
		if (part)
			part->bfmeSetSize(*(float *)&arg1, *(float *)&arg2);
	}

	for (Rva00769490SlotRecord *slot = m_slotsBBegin; slot != m_slotsBEnd;
		++slot)
	{
		BfmeShadowPart *part = slot->m_part;
		if (part)
			part->bfmeSetSize(*(float *)&arg1, *(float *)&arg2);
	}
}
