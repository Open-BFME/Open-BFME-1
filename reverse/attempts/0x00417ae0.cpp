// ?run@Rva00417AE0@@QAEXH@Z
// partial score=0.26 date=2026-09-16
// scratch-only native reconstruction for retail RVA 0x00417AE0 (366 bytes)
// No identity or callee ABI claim is made for the neutral 0x00417430 adapter.
// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

class Rva00087750Counted
{
public:
	virtual ~Rva00087750Counted();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

// This is the proven 73-byte intrusive-reference assignment ABI at 0x00087750.
class Rva00087750Ref
{
public:
	Rva00087750Ref &operator=(const Rva00087750Ref &rhs);

	~Rva00087750Ref()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva00087750Counted *m_ptr;
};

class Rva00417430
{
public:
	// Neutral callsite view: the retail body is separately ABI-checked at its
	// exact caller. Its native return is a one-pointer ref passed by hidden
	// result address, followed by the selector integer.
	Rva00087750Ref call(int selector);
	Rva00087750Ref select(int selector);
	void emit(void *value, void *param);

private:
	unsigned char m_head[0x140];
};

class Rva00417AudioSlot
{
public:
	unsigned char m_head[0x0c];
	Rva00087750Ref m_info;
	unsigned int m_handle;
};

class Rva00417AE0 : public Rva00417430
{
public:
	void run(int arg);

private:
	bool m_flagA;				// +0x140
	bool m_flagB;				// +0x141
	unsigned char m_unused142;			// +0x142
	bool m_flagC;				// +0x143
	Rva00417AudioSlot *m_first;		// +0x144
	Rva00417AudioSlot *m_second;		// +0x148
};

void Rva00417AE0::run(int arg)
{
	if (m_flagA && m_flagB && m_flagC)
	{
		bool changed = false;
		Rva00087750Ref first = call(arg);

		Rva00087750Ref firstSlot = { 0 };
		if (m_first)
			firstSlot = m_first->m_info;

		if (first.m_ptr != firstSlot.m_ptr)
			changed = true;

		Rva00087750Ref second = select((int)arg);
		Rva00087750Ref secondSlot = { 0 };
		if (m_second)
			secondSlot = m_second->m_info;

		if (second.m_ptr != secondSlot.m_ptr || changed)
			emit((void *)arg, 0);
	}
}

