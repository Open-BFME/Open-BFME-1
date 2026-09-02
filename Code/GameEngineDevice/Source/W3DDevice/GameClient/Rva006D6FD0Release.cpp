// cl: /DNDEBUG /MD /EHsc
// Retail 0x006D6FD0 (134 bytes). Named callers: BaseHeightMapRenderObjClass
// destructor and a scalar deleting dtor. Two inline Release_Ref at +0 and +8,
// then two out-of-line releases at +0x14 and +0x10.

typedef int Int;

class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	Int NumRefs;
};

class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureRef
{
public:
	~TextureRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	TextureClass *m_ptr;
};

class Rva006D6FD0
{
public:
	~Rva006D6FD0();

private:
	RefCountClass *m_a;
	unsigned char m_pad04[4];
	RefCountClass *m_b;
	unsigned char m_pad0C[4];
	TextureRef m_c;
	TextureRef m_d;
};

Rva006D6FD0::~Rva006D6FD0()
{
	if (m_a)
	{
		m_a->Release_Ref();
		m_a = 0;
	}
	if (m_b)
	{
		m_b->Release_Ref();
		m_b = 0;
	}
}
