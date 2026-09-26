// Holder destructor: release the object behind this+0 whose refcount mixin
// lives at +0x70 (vtable) / +0x74 (count). InterlockedDecrement, then delete
// through slot 0 with the deleting flag when the count has fallen to <= 0.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class Rva00691200RefBase
{
public:
	virtual ~Rva00691200RefBase();

	void Release(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva00691200Pad
{
	unsigned char m_pad[0x70];
};

class Rva00691200Obj : public Rva00691200Pad, public Rva00691200RefBase
{
};

class Rva00691200Holder
{
public:
	~Rva00691200Holder();

private:
	Rva00691200Obj *m_ptr;
};

// ??1Rva00691200Holder@@QAE@XZ
Rva00691200Holder::~Rva00691200Holder()
{
	Rva00691200Obj *obj = m_ptr;
	if (obj)
	{
		Rva00691200RefBase *ref = (Rva00691200RefBase *)((char *)obj + 0x70);
		ref->Release();
	}
}
