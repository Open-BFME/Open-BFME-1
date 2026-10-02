// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

#include "ascii_string.h"

class StateMachine;

class AIInternalMoveToState
{
public:
	// Retail's base-ctor call goes through the 0x00032182 thunk into the matched
	// ??0AIInternalMoveToState@@QAE@PAVStateMachine@@VAsciiString@@@Z at
	// 0x0014F280 (functions.csv:2314). Declaring the machine parameter with the
	// real class makes this TU call that definition instead of the one-argument
	// spelling (PAXVAsciiString@@) that nothing defines.
	AIInternalMoveToState( StateMachine *machine, AsciiString name );
};

// Retail installs its vtable at 0x0109A738, ??_7AIAttackMeleeSquishState@@6B@
// (symbols.csv:10467; this exact ctor stores it and computePath at 0x0016BD60 is
// its slot 17). That datum IS defined, as a COMDAT .rdata symbol in
// AITargetMovementDeletingDestructors.cpp, which declares the same class's
// protected destructor. No C++ declarator spells a vftable name, so the store
// keeps this TU's explicit layout (a plain leading pointer) and names the datum
// with __identifier, the same spelling convention
// GameEngineDevice/.../WorldHeightMapRva0074ACB0Load.cpp uses for
// ??_7BfmeParserBindingBaseVE@@6B@. Declaring this class polymorphic instead
// would also reference the real vftable, but VC7.1 then emits the automatic
// vptr store after every member store (c7 06 lands after 89 46 64), where retail
// has it second, so the bytes would not match.
extern "C" int __identifier("??_7AIAttackMeleeSquishState@@6B@")[];

class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	AIAttackMeleeSquishState( StateMachine *machine );

private:
	int *volatile m_vftable;
	char m_baseFields[ 0x4C ];
	volatile int m_targetId;
	volatile int m_startX;
	volatile int m_startY;
	volatile int m_startZ;
	volatile int m_goalX;
	volatile int m_goalY;
	volatile bool m_initialPass;
};

AIAttackMeleeSquishState::AIAttackMeleeSquishState( StateMachine *machine )
	: AIInternalMoveToState( machine, AsciiString( "AIAttackMeleeSquishState" ) )
{
	m_targetId = 0;
	m_vftable = __identifier("??_7AIAttackMeleeSquishState@@6B@");
	m_startX = 0;
	m_startY = 0;
	m_startZ = 0;
	m_goalX = 0;
	m_goalY = 0;
	m_initialPass = true;
}
