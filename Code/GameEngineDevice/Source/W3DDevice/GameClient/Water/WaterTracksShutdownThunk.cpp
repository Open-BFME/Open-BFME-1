// cl: /O2 /DNDEBUG /MD /EHsc-
//
// Retail 0x000319CB is the incremental-link thunk for the matched
// WaterTracksRenderSystem::shutdown body at 0x007AC560.

class WaterTracksRenderSystem
{
public:
	void shutdown();
	void shutdownThunk();
};

void WaterTracksRenderSystem::shutdownThunk()
{
	shutdown();
}
