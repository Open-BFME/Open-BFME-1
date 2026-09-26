// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME-layout reconstruction of W3DPoliceCarDraw::~W3DPoliceCarDraw.

// The retail destructor calls the dynamic-light fade helper through the ILT
// already named for this ABI slice, then marks the light's two decay modes and
// clears the member before delegating to the truck-draw base destructor.
class W3DDynamicLightPulseShim
{
public:
	void setFrameFade(unsigned int frameIncreaseTime, unsigned int decayFrameTime);
	void setDecayRange(void) { m_decayRange = true; }
	void setDecayColor(void) { m_decayColor = true; }

	public:
	char m_pad[0x149];
	bool m_decayRange;
	bool m_decayColor;
};

class W3DTruckDrawPrimaryBase
{
public:
	virtual void sharedSlot();

private:
	char m_pad[8];
};

class W3DTruckDrawSecondaryBase
{
public:
	virtual void sharedSlot();
};

// The unresolved base destructor is the landed retail body at 0x00781630,
// whose ILT is pinned as Gen_dtor_00781630 at 0x00025A40.
class Gen_dtor_00781630 : public W3DTruckDrawPrimaryBase,
	public W3DTruckDrawSecondaryBase
{
public:
	virtual ~Gen_dtor_00781630();
	virtual void sharedSlot();

private:
	char m_pad[0x3EC - 0x10];
};

class W3DPoliceCarDraw : public Gen_dtor_00781630
{
	public:
	virtual ~W3DPoliceCarDraw();

	private:
	W3DDynamicLightPulseShim *m_light;
	float m_curFrame;
};

// ??1W3DPoliceCarDraw@@UAE@XZ
W3DPoliceCarDraw::~W3DPoliceCarDraw()
{
	if (m_light)
	{
		m_light->setFrameFade(0, 5);
		m_light->setDecayRange();
		m_light->setDecayColor();
		m_light = 0;
	}
}
