// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x007461B0 (390 B) of the 0x2450-byte owner
// whose constructor is the 977-byte dump at 0x00745B10. Three bases: a primary
// base destroyed out of line through the ILT at 0x0003732B, a second base at
// +0xb4 whose destructor only restores its own vtable, and SubsystemInterface
// at +0xfc. Members, in destruction order: two manually released ref-counted
// pointers at +0x108/+0x104, the tgrid member at +0x2448 (ILT 0x0001A933), two
// AsciiStrings, a vector of 24-byte records (inline STLport deallocation), two
// embedded Rva00740AE0Base-derived objects (each owning a record vector
// destroyed through the ILT at 0x00021E18) and the Rva00740BC0 two-array
// member at +0x280 (ILT 0x000063DE).
extern void __cdecl operator delete(void *);

namespace _STL
{
template <bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};
}

class AsciiString
{
public:
	~AsciiString() { releaseBuffer(); }
private:
	void releaseBuffer();
	char *m_data;
};

class Rva007461B0RefCounted
{
public:
	virtual void Delete_This() = 0;
	int NumRefs;
};

class Rva00459D50Member
{
public:
	~Rva00459D50Member();
private:
	char m_body[8];
};

struct Rva007461B0Record
{
	char m_body[24];
};

template <class T>
class Rva007461B0Vector
{
public:
	~Rva007461B0Vector()
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

class GiantBirdNestedTail
{
public:
	~GiantBirdNestedTail();
private:
	char m_body[12];
};

class Rva00740AE0Base
{
public:
	virtual void dummy();
	~Rva00740AE0Base() {}
	char m_body[0x28];
};

class Rva007461B0Path : public Rva00740AE0Base
{
public:
	~Rva007461B0Path() {}
private:
	GiantBirdNestedTail m_records;
	char m_tail[0x64 - 0x2c - 12];
};

class Rva00740BC0Member
{
public:
	~Rva00740BC0Member();
private:
	char m_body[0x22f4 - 0x280];
};

class Rva0045C1B0Base
{
public:
	virtual ~Rva0045C1B0Base();
	char m_body[0xb4 - 4];
};

class Rva007461B0BaseS
{
public:
	virtual ~Rva007461B0BaseS() {}
	char m_body[0x48 - 4];
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class Rva00745B10Owner : public Rva0045C1B0Base, public Rva007461B0BaseS, public SubsystemInterface
{
public:
	virtual ~Rva00745B10Owner();
private:
	int m_100;
	Rva007461B0RefCounted *m_104;
	Rva007461B0RefCounted *m_108;
	char m_gap10c[0x280 - 0x10c];
	Rva00740BC0Member m_280;
	Rva007461B0Path m_22f4;
	Rva007461B0Path m_2358;
	char m_gap23bc[0x23cc - 0x23bc];
	Rva007461B0Vector<Rva007461B0Record> m_23cc;
	char m_gap23d8[0x242c - 0x23d8];
	AsciiString m_242c;
	AsciiString m_2430;
	char m_gap2434[0x2448 - 0x2434];
	Rva00459D50Member m_2448;
};

Rva00745B10Owner::~Rva00745B10Owner()
{
	Rva007461B0RefCounted *p = m_108;
	if (p)
	{
		if (--p->NumRefs == 0)
			p->Delete_This();
		m_108 = 0;
	}
	p = m_104;
	if (p)
	{
		if (--p->NumRefs == 0)
			p->Delete_This();
		m_104 = 0;
	}
}
