// cl: /DNDEBUG /MD /EHsc
// W3DFloorBuffer::releaseResources, retail 0x006F7350, called by the destructor
// through the ILT thunk at 0x000315F2.

typedef int Int;

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

class W3DRadarResetGuard
{
public:
	W3DRadarResetGuard(void)
	{
		W3DRadarResetLock();
	}

	~W3DRadarResetGuard(void)
	{
		bfmeUnlock1179();
	}
};

class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;

	void Release_Ref(void)
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

	Int m_numRefs;
};

class TextureClass
{
public:
	void Release_Ref(void);
};

class TextureRef
{
public:
	TextureClass *m_texture;
};

class W3DFloorBuffer
{
public:
	void releaseResources(void);

private:
	void *m_vftable;
	RefCountClass *m_04;
	RefCountClass *m_08;
	RefCountClass *m_0c;
	unsigned char m_padding10[0x0c];
	TextureRef m_1c;
};

// ?releaseResources@W3DFloorBuffer@@QAEXXZ
void W3DFloorBuffer::releaseResources(void)
{
	W3DRadarResetGuard lock;

	if (m_04)
	{
		m_04->Release_Ref();
		m_04 = 0;
	}
	if (m_08)
	{
		m_08->Release_Ref();
		m_08 = 0;
	}
	if (m_0c)
	{
		m_0c->Release_Ref();
		m_0c = 0;
	}
	if (m_1c.m_texture)
	{
		m_1c.m_texture->Release_Ref();
		m_1c.m_texture = 0;
	}
}
