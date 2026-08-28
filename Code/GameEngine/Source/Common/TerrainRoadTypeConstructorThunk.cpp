// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// TerrainRoadType's constructor, body verbatim from the reference TerrainRoads.cpp.
//
// Layout read straight off the retail body: vptr at 0, m_name at 4, the three
// Reals at 0x14/0x18/0x1c, the two scaffold strings at 0x20/0x24, RGBColor at
// 0x28, and the five model/texture string pairs at 0x34..0x50 -- each zeroed
// inline by AsciiString's default ctor. The string arrays that follow are built
// with the eh-vector-constructor-iterator, which is the push of the element ctor
// at 0x40d828 right after the 0x50 store.
#include "Common/AsciiString.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum { BRIDGE_MAX_TOWERS = 4, MAX_BRIDGE_BODY_FX = 3, BODYDAMAGETYPE_COUNT = 4 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolObject
{
public:
	// A vptr but no destructor: giving this base a virtual destructor makes it a
	// destructible sub-object and shifts every unwind state index up by one.
	virtual void anchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainRoads.h
class TerrainRoadType : public MemoryPoolObject
{
public:
	TerrainRoadType();
	virtual ~TerrainRoadType() {}

protected:
	AsciiString m_name;
	Bool m_isBridge;
	UnsignedInt m_id;
	TerrainRoadType *m_next;

	Real m_roadWidth;
	Real m_roadWidthInTexture;

	Real m_bridgeScale;

	AsciiString m_scaffoldObjectName;
	AsciiString m_scaffoldSupportObjectName;

	RGBColor m_radarColor;

	AsciiString m_bridgeModelName;
	AsciiString m_texture;

	AsciiString m_bridgeModelNameDamaged;
	AsciiString m_textureDamaged;

	AsciiString m_bridgeModelNameReallyDamaged;
	AsciiString m_textureReallyDamaged;

	AsciiString m_bridgeModelNameBroken;
	AsciiString m_textureBroken;

	AsciiString m_towerObjectName[ BRIDGE_MAX_TOWERS ];

	AsciiString m_damageToSoundString[ BODYDAMAGETYPE_COUNT ];
	AsciiString m_damageToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	AsciiString m_damageToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	AsciiString m_repairedToSoundString[ BODYDAMAGETYPE_COUNT ];
	AsciiString m_repairedToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	AsciiString m_repairedToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];
	Real m_transitionEffectsHeight;
	Int m_numFXPerType;
};

// ??0TerrainRoadType@@QAE@XZ
TerrainRoadType::TerrainRoadType( void )
{

	m_isBridge = false;
	m_id = 0;
	m_next = 0;
	m_roadWidth = 0.0f;
	m_roadWidthInTexture = 0.0f;
	m_bridgeScale = 1.0f;
	m_radarColor.red = 0.0f;
	m_radarColor.green = 0.0f;
	m_radarColor.blue = 0.0f;
	m_transitionEffectsHeight = 0.0f;
	m_numFXPerType = 0;

}
