// Open-BFME5 conversions.

class BfmeE1227
{
public:
	int m_bfme00;
	void *m_bfme04;
};

struct BfmeP1227
{
	int m_bfme00;
	BfmeE1227 **m_bfme04;
};

// BfmeOtherLP and BfmeThingLP are real classes (defined in
// game/GameEngine/Source/Common/BfmeTwoHundredThirtyTwo.cpp); no header declares
// them, so name the callee by its defining spelling with a declaration-only
// slice: this body only calls bfmePushLP through the singleton, never a layout.
class BfmeR1227
{
};

// Retail 0x013377D8: use the existing data owner; retain the local pointee view.
extern struct BfmePickWorld1284 *g_bfmeHolderBU;

// BfmeOtherLP and BfmeThingLP are real classes (defined in
// game/GameEngine/Source/Common/BfmeTwoHundredThirtyTwo.cpp); no header declares
// them, so name the callee by its defining spelling with a declaration-only
// slice: this body only calls bfmePushLP through the singleton, never a layout.
class BfmeOtherLP;

class BfmeThingLP
{
public:
	void bfmePushLP(void *what, BfmeOtherLP *other, int note);
};
extern void *g_bfmeExtra1282;

class BfmeA1227
{
public:
	void bfmeDump1227(void *a, int k);
	int m_bfme00;
	BfmeP1227 *m_bfme04;
};

/// @ai-edited: use the existing canonical global at the same retail address.
void BfmeA1227::bfmeDump1227(void *a, int k)
{
	int i;
	BfmeE1227 *e;

	for (i = 0; i < m_bfme04[k].m_bfme00; ++i) {
		e = m_bfme04[k].m_bfme04[i];
		if (e->m_bfme00 == 1)
			reinterpret_cast<BfmeThingLP *>(g_bfmeHolderBU)->bfmePushLP(
				&e->m_bfme04,
				reinterpret_cast<BfmeOtherLP *>(a),
				reinterpret_cast<int>(g_bfmeExtra1282));
	}
}
