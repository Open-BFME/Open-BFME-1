// cl: /DNDEBUG /MD

typedef bool Bool;
typedef float Real;
typedef unsigned int StateID;

enum
{
	INVALID_STATE_ID = 999999
};

extern const Real g_rva01075350;

class State
{
public:
	virtual void slot00() = 0;

	StateID m_id;
};

// File-static, not State::getID: retail ?getID@State@@QBEIXZ (0x00106670)
// reads +8, while this view's id at +4 is read inline by 0x002BC870.
static inline StateID stateGetID(const State *state) { return state->m_id; }

class Rva002BC870Target
{
public:
	unsigned char m_head[0x3f0];
	unsigned int m_bits3F0;
	Bool flag4() const { return (Bool)((m_bits3F0 >> 4) & 1); }
	Bool flag6() const { return (Bool)((m_bits3F0 >> 6) & 1); }
	unsigned char m_pad3F4[0x46c - 0x3f4];
	unsigned char m_value46C;
};

class AIUpdateInterface
{
public:
#define AI_SLOT(N) virtual void slot##N() = 0
	AI_SLOT(00); AI_SLOT(01); AI_SLOT(02); AI_SLOT(03); AI_SLOT(04); AI_SLOT(05);
	AI_SLOT(06); AI_SLOT(07); AI_SLOT(08); AI_SLOT(09); AI_SLOT(10); AI_SLOT(11);
	AI_SLOT(12); AI_SLOT(13); AI_SLOT(14); AI_SLOT(15); AI_SLOT(16); AI_SLOT(17);
	AI_SLOT(18); AI_SLOT(19); AI_SLOT(20); AI_SLOT(21); AI_SLOT(22); AI_SLOT(23);
	AI_SLOT(24); AI_SLOT(25); AI_SLOT(26); AI_SLOT(27); AI_SLOT(28); AI_SLOT(29);
	AI_SLOT(30); AI_SLOT(31); AI_SLOT(32); AI_SLOT(33); AI_SLOT(34); AI_SLOT(35);
	AI_SLOT(36); AI_SLOT(37); AI_SLOT(38); AI_SLOT(39); AI_SLOT(40); AI_SLOT(41);
	AI_SLOT(42); AI_SLOT(43); AI_SLOT(44); AI_SLOT(45); AI_SLOT(46); AI_SLOT(47);
	AI_SLOT(48); AI_SLOT(49); AI_SLOT(50); AI_SLOT(51); AI_SLOT(52); AI_SLOT(53);
	AI_SLOT(54); AI_SLOT(55); AI_SLOT(56); AI_SLOT(57); AI_SLOT(58); AI_SLOT(59);
	AI_SLOT(60); AI_SLOT(61); AI_SLOT(62); AI_SLOT(63); AI_SLOT(64); AI_SLOT(65);
	AI_SLOT(66); AI_SLOT(67); AI_SLOT(68); AI_SLOT(69); AI_SLOT(70); AI_SLOT(71);
	AI_SLOT(72); AI_SLOT(73); AI_SLOT(74); AI_SLOT(75);
	virtual Bool slot76() = 0;
	AI_SLOT(77); AI_SLOT(78); AI_SLOT(79); AI_SLOT(80); AI_SLOT(81); AI_SLOT(82);
	AI_SLOT(83);
#undef AI_SLOT
	virtual Rva002BC870Target *slot84() = 0;
};

class Object
{
public:
	AIUpdateInterface *getAI() const { return m_ai; }

	unsigned char m_head[0x204];
	AIUpdateInterface *m_ai;
};

// Retail 0x002BC870 (139 bytes): slot 11 of the AIAttackSwoopThenIdleStateMachine
// vtable 0x010C7460 that AIAttackSwoopThenIdleStateMachineCtor.cpp proves
// (rdata 0x00CC748C via ILT 0x00034810).  True in state 0; in state 1013 it
// asks the owner's AI (slots 76 and 84) for a target and is true while that
// target has flag 4 without flag 6, or a nonzero +0x46C byte.  The slot name
// is not recovered and keeps the address.
class AIAttackSwoopThenIdleStateMachine
{
public:
#define SM_SLOT(N) virtual void slot##N() = 0
	SM_SLOT(00); SM_SLOT(01); SM_SLOT(02); SM_SLOT(03); SM_SLOT(04); SM_SLOT(05);
	SM_SLOT(06); SM_SLOT(07); SM_SLOT(08); SM_SLOT(09); SM_SLOT(10);
#undef SM_SLOT
	virtual Bool rva002BC870() const;

	StateID getCurrentStateID() const { return m_currentState ? stateGetID(m_currentState) : INVALID_STATE_ID; }

private:
	unsigned char m_pad04[0x0c];
	Object *m_owner;
	unsigned char m_pad14[0x08];
	State *m_currentState;
};

Bool AIAttackSwoopThenIdleStateMachine::rva002BC870() const
{
	switch (getCurrentStateID())
	{
		case 0:
			return true;

		case 1013:
		{
			AIUpdateInterface *ai = m_owner->getAI();
			if (ai && ai->slot76())
			{
				Rva002BC870Target *target = ai->slot84();
				if (target)
				{
					if (!target->flag6() && target->flag4())
						return true;
					if ((Real)target->m_value46C != g_rva01075350)
						return true;
					return false;
				}
			}
			break;
		}
	}
	return false;
}
