// Open-BFME5 conversions.

extern const float g_rva0107533C;
extern int Rva00510DC0DisplayWidth;
extern int Rva00510DC0DisplayHeight;

struct BfmeVec1264
{
	float m_bfme00;
	float m_bfme04;
};

class BfmeR1264
{
public:
	virtual void bfmeV1264_00();
	virtual void bfmeV1264_01();
	virtual void bfmeV1264_02();
	virtual int bfmeReady1264();
	virtual void bfmeW1264_00();
	virtual void bfmeW1264_01();
	virtual void bfmeW1264_02();
	virtual void bfmeW1264_03();
	virtual void bfmeW1264_04();
	virtual void bfmeW1264_05();
	virtual void bfmeW1264_06();
	virtual void bfmeW1264_07();
	virtual void bfmeW1264_08();
	virtual void bfmeAt1264(int a, int b);
};

class Rva00510DC0DisplayView;
extern Rva00510DC0DisplayView *Rva00510DC0Display;

void bfmeMark1264(BfmeVec1264 *a, BfmeVec1264 *b)
{
	if (!reinterpret_cast<BfmeR1264 * &>(Rva00510DC0Display))
		return;
	if (!reinterpret_cast<BfmeR1264 * &>(Rva00510DC0Display)->bfmeReady1264())
		return;
	reinterpret_cast<BfmeR1264 * &>(Rva00510DC0Display)->bfmeAt1264(
		(int)(*(volatile float *)&b->m_bfme00 * g_rva0107533C + a->m_bfme00 - Rva00510DC0DisplayWidth * g_rva0107533C + g_rva0107533C),
		(int)(*(volatile float *)&b->m_bfme04 * g_rva0107533C + a->m_bfme04 - Rva00510DC0DisplayHeight * g_rva0107533C + g_rva0107533C));
}
