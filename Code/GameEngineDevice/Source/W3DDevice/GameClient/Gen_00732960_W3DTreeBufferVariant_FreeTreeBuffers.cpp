// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?d_00732960@@YAXXZ: address-derived near-twin of
// ?freeTreeBuffers@W3DTreeBuffer@@QAEXXZ @ Code/GameEngineDevice/Source/W3DDevice/GameClient/Gen_0071C2D0_W3DTreeBuffer_FreeTreeBuffers.cpp
// Same shape; this class's tree texture/count fields sit at +0x2A9904/+0x2A9908
// instead of +0x1E3914/+0x1E3918 (a wider padding block between the shader
// resource slots and the tree texture pointer).

typedef int Int;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass_732960
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

class BfmeShaderResource_732960
{
public:
	virtual long __stdcall slot0(void);
	virtual long __stdcall slot4(void);
	virtual long __stdcall Release_Ref(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass_732960
{
public:
	void Release_Ref(void);
};

class BfmeRadarResetLock_732960
{
public:
	BfmeRadarResetLock_732960() { W3DRadarResetLock(); }
	~BfmeRadarResetLock_732960() { W3DRadarResetUnlock(); }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTreeBuffer.h
class Gen_00732960_W3DTreeBufferVariant
{
public:
	void freeTreeBuffers(void);

private:
	void *m_vftable;
	RefCountClass_732960 *m_typeVertex[20];
	RefCountClass_732960 *m_typeIndex[20];
	BfmeShaderResource_732960 *m_resource0;
	BfmeShaderResource_732960 *m_resource1;
	BfmeShaderResource_732960 *m_resource2;
	BfmeShaderResource_732960 *m_resource3;
	BfmeShaderResource_732960 *m_resource4;
	char m_padding[0x2a9904 - 0xb8];
	TextureClass_732960 *m_treeTexture;
	Int m_numTreeTypes;
};

void Gen_00732960_W3DTreeBufferVariant::freeTreeBuffers(void)
{
	BfmeRadarResetLock_732960 lock;

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
