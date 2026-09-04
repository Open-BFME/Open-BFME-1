// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Open-BFME BFME-layout reconstruction of W3DTankTruckDraw::enableEmitters.

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
	operator bool() const { return m_system != 0; }

	ParticleSystem *operator->() const
	{
		if( !m_system )
			return Make00001B18();
		return m_system;
	}

	ParticleSystem *m_system;
	BfmeTankTruckParticlePtr *m_previous;
	BfmeTankTruckParticlePtr *m_next;
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

// ?enableEmitters@W3DTankTruckDraw@@IAEX_N@Z 0x007800A0
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
