// cl: /DNDEBUG /MD /EHsc
// readable body of ?shutdown@TerrainTracksRenderObjClassSystem@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
// Open-BFME: TerrainTracksRenderObjClassSystem::shutdown, retail 0x0072EDF0,
// 142 bytes.
//
// The reference's body unchanged: release the unbound tracks still fading out,
// then walk the free list releasing each module, then drop the three render
// resources.
//
// Every reference count is inlined, so the shape names the layout. A release
// is `dec [ecx+4]` and, at zero, vtable slot 0 -- RefCountClass with its count
// at +4 behind the vptr -- and the pointer is cleared afterwards, which is the
// reference's REF_PTR_RELEASE down to the store. The tracks carry m_bound at
// +0x12ED and m_nextSystem at +0x12FC, and the system itself has the vertex
// buffer at +0x00, the index buffer at +0x04, the material at +0x08 and the
// two module lists at +0x10 and +0x14 -- the release order being what tells
// the three resources apart.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;			// vtable slot 0

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	Int NumRefs;						// this+0x04
};

#define REF_PTR_RELEASE(x) { if (x) { (x)->Release_Ref(); x = 0; } }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClass : public RefCountClass
{
public:
	char m_bfme_head[0x12ED - 8];				// this+0x08 .. +0x12EC, untouched
	Bool m_bound;						// this+0x12ED
	char m_bfme_mid[0x12FC - 0x12EE];
	TerrainTracksRenderObjClass *m_nextSystem;		// this+0x12FC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTerrainTracks.h
class TerrainTracksRenderObjClassSystem
{
public:
	void shutdown(void);

private:
	void releaseTrack(TerrainTracksRenderObjClass *mod);	// ILT 0x000357E7

	RefCountClass *m_vertexBuffer;				// this+0x00
	RefCountClass *m_indexBuffer;				// this+0x04
	RefCountClass *m_vertexMaterialClass;			// this+0x08
	char m_bfme_pad[4];					// this+0x0C, untouched
	TerrainTracksRenderObjClass *m_usedModules;		// this+0x10
	TerrainTracksRenderObjClass *m_freeModules;		// this+0x14
};

void TerrainTracksRenderObjClassSystem::shutdown( void )
{
	TerrainTracksRenderObjClass *nextMod,*mod;

	//release unbound tracks that may still be fading out
	mod=m_usedModules;

	while(mod)
	{
		nextMod=mod->m_nextSystem;

		if (!mod->m_bound)
			releaseTrack(mod);

		mod = nextMod;
	}  // end while

	// free all module storage
	while( m_freeModules )
	{

		nextMod = m_freeModules->m_nextSystem;
		REF_PTR_RELEASE (m_freeModules);
		m_freeModules = nextMod;

	}  // end while

	REF_PTR_RELEASE(m_indexBuffer);
	REF_PTR_RELEASE(m_vertexMaterialClass);
	REF_PTR_RELEASE(m_vertexBuffer);

}  // end shutdown
