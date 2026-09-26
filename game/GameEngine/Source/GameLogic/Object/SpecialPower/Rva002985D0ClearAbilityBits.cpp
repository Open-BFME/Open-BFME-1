// cl: /DNDEBUG /MD /EHsc
// COUNT lane near-twin of ?clearAbilityBits@SpecialAbilityUpdate@@QAEX_N0@Z
// @ 0x0026D950 (Rva0026D950ClearAbilityBits.cpp). Same onExit-then-switch
// shape; this target's module-data selector sits at +0x254 (not +0x258),
// its Object status field sits at +0x128 (not +0x12c), and the three
// selectable bits are 0x400/0x200/0x100 for which==3/2/1 (not
// 0x800/0x400/0x200) -- confirmed against the disassembly bit-by-bit.

typedef bool Bool;

class Object
{
public:
	void notifyModelConditionChanged(void);

	char m_pad[0x128];
	unsigned int m_privateStatus;			// +0x128
};

class Rva002985D0ModuleData
{
public:
	char m_pad[0x254];
	int m_which;							// +0x254
};

class Rva002985D0Update
{
public:
	void clearAbilityBits(Bool a, Bool b);

private:
	void onExit(Bool a, Bool b);			// ILT 0x0000F975

	void *m_vtable;
	Rva002985D0ModuleData *m_moduleData;	// +0x04
	Object *m_obj;							// +0x08
};

// ?clearAbilityBits@Rva002985D0Update@@QAEX_N0@Z
void Rva002985D0Update::clearAbilityBits(Bool a, Bool b)
{
	onExit(a, b);

	Object *obj = m_obj;
	switch (m_moduleData->m_which)
	{
	case 3:
		if (obj->m_privateStatus & 0x400)
		{
			obj->m_privateStatus &= ~0x400u;
			obj->notifyModelConditionChanged();
		}
		return;
	case 2:
		if (obj->m_privateStatus & 0x200)
		{
			obj->m_privateStatus &= ~0x200u;
			obj->notifyModelConditionChanged();
		}
		return;
	case 1:
		if (obj->m_privateStatus & 0x100)
		{
			obj->m_privateStatus &= ~0x100u;
			obj->notifyModelConditionChanged();
		}
		return;
	default:
		return;
	}
}
