// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/framedata /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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


// Claim the real GameNetwork/FrameDataManager.h include guard before anything
// can pull it in transitively: its FrameDataManager derives from
// MemoryPoolObject, which BFME's does not, and the class is declared below
// instead.
#define __FRAMEDATAMANAGER_H

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameNetwork/FrameData.h"
#include "GameNetwork/NetworkDefs.h"

// Declared here rather than in a shim header: a shim directory makes every
// later commit run the full gate, and on a machine running six clones at once
// that gate is both slow and prone to wedging. Nothing outside this file needs
// the declaration.
// BFME de-pooled this the same way it de-pooled FrameData, NetCommandList,
// NetCommandRef and Connection: the destructor at 0x00670540 stores a vptr, so
// the class still has a vtable, but it carries no SEH frame at all -- there is
// no MemoryPoolObject base destructor to unwind past. It goes straight from the
// clear loop to the vector-destructor iterator and operator delete[]. The field
// offsets are unchanged (m_frameData at +4), which is why the accessors already
// matched against the reference layout.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FrameDataManager.h
class FrameDataManager
{
public:
	FrameDataManager(Bool isLocal);

	void init();
	void reset();
	void update();

	NetCommandRef *addNetCommandMsg(NetCommandMsg *msg);
	void setIsLocal(Bool isLocal);
	FrameDataReturnType allCommandsReady(UnsignedInt frame, Bool debugSpewage);
	NetCommandList * getFrameCommandList(UnsignedInt frame);
	UnsignedInt getCommandCount(UnsignedInt frame);
	void setFrameCommandCount(UnsignedInt frame, UnsignedInt commandCount);
	UnsignedInt getFrameCommandCount(UnsignedInt frame);
	void zeroFrames(UnsignedInt startingFrame, UnsignedInt numFrames);
	void destroyGameMessages();
	void resetFrame(UnsignedInt frame, Bool isAdvancing = TRUE);
	void setQuitFrame(UnsignedInt frame);
	UnsignedInt getQuitFrame();
	Bool getIsQuitting();

protected:
	// Protected and virtual: retail's destructor mangles ??1FrameDataManager@@MAE@XZ.
	virtual ~FrameDataManager();

	FrameData *m_frameData;
	Bool m_isLocal;

	Bool m_isQuitting;
	UnsignedInt m_quitFrame;
};
#include "GameNetwork/NetworkUtil.h"

/**
 * Constructor.  isLocal tells it whether its the frame data manager for the local player or not.
 */
FrameDataManager::FrameDataManager(Bool isLocal) {
	m_isLocal = isLocal;
	
	m_frameData = NEW FrameData[FRAME_DATA_LENGTH];

	m_isQuitting = FALSE;
	m_quitFrame = 0;
}

/**
 * destructor.
 */
FrameDataManager::~FrameDataManager() {
	// init(), not reset(): the reference's FrameData::reset is nothing but a call
	// to init, so the two bodies are identical and the image carries only one of
	// them at 0x00670170. Whichever name BFME's source used, the call lands
	// there. FRAME_DATA_LENGTH is re-read from its global on every iteration.
	for (Int i = 0; i < FRAME_DATA_LENGTH; ++i) {
		m_frameData[i].init();
	}

	if (m_frameData)
	{
		delete[] m_frameData;
		m_frameData = NULL;
	}
}

/**
 * Initialize all of the frame datas associated with this manager.
 */
void FrameDataManager::init() {
	for (Int i = 0; i < FRAME_DATA_LENGTH; ++i) {
		m_frameData[i].init();
		if (m_isLocal) {
			// BFME stamps -1 rather than the reference's getCommandCount(), the
			// same substitution resetFrame makes: a fresh frame is "count not yet
			// known", not "zero commands".
			m_frameData[i].setFrameCommandCount(-1);
		}
	}

	m_isQuitting = FALSE;
	m_quitFrame = 0;
}

/**
 * Reset the state of all the frames.
 */
// ?reset@FrameDataManager@@ present-unmatched
void FrameDataManager::reset() {
	init();
}

/**
 * update function. Does nothing at this time.
 */
void FrameDataManager::update() {
}

/**
 * Add a network command to the appropriate frame.
 */
