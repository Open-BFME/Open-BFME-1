// cl: /DNDEBUG /MD /EHsc
// readable body of ?freeTerrainBuffers@W3DTerrainBackground@@IAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackground.cpp
// Open-BFME: W3DTerrainBackground::freeTerrainBuffers, retail 0x007286F0,
// 97 bytes.
//
// The reference's body: release the two buffers, zero the two counts, release
// the map twice.  In BFME the second release is a SECOND pointer, at +0x60
// rather than the +0x58 the first one uses, and two more words at +0x68 and
// +0x6C are zeroed after it; the reference's m_initialized store is gone.
//
// REF_PTR_RELEASE and Release_Ref are both inline, which is the whole shape of
// the body: test the pointer, decrement the count at +0x04, and only on zero
// take the virtual slot 0 -- Delete_This, called with no argument, not a
// deleting destructor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);				// vtable slot 0

	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

private:
	int NumRefs;						// +0x04, behind the vtable pointer
};

// BFME clears the pointer INSIDE the guard: a null pointer skips the store
// too, which is what puts each store ahead of the next block's load.
#define REF_PTR_RELEASE(x)	{ if (x) { x->Release_Ref(); x = 0; } }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainBackground.h
class W3DTerrainBackground
{
protected:
	void freeTerrainBuffers(void);

private:
	unsigned char m_unmodelled_000[0x1C];
	RefCountClass *m_vertexTerrain;				// +0x1C
	unsigned char m_unmodelled_020[0x24 - 0x20];
	RefCountClass *m_indexTerrain;				// +0x24
	unsigned char m_unmodelled_028[0x38 - 0x28];
	int m_curNumTerrainVertices;				// +0x38
	int m_curNumTerrainIndices;				// +0x3C
	unsigned char m_unmodelled_040[0x58 - 0x40];
	RefCountClass *m_map;					// +0x58
	unsigned char m_unmodelled_05c[0x60 - 0x5C];
	RefCountClass *m_bfmeSecondMap;				// +0x60
	unsigned char m_unmodelled_064[0x68 - 0x64];
	int m_bfmeCount68;					// +0x68
	int m_bfmeCount6C;					// +0x6C
};

void W3DTerrainBackground::freeTerrainBuffers(void)
{
	REF_PTR_RELEASE(m_vertexTerrain);
	REF_PTR_RELEASE(m_indexTerrain);
	m_curNumTerrainVertices=0;
	m_curNumTerrainIndices=0;
	REF_PTR_RELEASE(m_map);
	REF_PTR_RELEASE(m_bfmeSecondMap);
	m_bfmeCount68=0;
	m_bfmeCount6C=0;
}
