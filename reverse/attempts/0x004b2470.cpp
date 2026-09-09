// ?bfmeCloneZW@BfmeHostZW@@QBE?AVBfmeHandleZW@@XZ
// partial score=0.74 date=2026-09-09
void *__cdecl operator new(unsigned int n);

extern "C" void *g_bfmeMsgVftDN[];

class BfmeMsgZW
{
public:
	__forceinline BfmeMsgZW(int a, int b)
	{
		m_bfmeVftZW = g_bfmeMsgVftDN;
		m_bfme04ZW = a;
		m_bfme08ZW = b;
	}

	void *m_bfmeVftZW;
	int m_bfme04ZW;
	int m_bfme08ZW;
};

class BfmeHandleZW
{
public:
	BfmeHandleZW(BfmeMsgZW *p) : m_bfmePtrZW(p) {}
	BfmeHandleZW(const BfmeHandleZW &o) : m_bfmePtrZW(o.m_bfmePtrZW) {}
	~BfmeHandleZW();

	BfmeMsgZW *m_bfmePtrZW;
};

class BfmeHostZW
{
public:
	BfmeHandleZW bfmeCloneZW() const;

	int m_bfmeHeadZW;
	int m_bfme04ZW;
	int m_bfme08ZW;
};

BfmeHandleZW BfmeHostZW::bfmeCloneZW() const
{
	return BfmeHandleZW(new BfmeMsgZW(m_bfme04ZW, m_bfme08ZW));
}
