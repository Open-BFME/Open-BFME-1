// cl: /DNDEBUG /MD /EHsc
// readable body of ?allocateTerrainBuffers@W3DTerrainBackground@@QAEXPAVWorldHeightMap@@HHH@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackground.cpp
// Open-BFME5: W3DTerrainBackground::allocateTerrainBuffers, retail 0x00728770,
// converted out of Code/gen_asm/d_0071bb90.asm. The reference body ports
// unchanged.
//
// The 83 bytes date the class: +0x38 m_curNumTerrainVertices,
// +0x3C m_curNumTerrainIndices, +0x40 m_xOrigin, +0x44 m_yOrigin,
// +0x48 m_width, +0x4C m_map, +0x50 m_initialized.
//
// The tail is REF_PTR_SET spelled out. Retail adds a reference to the incoming
// map without testing it -- the null test at the top of the function already
// proved it -- then releases the old one under a test, and Release_Ref's
// `--NumRefs == 0` arm goes through slot 0 of the object's own vtable. NumRefs
// is at +0x04, which is the WWLib RefCountClass layout unchanged.

typedef int Int;

#define NULL 0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_Self( void );						///< slot 0

	void Add_Ref( void ) { NumRefs++; }
	void Release_Ref( void ) { if (--NumRefs == 0) Delete_Self(); }

protected:
	Int NumRefs;											///< +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap : public RefCountClass
{
};

#define REF_PTR_SET(dst, src)								\
	{														\
		if (src) (src)->Add_Ref();							\
		if (dst) (dst)->Release_Ref();						\
		(dst) = (src);										\
	}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainBackground.h
class W3DTerrainBackground
{
public:
	void allocateTerrainBuffers( WorldHeightMap *htMap, Int xOrigin, Int yOrigin, Int width );

protected:
	void freeTerrainBuffers( void );

private:
	unsigned char m_unreconstructed_00[0x38];
	Int m_curNumTerrainVertices;							///< +0x38
	Int m_curNumTerrainIndices;								///< +0x3C
	Int m_xOrigin;											///< +0x40
	Int m_yOrigin;											///< +0x44
	Int m_width;											///< +0x48
	WorldHeightMap *m_map;									///< +0x4C
	bool m_initialized;										///< +0x50
};

// ?allocateTerrainBuffers@W3DTerrainBackground@@QAEXPAVWorldHeightMap@@HHH@Z
void W3DTerrainBackground::allocateTerrainBuffers(WorldHeightMap *htMap, Int xOrigin, Int yOrigin, Int width)
{
	if (htMap==NULL) return;
	freeTerrainBuffers(); // in case already allocated. jba [3/24/2003]
	m_curNumTerrainVertices=0;
	m_curNumTerrainIndices=0;
	m_xOrigin = xOrigin;
	m_yOrigin = yOrigin;
	m_width = width;
	m_initialized = true;
	REF_PTR_SET(m_map, htMap);
}
