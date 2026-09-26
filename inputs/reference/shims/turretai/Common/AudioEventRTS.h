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

// BFME AudioEventRTS layout shim (TU-scoped to the turretai shim dir, so only
// TurretAI.cpp sees it). BFME restructured the class: retail is 0x70 bytes
// where the ZH reference compiles to 0x64, with the object/owner/position
// block moved to +0x2C..+0x3F and three extra dwords in the tail.
//
// Offsets below are pinned by matched retail getters/setters in
// Code/GameEngine/Source/Common/Audio/AudioEventRTS.cpp:
//   m_playingHandle +0x0C (setPlayingHandle @0xB2200), m_killThisHandle +0x10
//   (@0xB2310), m_priority +0x20 (getAudioPriority @0x87410),
//   m_volume +0x24 (setVolume @0xB23B0), m_timeOfDay +0x28 (setTimeOfDay
//   @0x873F0), m_objectID/m_drawableID +0x2C and m_ownerType +0x30
//   (setObjectID @0xB2250, setDrawableID @0xB2290), m_positionOfAudio +0x34
//   (setPosition @0xB2210), m_shouldFade +0x40 (getShouldFade @0x6B3B0),
//   m_isLogicalAudio +0x41 (@0xB2330), m_uninterruptable +0x42 (@0xB2350),
//   m_pitchShift +0x4C (getPitchShift @0xB21C0), m_volumeShift +0x50
//   (@0xB21D0), m_delay +0x54 (decrementDelay @0xB21E0),
//   m_playerIndex +0x5C (setPlayerIndex @0xB23C0),
//   m_portionToPlayNext +0x60 (setNextPlayPortion @0xB21F0).
// The dwords at +0x44..+0x4B, +0x58 and +0x64..+0x6C are BFME additions whose
// identity is not yet pinned; they are held as opaque slots so sizeof is 0x70.

#pragma once

#ifndef _H_AUDIOEVENTRTS_
#define _H_AUDIOEVENTRTS_

#include "Common/AsciiString.h"
#include "Common/GameAudio.h"
#include "Common/GameMemory.h"
#include "Common/GameType.h"
#include "Common/AudioEventInfo.h"

// forward declarations ///////////////////////////////////////////////////////////////////////////
struct AudioEventInfo;

enum OwnerType
{
	OT_Positional,
	OT_Drawable,
	OT_Object,
	OT_Dead,
	OT_INVALID
};

enum PortionToPlay
{
	PP_Attack,
	PP_Sound,
	PP_Decay,
	PP_Done
};

class AudioEventRTS
{
public:
	AudioEventRTS();
	AudioEventRTS(const AsciiString& eventName);
	AudioEventRTS(const AsciiString& eventName, ObjectID ownerID);
	AudioEventRTS(const AsciiString& eventName, DrawableID drawableID);
	AudioEventRTS(const AsciiString& eventName, const Coord3D* positionOfAudio);

	virtual ~AudioEventRTS();

	AudioEventRTS(const AudioEventRTS& right);
	AudioEventRTS& operator=(const AudioEventRTS& right);

	Bool isCurrentlyPlaying() const;

	void setPlayingHandle(AudioHandle handle);
	AudioHandle getPlayingHandle();

	void setObjectID(ObjectID objID);

protected:
	AsciiString					m_filenameToLoad;		// +0x04
	const AudioEventInfo*	m_eventInfo;				// +0x08
	AudioHandle					m_playingHandle;		// +0x0C
	AudioHandle					m_killThisHandle;		// +0x10
	AsciiString					m_eventName;				// +0x14
	AsciiString					m_attackName;				// +0x18
	AsciiString					m_decayName;				// +0x1C
	AudioPriority				m_priority;					// +0x20
	Real								m_volume;						// +0x24
	TimeOfDay						m_timeOfDay;				// +0x28
	union
	{
		ObjectID					m_objectID;					// +0x2C
		DrawableID				m_drawableID;
	};
	OwnerType						m_ownerType;				// +0x30
	Coord3D							m_positionOfAudio;	// +0x34
	Bool								m_shouldFade;				// +0x40
	Bool								m_isLogicalAudio;		// +0x41
	Bool								m_uninterruptable;	// +0x42
	UnsignedInt					m_bfmeUnknown44;		// +0x44 (unidentified BFME field)
	UnsignedInt					m_bfmeUnknown48;		// +0x48 (unidentified BFME field)
	Real								m_pitchShift;				// +0x4C
	Real								m_volumeShift;			// +0x50
	Real								m_delay;						// +0x54
	UnsignedInt					m_bfmeUnknown58;		// +0x58 (unidentified BFME field)
	Int									m_playerIndex;			// +0x5C
	PortionToPlay				m_portionToPlayNext; // +0x60
	UnsignedInt					m_bfmeUnknown64;		// +0x64 (unidentified BFME field)
	UnsignedInt					m_bfmeUnknown68;		// +0x68 (unidentified BFME field)
	UnsignedInt					m_bfmeUnknown6C;		// +0x6C (unidentified BFME field)
};

class DynamicAudioEventRTS : public MemoryPoolObject
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(DynamicAudioEventRTS, "DynamicAudioEventRTS" )
public:

	DynamicAudioEventRTS() { }
	DynamicAudioEventRTS(const AudioEventRTS& a) : m_event(a) { }

	AudioEventRTS	m_event;
};
EMPTY_DTOR(DynamicAudioEventRTS)

#endif // _H_AUDIOEVENTRTS_
