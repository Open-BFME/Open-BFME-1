// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct _GUID { unsigned char bytes[16]; };
typedef _GUID GUID;
struct IUnknown;

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
	BfmeBstrVGP(const BfmeBstrVGP &other) throw() : m_data(other.m_data) {}
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
		long (__stdcall *slot28)(Rva00958D30 *, void *);
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

	Vtable *vtable;
};

__declspec(noinline) long forceRva00958D30(Rva00958D30 *self,
	BfmeBstrVGP arg)
{
	return self->invoke(arg);
}
