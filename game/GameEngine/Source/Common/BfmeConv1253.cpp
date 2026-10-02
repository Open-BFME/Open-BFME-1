// Open-BFME5 conversions.

struct BfmeVec1253
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeR1253
{
public:
	virtual void bfmeV1253_00();
	virtual void bfmeV1253_01();
	virtual void bfmeV1253_02();
	virtual void bfmeV1253_03();
	virtual void bfmeV1253_04();
	virtual void bfmeV1253_05();
	virtual void bfmeV1253_06();
	virtual void bfmeV1253_07();
	virtual void bfmeV1253_08();
	virtual void bfmeV1253_09();
	virtual void bfmeV1253_10();
	virtual void bfmeV1253_11();
	virtual void bfmeMark1253(BfmeVec1253 *p, int a, unsigned int c, int d);
};

// Retail spells this global View *TheTacticalView (0x012F1600); the TU-local
// BfmeR1253 is only the slot view used at the call sites below.
class View;
extern View *TheTacticalView;

class BfmeA1253
{
public:
	void bfmeDraw1253(BfmeVec1253 p);
	char m_bfmePad00[0x24];
	int m_bfme24;
	float m_bfme28;
};

void BfmeA1253::bfmeDraw1253(BfmeVec1253 p)
{
	p.m_bfme08 = p.m_bfme08 - *(volatile float *)&m_bfme28 * 0.5f;
	((BfmeR1253 *)TheTacticalView)->bfmeMark1253(&p, m_bfme24, 0xccaaffff, 0);
	p.m_bfme08 = p.m_bfme08 + m_bfme28;
	((BfmeR1253 *)TheTacticalView)->bfmeMark1253(&p, m_bfme24, 0xccaaffff, 0);
}
