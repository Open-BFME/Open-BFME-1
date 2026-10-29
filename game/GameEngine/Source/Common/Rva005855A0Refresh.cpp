// ?cachedPair@Rva005855A0Owner@@QAEXXZ
// Retail 0x005855A0 (167 bytes, thiscall, bare RET). No named caller or
// vtable reaches it, so the owner and method keep the address. It asks the
// 0x003C9470 fallback (receiver: the +0x28 object of the 0x012F1028 global)
// for a position keyed by the record at [this+8]+4, passes that position by
// value to BfmeHostESM::bfmeRunESM (0x00609DA0) on g_bfmeStateDF, converts it
// through the state's vtable slot 9 into an integer pair, and when the pair
// differs from the one cached at +0x10/+0x14 it reports it through
// bfmeGo1077C (0x0051B3D0) and caches it.
//
// Frame: retail keeps the bfmeRunESM float output right after the coordinate
// it was computed for (a 12-byte x/y/out record), and builds both the record's
// coordinate and the by-value argument from the fallback position (the
// argument's y is reloaded from the position, not from the record). The
// empty BfmeCoordESM destructor reproduces the by-value copy's saved-esp slot.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

struct Rva003C9470Output
{
	float x;
	float y;
};

struct BfmeCoordESM
{
	BfmeCoordESM(const Rva003C9470Output &o) { m_x = o.x; m_y = o.y; }
	BfmeCoordESM(const BfmeCoordESM &other) throw() { m_x = other.m_x; m_y = other.m_y; }
	~BfmeCoordESM() {}
	float m_x;
	float m_y;
};

struct Rva005855A0Query
{
	Rva005855A0Query(const Rva003C9470Output &p) : coord(p) {}
	BfmeCoordESM coord;
	float out;
};

struct Rva005855A0Pair
{
	int first;
	int second;
};

class Rva003C9470Key;


class Rva003C9470Owner
{
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);
};

class Glo012F1028Type
{
public:
	char pad00[0x28];
	Rva003C9470Owner *m_owner;
};

// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )
void bfmeGo1077C(int, float, float);

class BfmeHostESM
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24(BfmeCoordESM *coord, Rva005855A0Pair *result);
	char bfmeRunESM(BfmeCoordESM coord, float *out);
};

// Retail 0x012F7048 is ?g_rva012F7048LivingWorld@@3PAVRva006092D0State@@A (data_rows.csv,
// GameClient/LivingWorld.cpp); g_bfmeStateDF was only a pin.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;
#define g_bfmeStateDF ( *(BfmeHostESM **)&g_rva012F7048LivingWorld )

class Rva005855A0Owner
{
public:
	void cachedPair();

private:
	char pad00[0x10];
	int m_cachedFirst;
	int m_cachedSecond;
};

void Rva005855A0Owner::cachedPair()
{
	Rva003C9470Owner *owner = Glo012F1028->m_owner;
	Rva003C9470Output position;
	owner->fallback(
		(Rva003C9470Key *)(*(char **)((char *)this + 8) + 4), &position);
	Rva005855A0Query query(position);
	g_bfmeStateDF->bfmeRunESM(position, &query.out);
	Rva005855A0Pair result;
	g_bfmeStateDF->slot24(&query.coord, &result);
	if (result.first != m_cachedFirst || result.second != m_cachedSecond)
	{
		bfmeGo1077C(0, (float)result.first, (float)result.second);
		m_cachedFirst = result.first;
		m_cachedSecond = result.second;
	}
}
