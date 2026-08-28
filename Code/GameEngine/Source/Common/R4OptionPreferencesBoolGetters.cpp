// cl: /DNDEBUG /MD /EHs-c-
// Thirteen OptionPreferences boolean getters, all one skeleton:
//
//     Bool OptionPreferences::getX(void)
//     {
//         it = find("<KEY>");
//         if (it == end())  return TheGlobalData-><byte at OFFSET>;
//         return <compare>(it->second.str(), "yes") == 0;
//     }
//
// This is the shape already landed for getLanguageFilter at 0x00091B40; these
// thirteen are its siblings, and the KEY STRING NAMES EACH ONE.  The key is
// pushed as a literal into a four-byte local built by an explicit init call and
// torn down by an explicit destroy call, because retail reserves exactly four
// bytes with `push ecx` and a real AsciiString destructor would want an unwind
// frame these functions do not have.  The map pointer is formed AFTER the key is
// built -- retail keeps plain `this` in esi across the constructor and only then
// does `add esi,4` -- and `it == end()` is the compare against the dword at the
// map's offset 0, its header node.  Every exit is a single byte: the miss path
// reads one byte out of the global at 0x012ED5C8 and the hit path ends in a
// set-on-equal, so the return type is Bool and nothing here touches the FPU.
//
// THE FAMILY SPLITS ON WHICH COMPARE THE SOURCE CALLED, and the split is not
// cosmetic.  Six rows compare with `strcmp`, which MSVC expands INLINE to a
// four-byte `repe cmpsb` (terminator included) ending `sete al` -- 101 bytes.
// Seven compare case-insensitively, which is not an intrinsic, so they end in
// `ff 15` through the import slot at 0x0135933C -- already identified in the
// ledger as `_strcmpi` -- followed by `neg/sbb/inc`, the compiler's way of
// spelling `== 0` on a value it did not produce: 102 bytes.  The extra byte is
// the indirect call form, which is why the declaration below carries
// `__declspec(dllimport)`: without it the call assembles as a direct REL32 and
// the body is one byte short.
//
// TWO AXES BESIDES THE COMPARE: the key literal and the byte offset into the
// global, and every row has its own pair.  The offsets fall in two clusters --
// 0x1B to 0x8C for the case-insensitive rows and 0xA75 to 0xC09 for the strcmp
// rows -- which is consistent with two different regions of the global being
// read by two different groups of settings, and is noted rather than relied on.
//
// The map, node and string shims reuse the names an earlier CustomMatchPreferences
// conversion pinned rather than restating the _Rb_tree and StringBase template
// names.  The global is a DIR32 operand and costs no pin, so only the byte it
// reads is modelled and its structure is not asserted.

typedef unsigned char Bool;   ///< a byte, not bool: retail never zero-extends the result

extern "C" int __cdecl strcmp( const char *a, const char *b );
extern "C" __declspec( dllimport ) int __cdecl _strcmpi( const char *a, const char *b );

struct CustomAsciiStringShim
{
	void *m_data;
	void init( const char *s );                     ///< body at 0x00888BC0
	void destroy( void );                           ///< body at 0x00887940
};

struct CustomStringDataShim
{
	unsigned char m_header[ 8 ];                    ///< characters follow at +8
};

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[ 0x14 ];
	CustomStringDataShim *m_value;                  ///< retail node+0x14
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;                    ///< doubles as the end sentinel
	CustomMapNodeShim *find( CustomAsciiStringShim *key );   ///< ILT thunk at 0x0000AEAC
};

// Only the single byte each getter reads is reconstructed; no field layout is
// asserted, because nothing outside these bodies attests one.
struct R4GlobalDataShim { unsigned char m_bytes[ 0x1000 ]; };
extern R4GlobalDataShim *TheGlobalData;             ///< retail [0x012ED5C8]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	Bool getAnisotropicTextureFiltering( void );
	Bool getTerrainLighting( void );
	Bool getSmoothWaterBorder( void );
	Bool getUseHighQualityVideo( void );
	Bool get3DShadows( void );
	Bool get2DShadows( void );
	Bool getGrassDrawSkip( void );
	Bool getTurnOffMessengerInGame( void );
	Bool getDoubleClickGuard( void );
	Bool getAllHealthBars( void );
	Bool getUnitDecals( void );
	Bool getRefreshNet( void );
	Bool getDisplayForeignLanguage( void );
};

#define R4_PREF_BODY( GETTER, KEY, OFFSET, COMPARE )                          \
	Bool OptionPreferences::GETTER( void )                                    \
	{                                                                         \
		CustomAsciiStringShim key;                                            \
		key.init( KEY );                                                      \
		CustomPreferenceMapShim *map =                                        \
			(CustomPreferenceMapShim *)( (unsigned char *)this + 4 );          \
		CustomMapNodeShim *node = map->find( &key );                          \
		key.destroy();                                                        \
		if ( node == map->m_header )                                          \
			return TheGlobalData->m_bytes[ OFFSET ];                          \
		CustomStringDataShim *data = node->m_value;                           \
		const char *text = data ? (const char *)( (unsigned char *)data + 8 ) : ""; \
		return COMPARE( text, "yes" ) == 0;                                   \
	}

// 102 bytes -- case-insensitive compare through the import slot.
R4_PREF_BODY( getAnisotropicTextureFiltering, "AnisotropicTextureFiltering", 0x47, _strcmpi )
R4_PREF_BODY( getTerrainLighting,             "TerrainLighting",             0x44, _strcmpi )
R4_PREF_BODY( getSmoothWaterBorder,           "SmoothWaterBorder",           0x8C, _strcmpi )
R4_PREF_BODY( getUseHighQualityVideo,         "UseHighQualityVideo",         0x1F, _strcmpi )
R4_PREF_BODY( get3DShadows,                   "3DShadows",                   0x64, _strcmpi )
R4_PREF_BODY( get2DShadows,                   "2DShadows",                   0x65, _strcmpi )
R4_PREF_BODY( getGrassDrawSkip,               "GrassDrawSkip",               0x1B, _strcmpi )

// 101 bytes -- strcmp, expanded inline to a four-byte repe cmpsb.
R4_PREF_BODY( getTurnOffMessengerInGame,      "TurnOffMessengerInGame",      0xC05, strcmp )
R4_PREF_BODY( getDoubleClickGuard,            "DoubleClickGuard",            0xC06, strcmp )
R4_PREF_BODY( getAllHealthBars,               "AllHealthBars",               0xA8E, strcmp )
R4_PREF_BODY( getUnitDecals,                  "UnitDecals",                  0xA75, strcmp )
R4_PREF_BODY( getRefreshNet,                  "RefreshNet",                  0xC08, strcmp )
R4_PREF_BODY( getDisplayForeignLanguage,      "DisplayForeignLanguage",      0xC09, strcmp )
