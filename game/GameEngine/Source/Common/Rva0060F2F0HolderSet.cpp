// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: Rva0060F2F0Holder::bfmeSet(Rva0060F2F0Ptr, int) -- retail 0x0060F2F0, 166B.
//
// Refcounted smart-pointer assignment with a by-value parameter: addRef the
// incoming pointee, release the old one at +0x238, store, then write the int
// at +0x23C; the parameter's own destructor releases its reference last. No
// named caller reaches the body (ILT 0x00042AD2 is a gap thunk), so every
// name here is address-derived.
//
// Shape lever: retail re-tests the OLD pointee before its virtual drop
// (`test esi,esi / je` after InterlockedDecrement) but tests the parameter's
// pointee only once. VC7.1 folds a `delete p` null test once `p` was tested
// or dereferenced, so the assignment must release through an inlined member
// that does `delete this`, while the destructor tests and deletes the same
// variable. Spelling both the same way lands 162 B (see docs/shape_levers.md).
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *lpAddend);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class Rva0060F2F0Counted
{
public:
	virtual ~Rva0060F2F0Counted();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class Rva0060F2F0Ptr
{
public:
	Rva0060F2F0Ptr(const Rva0060F2F0Ptr &other);

	~Rva0060F2F0Ptr()
	{
		if (m_ptr && InterlockedDecrement(&m_ptr->m_refCount) <= 0)
			delete m_ptr;
	}

	Rva0060F2F0Ptr &operator=(const Rva0060F2F0Ptr &other)
	{
		if (this != &other)
		{
			Rva0060F2F0Counted *p = other.m_ptr;

			if (p)
				InterlockedIncrement(&p->m_refCount);
			if (m_ptr)
				m_ptr->Release_Ref();
			m_ptr = p;
		}

		return *this;
	}

	Rva0060F2F0Counted *m_ptr;
};

class Rva0060F2F0Holder
{
public:
	void bfmeSet(Rva0060F2F0Ptr src, int extra);

	unsigned char m_head[0x238];
	Rva0060F2F0Ptr m_ptr;
	int m_extra;
};

// ?bfmeSet@Rva0060F2F0Holder@@QAEXVRva0060F2F0Ptr@@H@Z
void Rva0060F2F0Holder::bfmeSet(Rva0060F2F0Ptr src, int extra)
{
	m_ptr = src;
	m_extra = extra;
}
