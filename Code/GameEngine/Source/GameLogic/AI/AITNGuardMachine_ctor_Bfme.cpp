// Real C++ body for the retail AITNGuardMachine constructor.
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// The retail constructor is identified by AITunnelNetworkGuardState::onEnter
// at 0x0016DAC0, which calls its one-argument ILT at VA 0x0040715D.  The
// constructor installs the AITNGuardMachine vtable at 0x0109B4B0 and the
// complete retail body is RVA 0x0018AFB0..0x0018B2A1 (753 bytes).  These
// ABI/layout donor: the EA/GPL AITNGuard.cpp and AITNGuard.h sources under
// reference/CnC_Generals_Zero_Hour/GeneralsMD.  This TU keeps only independent
// layout views and declarations; it does not provide donor callback bodies.

class Object;
class State
{
};

struct StateConditionInfo;
typedef bool (__cdecl *StateTransFuncPtr)(State *, void *);

class StateMachine
{
public:
	StateMachine(Object *owner, AsciiString name, bool flag);
	virtual ~StateMachine();

protected:
	void defineState(unsigned int id, State *state,
		unsigned int successID, unsigned int failureID,
		const StateConditionInfo *conditions);

private:
	char m_layout[0x40];
};

struct StateConditionInfo
{
	StateTransFuncPtr test;
	unsigned int toStateID;
	void *userData;

	StateConditionInfo(StateTransFuncPtr t, unsigned int id, void *ud)
		: test(t), toStateID(id), userData(ud) { }
};

// The retail condition-table function is the complete 118-byte body at
// VA 0x0058A0F0 (RVA 0x0018A0F0), ending in a plain cdecl ret.  Its first
// parameter is the State* at [esp+4], its callback userdata at [esp+8] is
// unused, and its bool result is returned in AL.  The constructor writes VA
// 0x0058A0F0 into the condition-table record at +0x6A.  Keep this callback
// declaration-only: the address-qualified direct-body pin names the retail
// implementation without inventing a false fallback body here.
extern "C" bool __cdecl Rva0018A0F0StatePredicate(State *, void *);

class Rva000A19E0StateBase : public State
{
public:
	Rva000A19E0StateBase(void *machine, AsciiString name);
};

class Rva0014F280StateBase : public State
{
public:
	Rva0014F280StateBase(void *machine, AsciiString name);
};

// Both base calls above are declaration-only ABI views of the retail state
// constructors at RVA 0x000A19E0 and RVA 0x0014F280.  The derived BFME state
// records below intentionally model their empty base contribution with
// explicit vptr and field offsets; no synthetic inline base bodies are used.
extern int g_AITNGuardMachineVTable;
extern int g_AITNGuardReturnStateVTable;
extern int g_AITNGuardIdleStateVTable;
extern int g_AITNGuardInnerStateVTable;
extern int g_AITNGuardOuterStateVTable;
extern int g_AITNGuardPickUpCrateStateVTable;
extern int g_AITNGuardAttackAggressorStateVTable;
extern int g_Rva0109B558StateSecondaryVTable;

class AITNGuardReturnState : public Rva0014F280StateBase
{
public:
	// Retail derived view: primary vptr at this+0, fields at this+0x50/0x54.
	AITNGuardReturnState(void *machine)
		: Rva0014F280StateBase(machine, AsciiString("AIEnterState"))
	{
		m_field50 = 0;
		m_vftable = &g_AITNGuardReturnStateVTable;
		m_field54 = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x4c];
	volatile unsigned int m_field50;
	volatile unsigned int m_field54;
};

class AITNGuardIdleState : public Rva000A19E0StateBase
{
public:
	// Retail derived view: primary vptr at this+0; the base is declaration-only.
	AITNGuardIdleState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardIdleState"))
	{
		m_vftable = &g_AITNGuardIdleStateVTable;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x30];
};

