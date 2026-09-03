// cl: /DNDEBUG /MD /EHsc
// ParticleSystem::setSaveable -- BFME walks the slave chain through a lazy
// pointer at +0x160 (null dereference calls 0x00001B18) and stores the flag
// at +0x1AA, two bytes after m_isDestroyed at +0x1A8.

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
	void setSaveable( bool b );

	unsigned char m_unreconstructed_000[ 0x160 ];
	BfmeParticleSystemPtr m_slaveSystem;
	unsigned char m_unreconstructed_164[ 0x1aa - 0x164 ];
	unsigned char m_isSaveable;
};

void ParticleSystem::setSaveable( bool b )
{
	m_isSaveable = b;
	if( m_slaveSystem )
		m_slaveSystem->setSaveable( b );
}
