// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

extern void __stdcall _com_issue_errorex(long error, IUnknown *object,
	const GUID &iid);
extern GUID g_bfmeIidTSA;

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
	BfmeBstrVGP(const BfmeBstrVGP &other) throw() : m_data(other.m_data)
	{ if (m_data) InterlockedIncrement((long volatile *)&m_data->m_bfme08); }
	~BfmeBstrVGP() throw()
	{
		if (m_data)
			m_data->bfmeGoVGP();
	}
};

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
		void *slot28;
		void *slot2C;
		void *slot30;
		void *slot34;
		void *slot38;
		void *slot3C;
		void *slot40;
		long (__stdcall *slot44)(Rva00958D30 *, void *, void *);
	};

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

// forceRva00958EB0 absent-from-retail: emission host for inline COM wrapper.
__declspec(noinline) long forceRva00958EB0(Rva00958D30 *self,
	BfmeBstrVGP arg, void *value)
{
	return self->invoke(arg, value);
}
