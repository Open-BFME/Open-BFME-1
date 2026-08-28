extern "C" __declspec(dllimport) void *__stdcall SelectObject(void *dc, void *obj);

class BfmePoolCJD
{
public:
	void bfmeFreeCJD(void *what);
};

extern BfmePoolCJD bfmeThePoolCJD;

class BfmeThingCJD
{
public:
	void bfmeGoCJD();
	unsigned char m_bfmeHead[0x24];
	void *m_bfmeObj;
	int m_bfmeCount;
	void *m_bfmeDc;
};

void BfmeThingCJD::bfmeGoCJD()
{
	if (--m_bfmeCount == 0)
	{
		SelectObject(m_bfmeObj, m_bfmeDc);
		bfmeThePoolCJD.bfmeFreeCJD(m_bfmeObj);
		m_bfmeObj = 0;
	}
}
