// cl: /DNDEBUG /MD /EHsc
// BFME W3DDisplay vtable 0x0111EDD0, installed by constructor 0x006EF850.
// Slots35/36 access the clipping flag at+178; slot82 returns average FPS+17C.
// The named command-bar callback disables clipping through slot36 after drawing;
// drawFillRect independently tests+178 before clamping. The getter name follows
// the reference virtual interface; no direct retail getter caller was found.
// StatsCollector calls the FPS slot, and updateAverageFPS writes its mean+17C.

// Partial observed view. The full reference-derived W3DDisplay.cpp still uses
// an older layout, so keep these BFME accessors at their verified offsets.
class W3DDisplay
{
public:
	virtual bool isClippingEnabled(void);
	virtual void enableClipping(bool onoff);
	virtual float getAverageFPS(void);

private:
	unsigned char m_unmodelled04[0x174];
	bool m_isClippedEnabled;
	unsigned char m_unmodelled179[3];
	float m_averageFPS;
};

bool W3DDisplay::isClippingEnabled(void)
{
	return m_isClippedEnabled;
}

void W3DDisplay::enableClipping(bool onoff)
{
	m_isClippedEnabled = onoff;
}

float W3DDisplay::getAverageFPS(void)
{
	return m_averageFPS;
}
