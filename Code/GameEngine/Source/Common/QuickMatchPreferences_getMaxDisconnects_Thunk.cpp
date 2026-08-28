// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?getMaxDisconnects@QuickMatchPreferences@@QAEHXZ: Code/GameEngine/Source/Common/UserPreferences.cpp
// Lift the QuickMatchPreferences::getMaxDisconnects __emit thunk to clean C++.
//
// This body was filed as QuickMatchPreferences::getLastLadderPort returning
// UnsignedShort. Its own bytes refute that twice over: the key it looks up is
// "MaxDisconnects", and it returns atoi's result straight out of eax with no
// truncation, which a UnsignedShort return would have to narrow. Zero Hour
// declares Int QuickMatchPreferences::getMaxDisconnects(void) in
// QuickmatchPreferences.h, and the setter half, setMaxDisconnects, is already in
// the ledger keyed on the same string. Byte-verifying here is what proves it.
//
// The key is a plain shim object driven by explicit init/destroy calls rather
// than a C++ object with a destructor -- retail reserves exactly four bytes for
// it with `push ecx`, and a destructor would want an unwind frame this function
// does not have. Same reason the map pointer is formed after the key is built:
// retail holds plain `this` in esi across the constructor and only then does
// `add esi,4`.
//
// The map's header node doubles as the end sentinel. On a miss the answer is 0.
// On a hit the value's character data is read directly rather than copied, which
// is why this getter avoids the by-value AsciiString argument that blocks its
// siblings. A value with no data falls back to the empty literal, and the
// address of the characters is computed before the null test because both arms
// need it.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl atoi(const char *str);

// Reusing the shim names an earlier CustomMatchPreferences conversion already
// pinned rather than restating the _Rb_tree and StringBase template names.
struct CustomAsciiStringShim
{
	void *m_data;
	void init(const char *s);						///< body at 0x00888BC0
	void destroy(void);								///< body at 0x00887940
};

struct CustomStringDataShim
{
	unsigned char m_header[8];						///< characters follow at +8
};

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[0x14];
	CustomStringDataShim *m_value;					///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;					///< doubles as the end sentinel
	CustomMapNodeShim *find(CustomAsciiStringShim *key);	///< ILT thunk at 0x0000AEAC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/QuickmatchPreferences.h
class QuickMatchPreferences
{
public:
	Int getMaxDisconnects(void);
};

// ?getMaxDisconnects@QuickMatchPreferences@@QAEHXZ
Int QuickMatchPreferences::getMaxDisconnects(void)
{
	CustomAsciiStringShim key;
	key.init("MaxDisconnects");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((unsigned char *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return 0;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((unsigned char *)data + 8) : "";
	return atoi(text);
}
