// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// The four slots below are the FXParticleSystem module bases' vtable entries.
// Retail fills them from the DLL's own vftables, whose slots are ILT thunks
// (?j_<rva>@@YAXXZ) into that module; a member function here cannot carry such
// a name, and this TU has no body for any of them -- the concrete modules
// supply the overrides.  Declaring the slots pure says exactly that, and the
// constructor's bytes are unchanged: it only stamps the vftable addresses.
struct ParticleModuleStateSource005FD300
{
	char m_pad00[ 8 ];
	unsigned char m_flag08;
	char m_pad09[ 7 ];
	unsigned int m_value10;
	unsigned int m_value14;
	unsigned char m_flag18;
};

class ParticleModuleOwnerBase005FD300
{
public:
	ParticleModuleOwnerBase005FD300( void *owner ) : m_owner( owner ) {}
	virtual void ownerSlot() = 0;

private:
	void *m_owner;
};

class ParticleModuleFlagBase005FD300
{
public:
	ParticleModuleFlagBase005FD300() : m_flag( 1 ) {}
	virtual void flagSlot() = 0;

protected:
	unsigned char m_flag;
	char m_pad[ 3 ];
};

class ParticleModuleValuesBase005FD300
{
public:
	ParticleModuleValuesBase005FD300()
		: m_value0( 0 ), m_value1( 0 ), m_flag( 0 ) {}
	virtual void valuesSlot() = 0;

protected:
	unsigned int m_value0;
	unsigned int m_value1;
	unsigned char m_flag;
	char m_pad[ 3 ];
	unsigned char m_trailingFlag;
};

class ParticleModuleState005FD300
	: public ParticleModuleOwnerBase005FD300,
	  public ParticleModuleFlagBase005FD300,
	  public ParticleModuleValuesBase005FD300
{
public:
	ParticleModuleState005FD300( void *owner,
		const ParticleModuleStateSource005FD300 *source );
	virtual void stateSlot() = 0;
};

ParticleModuleState005FD300::ParticleModuleState005FD300( void *owner,
	const ParticleModuleStateSource005FD300 *source )
	: ParticleModuleOwnerBase005FD300( owner )
{
	m_value0 = source->m_value10;
	m_value1 = source->m_value14;
	ParticleModuleFlagBase005FD300::m_flag = source->m_flag08;
	ParticleModuleValuesBase005FD300::m_flag = source->m_flag18;
	m_trailingFlag = 1;
}
