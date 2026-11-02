// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00958730 validates its argument through _com_issue_error and
// reports whether the held pointer is null: a null argument returns the
// null-test directly, otherwise the 0x80004003 failure is raised first and
// the same null-test follows. The callee is the real comutil.h declaration
// (void __stdcall _com_issue_error(HRESULT) at the 0x00AFD540 pin), so the
// reference carries its defining name and links.
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
// comutil.h declares `void __stdcall _com_issue_error(HRESULT)`; the sweep
// comutil.h shim does not, so the declaration is repeated here under its
// exact defining spelling (?_com_issue_error@@YGXJ@Z).
extern void __stdcall _com_issue_error(long);

class Rva00958730Box
{
public:
	int check(void *arg);
	void *m_ptr;
};

int Rva00958730Box::check(void *arg)
{
	if (arg == 0)
		return m_ptr == 0;
	_com_issue_error((long)0x80004003);
	return m_ptr == 0;
}

// Retail 0x00958760 and 0x00958780, the same smart-pointer family's release
// and add-ref leaves (unreferenced, after int3 padding): when the held
// interface is non-null, call its IUnknown Release (slot 2) or AddRef
// (slot 1); the pointer itself is left in place. Address-derived names.
struct Rva00958760Unknown
{
	virtual long __stdcall QueryInterface(const void *iid, void **out) = 0;
	virtual unsigned long __stdcall AddRef(void) = 0;
	virtual unsigned long __stdcall Release(void) = 0;
};

class Rva00958760Ptr
{
public:
	void release(void);
	void addRef(void);
	Rva00958760Unknown *m_ptr;
};

void Rva00958760Ptr::release(void)
{
	if (m_ptr != 0)
		m_ptr->Release();
}

void Rva00958760Ptr::addRef(void)
{
	if (m_ptr != 0)
		m_ptr->AddRef();
}

// Retail 0x00958770 and 0x00958950 (unreferenced, after int3 padding): the
// smart-pointer families' interface-id leaves, `mov eax,offset; ret` with
// the address of the IFEBrowserEngine2 GUID constant at 0x0113DF00 (the
// __GUID_<uuid> spelling WebBrowserComWrappers.cpp references). Retail
// 0x00958940 is the second family's release leaf, the same shape as
// 0x00958760. Address-derived names.
struct _GUID { unsigned char bytes[16]; };
// __uuidof names the compiler's own __GUID_<uuid> symbol; an extern "C"
// declaration would reference the underscore-decorated ___GUID_<uuid> instead.
struct __declspec(uuid("ee883b17-0778-4b18-a12b-e44c0d298412")) IFEBrowserEngine2;

class Rva00958770Iid
{
public:
	static const _GUID &get(void);
};

const _GUID &Rva00958770Iid::get(void)
{
	return __uuidof(IFEBrowserEngine2);
}

class Rva00958940Ptr
{
public:
	void release(void);
	static const _GUID &iid(void);
	Rva00958760Unknown *m_ptr;
};

void Rva00958940Ptr::release(void)
{
	if (m_ptr != 0)
		m_ptr->Release();
}

const _GUID &Rva00958940Ptr::iid(void)
{
	return __uuidof(IFEBrowserEngine2);
}
