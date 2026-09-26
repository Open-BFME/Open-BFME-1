// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX
// readable body of ?canAffordBuild@Player@@QBE_NPBVThingTemplate@@@Z: game/GameEngine/Source/Common/RTS/Player.cpp

// The two questions a Player answers about what production costs it:
//
//   0x000C99D0  canAffordBuild                   26 bytes
//   0x000D47F0  getProductionCostChangePercent   91 bytes
//
// One compares a template's build cost against the money at Player+0x4C, the
// other looks a name up in the per-name cost-change map at Player+0x1CC. They
// sat in two files that each named one of those two fields and spelled the
// other as nothing, so no file said the two live in the same object.
//
// The map at +0x1CC is keyed on the name key rather than the string. find
// returns its iterator by value, so it comes back through a hidden pointer the
// callee pops alongside the key reference -- eight bytes in total -- which is
// why the iterator shim needs a declared copy constructor to stay out of a
// register. A miss compares equal to the map's header node and yields 0.
//
// The row for getProductionCostChangePercent had had the parameter as
// AsciiString by value. It is a const reference: the body loads [esp+8] and
// then dereferences it before touching the string data. Both forms occupy one
// stack slot, so ret 4 agrees with either and the arity screen cannot see the
// difference -- only the extra indirection shows it.
//
// The cost-map file built with /DNDEBUG /MD /EHs-c-; it byte-verifies
// unchanged under canAffordBuild's flags (/GX being the old spelling of
// /EHsc), which is what let the two share a TU.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	const char *str(void) const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) : "";
	}

private:
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	UnsignedInt m_money;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	int calcCostToBuild(const Player *player, int buildIndex) const;
};

// Address-derived name: 0x0003ADD7 is ICF-folded and already pinned under
// findMemoryPool and concat among others, none of which is what it does here --
// it turns characters into the key this map is indexed by.
class NameKeyGeneratorShim
{
public:
	Int unidentified_0003ADD7(const char *name);	///< ILT thunk at 0x0003ADD7
};

extern NameKeyGeneratorShim *TheNameKeyGeneratorShim;	///< retail [0x012ED600]

struct CostMapNodeShim
{
	unsigned char m_unreconstructed_00[0x14];
	Real m_value;									///< retail node+0x14
};

struct CostMapIteratorShim
{
	CostMapIteratorShim(const CostMapIteratorShim &other);	///< forces the hidden-pointer return
	CostMapNodeShim *m_node;
};

struct CostMapShim
{
	CostMapNodeShim *m_header;						///< doubles as the end sentinel
	CostMapIteratorShim find(const Int &key);		///< ILT thunk at 0x0001D980
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool canAffordBuild(const ThingTemplate *whatToBuild) const;
	Real getProductionCostChangePercent(const AsciiString &name) const;

private:
	unsigned char m_beforeMoney[0x4C];
	Money m_money;								///< retail this+0x4C
	unsigned char m_beforeCostMap[0x1CC - 0x50];
	CostMapShim m_costMap;							///< retail this+0x1CC
};

// ?canAffordBuild@Player@@QBE_NPBVThingTemplate@@@Z
Bool Player::canAffordBuild(const ThingTemplate *whatToBuild) const
{
	UnsignedInt money = m_money.m_money;
	if (whatToBuild->calcCostToBuild(this, -1) <= money)
	{
		return true;
	}
	return false;
}

// ?getProductionCostChangePercent@Player@@QBEMABVAsciiString@@@Z
Real Player::getProductionCostChangePercent(const AsciiString &name) const
{
	Int key = TheNameKeyGeneratorShim->unidentified_0003ADD7(name.str());

	CostMapShim *map = (CostMapShim *)&m_costMap;
	CostMapIteratorShim it = map->find(key);
	// Written so the hit is the fall-through: retail branches away on a miss,
	// and testing for equality instead puts the 0 first and inverts the jump.
	if (it.m_node != map->m_header)
	{
		return it.m_node->m_value;
	}
	return 0.0f;
}
