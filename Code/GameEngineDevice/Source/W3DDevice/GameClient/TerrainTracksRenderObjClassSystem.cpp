// cl: /DNDEBUG /MD /EHsc
// readable body of ??0TerrainTracksRenderObjClassSystem@@QAE@XZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
// readable body of ?setDetail@TerrainTracksRenderObjClassSystem@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
// readable body of ?shutdown@TerrainTracksRenderObjClassSystem@@QAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp
//
// Construction (retail 0x0072EA50), setDetail and shutdown (0x0072EDF0): the
// three bodies that own the tank-track system's own storage. They came from
// three files with three copies of the class, and the three copies disagreed
// about which of the three W3D resources sits at which of +0x00/+0x04/+0x08 --
// the constructor's copy named them index, material, vertex in that order and
// shutdown's named them vertex, index, material.
//
// Upstream settles it, twice over. The declaration order in
// W3DTerrainTracks.h is m_vertexBuffer, m_indexBuffer, m_vertexMaterialClass,
// m_shaderClass, so shutdown's copy is the one that was right; and once the
// fields are named that way both other bodies fall onto their upstream twins
// line for line. The constructor clears +0x04, +0x08, +0x00 in that order,
// which is upstream's `m_indexBuffer; m_vertexMaterialClass; m_vertexBuffer;`,
// and setDetail releases +0x04 then +0x00, which is the REF_PTR_RELEASE pair
// at the top of upstream's ReAcquireResources. Neither reading is available
// from one body alone.
//
// BFME's constructor has no m_edgesToFlush, so the three GlobalData-fed limits
// sit at +0x1C/+0x20/+0x24 rather than upstream's +0x20/+0x24/+0x28.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct GlobalData
{
	char pad[0x1f4];
	Int m_maxTankTrackEdges;
	Int m_maxTankTrackOpaqueEdges;
	Int m_maxTankTrackFadeDelay;
};

extern GlobalData *TheGlobalData;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	ShaderClass() : shaderBits(0x0010441b) {}

private:
	unsigned int shaderBits;
};

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
	TerrainTracksRenderObjClassSystem();
	void setDetail(void);
	void shutdown(void);
	void ReAcquireResources(void);

private:
	// The access specifiers are half of each mangled name: releaseTrack is
	// ?releaseTrack@...@@AAE..., clearTracks is ?clearTracks@...@@IAE...
	void releaseTrack(TerrainTracksRenderObjClass *mod);	// ILT 0x000357E7

protected:
	void clearTracks(void);

	RefCountClass *m_vertexBuffer;				// this+0x00
	RefCountClass *m_indexBuffer;				// this+0x04
	RefCountClass *m_vertexMaterialClass;			// this+0x08
	ShaderClass m_shaderClass;				// this+0x0C
	TerrainTracksRenderObjClass *m_usedModules;		// this+0x10
	TerrainTracksRenderObjClass *m_freeModules;		// this+0x14
	void *m_TerrainTracksScene;				// this+0x18
	Int m_maxTankTrackEdges;				// this+0x1C
	Int m_maxTankTrackOpaqueEdges;				// this+0x20
	Int m_maxTankTrackFadeDelay;				// this+0x24
};

// ??0TerrainTracksRenderObjClassSystem@@QAE@XZ
TerrainTracksRenderObjClassSystem::TerrainTracksRenderObjClassSystem()
{
	m_usedModules = 0;
	m_freeModules = 0;
	m_TerrainTracksScene = 0;
	m_indexBuffer = 0;
	m_vertexMaterialClass = 0;
	m_vertexBuffer = 0;

	m_maxTankTrackEdges = TheGlobalData->m_maxTankTrackEdges;
	m_maxTankTrackOpaqueEdges = TheGlobalData->m_maxTankTrackOpaqueEdges;
	m_maxTankTrackFadeDelay = TheGlobalData->m_maxTankTrackFadeDelay;
}

// ?setDetail@TerrainTracksRenderObjClassSystem@@QAEXXZ
void TerrainTracksRenderObjClassSystem::setDetail()
{
	clearTracks();

	RefCountClass *resource = m_indexBuffer;
	if (resource) {
		resource->Release_Ref();
		*(RefCountClass * volatile *)&m_indexBuffer = 0;
	}
	resource = m_vertexBuffer;
	if (resource) {
		resource->Release_Ref();
		*(RefCountClass * volatile *)&m_vertexBuffer = 0;
	}

	m_maxTankTrackEdges = TheGlobalData->m_maxTankTrackEdges;
	m_maxTankTrackOpaqueEdges = TheGlobalData->m_maxTankTrackOpaqueEdges;
	m_maxTankTrackFadeDelay = TheGlobalData->m_maxTankTrackFadeDelay;

	ReAcquireResources();
}

// ?shutdown@TerrainTracksRenderObjClassSystem@@QAEXXZ
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
