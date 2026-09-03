// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME W3DTreeBuffer resource release path.  The BFME layout has per-type
// vertex/index resources at +0x04/+0x54, five shader/resource slots at
// +0xA4, and the tree texture/count at +0x1E3914/+0x1E3918.

typedef int Int;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class RefCountClass
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

private:
	Int m_refCount;
};

class BfmeShaderResource
{
public:
	virtual long __stdcall slot0(void);
	virtual long __stdcall slot4(void);
	virtual long __stdcall Release_Ref(void);
};

class TextureClass
{
public:
	void Release_Ref(void);
};

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock() { W3DRadarResetLock(); }
	~BfmeRadarResetLock() { W3DRadarResetUnlock(); }
};

class W3DTreeBuffer
{
public:
	void freeTreeBuffers(void);

private:
	void *m_vftable;
	RefCountClass *m_typeVertex[20];
	RefCountClass *m_typeIndex[20];
	BfmeShaderResource *m_resource0;
	BfmeShaderResource *m_resource1;
	BfmeShaderResource *m_resource2;
	BfmeShaderResource *m_resource3;
	BfmeShaderResource *m_resource4;
	char m_padding[0x1e3914 - 0xb8];
	TextureClass *m_treeTexture;
	Int m_numTreeTypes;
};

void W3DTreeBuffer::freeTreeBuffers(void)
{
	BfmeRadarResetLock lock;

	Int i;
	for (i = 0; i < m_numTreeTypes; ++i) {
		if (m_typeVertex[i]) {
			m_typeVertex[i]->Release_Ref();
			m_typeVertex[i] = 0;
		}
		if (m_typeIndex[i]) {
			m_typeIndex[i]->Release_Ref();
			m_typeIndex[i] = 0;
		}
	}

	if (m_resource0)
		m_resource0->Release_Ref();
	if (m_resource1)
		m_resource1->Release_Ref();
	if (m_resource2)
		m_resource2->Release_Ref();
	if (m_resource3)
		m_resource3->Release_Ref();
	if (m_resource4)
		m_resource4->Release_Ref();
	m_resource4 = 0;
	_ReadWriteBarrier();

	if (m_treeTexture) {
		m_treeTexture->Release_Ref();
		m_treeTexture = 0;
	}

	m_resource0 = 0;
	m_resource1 = 0;
	m_resource2 = 0;
	m_resource3 = 0;

}
