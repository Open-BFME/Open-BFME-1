// Open-BFME5 conversions.

extern const float g_rva0107533C;

struct BfmeVec1263
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeR1263
{
public:
	virtual void bfmeV1263_00();
	virtual void bfmeV1263_01();
	virtual void bfmeV1263_02();
	virtual void bfmeV1263_03();
	virtual void bfmeV1263_04();
	virtual void bfmeV1263_05();
	virtual float bfmeHeight1263(float a, float b, int c);
};

// Retail 0x012EF4CC is EA's singleton; only its type spelling matters for the
// mangled name, so this TU declares it canonically and casts to its own
// TU-local view at the uses.
class TerrainLogic;

extern TerrainLogic *TheTerrainLogic;

// Retail 0x00032231 is the ILT thunk that lands on the assert body at
// 0x0018F400.  The only definition of that entry point in the image is the
// gen-small thunk j_00032231 (game/gen_small/thunks_023.cpp), so reference it
// instead of the pin-only _bfmeAssert1263 spelling nothing defines.
extern void j_00032231();

class BfmeA1263
{
public:
	void bfmeGet1263(BfmeVec1263 *out);
	char m_bfmePad00[0x1c];
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	char m_bfmePad2c[4];
	char m_bfme30;
};

void BfmeA1263::bfmeGet1263(BfmeVec1263 *out)
{
	if (!out)
		return;
	if (m_bfme30)
		j_00032231();
	out->m_bfme00 = (m_bfme1c + m_bfme24) * g_rva0107533C;
	out->m_bfme04 = (m_bfme20 + m_bfme28) * g_rva0107533C;
	if (TheTerrainLogic)
		out->m_bfme08 = ((BfmeR1263 *)TheTerrainLogic)->bfmeHeight1263(out->m_bfme00, out->m_bfme04, 0);
	else
		out->m_bfme08 = 0;
}
