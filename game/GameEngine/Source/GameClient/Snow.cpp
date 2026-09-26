// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/snow /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// Snow.cpp ////////////////////////////////////////////////////////////////////////////////
// Snow Rendering implementation
// Author: Mark Wilczynski, July 2003
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"

// BFME de-pooled this glue: retail's per-class `operator delete(void*, MagicEnum)`
// is one 12-byte body (0x007EFFF0) that calls the CRT free IMPORT THUNK -- a
// `call rel32` into `jmp [__imp__free]` -- where ::operator delete (0x00881EB0)
// is a different function. <stdlib.h> declares free __declspec(dllimport) under
// /MD, which compiles to the `ff 15` indirect form instead, so the C-linkage
// redeclaration below is what names `_free` for the linker's thunk; it is
// namespaced so every other free() call in this TU keeps the indirect form
// retail also uses. Same TU-scoped override Team.cpp already carries.
namespace BfmePoolGlue { extern "C" void __cdecl free(void *); }
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ return MP_GLUE_ALLOCATE(ARGCLASS); } \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ BfmePoolGlue::free(p); } \
protected: \
	inline void *operator new(size_t s) { return ::operator new(s); } \
	inline void operator delete(void *p) { ::operator delete(p); } \
private: \
	virtual MemoryPool *getObjectMemoryPool() { return ARGCLASS::getClassMemoryPool(); } \
public:
#include "Common/INI.h"
#include "Common/INIException.h"	// This must go first in EVERY cpp file int the Game
#include "GameClient/Snow.h"
#include "GameClient/view.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

SnowManager *TheSnowManager=NULL;

// ??0SnowManager@@ present-unmatched
SnowManager::SnowManager()
{
	m_time = 0;
	m_velocity = 1;
	m_isVisible = TRUE;	//default to showing if it's enabled via INI.
}

void SnowManager::init( void )
{
	//starting heights of each particle
	//TODO: replace this lookup table with some kind of procedural method that takes x,y as input.
	m_startingHeights=NEW Real [ SNOW_NOISE_X * SNOW_NOISE_Y];
	m_time = 0;

	updateIniSettings();
}

// ?updateIniSettings@SnowManager@@ present-unmatched
void SnowManager::updateIniSettings(void)
{
	Real *dst=m_startingHeights;
	//initialize a table of random starting positions for each particle.
	Int boxDimensions = (Int)TheWeatherSetting->m_snowBoxDimensions;
	for (Int y=0; y<SNOW_NOISE_Y; y++)
	{
		for (Int x=0; x<SNOW_NOISE_X; x++)
		{
			*dst=(Real)(rand()%(boxDimensions));
			dst++;
		}
	}

	m_velocity = TheWeatherSetting->m_snowVelocity;
	m_frequencyScaleX = TheWeatherSetting->m_snowFrequencyScaleX;
	m_frequencyScaleY = TheWeatherSetting->m_snowFrequencyScaleY;
	m_amplitude	= TheWeatherSetting->m_snowAmplitude;	
	m_pointSize = TheWeatherSetting->m_snowPointSize;	
	m_quadSize	= TheWeatherSetting->m_snowQuadSize;		
	m_boxDimensions	= TheWeatherSetting->m_snowBoxDimensions;
	m_emitterSpacing = 1.0f/TheWeatherSetting->m_snowBoxDensity;
	m_maxPointSize = TheWeatherSetting->m_snowMaxPointSize;
	m_minPointSize = TheWeatherSetting->m_snowMinPointSize;

	//Time for snow flake to make it from top to bottom of rendered cube around camera.
	m_fullTimePeriod = m_boxDimensions/m_velocity;
}

void SnowManager::setVisible(Bool showWeather)
{
	m_isVisible = showWeather;
}

void SnowManager::reset(void)
{
	m_isVisible = TRUE;	//default to showing if it's enabled via INI.
}

// ??1SnowManager@@ present-unmatched
SnowManager::~SnowManager()
{
	delete [] m_startingHeights;
	m_startingHeights=NULL;
}

OVERRIDE<WeatherSetting> TheWeatherSetting = NULL;

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
const FieldParse WeatherSetting::m_weatherSettingFieldParseTable[] = 
{
	{ "SnowTexture",							INI::parseAsciiString,NULL,			offsetof( WeatherSetting, m_snowTexture ) },
	{ "SnowFrequencyScaleX",					INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowFrequencyScaleX ) },
	{ "SnowFrequencyScaleY",					INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowFrequencyScaleY ) },
	{ "SnowAmplitude",							INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowAmplitude ) },
	{ "SnowPointSize",							INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowPointSize ) },
	{ "SnowMaxPointSize",						INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowMaxPointSize ) },
	{ "SnowMinPointSize",						INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowMinPointSize ) },
	{ "SnowQuadSize",							INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowQuadSize ) },
	{ "SnowBoxDimensions",						INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowBoxDimensions ) },
	{ "SnowBoxDensity",							INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowBoxDensity ) },
	{ "SnowVelocity",							INI::parseReal,NULL,			offsetof( WeatherSetting, m_snowVelocity ) },
	{ "SnowPointSprites",						INI::parseBool,NULL,			offsetof( WeatherSetting, m_usePointSprites ) },
	{ "SnowEnabled",							INI::parseBool,NULL,			offsetof( WeatherSetting, m_snowEnabled ) },
	{ 0, 0, 0, 0 },
};

//-------------------------------------------------------------------------------------------------
void INI::parseWeatherDefinition( INI *ini )
{
	const WeatherSetting *existing = TheWeatherSetting;

	if (existing == NULL) {
		TheWeatherSetting = newInstance(WeatherSetting);
	} else if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) {
		WeatherSetting* ws = (WeatherSetting*) (TheWeatherSetting.getNonOverloadedPointer());
		WeatherSetting* wsOverride = newInstance(WeatherSetting);
		*wsOverride = *ws;

		// Mark that it is an override.
		wsOverride->markAsOverride();

		ws->friend_getFinalOverride()->setNextOverride(wsOverride);
	} else {
		throw INIException( 3, "WeatherSetting defined twice" );
	}

	WeatherSetting* weatherSet = (WeatherSetting*) (TheWeatherSetting.getNonOverloadedPointer());
	weatherSet = (WeatherSetting*) (weatherSet->friend_getFinalOverride());
	// parse the data
	ini->initFromINI( weatherSet, weatherSet->getFieldParse() );

	if (TheSnowManager)
		TheSnowManager->updateIniSettings();

	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) {
		// Check to see if we overrode any textures.
		// If we did, then we need to replace them in the model.
	}
}
