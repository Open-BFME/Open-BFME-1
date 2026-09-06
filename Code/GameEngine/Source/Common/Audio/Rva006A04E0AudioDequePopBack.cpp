// cl: /O2 /DNDEBUG /MD /EHs-c-

// Retail 0x006A04E0, 54 bytes.  This is the fast path that retires the last
// handle in an STLport deque block: the current and first pointers are at
// +0x10 and +0x14, the handle points at a +4 refcount, and a non-positive
// InterlockedDecrement result dispatches the slot-zero deleting destructor.
// The empty path calls the existing thiscall deque helper via its retail
// thunk at ILT 0x0001309D (target 0x0069E810).  The helper's four-deque-
// pointer layout is kept here so its thiscall ABI is explicit.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *addend);

class Rva006A04E0AudioHandle
{
public:
	virtual ~Rva006A04E0AudioHandle();

	void releaseRef()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

typedef Rva006A04E0AudioHandle *Rva006A04E0AudioHandleRef;

class Rva006A04E0AudioDeque
{
public:
	void releaseLast();
	void _M_pop_back_aux();

private:
	char m_pad[0x10];
	Rva006A04E0AudioHandleRef *m_cur;
	Rva006A04E0AudioHandleRef *m_first;
	Rva006A04E0AudioHandleRef *m_last;
	Rva006A04E0AudioHandleRef **m_node;
};

void Rva006A04E0AudioDeque::releaseLast()
{
	if (m_cur != m_first)
	{
		m_cur = (Rva006A04E0AudioHandleRef *)((char *)m_cur - 4);
		if (*m_cur != 0)
			(*m_cur)->releaseRef();
	}
	else
		_M_pop_back_aux();
}
