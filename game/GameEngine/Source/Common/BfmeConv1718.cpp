// Callees (tools/callees.py 0x216520 60): ILT 0xFED4 -> 0x001E9D60 Weapon::loadAmmoNow,
// ILT 0x1F1D1 -> 0x001EA5F0 Weapon::rva001EA5F0.
class Object;
class BfmeThingGK;

class Weapon
{
public:
	void loadAmmoNow(const Object *victim);
	bool rva001EA5F0(const Object *source, int arg2, const Object *victim, int *arg4);
};

class BfmePrimaryGK
{
public:
	virtual void bfmeSlot00GK(void);
	virtual void bfmeSlot01GK(void);
	virtual void bfmeSlot02GK(void);
	virtual void bfmeSlot03GK(void);
	virtual void bfmeSlot04GK(void);
	virtual void bfmeSlot05GK(void);
	virtual void bfmeSlot06GK(void);
	virtual void bfmeSlot07GK(void);
	virtual void bfmeSlot08GK(void);
	virtual void bfmeSlot09GK(void);
	virtual char bfmeCheckGK(void);
};

class BfmeArgGK
{
public:
	unsigned char m_bfmeHeadGK[0x74];
	int m_bfmeKindGK;
};

class BfmeSecondGK
{
public:
	void bfmeGoGK(BfmeArgGK *arg, int unusedA, int unusedB);

	unsigned char m_bfmeHeadGK[4];
	Weapon *m_bfmeSubGK;
};

void BfmeSecondGK::bfmeGoGK(BfmeArgGK *arg, int unusedA, int unusedB)
{
	if (arg == 0)
		return;

	char *base = (char *)this;
	BfmeThingGK *thing = *(BfmeThingGK **)(base - 8);

	if (((BfmePrimaryGK *)(base - 0x10))->bfmeCheckGK() == 0)
		return;

	m_bfmeSubGK->loadAmmoNow((const Object *)thing);
	m_bfmeSubGK->rva001EA5F0((const Object *)thing, arg->m_bfmeKindGK, (const Object *)arg, 0);
}