// 0x00670640, 35 bytes.
//
// It returns the reference rather than discarding it, which is the whole
// difference between this and a version that tail-jumps: with a void return
// MSVC turns the last call into a jmp, and retail emits call plus ret.
//
// BFME also drops the reference's local-player adjustment -- there is no
// `if (m_isLocal) setFrameCommandCount(getCommandCount())` here. The announced
// total is stamped by the FRAMEINFO path instead.
NetCommandRef *FrameDataManager::addNetCommandMsg(NetCommandMsg *msg) {
	UnsignedInt frame = msg->getExecutionFrame();
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;
	return m_frameData[frameindex].addCommand(msg);
}

/**
 * Returns true if all the commands for the given frame are ready.
 */
// Landed at 0x00670670, 34 bytes, which reproduces this body exactly. An
// earlier note here placed it at 0x00670A30 instead -- a 448-byte body that
// walks the ring from a base in ebx and reads TheGlobalData+0xB1C -- and
// doubted the delegation on that basis. 0x00670670 settles it: it divides the
// frame by the FRAME_DATA_LENGTH global at 0x012BA088, indexes [this+4] by the
// remainder at a 20-byte stride, which is sizeof(FrameData) in this shim, and
// calls FrameData::allCommandsReady at 0x00670240 with debugSpewage. That is
// this function statement for statement, so BFME did not rewrite it. Whatever
// 0x00670A30 is, it is something else, and the TheGlobalData+0xB1C question it
// raised belongs with that body, not this one.
FrameDataReturnType FrameDataManager::allCommandsReady(UnsignedInt frame, Bool debugSpewage) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;
	//DEBUG_ASSERTCRASH(m_frameData[frameindex].getFrame() == frame || frame == 256, ("Looking at old commands!"));
	return m_frameData[frameindex].allCommandsReady(debugSpewage);
}

/**
 * Returns the command list for the given frame.
 */
NetCommandList * FrameDataManager::getFrameCommandList(UnsignedInt frame) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;
	return m_frameData[frameindex].getCommandList();
}

/**
 * Reset the contents of the given frame.
 */
// BFME drops ZH's isAdvancing branch along with m_frame, and passes -1 to
// setFrameCommandCount where ZH re-reads getCommandCount().
void FrameDataManager::resetFrame(UnsignedInt frame, Bool isAdvancing) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	m_frameData[frameindex].reset();

	if (m_isLocal) {
		m_frameData[frameindex].setFrameCommandCount(-1);
	}
}

/**
 * Returns the command count for the given frame.
 */
UnsignedInt FrameDataManager::getCommandCount(UnsignedInt frame) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	return m_frameData[frameindex].getCommandCount();
}

/**
 * Set the frame command count for the given frame.
 */
void FrameDataManager::setFrameCommandCount(UnsignedInt frame, UnsignedInt commandCount) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	m_frameData[frameindex].setFrameCommandCount(commandCount);
}

/**
 *
 */
UnsignedInt FrameDataManager::getFrameCommandCount(UnsignedInt frame) {
	UnsignedInt frameindex = frame % FRAME_DATA_LENGTH;

	return m_frameData[frameindex].getFrameCommandCount();
}

/**
 * Set both the command count and the frame command count to 0 for the given frames.
 */
void FrameDataManager::zeroFrames(UnsignedInt startingFrame, UnsignedInt numFrames) {
	UnsignedInt frameIndex = startingFrame % FRAME_DATA_LENGTH;
	for (UnsignedInt i = 0; i < numFrames; ++i) {
		//DEBUG_LOG(("Calling zeroFrame for frame index %d\n", frameIndex));
		m_frameData[frameIndex].zeroFrame();
		++frameIndex;
		frameIndex = frameIndex % FRAME_DATA_LENGTH;
	}
}

/**
 * Destroy all the commands held by this object.
 */
void FrameDataManager::destroyGameMessages() {
	for (Int i = 0; i < FRAME_DATA_LENGTH; ++i) {
		m_frameData[i].destroyGameMessages();
	}
}

/**
 * Sets the quit frame, also sets the isQuitting flag.
 */
void FrameDataManager::setQuitFrame(UnsignedInt frame) {
	m_isQuitting = TRUE;
	m_quitFrame = frame;
}

/**
 * returns the quit frame.
 */
UnsignedInt FrameDataManager::getQuitFrame() {
	return m_quitFrame;
}

/**
 * returns true if this frame data manager is quitting.
 */
Bool FrameDataManager::getIsQuitting() {
	return m_isQuitting;
}
