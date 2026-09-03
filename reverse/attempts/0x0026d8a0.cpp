// ?setAbilityBits@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.97 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Partial 132/135: SET twin of clearAbilityBits. Logic recovered (begin, flag25c
// gate, switch +0x258 -> or 0x800/0x400/0x200 into Object+0x12c, jmp notify).
// Residue: retail keeps mask in eax (mov eax,imm / test eax,edx / or edx,eax);
// MSVC folds to test ah / or imm (-3B). Same wall as HordeGarrisonContain ctor.

class Object
{
public:
	void notifyModelConditionChanged(void);
	char m_pad[0x12c];
	unsigned int m_privateStatus;
};

class SpecialAbilityUpdateModuleData
{
public:
	char m_pad[0x258];
	int m_which;
	unsigned char m_flag25c;
};

class SpecialAbilityUpdate
{
public:
	void setAbilityBits(void);
	void begin(void);
private:
	void *m_vtable;
	SpecialAbilityUpdateModuleData *m_moduleData;
	Object *m_obj;
	char m_pad0C[0x18];
	void *m_field24;
};

void SpecialAbilityUpdate::setAbilityBits(void)
{
	begin();
	SpecialAbilityUpdateModuleData *md = m_moduleData;
	Object *obj = m_obj;
	if (md->m_flag25c && m_field24)
		return;
	switch (md->m_which)
	{
	case 3:
	{
		unsigned int bits = obj->m_privateStatus;
		unsigned int mask = 0x800;
		if (bits & mask)
			return;
		obj->m_privateStatus = bits | mask;
		obj->notifyModelConditionChanged();
		return;
	}
	case 2:
	{
		unsigned int bits = obj->m_privateStatus;
		unsigned int mask = 0x400;
		if (bits & mask)
			return;
		obj->m_privateStatus = bits | mask;
		obj->notifyModelConditionChanged();
		return;
	}
	case 1:
	{
		unsigned int bits = obj->m_privateStatus;
		unsigned int mask = 0x200;
		if (bits & mask)
			return;
		obj->m_privateStatus = bits | mask;
		obj->notifyModelConditionChanged();
		return;
	}
	}
}
