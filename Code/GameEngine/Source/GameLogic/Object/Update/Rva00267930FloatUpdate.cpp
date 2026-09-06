// Clean C++ reconstruction of the body at retail RVA 0x00267930.
// The member name is not recovered; the address-derived owner preserves the
// observed module, target, progress, mode, and value layout.
// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

extern float g_bfmeDefaultBU;       // retail 0x01075334

class Rva00267930ModuleData
{
public:
	char m_pad00[0x21c];
	Int m_firstCount;                 // +0x21c
	Int m_secondCount;                // +0x220
	char m_pad224[0x34];
	float m_endpoint;                 // +0x258
};

class Rva00267930Result
{
public:
	char m_pad00[0xb0];
	float m_value;                    // +0xb0
};

class Rva00267930Target
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
	virtual Rva00267930Result *getResult();
};

// The retail call at 0x00267935 resolves to the already-proven shared
// advance helper used by the accepted 0x0026C7C0 body.
class Rva0026C7C0Owner
{
public:
	Bool bfmeAdvance();
};

class Rva00267930Owner
{
public:
	virtual void ownerAnchor();
	Rva00267930ModuleData *m_moduleData; // +0x04
	Rva00267930Target *m_target;         // +0x08
	char m_pad0c[0x1c];
	Int m_progress;                      // +0x28
	char m_pad2c[4];
	Int m_mode;                          // +0x30
	char m_pad34[0xb8];
	float m_value;                       // +0xec

	Bool update();
};

Bool Rva00267930Owner::update()
{
	Bool result = ((Rva0026C7C0Owner *)this)->bfmeAdvance();
	if (!result)
		return result;

	Rva00267930ModuleData *data = m_moduleData;
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
	m_value = start + (1.0f - fraction) * (end - start);
	Rva00267930Result *resultObject = m_target->getResult();
	if (resultObject != 0)
	{
		float value = m_value;
		resultObject = m_target->getResult();
		resultObject->m_value = value;
	}
	return result;
}
