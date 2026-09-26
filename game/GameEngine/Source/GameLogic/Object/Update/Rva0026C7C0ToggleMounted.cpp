// Clean C++ reconstruction of the body at retail RVA 0x0026C7C0.
// The original member name is not recovered, so the owner and method retain
// address-derived identity while the observed ToggleMounted layout is used.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class BfmeE1166
{
public:
	BfmeE1166(int tag, unsigned int a02, unsigned int a03,
		unsigned int a04, unsigned int a05, unsigned int a06);
	unsigned int m_bfme00[10];
};

class Module
{
};

class Rva0026C7C0Result
{
public:
	char m_pad00[0xb0];
	float m_value;                    // +0xb0
};

class Thing
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Rva0026C7C0Result *getResult();
	void setOrientation(float angle);
	char m_pad00[0x40];
	float m_cachedAngle;               // +0x44
};

class Object : public Thing
{
public:
	void clearModelConditionFlags(const BfmeE1166 &flags);
	Module *findModule(NameKeyType key) const;
};

class StealthUpdate
{
public:
	void receiveGrant(Bool active, UnsignedInt frames);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

extern float g_bfmeDefaultBU;       // retail 0x01075334

class Rva0026C7C0ModuleData
{
public:
	char m_pad00[0x21c];
	Int m_firstCount;                 // +0x21c
	Int m_secondCount;                // +0x220
	UnsignedInt m_stealthLimit;       // +0x224
	char m_pad228[0x1c];
	char m_modeOneEnabled;            // +0x244
	char m_modeTwoEnabled;            // +0x245
	char m_pad246[2];
	char m_stealthEnabled;            // +0x248
	char m_pad249[0xb];
	float m_endpoint;                 // +0x254
};

class Rva0026C7C0Owner
{
public:
	Rva0026C7C0ModuleData *m_moduleData; // +0x04
	Object *m_target;                    // +0x08
	char m_pad0c[0x1c];
	UnsignedInt m_progress;              // +0x28
	char m_pad2c[4];
	Int m_mode;                          // +0x30

	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	Bool bfmeAdvance();
	Bool update();
};

Bool Rva0026C7C0Owner::bfmeAdvance()
{
	Rva0026C7C0ModuleData *data = m_moduleData;
	if (m_progress <= 0)
		return false;

	--m_progress;
	UnsignedInt progress = m_progress;
	if (progress == 0)
	{
		Object *target = m_target;
		target->clearModelConditionFlags(
			BfmeE1166(0, 0x5f, 0x60, 0x61, 0x62, 0x5d));

		if (m_mode == 2)
		{
			if (data->m_modeTwoEnabled)
				m_target->setOrientation(m_target->m_cachedAngle + 3.1415927f);
			m_mode = 4;
			return false;
		}

		if (m_mode == 1)
		{
			if (data->m_modeOneEnabled)
				m_target->setOrientation(m_target->m_cachedAngle + 3.1415927f);
			m_mode = 3;
			slot17();
			return true;
		}
		return false;
	}
	else
	{
		if (data->m_stealthEnabled &&
			progress < data->m_stealthLimit)
		{
			static NameKeyType key_StealthUpdate =
				TheNameKeyGenerator->nameToKey("StealthUpdate");
			NameKeyType key = key_StealthUpdate;
			Object *target = m_target;
			StealthUpdate *stealth =
				(StealthUpdate *)target->findModule(key);
			if (stealth != 0)
				stealth->receiveGrant(false, 1);
		}
		return true;
	}
}

Bool Rva0026C7C0Owner::update()
{
	Bool result = bfmeAdvance();
	if (!result)
		return result;

	Rva0026C7C0ModuleData *data = m_moduleData;
	float start;
	float end;
	register Int count;
	if (m_mode == 2)
	{
		start = g_bfmeDefaultBU;
		count = data->m_secondCount;
		end = data->m_endpoint;
	}
	else
	{
		start = data->m_endpoint;
		count = data->m_firstCount;
		end = g_bfmeDefaultBU;
	}

	register Int progress = m_progress;
	float fraction = (float)(unsigned int)progress /
		(float)(unsigned int)count;
	float value = start + (1.0f - fraction) * (end - start);
	Rva0026C7C0Result *resultObject = m_target->getResult();
	if (resultObject != 0)
	{
		resultObject = m_target->getResult();
		resultObject->m_value = value;
	}
	return result;
}
