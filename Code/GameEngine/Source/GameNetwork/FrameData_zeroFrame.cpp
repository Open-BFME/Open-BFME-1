// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
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

// FrameData::zeroFrame -- Zero Hour's FrameData.cpp body, unchanged.
//
// It belongs in FrameData.cpp next to the rest of the class, and this file only
// exists because it cannot go there. FrameDataManager's sibling claim
// uw_00c44d50 is a SEH funclet pinned to FrameData::init by MSVC's generated
// label `$L38639` (object-symbol= in its ledger notes), and that label number is
// allocated across the whole translation unit: adding ANY function to
// FrameData.cpp -- start, middle or end, all three tried -- renumbers it and the
// funclet row stops resolving. A separate TU leaves the numbering alone.
//
// The class is spelled locally at the BFME offsets from
// reference/shims/framedata/GameNetwork/FrameData.h: BFME dropped ZH's m_frame
// (the ring index is the frame), so m_frameCommandCount sits at this+0 and
// m_commandCount at this+4 where ZH has +4 and +8. Retail writes [ecx+4] before
// [ecx], which is source order for those two offsets and nothing else.
//
// Landing this resolves FrameDataManager::zeroFrames' one REL32 call, which
// reaches the body through the ILT thunk at 0x00048748.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FrameData.h
class FrameData
{
public:

	void zeroFrame();

private:

	unsigned int m_frameCommandCount;					///< retail this+0x00
	unsigned int m_commandCount;						///< retail this+0x04
};

// ?zeroFrame@FrameData@@QAEXXZ
void FrameData::zeroFrame() {
	m_commandCount = 0;
	m_frameCommandCount = 0;
}
