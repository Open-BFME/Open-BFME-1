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

// comutil.h declares `void __stdcall _com_issue_error(HRESULT)`; the sweep
// comutil.h shim does not, so the declaration is repeated here under its exact
// defining spelling (?_com_issue_error@@YGXJ@Z).
extern void __stdcall _com_issue_error(long);

struct BfmePtrESQ
{
	BfmeTargetESQ *m_bfmePtrESQ;

	BfmeTargetESQ *operator->() const
	{
		if (m_bfmePtrESQ == 0)
			_com_issue_error(0x80004003);

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
