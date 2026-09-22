// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// The carved thunk at 0x0002C976 jumps to Radar::deleteListResources at
// 0x00106A90.  This forwarding method preserves that proven target without
// duplicating the implementation body.

class Radar
{
	friend class Rva0002C976RadarDeleteListResourcesThunk;

	protected:
	void deleteListResources();
};

class Rva0002C976RadarDeleteListResourcesThunk
{
public:
	void forward();
};

void Rva0002C976RadarDeleteListResourcesThunk::forward()
{
	((Radar *)this)->deleteListResources();
}
