// ?accepts@Rva0039F0A0@@QAE_NPBVThingTemplate@@PAVPlayer@@1@Z
// partial score=0.14 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/asciistring_outofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/AsciiString.h"

typedef unsigned int UnsignedInt;

extern char Rva006A16B0Empty[];
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct BfmeAsciiData
{
	UnsignedInt m_refCount;
	unsigned short m_length;
	unsigned short m_pad;
	char m_text[1];
};

__forceinline bool bfmeAsciiEqual(const AsciiString &left,
	const AsciiString &right)
{
	const BfmeAsciiData *leftData =
		*(const BfmeAsciiData *const *)&left;
	const BfmeAsciiData *rightData =
		*(const BfmeAsciiData *const *)&right;
	unsigned leftLength = leftData ? leftData->m_length : 0;
	unsigned rightLength = rightData ? rightData->m_length : 0;
	const char *leftText = leftData ? leftData->m_text : Rva006A16B0Empty;
	const char *rightText = rightData ? rightData->m_text : Rva006A16B0Empty;
	unsigned length = leftLength < rightLength ? leftLength : rightLength;
	if (memcmp(leftText, rightText, length) != 0)
		return false;
	return leftLength == rightLength;
}

class Team;

enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };

class Player
{
public:
	Relationship getRelationship(const Team *that) const;

	unsigned char m_unmodelled[0x230];
	Team *m_defaultTeam;
};

class Rva00132A20ThingMask
{
public:
	bool rva00132a20(const Rva00132A20ThingMask &that) const;

	UnsignedInt m_words[6];
};

template <int NUMBITS>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet,
		const BitFlags &mustBeClear) const;

	UnsignedInt m_words[6];
};

template <typename T>
struct BfmePtrVec
{
	T *m_begin;
	T *m_end;
	T *m_capacity;

	int size() const { return (int)(m_end - m_begin); }
};

struct BfmeAttributePlainBlock
{
	UnsignedInt m_values[6];
};

class BfmeCheckFH
{
public:
	char bfmeCheckFH(void *that);
};

class ThingTemplate : public BfmeCheckFH
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}

	const Rva00132A20ThingMask &getKindOf() const
	{
		return *(const Rva00132A20ThingMask *)((const char *)this + 0xc8);
	}

	const BitFlags<181> &getKindOfFlags() const
	{
		return *(const BitFlags<181> *)((const char *)this + 0xc8);
	}
};

class Gen00043699
{
public:
	Gen00043699();
	~Gen00043699();

	BfmePtrVec<ThingTemplate *> m_names;
	BfmePtrVec<ThingTemplate *> m_values;
	BfmePtrVec<ThingTemplate *> m_list0;
	BfmePtrVec<ThingTemplate *> m_list1;
	BfmePtrVec<ThingTemplate *> m_list2;
	BfmePtrVec<ThingTemplate *> m_list3;
	BfmeAttributePlainBlock m_firstPlain;
	BfmeAttributePlainBlock m_secondPlain;
	UnsignedInt m_kind;
	UnsignedInt m_index;
	bool m_enabled;
	unsigned char m_pad[3];
	UnsignedInt m_useCount;
};

struct BfmeAttributePool
{
	Gen00043699 *m_start;
	Gen00043699 *m_finish;
};

struct BfmeAttributeHandle
{
	UnsignedInt m_handle;
};

extern BfmeAttributePool TheBfmeAttributePool;
extern UnsignedInt bfmeInternAttributeEntry(Gen00043699 *entry);

extern const BitFlags<181> KINDOFMASK_NONE;

class Rva0039F0A0
{
public:
	bool accepts(const ThingTemplate *thing, Player *player, Player *observer);

private:
	UnsignedInt m_handle;
};

bool Rva0039F0A0::accepts(const ThingTemplate *thing, Player *player,
	Player *observer)
{
	if (thing != 0)
	{

	UnsignedInt handle = m_handle;
	int count = (int)(TheBfmeAttributePool.m_finish -
		TheBfmeAttributePool.m_start);
	if ((int)handle >= count)
		return false;

	if (handle == 0xffffffff)
	{
		Gen00043699 entry;
		m_handle = bfmeInternAttributeEntry(&entry);
	}

	Gen00043699 *entry = TheBfmeAttributePool.m_start + m_handle;
	if (entry->m_index != 0)
	{
		if (player != 0 && observer != 0)
		{
			Relationship relationship = observer->getRelationship(
				player->m_defaultTeam);
			if (relationship == ENEMIES && (entry->m_index & 1) == 0)
				return false;
			if (relationship == NEUTRAL && (entry->m_index & 4) == 0)
				return false;
			if (relationship == ALLIES && (entry->m_index & 2) == 0)
				return false;
		}
	}

	int list0Count = entry->m_list0.size();
	ThingTemplate **list0 = entry->m_list0.m_begin;
	for (int i = 0; i < list0Count; ++i)
	{
		if (thing->getName().compare(list0[i]->getName()) == 0)
			return true;
	}

	int list1Count = entry->m_list1.size();
	ThingTemplate **list1 = entry->m_list1.m_begin;
	for (int i = 0; i < list1Count; ++i)
	{
		if (bfmeAsciiEqual(list1[i]->getName(), thing->getName()))
			return false;
	}

	int list2Count = entry->m_list2.size();
	ThingTemplate **list2 = entry->m_list2.m_begin;
	for (int i = 0; i < list2Count; ++i)
	{
		if (const_cast<ThingTemplate *>(thing)->bfmeCheckFH(list2[i]))
			return true;
	}

	int list3Count = entry->m_list3.size();
	ThingTemplate **list3 = entry->m_list3.m_begin;
	for (int i = 0; i < list3Count; ++i)
	{
		if (const_cast<ThingTemplate *>(thing)->bfmeCheckFH(list3[i]))
			return false;
	}

	int secondPlainIndex = 0;
	for (; secondPlainIndex < 6; ++secondPlainIndex)
	{
		if (entry->m_secondPlain.m_values[secondPlainIndex] != 0)
			break;
	}
	if (secondPlainIndex < 6 && thing->getKindOf().rva00132a20(
		*(const Rva00132A20ThingMask *)&entry->m_secondPlain))
		return false;

	UnsignedInt mode = entry->m_kind;
	if (mode == 0)
	{
		entry->m_kind = 3;
		mode = 3;
	}
	if (mode == 2)
	{
		int firstPlainIndex = 0;
		for (; firstPlainIndex < 6; ++firstPlainIndex)
		{
			if (entry->m_firstPlain.m_values[firstPlainIndex] != 0)
				break;
		}
		if (firstPlainIndex < 6)
			return thing->getKindOf().rva00132a20(
				*(const Rva00132A20ThingMask *)&entry->m_firstPlain);
		return false;
	}
	if (mode == 1)
	{
		int firstPlainIndex = 0;
		for (; firstPlainIndex < 6; ++firstPlainIndex)
		{
			if (entry->m_firstPlain.m_values[firstPlainIndex] != 0)
				break;
		}
		if (firstPlainIndex < 6)
			return thing->getKindOfFlags().testSetAndClear(
				*(const BitFlags<181> *)&entry->m_firstPlain,
				KINDOFMASK_NONE);
		return false;
	}
	return mode == 3;
	}
	return false;
}
