// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The inline COM call wrappers the WOL browser dispatch pointer is driven
// through, plus the one caller of the two-string wrapper that survives:
//
//   ?invoke@Rva00958C80@@QAEJVBfmeBstrVGP@@0JJJJJJPAX@Z  0x00958C80  slot +0x24
//   ?invoke@Rva00958D30@@QAEJVBfmeBstrVGP@@@Z            0x00958D30  slot +0x28
//   ?invoke@Rva00958D30@@QAEJVBfmeBstrVGP@@0@Z           0x00958DA0  slot +0x2C
//   ?invoke@Rva00958D30@@QAEJVBfmeBstrVGP@@PAX@Z         0x00958EB0  slot +0x44
//   ?invoke@Rva00958E30@@QAEJV_bstr_t@@@Z                0x00958E30  slot +0x34
//   ?callTwoStrings@@YAXPBD0@Z                           0x00959410
//
// The three Rva00958D30 rows are overloads on ONE class -- the mangled names
// say so -- yet each lived in its own file, and each file cut the interface
// vtable off after the slot its own overload called: one ended at +0x28, one at
// +0x2C, one at +0x44. Reading any single file you could not tell whether the
// interface had ten slots or eighteen. Declared once, the vtable runs to +0x44
// and the three typed slots sit in it together.
//
// _bstr_t and BfmeBstrVGP are the same MSVC 7.1 _bstr_t, and both spellings are
// load-bearing: the parameter type is part of the mangled name, so the ledger's
// ?invoke@Rva00958E30@@QAEJV_bstr_t@@@Z pins one and the Rva00958C80 and
// Rva00958D30 rows pin the other, and neither can be renamed into the other.
// They differ in one more way that is not cosmetic: only the BfmeBstrVGP copy
// retains Data_t. That copy is made in the force* host rather than in any
// matched body, so nothing pins it either way; the retaining copy is the
// correct one and _bstr_t keeps the shallow copy it byte-matched with. (Bstr_t_ctor.cpp holds ??0_bstr_t@@QAE@PBD@Z, which builds the same
// Data_t these destroy; its nested Data spelling is a third view of it.)
//
// The force* hosts are absent from retail. They exist only because an inline
// method that is never called is never emitted, and each holds the copy that
// makes the compiler emit its invoke.

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
extern void __stdcall _com_issue_error(long error);
extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);
extern GUID g_bfmeIidTSA;

// _bstr_t's Data_t: the BSTR, its reference count and its length.
class BfmeThingVGP
{
public:
	void *m_bfme00;
	void *m_bfme04;
	int m_bfme08;
	int bfmeGoVGP() throw();
};

class BfmeBstrVGP
{
public:
	BfmeThingVGP *m_data;
	BfmeBstrVGP(const char *text) throw();
	// MSVC71 _bstr_t copies retain Data_t; a shallow owning copy is invalid.
	BfmeBstrVGP(const BfmeBstrVGP &other) throw() : m_data(other.m_data)
	{ if (m_data) InterlockedIncrement((long volatile *)&m_data->m_bfme08); }
	~BfmeBstrVGP() throw()
	{
		if (m_data)
			m_data->bfmeGoVGP();
	}
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

// The browser factory interface: one call, ten slots in, taking the two names
// and the window geometry.
class Rva00958C80
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		void *slot08;
		void *slot0C;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1C;
		void *slot20;
		long (__stdcall *slot24)(Rva00958C80 *, void *, void *, long,
			long, long, long, long, long, void *);
	};

	__declspec(noinline) long invoke(BfmeBstrVGP first,
		BfmeBstrVGP second, long hwnd, long x, long y, long w, long h,
		long options, void *gamedispatch)
	{
		BfmeThingVGP *secondData = second.m_data;
		BfmeThingVGP *firstData = first.m_data;
		void *secondValue = secondData ? secondData->m_bfme00 : 0;
		void *firstValue = firstData ? firstData->m_bfme00 : 0;
		long result = vtable->slot24(this, firstValue, secondValue, hwnd,
			x, y, w, h, options, gamedispatch);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
		return result;
	}

	Vtable *vtable;
};

