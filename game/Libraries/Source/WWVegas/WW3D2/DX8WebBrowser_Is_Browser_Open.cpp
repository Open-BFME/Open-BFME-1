// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern void __stdcall _com_issue_error(long error);

class BfmeThingVGP
{
public:
	void *m_bfme00;
	void *m_bfme04;
	int m_bfme08;
	int bfmeGoVGP() throw();
};

class _bstr_t
{
public:
	BfmeThingVGP *m_data;
	_bstr_t(const char *value);
	_bstr_t(const _bstr_t &other) throw() : m_data(other.m_data) {}
	~_bstr_t() throw()
	{
		if (m_data)
			m_data->bfmeGoVGP();
	}
};

class Rva00958E30
{
public:
	__declspec(noinline) long invoke(_bstr_t arg);
};

class BfmeObjECFPtr
{
public:
	Rva00958E30 *m_ptr;

	operator Rva00958E30 *() const throw()
	{
		return m_ptr;
	}

	Rva00958E30 *operator->() const
	{
		if (!m_ptr)
			_com_issue_error(0x80004003);
		return m_ptr;
	}
};

extern BfmeObjECFPtr g_bfmeObjECF;

class DX8WebBrowser
{
public:
	static __declspec(noinline) bool Is_Browser_Open(const char *browsername)
	{
		if (g_bfmeObjECF == 0)
			return false;
		return (g_bfmeObjECF->invoke(_bstr_t(browsername)) != 0);
	}
};

__declspec(noinline) bool forceIsBrowserOpen(const char *browsername)
{
	return DX8WebBrowser::Is_Browser_Open(browsername);
}
