// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?getMoodMatrixActionAdjustment@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// BFME's ThingTemplate kind-of words begin at +0xc8.  Keep the override
// walk and the AI object at their retail offsets in this TU; the vendored
// Zero Hour headers describe a different object layout.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	void *m_vtable;
	BfmeOverridable *m_nextOverride;
};

enum KindOfType
{
	KINDOF_INFANTRY = 8,
	KINDOF_IGNORED_IN_GUI = 47
};

class BfmeThingTemplate : public BfmeOverridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindof[(UnsignedInt)kind >> 5]
			& (1UL << ((UnsignedInt)kind & 31))) != 0;
	}

	unsigned char m_unreconstructed_008[0xc0];
	UnsignedInt m_kindof[6];
};

class BfmeObject
{
public:
	BfmeThingTemplate *finalTemplate() const
	{
		BfmeThingTemplate *tmpl = (BfmeThingTemplate *)m_template;
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
			tmpl = (BfmeThingTemplate *)tmpl->m_nextOverride->friend_getFinalOverride();
		return tmpl;
	}

	Bool isKindOf(KindOfType kind) const { return finalTemplate()->isKindOf(kind); }

	void *m_vtable;
	BfmeOverridable *m_template;
};

enum MoodMatrixAction
{
	MM_Action_Idle,
	MM_Action_Move,
	MM_Action_Attack,
	MM_Action_AttackMove
};

enum MoodMatrixParameter
{
	MM_Controller_Player = 0x00000001,
	MM_Mood_Sleep = 0x00000100,
	MM_Mood_Passive = 0x00000200,
	MM_Mood_Normal = 0x00000400,
	MM_Mood_Alert = 0x00000800,
	MM_Mood_Aggressive = 0x00001000,
	MM_Mood_Unreconstructed = 0x00002000,
	MM_Mood_Bitmask = 0x00001f00
};

enum MoodActionAdjustment
{
	MAA_Action_Ok = 0x00000001,
	MAA_Action_To_Idle = 0x00000002,
	MAA_Action_To_AttackMove = 0x00000004,
	MAA_Affect_Range_IgnoreAll = 0x00000010,
	MAA_Affect_Range_WaitForAttack = 0x00000020,
	MAA_Affect_Range_Alert = 0x00000040,
	MAA_Affect_Range_Aggressive = 0x00000080
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	BfmeObject *getObject() const { return m_object; }
	UnsignedInt getMoodMatrixValue() const;
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;

	void *m_vtable;
	unsigned char m_unreconstructed_004[4];
	BfmeObject *m_object;
};

UnsignedInt AIUpdateInterface::getMoodMatrixActionAdjustment(MoodMatrixAction action) const
{
	BfmeObject *obj = getObject();
	if (obj->isKindOf(KINDOF_INFANTRY) && obj->isKindOf(KINDOF_IGNORED_IN_GUI))
	{
		return MAA_Action_Ok;
	}

	UnsignedInt moodMatrix = getMoodMatrixValue();
	UnsignedInt returnVal = 0;

	if (moodMatrix & MM_Controller_Player)
	{
		returnVal = MAA_Action_Ok;
		return returnVal;
	}

	returnVal = MAA_Action_Ok;
	switch (action)
	{
		case MM_Action_Idle:
		{
			switch (moodMatrix & MM_Mood_Bitmask)
			{
				case MM_Mood_Sleep:
					returnVal = MAA_Action_Ok | MAA_Affect_Range_IgnoreAll;
					break;
				case MM_Mood_Passive:
					returnVal = MAA_Action_Ok | MAA_Affect_Range_WaitForAttack;
					break;
				case MM_Mood_Normal:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Alert:
					returnVal = MAA_Action_Ok | MAA_Affect_Range_Alert;
					break;
				case MM_Mood_Aggressive:
					returnVal = MAA_Action_Ok | MAA_Affect_Range_Aggressive;
					break;
				case MM_Mood_Unreconstructed:
					returnVal = MAA_Action_Ok;
					break;
			}
			break;
		}
		case MM_Action_Move:
		{
			switch (moodMatrix & MM_Mood_Bitmask)
			{
				case MM_Mood_Sleep:
					returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll;
					break;
				case MM_Mood_Passive:
					returnVal = MAA_Action_Ok | MAA_Affect_Range_WaitForAttack;
					break;
				case MM_Mood_Normal:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Alert:
					returnVal = MAA_Action_To_AttackMove | MAA_Affect_Range_Alert;
					break;
				case MM_Mood_Aggressive:
					returnVal = MAA_Action_To_AttackMove | MAA_Affect_Range_Aggressive;
					break;
				case MM_Mood_Unreconstructed:
					returnVal = MAA_Action_Ok;
					break;
			}
			break;
		}
		case MM_Action_Attack:
		{
			switch (moodMatrix & MM_Mood_Bitmask)
			{
				case MM_Mood_Sleep:
					returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll;
					break;
				case MM_Mood_Passive:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Normal:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Alert:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Aggressive:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Unreconstructed:
					returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll;
					break;
			}
			break;
		}
		case MM_Action_AttackMove:
		{
			switch (moodMatrix & MM_Mood_Bitmask)
			{
				case MM_Mood_Sleep:
					returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll;
					break;
				case MM_Mood_Passive:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Normal:
					returnVal = MAA_Action_Ok;
					break;
				case MM_Mood_Alert:
					returnVal = MAA_Action_Ok | MAA_Affect_Range_Alert;
					break;
				case MM_Mood_Aggressive:
					returnVal = MAA_Action_Ok | MAA_Affect_Range_Aggressive;
					break;
				case MM_Mood_Unreconstructed:
					returnVal = MAA_Action_To_Idle | MAA_Affect_Range_IgnoreAll;
					break;
			}
			break;
		}
	}

	return returnVal;
}
