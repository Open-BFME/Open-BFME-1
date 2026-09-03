// cl: /DNDEBUG /MD
//
// Retail 0x00742DF0: W3DView-family method that calls a helper, a virtual at
// +0x24B8 slot 0x48, scales two floats at +0x23D8/+0x23DC by +0xA0, writes
// default FOV/pitch, then tail-calls setCameraTransform.

#define BFME_VSLOT(n) virtual void slot##n();

class Rva00742DF0Sub
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4) BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7)
	BFME_VSLOT(8) BFME_VSLOT(9) BFME_VSLOT(10) BFME_VSLOT(11)
	BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14) BFME_VSLOT(15)
	BFME_VSLOT(16) BFME_VSLOT(17)
	virtual void apply(int mode, void *p);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView
{
public:
	void applyDefaultProjection();

private:
	void helper();
	void setCameraTransform();

private:
	unsigned char m_pad00[0x28];
	unsigned m_at28;
	unsigned char m_pad2c[0x6C - 0x2C];
	float m_fov;
	float m_pitch;
	unsigned char m_pad74[0xA0 - 0x74];
	float m_scale;
	unsigned char m_padA4[0x23D8 - 0xA4];
	float m_a;
	float m_b;
	unsigned char m_pad23E0[0x24B8 - 0x23E0];
	Rva00742DF0Sub m_sub;
};

void W3DView::applyDefaultProjection()
{
	helper();
	m_sub.apply(0, &m_at28);
	m_a *= m_scale;
	m_pitch = 1.0f;
	*(unsigned *)&m_fov = 0x3F5F66F3u;
	m_b *= m_scale;
	setCameraTransform();
}
