// ?bindTrack@TerrainTracksRenderObjClassSystem@@QAEPAVTerrainTracksRenderObjClass@@PAXMPBD11@Z
// partial score=0.75 date=2026-09-03
// BFME retail 0x0072FCA0: bind a terrain track object from the free list.

typedef unsigned char Bool;

class TerrainTracksRenderObjClass
{
public:
	void init(float width, float length, const char *texture);
	unsigned char m_pad00[0x12ED];
	Bool m_bound;
	unsigned char m_pad12EE[0x0E];
	TerrainTracksRenderObjClass *m_nextSystem;
	TerrainTracksRenderObjClass *m_prevSystem;
};

class TerrainTracksRenderObjClassSystem
{
public:
	TerrainTracksRenderObjClass *bindTrack(void *owner, float length,
		const char *texture, const char *leftBone, const char *rightBone);

private:
	unsigned char m_pad00[0x10];
	TerrainTracksRenderObjClass *m_usedModules;
	TerrainTracksRenderObjClass *m_freeModules;
};

extern float computeTrackSpacing(const char *rightBone, float length,
	const char *texture);

TerrainTracksRenderObjClass *TerrainTracksRenderObjClassSystem::bindTrack(
	void *renderObject, float length, const char *texture,
	const char *leftBone, const char *rightBone)
{
	TerrainTracksRenderObjClass *mod;

	mod = m_freeModules;
	if (mod)
	{
		if (mod->m_nextSystem)
			mod->m_nextSystem->m_prevSystem = mod->m_prevSystem;
		if (mod->m_prevSystem)
			mod->m_prevSystem->m_nextSystem = mod->m_nextSystem;
		else
			m_freeModules = mod->m_nextSystem;

		mod->m_prevSystem = 0;
		mod->m_nextSystem = m_usedModules;
		if (m_usedModules)
			m_usedModules->m_prevSystem = mod;
		m_usedModules = mod;
		mod->init(computeTrackSpacing(rightBone, length, texture),
			length, texture);
		mod->m_bound = 1;
	}

	return mod;
}
