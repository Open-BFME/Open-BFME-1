// cl: /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common
//
// ScriptGroup::xfer against BFME's real Snapshot/Xfer shape.
// Queue RVA 0xAF9B24 is a jump table (not a prologue); true body is ScriptGroup
// primary vtable slot 3 @ 0x350E90 (66B): Version(1,1) then bool at this+0x0C.
// ZH list-walking xfer is absent; BFME only persists m_isGroupActive.
// Layout: single vptr + two owned ptrs + packed bools (ctor/dtor at 0x352900/0x352950).

#include "xfer.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptGroup
{
public:
	// vptr @+0 (from virtuals below)
	void *m_firstScript;   // +0x04
	void *m_nextGroup;     // +0x08
	bool m_isGroupActive;  // +0x0C

protected:
	// MAE mangling matches reverse/functions.csv / ZH Snapshot::xfer(Xfer*)
	virtual void xfer(Xfer *xfer);
};

// ?xfer@ScriptGroup@@MAEXPAVXfer@@@Z
void ScriptGroup::xfer(Xfer *xfer)
{
	Xfer::Version v;
	v.data[0] = 1;
	v.data[1] = 1;
	(*xfer) == v;

	// Stack-temp bool matches retail (load [this+0xc] -> temp -> operator==(bool&) -> store back).
	bool active = m_isGroupActive;
	(*xfer) == active;
	m_isGroupActive = active;
}
