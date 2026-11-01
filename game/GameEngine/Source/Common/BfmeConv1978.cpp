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

// The browser pointer cell VA 0x0134B280 is defined once as
// ?Rva00959410Dispatch@@3URva00959410Ptr@@A (DX8WebBrowserShutdownStorage.cpp).
extern "C" BfmePtrESQ __identifier("?Rva00959410Dispatch@@3URva00959410Ptr@@A");
#define g_bfmeDispatchESQ __identifier("?Rva00959410Dispatch@@3URva00959410Ptr@@A")

void bfmeSendESQ(const char *text)
{
	if (g_bfmeDispatchESQ.m_bfmePtrESQ == 0)
		return;

	g_bfmeDispatchESQ->bfmeInvokeESQ(BfmeBstrESQ(text));
}
