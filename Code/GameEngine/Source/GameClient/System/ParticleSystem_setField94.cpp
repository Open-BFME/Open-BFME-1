// cl: /DNDEBUG /MD /EHsc
// ParticleSystem setter at +0x94; same lazy slave walk as setSaveable/destroy.

class ParticleSystem;

ParticleSystem *Make00001B18( void );

class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *( void ) const
	{
		return m_target;
	}

	ParticleSystem *operator->( void ) const
	{
		ParticleSystem *target = m_target;
		if( !target )
			target = Make00001B18();
		return target;
	}

private:
	ParticleSystem *m_target;
};

class ParticleSystem
{
public:
	void setField94( void *value );

	unsigned char m_unreconstructed_000[ 0x94 ];
	void *m_field94;
	unsigned char m_unreconstructed_098[ 0x160 - 0x98 ];
	BfmeParticleSystemPtr m_slaveSystem;
};

void ParticleSystem::setField94( void *value )
{
	m_field94 = value;
	if( m_slaveSystem )
		m_slaveSystem->setField94( value );
}
