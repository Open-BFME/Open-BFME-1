// ?dup_002d7890@@YAXXZ
// Retail RVA 0x002D7890. The owning class and method name remain unknown.

typedef float Real;

extern const Real g_bfmeK1239;
extern const Real BfmeShadowScale;

class Rva00010A23Target
{
public:
	void rva00010a23(void *tail, Real ratio, int extra);
};

class Player;

class Object
{
public:
	Player *getControllingPlayer(void) const;
};

class Rva002D7890Thing
{
public:
	unsigned char m_head[0x70];
	int m_extra;
	Real m_amount;
	unsigned char m_tail[4];
};

class Rva002D7890Owner
{
public:
	void rva002d7890(void);
};

void Rva002D7890Owner::rva002d7890(void)
{
	char *base = (char *)this;

	Object *holder = *(Object **)(base - 8);
	Rva002D7890Thing *thing = *(Rva002D7890Thing **)(base - 0xc);
	Rva00010A23Target *target =
		(Rva00010A23Target *)holder->getControllingPlayer();

	if (target == 0)
		return;

	target->rva00010a23(thing->m_tail,
		(thing->m_amount - g_bfmeK1239) /
		(*(volatile Real *)&thing->m_amount * BfmeShadowScale),
		thing->m_extra);
}
