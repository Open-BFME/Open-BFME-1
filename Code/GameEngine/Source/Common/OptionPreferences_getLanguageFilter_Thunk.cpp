// cl: /DNDEBUG /MD /EHs-c-
// Lift the OptionPreferences language-filter getter to clean C++.
//
// This body was filed as OptionPreferences::getMusicVolume returning Real. Its
// own bytes refute that: the key it looks up is "LanguageFilter", the hit path
// compares the stored value against "yes" and ends in `sete al`, and the miss
// path returns a single byte read out of the global at 0x012ED5C8. Every exit is
// a Bool; nothing here touches the FPU. The name is taken from the key string
// rather than from a Zero Hour declaration.
//
// Same skeleton as getMaxDisconnects: the key is a plain shim object driven by
// explicit init/destroy calls, because retail reserves exactly four bytes for it
// with `push ecx` and a destructor would want an unwind frame this function does
// not have. The map pointer is formed after the key is built -- retail holds
// plain `this` in esi across the constructor and only then does `add esi,4`.
//
// The comparison is strcmp against a constant, which MSVC expands inline to a
// four-byte `repe cmpsb` -- the terminator included -- rather than calling out. Reading the characters
// directly instead of copying an AsciiString is what keeps this getter clear of
// the by-value blocker that gates its siblings.

typedef int Int;
typedef unsigned char Bool;   ///< a byte, not bool: retail never zero-extends the result

extern "C" int __cdecl strcmp(const char *a, const char *b);

// Reusing the shim names an earlier CustomMatchPreferences conversion pinned
// rather than restating the _Rb_tree and StringBase template names.
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

// Only the one byte this function reads is reconstructed; the offset is not
// attested anywhere but here.
struct GlobalDataShim
{
	unsigned char m_unreconstructed_00[0xC04];
	Bool m_languageFilterDefault;					///< retail global+0xC04
};

extern GlobalDataShim *TheGlobalData;				///< retail [0x012ED5C8]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	Bool getLanguageFilter(void);
};

// ?getLanguageFilter@OptionPreferences@@QAEEXZ
Bool OptionPreferences::getLanguageFilter(void)
{
	CustomAsciiStringShim key;
	key.init("LanguageFilter");

	CustomPreferenceMapShim *map =
		(CustomPreferenceMapShim *)((unsigned char *)this + 4);
	CustomMapNodeShim *node = map->find(&key);
	key.destroy();

	if (node == map->m_header)
	{
		return TheGlobalData->m_languageFilterDefault;
	}

	CustomStringDataShim *data = node->m_value;
	const char *text = data ? (const char *)((unsigned char *)data + 8) : "";
	return strcmp(text, "yes") == 0;
}
