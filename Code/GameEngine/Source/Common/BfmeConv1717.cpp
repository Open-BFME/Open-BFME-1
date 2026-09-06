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

extern BfmeTerrainGJ *g_bfmeTerrainGJ;

class BfmeOwnerGJ
{
public:
	Real bfmeMaxGJ(Real x, Real y);
	Real bfmeOwnGJ(Real x, Real y);
};

Real BfmeOwnerGJ::bfmeMaxGJ(Real x, Real y)
{
	Real ground = g_bfmeTerrainGJ->bfmeHeightGJ(x, y, 0);
	Real mine = bfmeOwnGJ(x, y);

	return (mine > ground) ? mine : ground;
}
