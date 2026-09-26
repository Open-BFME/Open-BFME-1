struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class Weapon
{
public:
	Coord3D bfmeGetLOSVictimPos(const Object *shooter, const Object *victim, int mode) const;
};

class BfmeHolderNS
{
public:
	int bfmeQueryNS();
};

struct Rva003FD060TerrainLogic
{
	virtual void bfmeSlot0AAE();
	virtual void bfmeSlot1AAE();
	virtual void bfmeSlot2AAE();
	virtual void bfmeSlot3AAE();
	virtual void bfmeSlot4AAE();
	virtual void bfmeSlot5AAE();
	virtual void bfmeSlot6AAE();
	virtual float bfmeHeightAAE(float x, float y, int layer, int a, int b);
};

extern Rva003FD060TerrainLogic *TheTerrainLogic;

class BfmeAimAAE
{
public:
	virtual void bfmeSlotA0AAE();
	virtual void bfmeSlotA1AAE();
	virtual void bfmeSlotA2AAE();
	virtual void bfmeSlotA3AAE();
	virtual void bfmeSlotA4AAE();
	virtual void bfmeSlotA5AAE();
	virtual void bfmeAimAtAAE(Weapon *weapon, const Coord3D *pos);

	void bfmeFireAAE(Weapon *weapon, BfmeHolderNS *victim);
};

void BfmeAimAAE::bfmeFireAAE(Weapon *weapon, BfmeHolderNS *victim)
{
	Coord3D pos = weapon->bfmeGetLOSVictimPos(0, (const Object *)victim, 1);

	pos.z = TheTerrainLogic->bfmeHeightAAE(pos.x, pos.y, victim->bfmeQueryNS(), 0, 1);

	bfmeAimAtAAE(weapon, &pos);
}
