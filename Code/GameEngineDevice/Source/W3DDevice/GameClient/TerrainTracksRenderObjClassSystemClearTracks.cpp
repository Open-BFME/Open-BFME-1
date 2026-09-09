// cl: /DNDEBUG /MD /EHsc
// BFME retail 0x0072F030: the clearTracks helper reached by the named
// TerrainTracksRenderObjClassSystem::setDetail body through ILT 0x0001C3F0.
// The retail loop establishes the BFME member offsets directly: the track
// object links at +0x12FC and the reset packet at +0x0c/+0x10, +0x12e4,
// +0x12e8, +0x12ec and +0x12f9.  In particular, the helper's packet does not
// write +0x14; that field is owned by the edge update paths, so it is not
// invented here merely because the Zero Hour header places an active-edge
// counter there.

typedef unsigned char Bool;

class TerrainTracksRenderObjClass
{
public:
	unsigned char m_head[0x0c];
	int m_topIndex;                         // this+0x0c
	int m_bottomIndex;                      // this+0x10
	unsigned char m_beforeTotalEdges[0x12e4 - 0x14];
	int m_totalEdgesAdded;                  // this+0x12e4
	int m_ownerState;                       // this+0x12e8
	Bool m_haveAnchor;                      // this+0x12ec
	unsigned char m_beforeHaveCap[0x12f9 - 0x12ed];
	Bool m_haveCap;                         // this+0x12f9
	unsigned char m_beforeNext[2];
	TerrainTracksRenderObjClass *m_nextSystem; // this+0x12fc
};

class TerrainTracksRenderObjClassSystem
{

protected:
	void clearTracks(void);

private:
	unsigned char m_head[0x10];
	TerrainTracksRenderObjClass *m_usedModules; // this+0x10
};

void TerrainTracksRenderObjClassSystem::clearTracks(void)
{
	TerrainTracksRenderObjClass *mod = m_usedModules;

	while (mod)
	{
		mod->m_haveAnchor = false;
		mod->m_haveCap = true;
		mod->m_ownerState = 0;
		mod->m_totalEdgesAdded = 0;
		mod->m_topIndex = 0;
		mod->m_bottomIndex = 0;
		mod = mod->m_nextSystem;
	}
}
