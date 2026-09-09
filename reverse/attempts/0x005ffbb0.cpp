// ??0BaseY005E7620@@QAE@PAVOwnerY005E7620@@@Z
// partial score=0.45 date=2026-09-09
// Probe for the address-derived Q4 constructor at retail 0x005FFBB0.
// The three-vtable layout is established by the adjacent Rva005FFAC0 and
// Rva005E99D0 bodies; the semantic owner/class names remain unresolved.

#include "../Code/GameEngine/Source/Common/System/game_client_random_variable.h"

class ParticleSystem;
ParticleSystem *Make00001B18();

class ParticleSystemHandle
{
public:
	~ParticleSystemHandle() throw();

	ParticleSystem *operator->() const
	{
		if ( m_system != 0 )
			return m_system;
		return Make00001B18();
	}

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
	unsigned int m_padding;
};

class ParticleSystem
{
public:
	virtual ~ParticleSystem();

	char m_pad00[ 0x24 ];
	GameClientRandomVariable m_value;
	char m_pad34[ 0x14c ];
	float m_scale;
	float m_bias;
};

class Rva005FB4D0HandleSource
{
public:
	virtual void sourceSlot();
	ParticleSystemHandle makeHandle();

	ParticleSystem *m_system;
};

class OwnerY005E7620 : public Rva005FB4D0HandleSource
{
public:
	char m_pad08[ 0x18 ];
	GameClientRandomVariable m_value0;
	GameClientRandomVariable m_value1;
	GameClientRandomVariable m_value2;
	GameClientRandomVariable m_value3;
	GameClientRandomVariable m_value4;
	unsigned int m_field5c;
};

class BaseY005FFBB0Primary
{
public:
	virtual void baseSlot();
};

class BaseY005FFBB0Secondary
{
public:
	virtual void secondarySlot();
};

class BaseY005FFBB0Values
{
public:
	BaseY005FFBB0Values()
		: m_field0( 0 ), m_field1( 0 ), m_field2( 0 ), m_field3( 0 ),
		  m_field4( 0 ), m_field5( 0 ), m_field6( 1 )
	{
	}

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
	char m_pad00[ 0xab4 ];
	float m_scale;
};

extern GlobalData *TheWritableGlobalData;

class BaseY005E7620 : public BaseY005FFBB0Primary,
	public BaseY005FFBB0Secondary,
	public BaseY005FFBB0Values
{
public:
	BaseY005E7620( OwnerY005E7620 *owner );
	virtual void baseSlot();
};

BaseY005E7620::BaseY005E7620( OwnerY005E7620 *owner )
{
	ParticleSystemHandle handle = owner->makeHandle();
	ParticleSystem *system = handle.m_system;
	if ( system == 0 )
		system = Make00001B18();

	m_field0 = system->m_value.getValue()
		* TheWritableGlobalData->m_scale * system->m_scale;
	ParticleSystem *scaleSystem = handle.m_system;
	if ( scaleSystem == 0 )
		scaleSystem = Make00001B18();
	m_field1 = owner->m_value0.getValue()
		* TheWritableGlobalData->m_scale * scaleSystem->m_scale;
	m_field2 = owner->m_value1.getValue();
	ParticleSystem *biasSystem = handle.m_system;
	if ( biasSystem == 0 )
		biasSystem = Make00001B18();
	m_field0 += biasSystem->m_bias;
	m_field3 = owner->m_value2.getValue();
	m_field4 = owner->m_value3.getValue();
	m_field5 = owner->m_value4.getValue();
	m_field6 = owner->m_field5c;
}
