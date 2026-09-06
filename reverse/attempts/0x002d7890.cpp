// ?bfmeGoGL@BfmeSecondGL@@QAEXXZ (identity unknown)
// partial score=0.95 date=2026-09-06
// 59/59 exact size; only the second x87 pair is transposed - retail does
// fld [esi+0x74] then fmul BfmeShadowScale, MSVC does fld the constant then
// fmul the member. Pins: resolve 0x00020824, apply 0x00010A23.
typedef float Real;

extern const Real g_bfmeK1239;
extern const Real BfmeShadowScale;

class BfmeTargetGL
{
public:
	void bfmeApplyGL(void *tail, Real ratio, int extra);
};

class BfmeHolderGL
{
public:
	BfmeTargetGL *bfmeResolveGL(void);
};

class BfmeThingGL
{
public:
	unsigned char m_bfmeHeadGL[0x70];
	int m_bfmeExtraGL;
	Real m_bfmeAmountGL;
	unsigned char m_bfmeTailGL[4];
};

class BfmeSecondGL
{
public:
	void bfmeGoGL(void);
};

void BfmeSecondGL::bfmeGoGL(void)
{
	char *base = (char *)this;

	BfmeHolderGL *holder = *(BfmeHolderGL **)(base - 8);
	BfmeThingGL *thing = *(BfmeThingGL **)(base - 0xc);
	BfmeTargetGL *target = holder->bfmeResolveGL();

	if (target == 0)
		return;

	target->bfmeApplyGL(thing->m_bfmeTailGL,
		(thing->m_bfmeAmountGL - g_bfmeK1239) / (thing->m_bfmeAmountGL * BfmeShadowScale),
		thing->m_bfmeExtraGL);
}
