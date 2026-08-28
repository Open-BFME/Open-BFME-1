// Five 36-byte bodies with one shape: test bit 28 of the word at +0x114 of
// the object handed in, and when it is set clear it and call
// Object::notifyModelConditionChanged on that object.
//
// The argument goes into ecx and stays there for the call, so the callee is a
// member of the argument's class, not of any class these belong to. They clean
// their own single argument (ret 4) while never using an incoming ecx, which
// makes them __stdcall. The call is a plain call rather than a tail jump
// because the ret still has an argument to pop.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void notifyModelConditionChanged(void);				// ILT 0x0002191D

	char m_bfmeHead[0x114];
	unsigned int m_bfmeFlags;					// +0x114
};

// ?Gen_001b9560@@YGXPAVObject@@@Z
void __stdcall Gen_001b9560(Object *object)
{
	if (object->m_bfmeFlags & 0x10000000)
	{
		object->m_bfmeFlags &= ~0x10000000;

		object->notifyModelConditionChanged();
	}
}

// ?Gen_001b9a90@@YGXPAVObject@@@Z
void __stdcall Gen_001b9a90(Object *object)
{
	if (object->m_bfmeFlags & 0x10000000)
	{
		object->m_bfmeFlags &= ~0x10000000;

		object->notifyModelConditionChanged();
	}
}

// ?Gen_001b9ac0@@YGXPAVObject@@@Z
void __stdcall Gen_001b9ac0(Object *object)
{
	if (object->m_bfmeFlags & 0x10000000)
	{
		object->m_bfmeFlags &= ~0x10000000;

		object->notifyModelConditionChanged();
	}
}

// ?Gen_001b9af0@@YGXPAVObject@@@Z
void __stdcall Gen_001b9af0(Object *object)
{
	if (object->m_bfmeFlags & 0x10000000)
	{
		object->m_bfmeFlags &= ~0x10000000;

		object->notifyModelConditionChanged();
	}
}

// ?Gen_001b9b20@@YGXPAVObject@@@Z
void __stdcall Gen_001b9b20(Object *object)
{
	if (object->m_bfmeFlags & 0x10000000)
	{
		object->m_bfmeFlags &= ~0x10000000;

		object->notifyModelConditionChanged();
	}
}
