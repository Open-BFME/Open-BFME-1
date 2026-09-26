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

// Drawable.h /////////////////////////////////////////////////////////////////
// Reconstructed BFME (lotrbfme.exe 1.03) Drawable layout.
//
// This is NOT the ZH Drawable.h: it is an opaque-padded skeleton that
// reproduces only the field offsets proven from retail accessor bodies, so
// leaf Drawable members can be byte-matched without disturbing the ~30 rows
// that still compile against the ZH-shaped reference GameClient/Drawable.h.
// Follows the reference/shims/gamewindow and (unlanded) reference/shims/
// bfmeobject precedent: named fields only where a retail body proves both
// the offset AND the identity; everything else stays an opaque pad so we
// never assert a field name/type we cannot back with evidence.
//
// Proven retail offsets:
//   0x004 m_template   (Thing base; shared with Object, see the sweep/
//                        bfmeobject Object shim precedent -- Thing is
//                        Drawable's first base, so the vptr+template layout
//                        Thing itself already uses is unshifted here)
//   0x100 m_id          getID          0x4116B0  mov eax,[ecx+0x100]; ret
//                        mangleCustomAudioName 0x417330 also reads +0x100
//                        (blocker note: ZH-compiled offset for m_id is
//                        0x08c, so +0x74 (116B) of unidentified BFME fields
//                        are inserted somewhere before it)
//   0x138 m_locoInfo     getWheelInfo   0x77F6B0  mov eax,[ecx+0x138];
//                        test eax,eax; je +4; add eax,0x3c; ret  (returns
//                        &m_locoInfo->m_wheelInfo, DrawableLocoInfo+0x3c
//                        matches ZH's own DrawableLocoInfo::m_wheelInfo
//                        layout unchanged -- only the Drawable-level
//                        m_locoInfo pointer moved, ZH offset 0x0b8 -> +0x80
//                        of insertions before it, i.e. +0xc more than m_id)
//   0x150 m_modules[3]   xferDrawableModules 0x417E20 (existing matched
//                        row's note); ZH offset 0x0c0, NUM_DRAWABLE_MODULE_
//                        TYPES retail=3 vs ZH=2 -- +0x90 of insertions
//                        before it, i.e. +0x10 more than m_locoInfo)
//
// The three checkpoints (m_id/+0x74, m_locoInfo/+0x80, m_modules/+0x90)
// prove insertions are NOT one contiguous block: BFME added a handful of
// new fields scattered across at least three points in Drawable's private
// section. Only the cumulative sizes up to each checkpoint are proven, not
// which individual fields moved -- hence opaque byte-array pads rather than
// named fields for everything in between.

#pragma once
#ifndef _BFME_DRAWABLE_SHIM_H_
#define _BFME_DRAWABLE_SHIM_H_

#include "Lib/BaseType.h"
#include "Common/GameType.h"	// DrawableID

class ThingTemplate;
class Module;
struct TWheelInfo;

// ---------------------------------------------------
class Drawable
{
public:

	DrawableID getID( void ) const;
	const TWheelInfo *getWheelInfo( void ) const;

private:

	UnsignedByte				_bfme_vtbl[4];
	const ThingTemplate*	m_template;					///< 0x004 (Thing base)
	UnsignedByte				_bfme_pad_008[0xf8];	///< unproven: rest of Thing + Snapshot + early Drawable fields
	DrawableID					m_id;								///< 0x100
	UnsignedByte				_bfme_pad_104[0x34];	///< unproven: m_nextDrawable..m_shroudClearFrame + BFME insertions
	void*								m_locoInfo;					///< 0x138 (DrawableLocoInfo*; opaque here -- DrawableLocoInfo's OWN
																				///  layout is unchanged from ZH, only this outer pointer moved, so
																				///  getWheelInfo below reproduces retail's raw "+0x3c" byte offset
																				///  into it rather than declaring the full DrawableLocoInfo type)
	UnsignedByte				_bfme_pad_13c[0x14];	///< unproven: m_ambientSound + BFME insertions
	Module**						m_modules[3];				///< 0x150 (NUM_DRAWABLE_MODULE_TYPES retail=3, ZH=2)

};  // end class Drawable

#endif // _BFME_DRAWABLE_SHIM_H_
