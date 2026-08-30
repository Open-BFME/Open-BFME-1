// Open-BFME5 conversions.

extern const float g_bfmeK1264;
extern int g_bfmeCx1264;
extern int g_bfmeCy1264;

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

extern BfmeR1264 *g_bfme1264;

void bfmeMark1264(BfmeVec1264 *a, BfmeVec1264 *b)
{
	if (!g_bfme1264)
		return;
	if (!g_bfme1264->bfmeReady1264())
		return;
	g_bfme1264->bfmeAt1264(
		(int)(*(volatile float *)&b->m_bfme00 * g_bfmeK1264 + a->m_bfme00 - g_bfmeCx1264 * g_bfmeK1264 + g_bfmeK1264),
		(int)(*(volatile float *)&b->m_bfme04 * g_bfmeK1264 + a->m_bfme04 - g_bfmeCy1264 * g_bfmeK1264 + g_bfmeK1264));
}
