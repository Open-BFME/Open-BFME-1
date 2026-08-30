// Open-BFME5 conversions.

struct BfmeVec1283
{
	float x;
	float y;
	float z;
};

class TacticalViewFadeShim
{
public:
	virtual void bfmeV1283_00();
	virtual void bfmeV1283_01();
	virtual void bfmeV1283_02();
	virtual void bfmeV1283_03();
	virtual void bfmeV1283_04();
	virtual void bfmeV1283_05();
	virtual void bfmeV1283_06();
	virtual void bfmeV1283_07();
	virtual void bfmeV1283_08();
	virtual void bfmeV1283_09();
	virtual void bfmeV1283_10();
	virtual void bfmeMark1283(BfmeVec1283 *lo, BfmeVec1283 *hi, unsigned int color, int flags);
};

extern TacticalViewFadeShim *TheTacticalViewFadeShim;

class BfmeA1283
{
public:
	void bfmePlotBounds1283(BfmeVec1283 offset);
	char m_bfmePad00[0x24];
	BfmeVec1283 m_lo;
	BfmeVec1283 m_hi;
};

void BfmeA1283::bfmePlotBounds1283(BfmeVec1283 offset)
{
	BfmeVec1283 lo = {
		offset.x + m_lo.x,
		offset.y + m_lo.y,
		offset.z + m_lo.z,
	};
	BfmeVec1283 hi = {
		offset.x + m_hi.x,
		offset.y + m_hi.y,
		offset.z + m_hi.z,
	};
	TheTacticalViewFadeShim->bfmeMark1283(&lo, &hi, 0xccaaffff, 0);
}
