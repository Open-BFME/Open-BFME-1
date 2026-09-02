// cl: /O2 /DNDEBUG /MD /EHsc
// W3DBridge::clearBridge, retail 0x006D7680 (78 bytes).
//
// Zero Hour releases the texture plus three meshes. BFME load() already showed
// the texture at +0x34 uses a different out-of-line release, so this body only
// clears m_visible and the three mesh RefCount pointers at +0x38/+0x7C/+0xB8.
// Named caller: W3DBridge::load. Adjacent to cullBridge at 0x006D76F0.

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

class MeshClass : public RefCountClass
{
};

class W3DBridge
{
public:
	void clearBridge(void);

private:
	unsigned char m_unmodelled_000[0x38];
	MeshClass *m_leftMesh;
	unsigned char m_unmodelled_03C[0x7C - 0x3C];
	MeshClass *m_sectionMesh;
	unsigned char m_unmodelled_080[0xB8 - 0x80];
	MeshClass *m_rightMesh;
	unsigned char m_unmodelled_0BC[0x104 - 0xBC];
	bool m_visible;
};

void W3DBridge::clearBridge(void)
{
	m_visible = false;
	if (m_leftMesh)
	{
		m_leftMesh->Release_Ref();
		m_leftMesh = 0;
	}
	if (m_sectionMesh)
	{
		m_sectionMesh->Release_Ref();
		m_sectionMesh = 0;
	}
	if (m_rightMesh)
	{
		m_rightMesh->Release_Ref();
		m_rightMesh = 0;
	}
}
