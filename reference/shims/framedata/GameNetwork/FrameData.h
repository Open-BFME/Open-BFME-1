#pragma once

#ifndef __FRAMEDATA_H
#define __FRAMEDATA_H

// TU-scoped stand-in for the real GameNetwork/FrameData.h. BFME's FrameData is
// 20 bytes, not the ZH reference's 24: the element stride in retail
// FrameDataManager::setFrameCommandCount (0x00670750) is
// `lea edx,[edx+edx*4]; lea ecx,[eax+edx*4]`, i.e. 5 dwords. The dropped member
// is ZH's leading m_frame -- retail's FrameData accessors put
// m_frameCommandCount at this+0 (written by 0x006702C0, read by 0x006702D0) and
// m_commandCount at this+4 (read by 0x006702E0), where ZH has them at +4 and +8.
// The frame number is implicit in the ring index, so nothing needs it.
//
// Scoped to this TU via a private /Ireference/shims/framedata include -- every
// other TU still resolves GameNetwork/FrameData.h to the real header.

#include "Lib/BaseType.h"
#include "GameNetwork/NetCommandList.h"

enum FrameDataReturnType {
	FRAMEDATA_NOTREADY,
	FRAMEDATA_RESEND,
	FRAMEDATA_READY
};

class FrameData {
public:
	FrameData();
	~FrameData();

	void init();
	void reset();
	void update();

	// Declared, never defined: BFME has no m_frame, so these have no retail
	// body. Only the TU's still-unmatched resetFrame references them, and it is
	// exactly the function BFME must have rewritten to drop the member.
	UnsignedInt getFrame();
	void setFrame(UnsignedInt frame);

	FrameDataReturnType allCommandsReady(Bool debugSpewage);
	NetCommandList *getCommandList();
	void setFrameCommandCount(UnsignedInt totalCommandCount);
	UnsignedInt getFrameCommandCount();
	// Returns the new NetCommandRef in BFME, where ZH returns void: the
	// duplicate path is `xor eax,eax` and the success path leaves addMessage's
	// return value in eax, which is also why retail increments m_commandCount
	// through ecx rather than clobbering it.
	NetCommandRef *addCommand(NetCommandMsg *msg);
	UnsignedInt getCommandCount();
	UnsignedInt getAckCommandCount();
	void zeroFrame();
	void destroyGameMessages();

protected:
	UnsignedInt m_frameCommandCount;			// this+0
	UnsignedInt m_commandCount;					// this+4
	NetCommandList *m_commandList;				// this+8
	UnsignedInt m_lastFailedCC;					// this+0xc
	UnsignedInt m_lastFailedFrameCC;			// this+0x10
};

#endif
