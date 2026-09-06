// Clean C++ reconstruction of the body at retail RVA 0x0026C7C0.
// The original member name is not recovered, so the owner and method retain
// address-derived identity while the observed ToggleMounted layout is used.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

extern float g_bfmeDefaultBU;       // retail 0x01075334

class Rva0026C7C0ModuleData
{
public:
	char m_pad00[0x21c];
	Int m_firstCount;                 // +0x21c
	Int m_secondCount;                // +0x220
	char m_pad224[0x30];
	float m_endpoint;                 // +0x254
};

class Rva0026C7C0Result
{
public:
	char m_pad00[0xb0];
	float m_value;                    // +0xb0
};

class Rva0026C7C0Target
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
};

class Rva0026C7C0Owner
{
public:
	virtual void ownerAnchor();
	Rva0026C7C0ModuleData *m_moduleData; // +0x04
	Rva0026C7C0Target *m_target;         // +0x08
	char m_pad0c[0x1c];
	Int m_progress;                      // +0x28
	char m_pad2c[4];
	Int m_mode;                          // +0x30

	Bool bfmeAdvance();
	Bool update();
};

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
