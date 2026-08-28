// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?getLastLadderAddr@CustomMatchPreferences@@QAE?AVAsciiString@@XZ: Code/GameEngine/Source/Common/UserPreferences.cpp
// Lift the CustomMatchPreferences::getLastLadderAddr __emit thunk to clean C++.
//
// Same preferences skeleton as getMaxDisconnects and getLanguageFilter: a plain
// shim key driven by explicit init/destroy rather than a C++ object with a
// destructor, the map at this+4, and the map's header node doubling as the end
// sentinel. The key is built before the map pointer is formed, because retail
// holds plain `this` in esi across the constructor and only then does
// `add esi,4`.
//
// This one returns AsciiString by value, so it carries a hidden return pointer
// and ends `ret 4`. Both exits copy-construct into that buffer: the empty string
// global on a miss, and the value at node+0x14 on a hit.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);			///< body at 0x00887B60
	~AsciiString();									///< body at 0x00887940

	static AsciiString TheEmptyString;				///< retail [0x01336E50]

private:
	void *m_data;
};

// Shim names an earlier CustomMatchPreferences conversion already pinned.
struct CustomAsciiStringShim
{
	void *m_data;
	void init(const char *s);						///< body at 0x00888BC0
	void destroy(void);								///< body at 0x00887940
};

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;							///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;					///< doubles as the end sentinel
	CustomMapNodeShim *find(CustomAsciiStringShim *key);	///< ILT thunk at 0x0000AEAC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/CustomMatchPreferences.h
class CustomMatchPreferences
{
public:
	AsciiString getLastLadderAddr(void);
};

// ?getLastLadderAddr@CustomMatchPreferences@@QAE?AVAsciiString@@XZ
AsciiString CustomMatchPreferences::getLastLadderAddr(void)
{
	// Zero-initialised: retail nulls the slot before constructing into it, which
	// the sibling getters that return a scalar do not do.
	CustomAsciiStringShim key = { 0 };
	key.init("LastLadderAddr");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((unsigned char *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return AsciiString::TheEmptyString;
	}

	return node->m_value;
}
