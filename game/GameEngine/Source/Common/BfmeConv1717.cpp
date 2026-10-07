typedef float Real;

class BfmeTerrainGJ
{
public:
	virtual void bfmeSlot00GJ(void);
	virtual void bfmeSlot01GJ(void);
	virtual void bfmeSlot02GJ(void);
	virtual void bfmeSlot03GJ(void);
	virtual void bfmeSlot04GJ(void);
	virtual void bfmeSlot05GJ(void);
	virtual Real bfmeHeightGJ(Real x, Real y, int flags);
};

class TerrainLogic;
// The global at 0x012EF4CC is EA's TerrainLogic *TheTerrainLogic; this TU's
// view of its pointee keeps the BfmeTerrainGJ vtable layout it calls through.
extern TerrainLogic *TheTerrainLogic;

static inline BfmeTerrainGJ *bfmeTerrainGJ()
{
	return reinterpret_cast<BfmeTerrainGJ *>(TheTerrainLogic);
}

// Retail calls ILT 0x00036FCA -> 0x00148A10, the matched no-fly-zone height.
class AerialPathfinder
{
public:
	Real getNoFlyZoneHeight(Real x, Real y);
};

class BfmeOwnerGJ
{
public:
	Real bfmeMaxGJ(Real x, Real y);
};

Real BfmeOwnerGJ::bfmeMaxGJ(Real x, Real y)
{
	Real ground = bfmeTerrainGJ()->bfmeHeightGJ(x, y, 0);
	Real mine = ((AerialPathfinder *)this)->getNoFlyZoneHeight(x, y);

	return (mine > ground) ? mine : ground;
}
