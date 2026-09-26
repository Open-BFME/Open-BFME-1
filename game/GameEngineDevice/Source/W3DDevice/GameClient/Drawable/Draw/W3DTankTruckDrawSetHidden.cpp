// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME-layout reconstruction of W3DTankTruckDraw::setHidden at 0x00781390.
// The inherited hide step and the emitter fields are established by the
// retail W3DTankTruckDraw header/source and the matched enableEmitters body.

class ParticleSystem
{
public:
	void stop(void);
};

ParticleSystem *Make00001B18(void);

class BfmeTankTruckParticlePtr
{
public:
	operator bool(void) const { return m_system != 0; }

	ParticleSystem *operator->(void) const
	{
		if (!m_system)
			return Make00001B18();
		return m_system;
	}

	ParticleSystem *m_system;
	BfmeTankTruckParticlePtr *m_previous;
	BfmeTankTruckParticlePtr *m_next;
};

class BfmeA1035
{
public:
	virtual void unusedVirtual(void);
	void bfmeStep1035(char hidden);
};

class W3DTankTruckDraw : public BfmeA1035
{
private:
	unsigned char m_unreconstructed_004[0x278];
	unsigned char m_effectsInitialized;
	unsigned char m_unreconstructed_27d[3];
	BfmeTankTruckParticlePtr m_dustEffect;
	BfmeTankTruckParticlePtr m_dirtEffect;
	BfmeTankTruckParticlePtr m_powerslideEffect;

public:
	virtual void setHidden(bool hidden);

protected:
	void createEmitters(void);
};

void W3DTankTruckDraw::setHidden(bool hidden)
{
	BfmeA1035::bfmeStep1035(hidden);
	if (!hidden)
		return;

	createEmitters();
	m_effectsInitialized = 1;
	if (m_dustEffect)
		m_dustEffect->stop();
	if (m_dirtEffect)
		m_dirtEffect->stop();
	if (m_powerslideEffect)
		m_powerslideEffect->stop();
}
