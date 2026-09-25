// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWMath
// ?xfer@AIAttackMeleeEngageState@@MAEXPAVXfer@@@Z
// RVA 0x00177F40, 282 bytes. Vtable 0x01099848 (installed by the exact
// AIAttackMeleeEngageState constructor 0x0017F8D0) slot 3 routes through ILT
// 0x0003B0D9 to this body; slot 3 is the State snapshot xfer slot, as in
// AIAttackState::xfer (vtable 0x0109A0C8). The base call goes through ILT
// 0x00002379, which is slot 3 of vtable 0x01095B08 installed by the exact
// AIInternalMoveToState constructor 0x0014F280; its body 0x0016B140 follows
// the ZH AIInternalMoveToState::xfer order (version 1, Coord3D, layer helper,
// bool, Coord3D, two UnsignedInts, bool).
// The fire-weapon substate is built with the ZH State::getMachine() inline
// accessor rather than a direct m_machine read; written as a plain member
// read, VC7.1 stores the int transfer temporary before pushing its address
// and swaps EAX/EDX (retail +0xC2..+0xE4).

#include "xfer.h"
#include "snapshot.h"
#include "coord3d.h"

class StateMachine;
class NotifyWeaponFiredInterface;

// Xfer slot 19 (operator==(ICoord2D &)) transfers the 8-byte field at +0x68.
// Three headers define ICoord2D, so this TU keeps the plain two-int layout.
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
// Retail passes the state pointer unadjusted to Xfer slot 12
// (operator==(Snapshot &)), so the Snapshot view sits at offset 0.
class State : public Snapshot
{
public:
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

	inline StateMachine *getMachine() { return m_machine; }

private:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
	unsigned char m_pad20[0x04];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
// Size 0x2C: retail +0x8A allocates 0x2C bytes before the exact constructor
// 0x001712C0 (reached through ILT 0x0000FF1F), which stores notify at +0x24.
class AIAttackFireWeaponState : public State
{
public:
	AIAttackFireWeaponState(StateMachine *machine, NotifyWeaponFiredInterface *notify);

private:
	NotifyWeaponFiredInterface *m_att;
	bool m_28;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad24[0x2C];
};

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	AIAttackFireWeaponState *m_field50;
	int m_field54;
	unsigned int m_field58;
	Coord3DBase m_field5C;
	ICoord2D m_field68;
	unsigned int m_field70;
	bool m_field74;
	bool m_field75;
	NotifyWeaponFiredInterface *m_field78;
};

// ?xfer@AIAttackMeleeEngageState@@MAEXPAVXfer@@@Z
void AIAttackMeleeEngageState::xfer(Xfer *xfer)
{
	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 3;
	*xfer == version;
	AIInternalMoveToState::xfer(xfer);

	if (!xfer->IsLightCRC())
	{
		*xfer == m_field5C;
		*xfer == m_field68;
		*xfer == m_field58;
		*xfer == m_field75;

		if (version.data[1] > 1)
		{
			if (m_field50 == 0)
				m_field50 = new AIAttackFireWeaponState(getMachine(), m_field78);

			int field54 = m_field54;
			*xfer == field54;
			m_field54 = field54;
			*xfer == *m_field50;
		}

		if (version.data[1] > 2)
		{
			*xfer == m_field70;
			*xfer == m_field74;
		}
	}
}
