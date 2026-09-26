// TU-scoped shim: Zero Hour's Snow.h with BFME's WeatherSetting members and
// SnowManager vtable depth. Nothing else differs.

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

// FILE: Snow.h /////////////////////////////////////////////////////////

#pragma once
#ifndef _SNOW_H_
#define _SNOW_H_

#include "Lib/BaseType.h"
#include "Common/SubsystemInterface.h"
#include "Common/Overridable.h"
#include "Common/Override.h"
#include "WWMATH/Vector3.h"
#include "WWMATH/Vector4.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

//-------------------------------------------------------------------------------------------------
/** This structure keeps the transparency and vertex settings, which are the same regardless of the
		time of day. They can be overridden on a per-map basis. */
//-------------------------------------------------------------------------------------------------
class BFMELightningRandomVariable
{
public:
	BFMELightningRandomVariable() : m_low(0.0f), m_high(0.0f), m_distribution(0) {}
	Real m_low;
	Real m_high;
	Int m_distribution;
};

class BFMEWeatherAsciiString
{
public:
	void set(const char *text, Int length);
};

class WeatherSetting : public Overridable
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( WeatherSetting, "WeatherSetting"  )

	public:
		AsciiString m_snowTexture;
		volatile Real m_snowFrequencyScaleX;
		volatile Real m_snowFrequencyScaleY;
		volatile Real m_snowAmplitude;
		volatile Real m_snowPointSize;
		volatile Real m_snowMaxPointSize;
		volatile Real m_snowMinPointSize;
		volatile Real m_snowQuadSize;
		volatile Real m_snowBoxDimensions;
		volatile Real m_snowBoxDensity;
		volatile Real m_snowVelocity;
		volatile Bool m_usePointSprites;
		volatile Bool m_snowEnabled;
		// BFME extends the setting from 0x3C to 0x78 -- parseWeatherDefinition
		// allocates a literal 0x78 -- with lightning, a spell effect and three ramp
		// controls. Every offset below is what retail's field table at 0x010F6540
		// carries; the Coord2D members are what take it out to 0x78.
		volatile Bool m_isSnowing;			// 0x3a
		volatile Int m_numberTiles;			// 0x3c
		volatile Bool m_lightningEnabled;		// 0x40
		BFMELightningRandomVariable m_lightningFactor;	// 0x44 -- GameClientRandomVariable
		volatile Int m_lightningDuration;	// 0x50
		volatile Real m_lightningChance;		// 0x54
		volatile Bool m_spellEnabled;			// 0x58
		volatile Int m_spellDuration;		// 0x5c
		volatile Real m_rampControl[2];		// 0x60 -- Coord2D
		volatile Real m_rampSpeed[2];			// 0x68 -- Coord2D
		volatile Real m_rampSpacing[2];		// 0x70 -- Coord2D

	public:
		WeatherSetting()
		{
			reinterpret_cast<BFMEWeatherAsciiString *>(&m_snowTexture)->set("EXSnowFlake.tga", 15);
			m_snowEnabled=FALSE;
			m_snowMinPointSize=0.0f;
			m_isSnowing=FALSE;
			m_lightningEnabled=FALSE;
			m_snowFrequencyScaleX=0.0533f;
			m_snowFrequencyScaleY=0.0275f;
			m_snowAmplitude=5.0f;
			m_snowPointSize=1.0f;
			m_snowQuadSize=0.5f;
			m_snowBoxDimensions=200;
			m_usePointSprites=TRUE;
			m_snowMaxPointSize=64.0f;
			m_numberTiles=4;
			m_lightningDuration=30;
			m_lightningChance=0.01f;
			m_spellEnabled=TRUE;
			m_spellDuration=200;
			_ReadWriteBarrier();
			m_snowBoxDensity=50;
			m_snowVelocity=100;
			m_rampControl[0]=0.3f;
			m_rampControl[1]=0.7f;
			m_rampSpeed[0]=0.0f;
			m_rampSpeed[1]=100.0f;
			m_rampSpacing[0]=50.0f;
			m_rampSpacing[1]=20.0f;
		}

		static const FieldParse m_weatherSettingFieldParseTable[];		///< the parse table for INI definition

		/// Get the INI parsing table for loading
		const FieldParse *getFieldParse( void ) const { return m_weatherSettingFieldParseTable; }
};

EMPTY_DTOR(WeatherSetting)

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

class SnowManager : public SubsystemInterface
{
  public :
	  enum{
		 SNOW_NOISE_X=64,			//dimensions table holding noise function used for initial snow positions.
		 SNOW_NOISE_Y=64,			//dimensions table holding noise function used for initial snow positions.
	  };

	 SnowManager(void);
	~SnowManager(void);

	virtual void init( void );
	virtual void reset( void );
	// Three virtuals BFME has ahead of this one: retail dispatches updateIniSettings
	// through vtable slot 9 (+0x24) where the stock header puts it at slot 6
	// (+0x18). Only the count is proven, from that offset.
	virtual void _bfme_unknownVirtual_0( void ) = 0;
	virtual void _bfme_unknownVirtual_1( void ) = 0;
	virtual void _bfme_unknownVirtual_2( void ) = 0;
	virtual void updateIniSettings (void);
	void setVisible(Bool showWeather);	///<enable/disable rendering of weather - assuming it's available on map.

  protected :

	Real				*m_startingHeights;
	Real				m_time;	///<time elapsed since it started snowing.
	Real				m_velocity;	///<positive velocity of falling snow
	Real				m_fullTimePeriod;	///<time for snow to complete a full animation cycle.
	Real				m_frequencyScaleX;	///<used to adjust snow position.
	Real				m_frequencyScaleY;	///<used to adjust snow position.
	Real				m_amplitude;		///<used to adjust amount of of snow movement.
	Real				m_pointSize;		///<used to control hardware point-sprite size.
	Real				m_maxPointSize;		///<used to control maximum pixel size of sprites.
	Real				m_minPointSize;		///<used to control minimum pixel size of sprites.
	Real				m_quadSize;			///<used to control quad size when no hardware point sprites.
	Real				m_boxDimensions;	///<used to set dimensions of box surrounding camera.
	Real				m_emitterSpacing;		///<used to control how many emitters are present per world unit
	Bool				m_isVisible;		///<used to prevent map weather (if defined) from rendering.
};

extern SnowManager *TheSnowManager;  ///< the ray effects singleton external

#endif // _SNOW_H_

