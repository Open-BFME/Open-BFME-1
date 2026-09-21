// ?findSkirmishTemplateSide@Rva000D1C30Owner@@QAE_NPAH@Z
// partial score=0.37 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
// present-unmatched
//
// GameLogic::updateLoadProgress (0x000DB020, matched) calls this 405-byte
// method through an unnamed thunk (0x00032952) on a Player-shaped object.
// The existing Player::findSkirmishSide row (0x000D1A90,
// Code/GameEngine/Source/Common/RTS/PlayerFindSkirmishSide.cpp) already owns
// different semantics at a different offset (this+0x1c), and no source
// declares a second method at this+0x28, so the owner stays address-derived
// rather than asserted as Player.
//
// The body scans TheSidesList (same 0x32c-byte header / stride-0x18 array
// PlayerFindSkirmishSide.cpp already proved), converts each side's
// presence-dict string to a NameKeyType, resolves a PlayerTemplate for that
// key, and compares the template's m_side (PlayerTemplate+8, proven by
// PlayerTemplate.cpp's PlayerTemplateView shim) against this+0x28 using the
// same inline StringBase compare PlayerFindSkirmishSide.cpp's
// BFMERetailAsciiString::compare() already proved. On a match it writes the
// index and returns true; an empty table or no match returns false.
//
// callees, in body order (all already matched/pinned):
//   ??0GameSpyGroupRoom@@QAE@ABV0@@Z / ??0BFMERetailAsciiString@@QAE@ABV0@@Z
//     -> 0x00887B60 (StringBase<char> copy ctor; builds the local compare
//     copy of this+0x28)
//   ?fetch@GenKey@@QAEHXZ -> 0x00009304 (address-derived lazy key fetch,
//     ILT to ?key@StaticNameKey@@QBE?AW4NameKeyType@@XZ @ 0x00090290)
//   ?getAsciiString@BfmeStringPresenceDict@@QBE?AVBfmeStringPresenceValue@@HPA_N@Z
//     -> 0x0002FF6D (ILT to Dict::getAsciiString @ 0x00068580)
//   ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z -> 0x0003ADD7
//     (ILT to the real body @ 0x0008FFC0)
//   ?findPlayerTemplate@PlayerTemplateStore@@QBEPBVPlayerTemplate@@W4NameKeyType@@@Z
//     -> ILT 0x0002CD8B -> 0x000E0F30 (matched, 996B)
//   ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ -> 0x00887940 (x4)
//
// globals: TheSidesList (same global PlayerFindSkirmishSide.cpp uses; VA
// 0x012EF428 in this image), TheNameKeyGenerator (0x012ED600),
// ThePlayerTemplateStore (0x012ED750), and a second, distinct GenKey site
// (VA 0x0012A7938 -- NOT the 0x0012A7918 PlayerFindSkirmishSide.cpp reads,
// so a separate address-derived global).

#include <string.h>

#pragma intrinsic(memcmp)

typedef int Int;
typedef bool Bool;
enum NameKeyType { NAMEKEY_INVALID = 0 };

class BFMERetailAsciiString
{
private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;

public:
	BFMERetailAsciiString(const BFMERetailAsciiString &that);

	void releaseBuffer(void);

	const char *str() const { return m_data ? m_data->data : ""; }

	int compare(const BFMERetailAsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherData = other.m_data ? other.m_data->data : "";
		int thisLength = m_data ? m_data->length : 0;
		const char *thisData = m_data ? m_data->data : "";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	bool operator==(const BFMERetailAsciiString &other) const
	{
		return compare(other) == 0;
	}
};

class BfmeStringPresenceValue : public BFMERetailAsciiString
{
public:
	~BfmeStringPresenceValue(void)
	{
		reinterpret_cast<BFMERetailAsciiString *>(this)->releaseBuffer();
	}
};

class GenKey
{
public:
	int fetch(void);
};

class BfmeStringPresenceDict
{
private:
	char m_data[0x14];

public:
	BfmeStringPresenceValue getAsciiString(int key, bool *exists) const;
};

extern GenKey GenKey0012A7938;

struct BfmeSkirmishSide
{
	char m_prefix[4];
	BfmeStringPresenceDict m_dict;
};

class BfmeSidesList
{
public:
	char m_prefix[0x32c];
	int m_numSkirmishSides;
	BfmeSkirmishSide m_skirmishSides[1];

	BfmeSkirmishSide *getSkirmishSideInfo(int index)
	{
		if (index >= 0 && index < m_numSkirmishSides)
			return &m_skirmishSides[index];
		return 0;
	}
};

extern BfmeSidesList *TheSidesList;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
public:
	char m_pad00[8];
	BFMERetailAsciiString m_side;					///< retail this+0x08
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class Rva000D1C30Owner
{
public:
	Bool findSkirmishTemplateSide(int *index);

private:
	char m_prefix[0x28];
	BFMERetailAsciiString m_compareSide;				///< retail this+0x28
};

// address-derived: owner class unproven (see header comment above)
Bool Rva000D1C30Owner::findSkirmishTemplateSide(int *index)
{
	BFMERetailAsciiString compareSide(m_compareSide);

	int count = TheSidesList->m_numSkirmishSides;
	*index = 0;
	if (count <= 0)
	{
		compareSide.releaseBuffer();
		return false;
	}

	for (int i = 0; i < count; ++i)
	{
		BfmeStringPresenceValue sideName =
			TheSidesList->getSkirmishSideInfo(i)->m_dict.getAsciiString(
				GenKey0012A7938.fetch(), 0);

		NameKeyType key = TheNameKeyGenerator->nameToKey(sideName.str());
		const PlayerTemplate *tmpl = ThePlayerTemplateStore->findPlayerTemplate(key);

		if (tmpl != 0 && tmpl->m_side == compareSide)
		{
			*index = i;
			sideName.releaseBuffer();
			compareSide.releaseBuffer();
			return true;
		}

		sideName.releaseBuffer();
	}

	compareSide.releaseBuffer();
	return false;
}