class AITNGuardInnerState : public Rva000A19E0StateBase
{
public:
	// Retail derived view: primary vptr at this+0 and shared secondary table at
	// this+0x24; this secondary object is distinct from the primary Inner table.
	AITNGuardInnerState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardInner"))
	{
		m_vftable = &g_AITNGuardInnerStateVTable;
		m_field24 = &g_Rva0109B558StateSecondaryVTable;
		m_field28 = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x20];
	int *volatile m_field24;
	volatile unsigned int m_field28;
	char m_tail[0x8];
};

class AITNGuardOuterState : public Rva000A19E0StateBase
{
public:
	// Retail derived view: primary vptr at this+0, shared secondary table at
	// this+0x24, and scalar fields at this+0x28/+0x2c.
	AITNGuardOuterState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardOuter"))
	{
		m_vftable = &g_AITNGuardOuterStateVTable;
		m_field24 = &g_Rva0109B558StateSecondaryVTable;
		m_field28 = 0;
		m_field2c = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x20];
	int *volatile m_field24;
	volatile unsigned int m_field28;
	volatile unsigned int m_field2c;
};

class AITNGuardPickUpCrateState : public Rva0014F280StateBase
{
public:
	// Retail derived view: primary vptr at this+0 and field at this+0x50.
	AITNGuardPickUpCrateState(void *machine)
		: Rva0014F280StateBase(machine, AsciiString("AIAttackPickUpCrateState"))
	{
		m_field50 = 0;
		m_vftable = &g_AITNGuardPickUpCrateStateVTable;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x4c];
	volatile unsigned int m_field50;
};

class AITNGuardAttackAggressorState : public Rva000A19E0StateBase
{
public:
	// Retail derived view: primary vptr at this+0, shared secondary table at
	// this+0x24, and scalar fields at this+0x28/+0x2c.
	AITNGuardAttackAggressorState(void *machine)
		: Rva000A19E0StateBase(machine, AsciiString("AITNGuardAttackAggressorState"))
	{
		m_vftable = &g_AITNGuardAttackAggressorStateVTable;
		m_field24 = &g_Rva0109B558StateSecondaryVTable;
		m_field28 = 0;
		m_field2c = 0;
	}

private:
	int *volatile m_vftable;
	char m_gap0[0x20];
	int *volatile m_field24;
	volatile unsigned int m_field28;
	volatile unsigned int m_field2c;
};

struct Coord3D
{
	float x, y, z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

__declspec(novtable) class AITNGuardMachine : public StateMachine
{
public:
	AITNGuardMachine(Object *owner);

private:
	Coord3D m_positionToGuard;
	volatile unsigned int m_nemesisToAttack;
	volatile unsigned int m_guardMode;
};

// Retail constructor entry: ??0AITNGuardMachine@@QAE@PAVObject@@@Z.
AITNGuardMachine::AITNGuardMachine(Object *owner)
	: StateMachine(owner, AsciiString("AITNGuardMachine"), false)
{
	*reinterpret_cast<volatile int *volatile *>(this) = &g_AITNGuardMachineVTable;
	m_nemesisToAttack = 0;
	m_guardMode = 0;

	m_positionToGuard.zero();

	static const StateConditionInfo attackAggressors[] =
	{
		StateConditionInfo(Rva0018A0F0StatePredicate, 0x138d, 0),
		StateConditionInfo(0, 0, 0)
	};

	defineState(0x138b, new AITNGuardReturnState(this), 0x1389, 0x1388,
		attackAggressors);
	defineState(0x1389, new AITNGuardIdleState(this), 0x1388, 0x138b, 0);
	defineState(0x1388, new AITNGuardInnerState(this), 0x138a, 0x138a,
		attackAggressors);
	defineState(0x138a, new AITNGuardOuterState(this), 0x138c, 0x138c, 0);
	defineState(0x138c, new AITNGuardPickUpCrateState(this), 0x138b, 0x138b, 0);
	defineState(0x138d, new AITNGuardAttackAggressorState(this), 0x138b,
		0x138b, 0);
}
