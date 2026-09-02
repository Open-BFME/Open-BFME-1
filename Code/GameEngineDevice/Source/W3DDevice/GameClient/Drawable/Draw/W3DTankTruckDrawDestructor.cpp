// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS

class W3DTankTruckPrimaryBase
{
public:
	virtual void sharedSlot();
private:
	unsigned char m_unreconstructed_004[ 8 ];
};

class W3DTankTruckSecondaryBase
{
public:
	virtual void sharedSlot();
};

class Gen_dtor_0077bf80 : public W3DTankTruckPrimaryBase, public W3DTankTruckSecondaryBase
{
public:
	virtual ~Gen_dtor_0077bf80();
	virtual void sharedSlot();
private:
	unsigned char m_unreconstructed_010[ 0x280 - 0x10 ];
};

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw();
private:
	unsigned char m_storage[ 12 ];
};

class AudioEventRTS
{
public:
	~AudioEventRTS();
private:
	unsigned char m_storage[ 0x70 ];
};

class W3DTankTruckDraw : public Gen_dtor_0077bf80
{
private:
	BfmeParticleSystemHandle m_dustEffect;
	BfmeParticleSystemHandle m_dirtEffect;
	BfmeParticleSystemHandle m_powerslideEffect;
	unsigned char m_unreconstructed_2a4[ 0x308 - 0x2a4 ];
	AudioEventRTS m_powerslideSound;
	AudioEventRTS m_landingSound;

protected:
	virtual ~W3DTankTruckDraw();
	void tossEmitters();
};

W3DTankTruckDraw::~W3DTankTruckDraw()
{
	tossEmitters();
}
