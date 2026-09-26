// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/framedata /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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


#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/FrameData.h"
#include "GameNetwork/NetworkUtil.h"

// BFME's FrameData has no m_frame -- the ring index is the frame -- so the
// ZH getFrame/setFrame pair and every assignment to it are gone. See
// inputs/reference/shims/framedata/GameNetwork/FrameData.h for the offset evidence.

/**
 * Initialize this thing.
 */
void FrameData::init()
{
	if (m_commandList == NULL) {
		// Plain new, not ZH's newInstance: BFME de-pooled the Net* classes.
		m_commandList = new NetCommandList;
		m_commandList->init();
	}
	m_commandList->reset();

	m_frameCommandCount = -1;
	m_commandCount = 0;
	m_lastFailedCC = -2;
	m_lastFailedFrameCC = -2;
}

/**
 * Set the command count for this frame
 */
void FrameData::setFrameCommandCount(UnsignedInt frameCommandCount) {
	m_frameCommandCount = frameCommandCount;
}

/**
 * Get the command count for this frame.
 */
UnsignedInt FrameData::getFrameCommandCount() {
	return m_frameCommandCount;
}

/**
 * return the number of commands received so far.
 */
UnsignedInt FrameData::getCommandCount() {
	return m_commandCount;
}

/**
 * Add a command to this frame
 */
NetCommandRef *FrameData::addCommand(NetCommandMsg *msg) {
	// need to add the message in order of command ID
	if (m_commandList == NULL) {
		init();
	}

	// We don't need to worry about setting the relay since its not getting sent anywhere.
	if (m_commandList->findMessage(msg) != NULL) {
		// We don't want to add the same command twice.
		return NULL;
	}
	NetCommandRef *ref = m_commandList->addMessage(msg);

	++m_commandCount;
	return ref;
}

/**
 * Return the list of commands for this frame
 */
NetCommandList * FrameData::getCommandList() {
	return m_commandList;
}

/**
 * destroy all the commands in this frame.
 */
void FrameData::destroyGameMessages() {
	if (m_commandList == NULL) {
		return;
	}

	m_commandList->reset();
	m_commandCount = 0;
}

/**
 * Are all the commands for this frame accounted for?  Appended at the end of
 * the file rather than in the reference's position so the compiland's $L
 * numbering ahead of it -- which the init funclet row is keyed on -- does not
 * move.  Under NDEBUG every DEBUG_LOG in the reference body is a no-op, which
 * is why the resend arm is just reset().
 */
// ?allCommandsReady@FrameData@@QAE?AW4FrameDataReturnType@@_N@Z
FrameDataReturnType FrameData::allCommandsReady(Bool debugSpewage) {
	if (m_frameCommandCount == m_commandCount) {
		m_lastFailedFrameCC = -2;
		m_lastFailedCC = -2;
		return FRAMEDATA_READY;
	}

	if (debugSpewage) {
		if ((m_lastFailedFrameCC != m_frameCommandCount) || (m_lastFailedCC != m_commandCount)) {
			m_lastFailedFrameCC = m_frameCommandCount;
			m_lastFailedCC = m_commandCount;
		}
	}

	// Signed: retail compares with jle, so BFME's two counts are Int.
	if ((Int)m_commandCount > (Int)m_frameCommandCount) {
		// The reference walks the command list here logging every entry. Under
		// NDEBUG the log is a no-op but the walk survives, because each step is a
		// load the compiler cannot drop -- retail still has the loop. BFME also
		// inlines NetCommandList::getFirstMessage(), reading the head straight
		// out of [m_commandList+4]; the shim only declares it, so spell the load.
		NetCommandRef *ref = *(NetCommandRef **)((char *)m_commandList + 4);
		while (ref != NULL) {
			// m_next is at [ref+4] in BFME; the vendored NetCommandRef puts it
			// at +8. Only the walk needs it, so spell it here.
			ref = *(NetCommandRef **)((char *)ref + 4);
		}
		// Retail calls the init body at 0x00670170 here (ILT 0x00022340), not
		// the separate reset body at 0x00670220. BFME's reset() forwards to
		// init() and is inline, so the reference's reset() lands on init.
		init();
		return FRAMEDATA_RESEND;
	}
	return FRAMEDATA_NOTREADY;
}
