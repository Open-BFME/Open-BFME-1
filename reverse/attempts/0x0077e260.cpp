// ?stopMoveDebris@W3DTankDraw@@IAEXXZ
// partial score=0.5 date=2026-09-02
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS

class Drawable
{
public:
	bool isDrawableEffectivelyHidden( void ) const;
};

class ParticleSystem
{
public:
	void start( void );
	void stop( void );
};

ParticleSystem *Make00001B18( void );

class BfmeTankParticleSystemPtr
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

class W3DTankDraw
{
private:
	void *m_vtable;
	void *m_moduleData;
	Drawable *m_drawable;
	unsigned char m_unreconstructed_00c[ 0x27c - 0x00c ];
	BfmeTankParticleSystemPtr m_treadDebrisLeft;
	unsigned char m_unreconstructed_280[ 0x288 - 0x280 ];
	BfmeTankParticleSystemPtr m_treadDebrisRight;

protected:
	void startMoveDebris( void );
	void stopMoveDebris( void );
};

void W3DTankDraw::startMoveDebris( void )
{
	if( m_drawable->isDrawableEffectivelyHidden() )
		return;
	if( m_treadDebrisLeft )
		m_treadDebrisLeft->start();
	if( m_treadDebrisRight )
		m_treadDebrisRight->start();
}

void W3DTankDraw::stopMoveDebris( void )
{
	if( m_treadDebrisLeft )
		m_treadDebrisLeft->stop();
	if( m_treadDebrisRight )
		m_treadDebrisRight->stop();
}
