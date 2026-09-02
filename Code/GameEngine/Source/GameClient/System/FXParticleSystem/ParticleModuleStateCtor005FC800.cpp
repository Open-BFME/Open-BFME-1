// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct ParticleModuleStateSource005FC800
{
	char m_pad00[ 8 ];
	unsigned char m_flag08;
	char m_pad09[ 7 ];
	unsigned int m_value10;
	unsigned int m_value14;
};

class ParticleModuleOwnerBase005FC800
{
public:
	ParticleModuleOwnerBase005FC800( void *owner ) : m_owner( owner ) {}
	virtual void ownerSlot();

private:
	void *m_owner;
};

class ParticleModuleFlagBase005FC800
{
public:
	ParticleModuleFlagBase005FC800() : m_flag( 1 ) {}
	virtual void flagSlot();

protected:
	unsigned char m_flag;
	char m_pad[ 3 ];
};

class ParticleModuleValuesBase005FC800
{
public:
	ParticleModuleValuesBase005FC800() : m_value0( 0 ), m_value1( 0 ) {}
	virtual void valuesSlot();

protected:
	unsigned int m_value0;
	unsigned int m_value1;
};

class ParticleModuleState005FC800
	: public ParticleModuleOwnerBase005FC800,
	  public ParticleModuleFlagBase005FC800,
	  public ParticleModuleValuesBase005FC800
{
public:
	ParticleModuleState005FC800( void *owner,
		const ParticleModuleStateSource005FC800 *source );
	virtual void stateSlot();

private:
	unsigned char m_trailingFlag;
};

ParticleModuleState005FC800::ParticleModuleState005FC800( void *owner,
	const ParticleModuleStateSource005FC800 *source )
	: ParticleModuleOwnerBase005FC800( owner )
{
	m_value0 = source->m_value10;
	m_value1 = source->m_value14;
	ParticleModuleFlagBase005FC800::m_flag = source->m_flag08;
	m_trailingFlag = 1;
}
