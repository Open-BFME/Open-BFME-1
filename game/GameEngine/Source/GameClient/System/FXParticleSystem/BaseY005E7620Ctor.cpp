// ??0BaseY005E7620@@QAE@PAVOwnerY005E7620@@@Z
// Constructor at RVA 0x005FFBB0 (346 bytes), named by the matched
// HostY005E7620::create caller in Q4NewInlineCtorAdjusted.cpp.
// Retail unwind states destroy the composite head at +0, values at +8,
// then the 12-byte handle. See tools/eh_info.py 0x005FFBB0.
// makeHandle's complete 75-byte native return-by-value body independently
// matches 0x005FB4D0: it only links the handle, makes no calls and cannot
// throw a C++ exception. Its hidden return pointer explains the stack store
// in that callee; it is not a void method with an explicit node argument.
// Final tables: 0x011129A4 / 0x011127E0 / 0x011127CC.
// Keep all four handle resolutions and capture each scale before getValue:
// calls can change the handle or referenced fields. GlobalData +0xAB4 is
// m_particleScale in field_names.csv; no shipped INI value is asserted.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include "../../../Common/System/game_client_random_variable.h"

class BfmeHandleERU;

// The helper's independently matched ABI uses this 0xA0-byte host view only
// for the intrusive handle list.  The constructor below reads the same host
// through the native ParticleSystem view for its random values and floats.
struct Rva005FB4D0Host
{
	char prefix[0x98];
	BfmeHandleERU *head;
	BfmeHandleERU *tail;
};

class BfmeHandleERU
{
public:
	BfmeHandleERU(Rva005FB4D0Host *host) : m_host(host)
	{
		if ( host )
		{
			m_previous = host->tail;
			m_next = 0;
			host->tail = this;
			if ( m_previous )
				m_previous->m_next = this;
			else
				m_host->head = this;
		}
		else
		{
			m_next = 0;
			m_previous = 0;
		}
	}
	~BfmeHandleERU() throw();

	Rva005FB4D0Host *m_host;
	BfmeHandleERU *m_previous;
	BfmeHandleERU *m_next;
};

class Rva005FB4D0Owner
{
public:
	BfmeHandleERU makeHandle() throw();

	int prefix;
	Rva005FB4D0Host *m_host;
};

class ParticleSystem
{
public:
	virtual ~ParticleSystem();

	char m_pad00[0x24];
	GameClientRandomVariable m_random;
	char m_pad34[0x14c];
	float m_field180;
	float m_field184;
};

ParticleSystem *Make00001B18();

class OwnerY005E7620 : public Rva005FB4D0Owner
{
public:
	char m_pad08[0x18];
	GameClientRandomVariable m_random20;
	GameClientRandomVariable m_random2c;
	GameClientRandomVariable m_random38;
	GameClientRandomVariable m_random44;
	GameClientRandomVariable m_random50;
	unsigned int m_field5c;
};

class BaseY005FFBB0Primary
{
public:
	virtual void primarySlot();
};

class BaseY005FFBB0Secondary
{
public:
	virtual void secondarySlot();
};

class BaseY005FFBB0Composite
	: public BaseY005FFBB0Primary,
	  public BaseY005FFBB0Secondary
{
public:
	BaseY005FFBB0Composite() {}
	virtual ~BaseY005FFBB0Composite();
};

class BaseY005FFBB0Values
{
public:
	BaseY005FFBB0Values() throw()
		: m_field0( 0 ), m_field1( 0 ), m_field2( 0 ), m_field3( 0 ),
		  m_field4( 0 ), m_field5( 0 ), m_field6( 1 )
	{
	}

	virtual ~BaseY005FFBB0Values();
	virtual void valueSlot0();
	virtual void valueSlot1();
	virtual void valueSlot2();
	virtual void valueSlot3();

protected:
	float m_field0;
	float m_field1;
	float m_field2;
	float m_field3;
	float m_field4;
	float m_field5;
	unsigned int m_field6;
};

class GlobalData
{
public:
	char m_pad00[0xab4];
	float m_particleScale;
};

extern GlobalData *TheWritableGlobalData;

class BaseY005E7620
	: public BaseY005FFBB0Composite,
	  public BaseY005FFBB0Values
{
public:
	BaseY005E7620( OwnerY005E7620 *owner );
	virtual ~BaseY005E7620();
};

BaseY005E7620::BaseY005E7620( OwnerY005E7620 *owner )
{
	BfmeHandleERU handle = owner->makeHandle();
	ParticleSystem *system = !handle.m_host
		? Make00001B18() : (ParticleSystem *)handle.m_host;

	ParticleSystem *firstScaleSystem = (ParticleSystem *)handle.m_host;
	if ( firstScaleSystem == 0 )
		firstScaleSystem = Make00001B18();
	float firstScale = firstScaleSystem->m_field180;
	m_field0 = system->m_random.getValue()
			* TheWritableGlobalData->m_particleScale * firstScale;
	ParticleSystem *scaleSystem = (ParticleSystem *)handle.m_host;
	if ( scaleSystem == 0 )
		scaleSystem = Make00001B18();
	float scale = scaleSystem->m_field180;
	m_field1 = owner->m_random20.getValue()
			* TheWritableGlobalData->m_particleScale * scale;
	m_field2 = owner->m_random2c.getValue();
	ParticleSystem *biasSystem = (ParticleSystem *)handle.m_host;
	if ( biasSystem == 0 )
		biasSystem = Make00001B18();
	m_field0 += biasSystem->m_field184;
	m_field3 = owner->m_random38.getValue();
	m_field4 = owner->m_random44.getValue();
	m_field5 = owner->m_random50.getValue();
	m_field6 = owner->m_field5c;
}
