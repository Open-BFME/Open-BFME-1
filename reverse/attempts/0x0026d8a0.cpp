// ?setAbilityBits@SpecialAbilityUpdate@@QAEXXZ
// partial score=0.97 date=2026-09-04
// ?setAbilityBits@SpecialAbilityUpdate@@QAEXXZ
// Started from reverse/attempts/0x0026d8a0.cpp; first probe lever: local definition order.
// cl: /DNDEBUG /MD /EHsc

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
