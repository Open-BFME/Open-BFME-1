// ?bfmeDraw1293@BfmeOverlay1293@@QAEXXZ
// partial score=0.98 date=2026-09-04
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeRenderDevice1293
{
public:
	virtual void reserved00();
	virtual void reserved01();
	virtual void reserved02();
	virtual void reserved03();
	virtual void reserved04();
	virtual void reserved05();
	virtual void reserved06();
	virtual void reserved07();
	virtual void reserved08();
	virtual void reserved09();
	virtual void reserved10();
	virtual void reserved11();
	virtual void reserved12();
	virtual void reserved13();
	virtual void reserved14();
	virtual void reserved15();
	virtual void reserved16();
	virtual void reserved17();
	virtual void reserved18();
	virtual void reserved19();
	virtual void reserved20();
	virtual void reserved21();
	virtual void reserved22();
	virtual void reserved23();
	virtual void reserved24();
	virtual void reserved25();
	virtual void reserved26();
	virtual void reserved27();
	virtual void reserved28();
	virtual void reserved29();
	virtual void reserved30();
	virtual void reserved31();
	virtual void reserved32();
	virtual void reserved33();
	virtual void reserved34();
	virtual void reserved35();
	virtual void reserved36();
	virtual void reserved37();
	virtual void reserved38();
	virtual void reserved39();
	virtual void reserved40();
	virtual void reserved41();
	virtual void reserved42();
	virtual void reserved43();
	virtual void bfmeBegin1293();
	virtual void reserved45();
	virtual void reserved46();
	virtual void reserved47();
	virtual void bfmeDrawQuad1293(
		float left, float top, float right, float bottom, unsigned int color);
	virtual void reserved49();
	virtual void reserved50();
	virtual void reserved51();
	virtual void reserved52();
	virtual void reserved53();
	virtual void reserved54();
	virtual void bfmeEnd1293();
};

extern BfmeRenderDevice1293 *g_bfmeRenderDevice1293;
extern float g_bfmeAlphaScale1293;

class BfmeOverlay1293
{
public:
	void bfmeDraw1293();

private:
	char m_padding00[0x18];
	int m_left18;
	int m_top1c;
	int m_right20;
	int m_bottom24;
	float m_opacity28;
	int m_alpha2c;
	char m_padding30[0x0c];
	unsigned char m_red3c;
	unsigned char m_green3d;
	unsigned char m_blue3e;
};

void BfmeOverlay1293::bfmeDraw1293()
{
	int alpha = (int)(m_alpha2c * m_opacity28 * g_bfmeAlphaScale1293);
	if (alpha > 255)
		alpha = 255;

	unsigned char alphaByte = (unsigned char)alpha;
	unsigned int color = (alphaByte << 24) | (m_red3c << 16) |
		(m_green3d << 8) | m_blue3e;
	float bottom = (float)m_bottom24;
	float right = (float)m_right20;
	float top = (float)m_top1c;
	float left = (float)m_left18;
	_ReadWriteBarrier();
	BfmeRenderDevice1293 *device = g_bfmeRenderDevice1293;
	device->bfmeBegin1293();
	device->bfmeDrawQuad1293(left, top, right, bottom, color);
	device->bfmeEnd1293();
}