// The browser dispatch interface itself: three of its slots are called through
// wrappers that differ only in how many arguments they carry.
class Rva00958D30
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		void *slot08;
		void *slot0C;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1C;
		void *slot20;
		void *slot24;
		long (__stdcall *slot28)(Rva00958D30 *, void *);
		long (__stdcall *slot2C)(Rva00958D30 *, void *, void *);
		void *slot30;
		void *slot34;
		void *slot38;
		void *slot3C;
		void *slot40;
		long (__stdcall *slot44)(Rva00958D30 *, void *, void *);
	};

	__declspec(noinline) long invoke(BfmeBstrVGP arg)
	{
		BfmeThingVGP *data = arg.m_data;
		void *value = data ? data->m_bfme00 : 0;
		long result = vtable->slot28(this, value);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
		return result;
	}

	__declspec(noinline) long invoke(BfmeBstrVGP first, BfmeBstrVGP second)
	{
		BfmeThingVGP *secondData = second.m_data;
		BfmeThingVGP *firstData = first.m_data;
		void *secondValue = secondData ? secondData->m_bfme00 : 0;
		void *firstValue = firstData ? firstData->m_bfme00 : 0;
		long result = vtable->slot2C(this, firstValue, secondValue);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
		return result;
	}

	__declspec(noinline) long invoke(BfmeBstrVGP arg, void *value)
	{
		BfmeThingVGP *data = arg.m_data;
		void *text = data ? data->m_bfme00 : 0;
		long result = vtable->slot44(this, text, value);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
		return result;
	}

	Vtable *vtable;
};

// The one wrapper whose parameter the ledger pins as _bstr_t rather than
// BfmeBstrVGP -- same object, same slot number as the two-string overload
// above, a different interface.
class Rva00958E30
{
public:
	struct Vtable
	{
		void *slot00;
		void *slot04;
		void *slot08;
		void *slot0C;
		void *slot10;
		void *slot14;
		void *slot18;
		void *slot1C;
		void *slot20;
		void *slot24;
		void *slot28;
		void *slot2C;
		void *slot30;
		long (__stdcall *slot34)(Rva00958E30 *, void *, void *);
	};

	// The only one of the five that reads a result back rather than just
	// reporting failure: the slot writes through the out parameter.
	__declspec(noinline) long invoke(_bstr_t arg)
	{
		long value = 0;
		BfmeThingVGP *data = arg.m_data;
		void *text = data ? data->m_bfme00 : 0;
		long result = vtable->slot34(this, text, &value);
		if (result < 0)
			_com_issue_errorex(result, (IUnknown *)this, g_bfmeIidTSA);
		return value;
	}

	Vtable *vtable;
};

__declspec(noinline) long forceRva00958C80(Rva00958C80 *self,
	BfmeBstrVGP first, BfmeBstrVGP second, long hwnd, long x, long y,
	long w, long h, long options, void *gamedispatch)
{
	return self->invoke(first, second, hwnd, x, y, w, h, options,
		gamedispatch);
}

__declspec(noinline) long forceRva00958D30(Rva00958D30 *self,
	BfmeBstrVGP arg)
{
	return self->invoke(arg);
}

// ?forceRva00958DA0@@YAJPAVRva00958D30@@VBfmeBstrVGP@@1@Z absent-from-retail
__declspec(noinline) long forceRva00958DA0(Rva00958D30 *self,
	BfmeBstrVGP first, BfmeBstrVGP second)
{
	return self->invoke(first, second);
}

// forceRva00958EB0 absent-from-retail: emission host for inline COM wrapper.
__declspec(noinline) long forceRva00958EB0(Rva00958D30 *self,
	BfmeBstrVGP arg, void *value)
{
	return self->invoke(arg, value);
}

// forceRva00958E30 is an emission host for the inline COM wrapper.
__declspec(noinline) long forceRva00958E30(Rva00958E30 *self, _bstr_t arg)
{
	return self->invoke(arg);
}

// ?callTwoStrings@@YAXPBD0@Z
// Open-BFME7: 0x00959410 (133 B gap) forwards two C strings to the two-BSTR
// invoke wrapper on the WOL browser dispatch pointer when it is set; the
// smart pointer arrow raises E_POINTER through _com_issue_error.
struct Rva00959410Ptr
{
	Rva00958D30 *m_p;
	Rva00958D30 *operator->() const
	{
		if (!m_p)
			_com_issue_error(0x80004003);
		return m_p;
	}
	operator bool() const { return m_p != 0; }
};
extern Rva00959410Ptr Rva00959410Dispatch;

void callTwoStrings(const char *first, const char *second)
{
	if (Rva00959410Dispatch)
		Rva00959410Dispatch->invoke(first, second);
}
