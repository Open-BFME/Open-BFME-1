// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: ~Rva0049C020Owner at 0x0049C020 (556 B), a BfmeBaseVUH-derived
// record with 26 destructible members (EH states 0..0x19): AsciiStrings, two
// 12-byte member types destroyed through their ILT thunks (0x000351D4, the
// vector<Gen0049B890> destructor, for the twelve consecutive entries at
// +0xa8..+0x134; 0x00026AB2, the PlayerUpgradeSpecialPowerModuleData
// destructor, for the four others), two STLport vectors of 4-byte elements (inline deallocation:
// operator delete above 0x80 bytes, the node allocator below), and finally
// the base destructor that deletes the owned object at +4.
extern void __cdecl operator delete(void *);

class AsciiString
{
public:
	~AsciiString() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_data;
};

class Rva0049B890Elem
{
public:
	~Rva0049B890Elem();
private:
	char m_body[12];
};

class Rva000658A0Elem
{
public:
	~Rva000658A0Elem();
private:
	char m_body[12];
};

namespace _STL
{
template <bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};
}

template <class T>
class Rva0049C020Vector
{
public:
	~Rva0049C020Vector()
	{
		if (m_start != 0)
		{
			unsigned int bytes = (unsigned int)(m_end_of_storage - m_start) * sizeof(T);
			if (bytes > 0x80)
				::operator delete(m_start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
};

class Rva0049C020Owned
{
public:
	virtual ~Rva0049C020Owned();
};

class BfmeBaseVUH
{
public:
	virtual ~BfmeBaseVUH()
	{
		if (m_owned != 0)
			delete m_owned;
		m_owned = 0;
	}
	Rva0049C020Owned *m_owned;
};

class Rva0049C020Owner : public BfmeBaseVUH
{
public:
	virtual ~Rva0049C020Owner();
private:
	int m_08;
	AsciiString m_str0c;
	char m_gap10[0x18];
	Rva000658A0Elem m_b28;
	char m_gap34[8];
	AsciiString m_str3c;
	AsciiString m_str40;
	Rva000658A0Elem m_b44;
	Rva000658A0Elem m_b50;
	AsciiString m_str5c;
	AsciiString m_str60;
	AsciiString m_str64;
	AsciiString m_str68;
	char m_gap6c[0x18];
	Rva0049C020Vector<int> m_vec84;
	int m_90;
	Rva000658A0Elem m_b94;
	char m_gapa0[8];
	Rva0049B890Elem m_a0;
	Rva0049B890Elem m_a1;
	Rva0049B890Elem m_a2;
	Rva0049B890Elem m_a3;
	Rva0049B890Elem m_a4;
	Rva0049B890Elem m_a5;
	Rva0049B890Elem m_a6;
	Rva0049B890Elem m_a7;
	Rva0049B890Elem m_a8;
	Rva0049B890Elem m_a9;
	Rva0049B890Elem m_a10;
	Rva0049B890Elem m_a11;
	Rva0049C020Vector<int> m_vec138;
	char m_gap144[0x40];
	AsciiString m_str184;
};

Rva0049C020Owner::~Rva0049C020Owner()
{
}
