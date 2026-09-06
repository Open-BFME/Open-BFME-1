// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Open-BFME7: retail 0x00476440 (98 bytes) is the three-member cousin of the two-member
// destructors in BigTwoMemberDtors.cpp: the Inner010EAD58 vtable head, a ref-counted
// pointer at +8 (released when the count reaches zero) and a member with an out-of-line
// destructor at +0xC, destroyed in reverse declaration order.

class Inner010EAD58
{
public:
	virtual ~Inner010EAD58() {}
};

class Mem004CRefCounted
{
public:
	void Release_Ref()
	{
		if( (m_refs = m_refs - 1) <= 0 )
			Delete_This( 1 );
	}
protected:
	virtual void Delete_This( unsigned int );
	int m_refs;
};

class Rva00476440RefPtr
{
public:
	~Rva00476440RefPtr()
	{
		if( m_ptr )
			m_ptr->Release_Ref();
	}
private:
	Mem004CRefCounted *m_ptr;
};

class Mem0001FD66
{
public:
	~Mem0001FD66();
};

class Rva00476440
{
public:
	~Rva00476440();
	Inner010EAD58 m_head;
	char m_pad[ 4 ];
	Rva00476440RefPtr m_ref;		// +0x8
	Mem0001FD66 m_tail;			// +0xC
};

Rva00476440::~Rva00476440() {}
