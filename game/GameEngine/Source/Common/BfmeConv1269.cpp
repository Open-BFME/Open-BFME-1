// Open-BFME5 conversions.

// Retail 0x01075334 is the single float defined once by
// game/GameEngine/Source/Common/BfmeConv1813.cpp as ?g_bfmeDefaultBU@@3MA
// (targets/game/reverse/data_rows.csv); this TU only reads it.
//
// The declaration MUST drop `const`: a namespace-scope `const float` mangles
// as ?g_bfmeDefaultBU@@3MB, which nothing defines -- the defining object
// exports the non-const float, ?g_bfmeDefaultBU@@3MA, as
// game/GameEngineDevice/Source/W3DDevice/Common/System/
// W3DRadar_setShroudLevel_Thunk.cpp already spells it. Reading through a
// non-const extern float and a const one loads the same address, so the code
// is byte-identical; only the reference's mangled name changes.
extern float g_bfmeDefaultBU;
// Retail 0x0107533C is the 0.5f in game/Libraries/Source/EA/Apt/aptMathRound.cpp
// as ?g_rva0107533C@@3MB, written there as `extern const float g_rva0107533C`,
// so the datum really has external linkage: aptMathRound.obj carries it as
// IMAGE_SYM_CLASS_EXTERNAL (storage 2), not STATIC. This TU's reference
// therefore resolves at link time. The census still charges it as unresolved
// because link_census indexes no object under game/Libraries/Source/EA/ -- a
// census scope gap, not a defect in this declaration.
extern const float g_rva0107533C;

struct BfmeVec1269
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeG1269
{
public:
	char m_bfmePad00[0xab4];
	float m_bfmeab4;
};

// Canonical identity of the retail global at 0x012ED5C8, defined once by
// game/GameEngine/Source/Common/GlobalData.cpp as
// ?TheWritableGlobalData@@3PAVGlobalData@@A.  The single float read keeps the
// local view and casts at the use.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

class BfmeA1269
{
public:
	virtual void bfmeV1269_00();
	virtual void bfmeV1269_01();
	virtual void bfmeV1269_02();
	virtual void bfmeV1269_03();
	virtual void bfmeV1269_04();
	virtual void bfmeV1269_05();
	virtual void bfmeFill1269(BfmeVec1269 *t, int a, int b, int c, int d);
	void bfmeGet1269(BfmeVec1269 *out, int a, int b, int c, int d);
};

void BfmeA1269::bfmeGet1269(BfmeVec1269 *out, int a, int b, int c, int d)
{
	BfmeVec1269 t;

	bfmeFill1269(&t, a, b, c, d);
	volatile float *bfmeBase = &((BfmeG1269 *)TheWritableGlobalData)->m_bfmeab4;
	t.m_bfme00 = (*bfmeBase + g_bfmeDefaultBU) * g_rva0107533C * t.m_bfme00;
	t.m_bfme04 = (*bfmeBase + g_bfmeDefaultBU) * g_rva0107533C * t.m_bfme04;
	t.m_bfme08 = (*bfmeBase + g_bfmeDefaultBU) * g_rva0107533C * t.m_bfme08;
	out->m_bfme00 = t.m_bfme00;
	out->m_bfme04 = t.m_bfme04;
	out->m_bfme08 = t.m_bfme08;
}
