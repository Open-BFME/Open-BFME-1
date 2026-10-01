// ?isPlayerAllowedCommon@CastleBehavior@@QAE_NPAVPlayer@@H@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef bool Bool;
typedef int Int;

extern const char Rva006A16B0Empty[];

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_pad00[0x28];
	AsciiString m_playerName;
};

typedef _STL::map<Int, Int> CastlePlayerKeyMap;

struct CastlePlayerKeyRange
{
	Int *m_begin;
	Int *m_end;
};

class CastleBehaviorModuleData
{
public:
	unsigned char m_pad00[0x0c];
	CastlePlayerKeyMap m_playerKeys;
	Bool m_hasSecondaryKeys;
	unsigned char m_pad1c[0x6c - 0x19];
	CastlePlayerKeyMap m_secondaryKeys;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
// NameKeyType is an enum, not a typedef of int: retail's mangled callee is
// ?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z (W4 = enum return).
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_00014a24(void);
extern void j_000196f0(void);

class CastleBehavior
{
public:
	Bool isPlayerAllowedCommon(Player *player, Int key);

private:
	void *m_vtable;
	CastleBehaviorModuleData *m_moduleData;
};

Bool CastleBehavior::isPlayerAllowedCommon(Player *player, Int key)
{
	CastleBehaviorModuleData *data = m_moduleData;
	Bool hasPrimaryKeys = false;
	if (data->m_playerKeys.size() > 0)
		hasPrimaryKeys = true;
	if (data->m_hasSecondaryKeys)
	{
		if (data->m_secondaryKeys.size() > 0)
			hasPrimaryKeys = true;
	}
	if (!hasPrimaryKeys)
		return false;

	Int playerKey = TheNameKeyGenerator->nameToKey(player->m_playerName.str());
	struct MapIteratorResult
	{
		void *m_node;
	};
	typedef void (CastlePlayerKeyMap::*MapFind)(MapIteratorResult *,
		const Int &);
	union { void *asVoid; MapFind asMember; } mapFind;
	mapFind.asVoid = (void *)j_00014a24;
	MapIteratorResult it;
	(data->m_playerKeys.*mapFind.asMember)(&it, playerKey);
	if (it.m_node != *(void **)&data->m_playerKeys)
	{
		CastlePlayerKeyRange *range =
			(CastlePlayerKeyRange *)((unsigned char *)it.m_node + 0x14);
		Int *value = range->m_begin;
		Int *end = range->m_end;
		while (value != end)
		{
			if (*value == key)
				return true;
			++value;
		}
	}

	if (data->m_hasSecondaryKeys)
	{
		mapFind.asVoid = (void *)j_000196f0;
		MapIteratorResult secondary;
		(data->m_secondaryKeys.*mapFind.asMember)(&secondary, playerKey);
		if (secondary.m_node != *(void **)&data->m_secondaryKeys)
			return true;
	}
	return false;
}
