class BfmeBstrESQ
{
public:
	BfmeBstrESQ(const char *text);

	BfmeBstrESQ(const BfmeBstrESQ &other) throw()
	{
		m_bfmeDataESQ = other.m_bfmeDataESQ;
	}

	~BfmeBstrESQ();

	void *m_bfmeDataESQ;
};

class BfmeTargetESQ
{
public:
	long bfmeInvokeESQ(BfmeBstrESQ text);
};

void __stdcall bfmeThrowESQ(long hr);

struct BfmePtrESQ
{
	BfmeTargetESQ *m_bfmePtrESQ;

	BfmeTargetESQ *operator->() const
	{
		if (m_bfmePtrESQ == 0)
			bfmeThrowESQ(0x80004003);

		return m_bfmePtrESQ;
	}
};

extern BfmePtrESQ g_bfmeDispatchESQ;

void bfmeSendESQ(const char *text)
{
	if (g_bfmeDispatchESQ.m_bfmePtrESQ == 0)
		return;

	g_bfmeDispatchESQ->bfmeInvokeESQ(BfmeBstrESQ(text));
}
