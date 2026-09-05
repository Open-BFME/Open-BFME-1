// ?Rva006FE200@BfmeFacingBody@@QAEXPBUBfmeCoord2D@@M@Z
// partial score=0.35 date=2026-09-05
// Open-BFME: retail RVA 0x006FE200, 349 B. Reconstructed from
// tools/dis_retail.py: a __thiscall(pos-delta pointer, float) method that
// rotates a velocity by -m_facing (fsin/fcos), notifies through a virtual
// slot at +0x64, optionally forwards a debug sample to g_bfmeGameCW's
// consumer, then advances and clamps m_facing by param2*K3 against +-K4.
// Owning class and field names are unproven (address-derived); the six
// globals already carried names elsewhere in the ledger (g_bfmeK1253,
// BfmeZeroRange, g_bfmeGameCW) are reused, the rest are new address-derived
// pins. This is a best-effort shape match, banked if not byte-exact --
// the fsin/fcos operand shuffle (docs/matching.md "Equivalent x87
// expressions can compile differently") is the likely remaining hazard.

extern const float g_bfmeK1253;      // retail 0x0107533C
extern const float BfmeZeroRange;    // retail 0x01075350
extern void *g_bfmeGameCW;           // retail 0x012F706C (nonzero => debug consumer active)

extern const float g_Rva012F8274;    // gate threshold compared against +0xe4
extern const float g_Rva01083B6C;    // rotation blend constant (K2)
extern const float g_Rva012BAC54;    // facing delta scale constant (K3)
extern const float g_Rva012BAC50;    // facing clamp limit constant (K4)

struct BfmeCoord2D
{
	float x;
	float y;
};

extern "C" void __cdecl BfmeFacingDebugSample(const BfmeCoord2D *sample);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);

#define DECLARE_TEN(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); \
	virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); \
	virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9();

class BfmeFacingBody
{
public:
	DECLARE_TEN(slotA)
	DECLARE_TEN(slotB)
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24();
	virtual void notifyFacingChanged(void);   // +0x64 (idx 25)

private:
	unsigned char m_unmodelled_04[0xA8 - 4];
	float m_velX;                              // +0xA8
	float m_velY;                              // +0xAC
	float m_speed;                              // +0xB0
	unsigned char m_unmodelled_B4[0xCC - 0xB4];
	float m_facing;                              // +0xCC
	unsigned char m_unmodelled_D0[0xE4 - 0xD0];
	float m_gateMetric;                          // +0xE4

public:
	void Rva006FE200(const BfmeCoord2D *dir, float turnDelta);
};

#undef DECLARE_TEN

// ?Rva006FE200@BfmeFacingBody@@QAEXPBUBfmeCoord2D@@M@Z (address-derived name; identity unknown)
void BfmeFacingBody::Rva006FE200(const BfmeCoord2D *dir, float turnDelta)
{
	if (dir)
	{
		float dx = dir->x * g_bfmeK1253;
		float dy = dir->y * g_bfmeK1253;

		if (m_gateMetric > g_Rva012F8274)
		{
			if (!(dx < BfmeZeroRange && dy < BfmeZeroRange))
			{
				float theta = -m_facing;
				float s = (float)sin(theta);
				float c = (float)cos(theta);
				float r1 = dy * c - s * dx;
				float r2 = c * dx + s * dy;
				float newVelX = m_speed;
				(void)newVelX;
				float blendedY = m_velX + g_Rva01083B6C * r1;
				float blendedX = m_velY - g_Rva01083B6C * r2;

				notifyFacingChanged();

				if (g_bfmeGameCW)
				{
					BfmeCoord2D sample;
					sample.x = blendedY;
					sample.y = blendedX;
					BfmeFacingDebugSample(&sample);
				}
			}

			float newFacing = m_facing + turnDelta * g_Rva012BAC54;
			m_facing = newFacing;

			if (newFacing < -g_Rva012BAC50)
				m_facing = -g_Rva012BAC50;
			else if (!(newFacing <= g_Rva012BAC50))
				m_facing = g_Rva012BAC50;
		}
	}
}
