// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class AIAttackState;

class Object;

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<90>
{
public:
	virtual void *slot168() = 0;
};

class Object
{
public:
	char m_padding000[0x204];
	AIUpdateInterface *m_ai;
};

class AttackFireWhileMovingMachine
{
public:
	AttackFireWhileMovingMachine(Object *owner, AIAttackState *attack,
		AsciiString name);

private:
	char m_body[0x44];
};

class AttackMeleeStateMachine
{
public:
	AttackMeleeStateMachine(Object *owner, AIAttackState *attack,
		AsciiString name);

private:
	char m_body[0x44];
};

class Rva001812B0AIHordeMachine
{
public:
	Rva001812B0AIHordeMachine(Object *owner, AIAttackState *attack,
		AsciiString name);

private:
	char m_body[0x44];
};

class AttackHordeStateMachine
{
public:
	AttackHordeStateMachine(Object *owner, AIAttackState *attack,
		AsciiString name);

private:
	char m_body[0x44];
};

class AttackFireWhileChargingMachine
{
public:
	AttackFireWhileChargingMachine(Object *owner, AIAttackState *attack,
		AsciiString name, bool flag);

private:
	char m_body[0x44];
};

class Rva00180810AIAttackMachine
{
public:
	Rva00180810AIAttackMachine(Object *owner, AIAttackState *attack,
		AsciiString name, unsigned char follow, unsigned char attackingObject,
		unsigned char forceAttacking);

private:
	char m_body[0x44];
};

#pragma comment(linker, "/alternatename:??0Rva001812B0AIHordeMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@@Z=?j_000268dc@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva00180810AIAttackMachine@@QAE@PAVObject@@PAVAIAttackState@@VAsciiString@@EEE@Z=?j_00010ebf@@YAXXZ")

class AIAttackState
{
	protected:
	void createAttackMachine(Object *owner);

private:
	char m_padding000[0x28];
	void *m_attackMachine;
	char m_padding02c[0x18];
	unsigned char m_bfmeAttackState44;
	unsigned char m_isAttackingObject;
	unsigned char m_bfmeAttackState46;
	char m_padding047[0x09];
	unsigned int m_bfmeAttackState50;
};

// ?createAttackMachine@AIAttackState@@IAEXPAVObject@@@Z
void AIAttackState::createAttackMachine(Object *owner)
{
	if (m_bfmeAttackState50 == 1)
	{
		m_attackMachine = new AttackFireWhileMovingMachine(
			owner, this, AsciiString("AIAttackMovingMachine"));
	}
	else if (m_bfmeAttackState50 == 2)
	{
		m_attackMachine = new AttackMeleeStateMachine(
			owner, this, AsciiString("AIMeleeMachine"));
	}
	else if (m_bfmeAttackState50 == 5)
	{
		m_attackMachine = new Rva001812B0AIHordeMachine(
			owner, this, AsciiString("AIHordeMachine"));
	}
	else if (m_bfmeAttackState50 == 4)
	{
		m_attackMachine = new AttackHordeStateMachine(
			owner, this, AsciiString("AIAttackContesterMachine"));
	}
	else if (m_bfmeAttackState50 == 6)
	{
		m_attackMachine = new AttackFireWhileChargingMachine(
			owner, this, AsciiString("AIAttackFireWhileCharging"), true);
	}
	else if (m_bfmeAttackState50 == 0)
	{
		m_attackMachine = owner->m_ai->slot168();
	}
	else
	{
		m_attackMachine = new Rva00180810AIAttackMachine(
			owner, this, AsciiString("AIAttackMachine"),
			m_bfmeAttackState44, m_isAttackingObject,
			m_bfmeAttackState46);
	}
}
