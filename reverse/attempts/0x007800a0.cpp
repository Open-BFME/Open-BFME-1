// ?enableEmitters@W3DTankTruckDraw@@IAEX_N@Z
// partial score=0.57 date=2026-09-02
// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS

class ParticleSystem
{
public:
	void start();
	void stop();
};

ParticleSystem *Make00001B18();

class BfmeTankTruckParticlePtr
{
public:
	operator ParticleSystem *() const { return m_target; }
	ParticleSystem *operator->() const
	{
		ParticleSystem *target = m_target;
		if( !target )
			target = Make00001B18();
		return target;
	}
private:
	ParticleSystem *m_target;
	unsigned char m_unreconstructed_004[ 8 ];
};

class W3DTankTruckDraw
{
private:
	unsigned char m_unreconstructed_000[ 0x27c ];
	unsigned char m_effectsInitialized;
	unsigned char m_unreconstructed_27d[ 3 ];
	BfmeTankTruckParticlePtr m_dustEffect;
	BfmeTankTruckParticlePtr m_dirtEffect;
	BfmeTankTruckParticlePtr m_powerslideEffect;

protected:
	void createEmitters();
	void enableEmitters( bool enable );
};

void W3DTankTruckDraw::enableEmitters( bool enable )
{
	createEmitters();
	m_effectsInitialized = true;
	if( m_dustEffect )
	{
		if( enable )
			m_dustEffect->start();
		else
			m_dustEffect->stop();
	}
	if( m_dirtEffect )
	{
		if( enable )
			m_dirtEffect->start();
		else
			m_dirtEffect->stop();
	}
	if( m_powerslideEffect && !enable )
		m_powerslideEffect->stop();
}

