// cl: /DNDEBUG /MD /EHsc
// Open-BFME: TerrainRoadType::friend_setDamageToFXString (92B at 0x00601B50)
// and TerrainRoadType::friend_setRepairedToFXString (91B at 0x00601CC0).
//
// Both are one-line inlines in the reference's header, emitted out of line
// here because the INI parse table reaches them through a pointer. Each takes
// the AsciiString by value, so the assignment is StringBase<char>::set and the
// epilogue destroys the parameter through releaseBuffer -- the callee's job in
// MSVC 7.1 -- under the /EHsc frame that pairing needs.
//
// The two index computations are what fix the layout. The damage body forms
// index*4 + state*12 and adds 0xA4; the repaired body adds 0x17 to the state
// first, which is the same expression 0x114 bytes further along. That distance
// is 28 AsciiStrings, exactly m_damageToFXString plus m_repairedToSoundString
// plus m_repairedToOCLString with BODYDAMAGETYPE_COUNT at 4 and
// MAX_BRIDGE_BODY_FX at 3, so BFME kept both counts and the reference's member
// order.
//
// The reference's own order puts m_damageToFXString at 0xA0, not 0xA4. The
// four missing bytes sit ahead of m_name: TerrainRoads_find.cpp already
// measured m_next at this+0x10 where the reference would put it at 0x0C, so
// the shift is at the front of the object, not inside the string arrays.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

// Only the two members these bodies reach. Declaring the whole of
// string_base.h's StringBase would put its private destructor in the epilogue
// as a second call; the retail tail is releaseBuffer alone.
template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set( const StringBase<T> &src );			// retail 0x00887C90

private:
	void releaseBuffer();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() { m_string.releaseBuffer(); }

	const AsciiString &operator=( const AsciiString &src ) { m_string.set( src.m_string ); return *this; }

	StringBase<char> m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE,

	BODYDAMAGETYPE_COUNT
};

enum BridgeTowerType
{
	BRIDGE_TOWER_FROM_LEFT = 0,
	BRIDGE_TOWER_FROM_RIGHT,
	BRIDGE_TOWER_TO_LEFT,
	BRIDGE_TOWER_TO_RIGHT,
	BRIDGE_MAX_TOWERS				///< keep this last
};

enum { MAX_BRIDGE_BODY_FX = 3 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainRoads.h
class TerrainRoadType
{
public:

	void friend_setDamageToFXString( BodyDamageType state, Int index, AsciiString s );
	void friend_setRepairedToFXString( BodyDamageType state, Int index, AsciiString s );

protected:

	void *m_bfmeLeadingSlot;					///< this+0x00, ahead of the reference's first member
	AsciiString m_name;								///< entry name
	Bool m_isBridge;									///< true if entry is for a bridge
	UnsignedInt m_id;									///< unique id
	TerrainRoadType *m_next;					///< next in road list

	// road data
	Real m_roadWidth;														///< width of road
	Real m_roadWidthInTexture;									///< width of road in the texture

	// bridge data
	Real m_bridgeScale;													///< scale for bridge

	AsciiString m_scaffoldObjectName;						///< scaffold object name
	AsciiString m_scaffoldSupportObjectName;		///< scaffold support object name

	RGBColor m_radarColor;											///< color for this bridge on the radar

	AsciiString m_bridgeModelName;							///< model name for bridge
	AsciiString m_texture;											///< texture filename

	AsciiString m_bridgeModelNameDamaged;				///< model name for bridge
	AsciiString m_textureDamaged;								///< model name for bridge

	AsciiString m_bridgeModelNameReallyDamaged;	///< model name for bridge
	AsciiString m_textureReallyDamaged;					///< model name for bridge

	AsciiString m_bridgeModelNameBroken;				///< model name for bridge
	AsciiString m_textureBroken;								///< model name for bridge

	AsciiString m_towerObjectName[ BRIDGE_MAX_TOWERS ];	///< object names for the targetable towers on the bridge

	AsciiString m_damageToSoundString[ BODYDAMAGETYPE_COUNT ];
	AsciiString m_damageToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	AsciiString m_damageToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	AsciiString m_repairedToSoundString[ BODYDAMAGETYPE_COUNT ];
	AsciiString m_repairedToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	AsciiString m_repairedToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	Real m_transitionEffectsHeight;
	Int m_numFXPerType; ///< for *each* fx/ocl we will make this many of them on the bridge area

};

// ?friend_setDamageToFXString@TerrainRoadType@@QAEXW4BodyDamageType@@HVAsciiString@@@Z
void TerrainRoadType::friend_setDamageToFXString( BodyDamageType state, Int index, AsciiString s )
{
	m_damageToFXString[ state ][ index ] = s;
}

// ?friend_setRepairedToFXString@TerrainRoadType@@QAEXW4BodyDamageType@@HVAsciiString@@@Z
void TerrainRoadType::friend_setRepairedToFXString( BodyDamageType state, Int index, AsciiString s )
{
	m_repairedToFXString[ state ][ index ] = s;
}
