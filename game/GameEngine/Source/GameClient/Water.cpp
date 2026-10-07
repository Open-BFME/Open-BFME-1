// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// FILE: Water.cpp ////////////////////////////////////////////////////////////////////////////////
// Open-BFME: map water settings (Zero Hour GameClient/Water.cpp) on BFME data.
//
// The WaterSettings array lives in GameClient/Water/Rva00C6B810StaticInit.cpp
// and TheWaterTransparency in Common/INI/INIWater.cpp; this file carries the
// WaterSetting constructor/destructor and both INI parse tables.
//
// BFME's WaterTransparencySetting table (retail VA 0x010F6CD0) replaces Zero
// Hour's five skybox textures with StandingWaterColor, StandingWaterTexture,
// AdditiveBlending, RadarWaterColor and RiverTransparencyMultiplier.  The Zero
// Hour header lacks those members, so their offsets are spelled as the retail
// table stores them.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"

#include "GameClient/Water.h"
#include "Common/INI.h"

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
const FieldParse WaterSetting::m_waterSettingFieldParseTable[] =
{

	{ "SkyTexture",									INI::parseAsciiString,			NULL, offsetof( WaterSetting, m_skyTextureFile ) },
	{ "WaterTexture",								INI::parseAsciiString,			NULL, offsetof( WaterSetting, m_waterTextureFile ) },
	{ "Vertex00Color",							INI::parseRGBAColorInt,			NULL, offsetof( WaterSetting, m_vertex00Diffuse ) },
	{ "Vertex10Color",							INI::parseRGBAColorInt,			NULL, offsetof( WaterSetting, m_vertex10Diffuse ) },
	{ "Vertex01Color",							INI::parseRGBAColorInt,			NULL, offsetof( WaterSetting, m_vertex01Diffuse ) },
	{ "Vertex11Color",							INI::parseRGBAColorInt,			NULL, offsetof( WaterSetting, m_vertex11Diffuse ) },
	{ "DiffuseColor",								INI::parseRGBAColorInt,			NULL, offsetof( WaterSetting, m_waterDiffuseColor ) },
	{ "TransparentDiffuseColor",		INI::parseRGBAColorInt,			NULL, offsetof( WaterSetting, m_transparentWaterDiffuse ) },
	{ "UScrollPerMS",								INI::parseReal,							NULL, offsetof( WaterSetting, m_uScrollPerMs ) },
	{ "VScrollPerMS",								INI::parseReal,							NULL, offsetof( WaterSetting, m_vScrollPerMs ) },
	{ "SkyTexelsPerUnit",						INI::parseReal,							NULL, offsetof( WaterSetting, m_skyTexelsPerUnit ) },
	{ "WaterRepeatCount",						INI::parseInt,							NULL, offsetof( WaterSetting, m_waterRepeatCount ) },

	{ NULL,													NULL,												NULL, 0 },

};

const FieldParse WaterTransparencySetting::m_waterTransparencySettingFieldParseTable[] =
{

	{ "TransparentWaterDepth",			INI::parseReal,				NULL,			offsetof( WaterTransparencySetting, m_transparentWaterDepth ) },
	{ "TransparentWaterMinOpacity",	INI::parseReal,				NULL,			offsetof( WaterTransparencySetting, m_minWaterOpacity ) },
	{ "StandingWaterColor",					INI::parseRGBColor,		NULL,			0x14 },
	{ "StandingWaterTexture",				INI::parseAsciiString,NULL,			0x30 },
	{ "AdditiveBlending",						INI::parseBool,				NULL,			0x2C },
	{ "RadarWaterColor",						INI::parseRGBColor,		NULL,			0x20 },
	{ "RiverTransparencyMultiplier",	INI::parseReal,				NULL,			0x34 },

	{ 0, 0, 0, 0 },
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
WaterSetting::WaterSetting( void )
{

	m_skyTextureFile.clear();
	m_waterTextureFile.clear();
	m_waterRepeatCount = 0;
	m_skyTexelsPerUnit = 0.0f;

	m_vertex00Diffuse.red = 0;
	m_vertex00Diffuse.green = 0;
	m_vertex00Diffuse.blue = 0;
	m_vertex00Diffuse.alpha = 0;

	m_vertex01Diffuse.red = 0;
	m_vertex01Diffuse.green = 0;
	m_vertex01Diffuse.blue = 0;
	m_vertex01Diffuse.alpha = 0;

	m_vertex10Diffuse.red = 0;
	m_vertex10Diffuse.green = 0;
	m_vertex10Diffuse.blue = 0;
	m_vertex10Diffuse.alpha = 0;

	m_vertex11Diffuse.red = 0;
	m_vertex11Diffuse.green = 0;
	m_vertex11Diffuse.blue = 0;
	m_vertex11Diffuse.alpha = 0;

	m_waterDiffuseColor.red = 0;
	m_waterDiffuseColor.green = 0;
	m_waterDiffuseColor.blue = 0;
	m_waterDiffuseColor.alpha = 0;

	m_transparentWaterDiffuse.red = 0;
	m_transparentWaterDiffuse.green = 0;
	m_transparentWaterDiffuse.blue = 0;
	m_transparentWaterDiffuse.alpha = 0;

	m_uScrollPerMs = 0.0f;
	m_vScrollPerMs = 0.0f;

}  // end WaterSetting

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
WaterSetting::~WaterSetting( void )
{

}  // end WaterSetting
