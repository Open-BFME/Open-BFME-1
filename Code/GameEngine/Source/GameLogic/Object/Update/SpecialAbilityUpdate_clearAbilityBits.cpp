// cl: /DNDEBUG /MD /EHsc
// Retail 0x0026D950: SpecialAbilityUpdate::onExit then clear Object+0x12c bit
// selected by moduleData+0x258 (1/2/3 -> 0x200/0x400/0x800).

typedef bool Bool;

class Object
{
public:
	void notifyModelConditionChanged(void);

	char m_pad[0x12c];
	unsigned int m_privateStatus;			// +0x12c
};

class SpecialAbilityUpdateModuleData
{
public:
	char m_pad[0x258];
	int m_which;							// +0x258
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate
{
public:
	void clearAbilityBits(Bool a, Bool b);

private:
	void onExit(Bool a, Bool b);			// ILT 0x0000F975

	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;	// +0x04
	Object *m_obj;							// +0x08
};

// ?clearAbilityBits@SpecialAbilityUpdate@@QAEX_N0@Z
void SpecialAbilityUpdate::clearAbilityBits(Bool a, Bool b)
{
	onExit(a, b);

	Object *obj = m_obj;
	switch (m_moduleData->m_which)
	{
	case 3:
		if (obj->m_privateStatus & 0x800)
		{
			obj->m_privateStatus &= ~0x800u;
			obj->notifyModelConditionChanged();
		}
		return;
	case 2:
		if (obj->m_privateStatus & 0x400)
		{
			obj->m_privateStatus &= ~0x400u;
			obj->notifyModelConditionChanged();
		}
		return;
	case 1:
		if (obj->m_privateStatus & 0x200)
		{
			obj->m_privateStatus &= ~0x200u;
			obj->notifyModelConditionChanged();
		}
		return;
	default:
		return;
	}
}
