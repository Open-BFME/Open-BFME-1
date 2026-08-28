// cl: /DNDEBUG /MD /EHs-c-
// Lift Player::getProductionCostChangePercent to clean C++.
//
// The row had the parameter as AsciiString by value. It is a const reference:
// the body loads [esp+8] and then dereferences it before touching the string
// data. Both forms occupy one stack slot, so ret 4 agrees with either and the
// arity screen cannot see the difference -- only the extra indirection shows it.
//
// str() is the usual inline: the characters live at data+8, or the empty literal
// when there is no data, and the address is computed before the null test
// because both arms need it.
//
// The map at this+0x1CC is keyed on the name key rather than the string. find
// returns its iterator by value, so it comes back through a hidden pointer the
// callee pops alongside the key reference -- eight bytes in total -- which is
// why the iterator shim needs a declared copy constructor to stay out of a
// register. A miss compares equal to the map's header node and yields 0.

typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Real getProductionCostChangePercent(const AsciiString &name) const;
};

// ?getProductionCostChangePercent@Player@@QBEMABVAsciiString@@@Z
Real Player::getProductionCostChangePercent(const AsciiString &name) const
{
	Int key = TheNameKeyGeneratorShim->unidentified_0003ADD7(name.str());

	CostMapShim *map = (CostMapShim *)((unsigned char *)this + 0x1CC);
	CostMapIteratorShim it = map->find(key);
	// Written so the hit is the fall-through: retail branches away on a miss,
	// and testing for equality instead puts the 0 first and inverts the jump.
	if (it.m_node != map->m_header)
	{
		return it.m_node->m_value;
	}
	return 0.0f;
}
