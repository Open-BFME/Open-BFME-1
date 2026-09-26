// cl: /O2 /DNDEBUG /MD /EHsc-
//
// Retail 0x0002C6E7 is the incremental-link thunk for the matched
// TerrainTracksRenderObjClassSystem::shutdown body at 0x0072EDF0.

class TerrainTracksRenderObjClassSystem
{
public:
	void shutdown();
	void shutdownThunk();
};

void TerrainTracksRenderObjClassSystem::shutdownThunk()
{
	shutdown();
}
