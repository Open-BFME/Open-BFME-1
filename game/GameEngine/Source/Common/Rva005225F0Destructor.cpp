// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the destructor at 0x005225F0 (141 B) zeroes the singleton
// g_bfmeThingCB (0x012F49D0, already named) then releases two ref-counted
// pointers at +0x3C and +0x40 -- each a manual (non-atomic) refcount at the
// pointee's +4 decremented, and the pointee's virtual deleting destructor
// (vtable slot 0, push 1) called once the count reaches zero, the same shape
// as Bfme5RefHoldersByVal.cpp's Bfme5RefCounted/Release_Ref -- before
// chaining to the already-landed base destructor Gen_dtor_004654c0
// (0x00021FC1).

class BfmeThingCB;
extern BfmeThingCB *g_bfmeThingCB;				// retail 0x012F49D0

class Rva005225F0RefCounted
{
public:
	void Release_Ref()
	{
		if ((m_refs = m_refs - 1) <= 0)
			Delete_This(1);
	}

protected:
	virtual void Delete_This(unsigned int);
	int m_refs;
};

class Rva005225F0RefPtr
{
public:
	~Rva005225F0RefPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva005225F0RefCounted *m_ptr;
};

class Gen_dtor_004654c0
{
public:
	virtual ~Gen_dtor_004654c0();
};

class Rva005225F0 : public Gen_dtor_004654c0
{
public:
	virtual ~Rva005225F0();

private:
	char m_unreconstructed04[ 0x3c - 0x04 ];
	Rva005225F0RefPtr m_ptr3c;
	Rva005225F0RefPtr m_ptr40;
};

// ??1Rva005225F0@@UAE@XZ
Rva005225F0::~Rva005225F0()
{
	g_bfmeThingCB = 0;
}
