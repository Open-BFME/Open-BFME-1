// Four 46-byte destructors of a vector-like member pair. Nothing is released
// when the start pointer is null; otherwise the byte count is the pointer
// difference in elements scaled back up by four -- sar 2 then shl 2, which is
// what a T * difference times sizeof(T) compiles to for a four-byte T -- and
// the release forks on 0x80.
//
// Above 0x80 bytes the block goes to plain operator delete; at or below it,
// to __node_alloc::_M_deallocate with the size. That fork IS the STLport node
// allocator's deallocate, inlined, and the comparison is unsigned because the
// size is.
//
// _M_deallocate is a PRIVATE static there -- its decorated name says C, not S
// -- so each of these classes has to be a friend of it to reach the same
// symbol. Declaring it public would mangle a name that does not exist.

typedef unsigned int UnsignedInt;

void __cdecl operator delete(void *block);				// retail 0x00881EB0

class Gen_00136800;
class Gen_001d7220;
class Gen_00261400;
class Gen_00370da0;

namespace _STL
{

template <bool __threads, int __inst> class __node_alloc
{
private:
	static void _M_deallocate(void *block, UnsignedInt bytes);	// retail 0x0082E5F0

	friend class ::Gen_00136800;
	friend class ::Gen_001d7220;
	friend class ::Gen_00261400;
	friend class ::Gen_00370da0;
};

}

class Gen_00136800
{
public:
	~Gen_00136800();

private:
	char m_bfmeHead[0x04];
	int *m_bfmeStart;						// +0x04
	char m_bfmeMid[0x0C - 0x08];
	int *m_bfmeEnd;							// +0x0C
};

class Gen_001d7220
{
public:
	~Gen_001d7220();

private:
	char m_bfmeHead[0x04];
	int *m_bfmeStart;						// +0x04
	char m_bfmeMid[0x0C - 0x08];
	int *m_bfmeEnd;							// +0x0C
};

class Gen_00261400
{
public:
	~Gen_00261400();

private:
	char m_bfmeHead[0x04];
	int *m_bfmeStart;						// +0x04
	char m_bfmeMid[0x0C - 0x08];
	int *m_bfmeEnd;							// +0x0C
};

class Gen_00370da0
{
public:
	~Gen_00370da0();

private:
	char m_bfmeHead[0x04];
	int *m_bfmeStart;						// +0x04
	char m_bfmeMid[0x0C - 0x08];
	int *m_bfmeEnd;							// +0x0C
};

// ??1Gen_00136800@@QAE@XZ
Gen_00136800::~Gen_00136800(void)
{
	if (m_bfmeStart)
	{
		UnsignedInt bytes = (UnsignedInt)((m_bfmeEnd - m_bfmeStart) * sizeof(int));

		if (bytes > 0x80)
			operator delete(m_bfmeStart);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(m_bfmeStart, bytes);
	}
}

// ??1Gen_001d7220@@QAE@XZ
Gen_001d7220::~Gen_001d7220(void)
{
	if (m_bfmeStart)
	{
		UnsignedInt bytes = (UnsignedInt)((m_bfmeEnd - m_bfmeStart) * sizeof(int));

		if (bytes > 0x80)
			operator delete(m_bfmeStart);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(m_bfmeStart, bytes);
	}
}

// ??1Gen_00261400@@QAE@XZ
Gen_00261400::~Gen_00261400(void)
{
	if (m_bfmeStart)
	{
		UnsignedInt bytes = (UnsignedInt)((m_bfmeEnd - m_bfmeStart) * sizeof(int));

		if (bytes > 0x80)
			operator delete(m_bfmeStart);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(m_bfmeStart, bytes);
	}
}

// ??1Gen_00370da0@@QAE@XZ
Gen_00370da0::~Gen_00370da0(void)
{
	if (m_bfmeStart)
	{
		UnsignedInt bytes = (UnsignedInt)((m_bfmeEnd - m_bfmeStart) * sizeof(int));

		if (bytes > 0x80)
			operator delete(m_bfmeStart);
		else
			_STL::__node_alloc<true, 0>::_M_deallocate(m_bfmeStart, bytes);
	}
}
