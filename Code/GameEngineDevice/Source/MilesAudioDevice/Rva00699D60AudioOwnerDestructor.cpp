// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The 0x00699D60 body is the scalar destructor reached by the vector-deleting
// destructor at 0x00699E90 through the existing 0x0002D902 thunk.  The retail
// body has no recoverable semantic class name, so the type name is deliberately
// address-derived.  The target itself has no vptr store; no vtable claim is
// made here.

extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(void *);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(void *);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *);

// Keep the retail vector-delete import.  Without this declaration MSVC folds
// a delete of the trivially destructible byte array to scalar operator delete.
void __cdecl operator delete[](void *block);

// These are the existing compiler-ABI thunks selected by the retail member
// subobject destructors.  They are called with the subobject address in ECX;
// their published zero-argument spelling reflects the thunk's actual COFF
// name and stack arity.
void j_000298e8(void);
void j_000351b6(void);

class Rva00691200RefBase
{
public:
	virtual ~Rva00691200RefBase();

	void Release()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva00691200Pad
{
	unsigned char m_padding[0x70];
};

class Rva00691200Obj : public Rva00691200Pad, public Rva00691200RefBase
{
};

class Rva00691200Holder
{
public:
	~Rva00691200Holder()
	{
		Rva00691200Obj *object = m_pointer;
		if (object)
		{
			Rva00691200RefBase *ref =
				(Rva00691200RefBase *)((char *)object + 0x70);
			ref->Release();
		}
	}

	Rva00691200Obj *m_pointer;
};

class Rva006910F0Handle
{
public:
	~Rva006910F0Handle();
private:
	void *m_pointer;
};

class Rva00699D60ManualRef
{
public:
	void release(void)
	{
		((void (__fastcall *)(Rva00699D60ManualRef *))j_000298e8)(this);
	}

private:
	unsigned char m_storage[4];
};

class Rva00690FF0Handle
{
public:
	~Rva00690FF0Handle();
private:
	void *m_pointer;
};

class Rva00699D60AudioOwner
{
public:
	~Rva00699D60AudioOwner(void);

private:
	unsigned char m_head[0x04];
	void *m_sample;
	Rva00691200Holder m_child;
	unsigned char m_padding0c[0x08];
	unsigned char *m_array;
	unsigned char m_padding18[0x04];
	Rva00690FF0Handle m_special;    // +0x1c
	Rva006910F0Handle m_ref20;          // +0x20
	Rva00699D60ManualRef m_ref24;            // +0x24, explicitly released
	unsigned char m_tail[0x18];             // object size 0x40
};

Rva00699D60AudioOwner::~Rva00699D60AudioOwner(void)
{
	if (m_sample)
	{
		bool statusIsDifferent = AIL_3D_sample_status(m_sample) != 4;
		if (!statusIsDifferent)
			AIL_stop_3D_sample(m_sample);
	}

	if (m_array)
	{
		delete [] m_array;
		m_array = 0;
	}

	m_ref24.release();
}
