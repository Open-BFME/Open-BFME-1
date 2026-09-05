// cl: /DNDEBUG /MD /EHsc-
// RVA-derived Object method at 0x001CC660, 238 bytes. Identity unknown:
// sits immediately before crushPolicy. If +0x214 is set (container?), walk
// that object's template kindof[3] bit 0x1000 and its AI+0x1cc query/set
// pair; otherwise ENEMIES-only relationship, current weapon accepts, vcall
// +0x68, then the same AI query/set on this.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum Relationship
{
	ENEMIES = 0
};

class Object;
class ThingTemplate;

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	Overridable *getFinalOverride();
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad08[0xc8 - 0x08];
	UnsignedInt m_kindOf[4];
};

class BfmeSub1CC_EC3
{
public:
	float queryCached(Object *val);
	void cache1B4980(float value, unsigned int frames);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad[0x1cc];
	BfmeSub1CC_EC3 *m_sub1cc;
};

class Rva001E1770ByteField
{
public:
	unsigned char get() const;
};

class Weapon
{
public:
	void *m_vtable;
	Rva001E1770ByteField *m_template;
	Bool isWithinAttackRange(const Object *self, const Object *other, int mode) const;
};

class BfmeObjectV68
{
public:
	virtual void s00() = 0; virtual void s04() = 0; virtual void s08() = 0;
	virtual void s0c() = 0; virtual void s10() = 0; virtual void s14() = 0;
	virtual void s18() = 0; virtual void s1c() = 0; virtual void s20() = 0;
	virtual void s24() = 0; virtual void s28() = 0; virtual void s2c() = 0;
	virtual void s30() = 0; virtual void s34() = 0; virtual void s38() = 0;
	virtual void s3c() = 0; virtual void s40() = 0; virtual void s44() = 0;
	virtual void s48() = 0; virtual void s4c() = 0; virtual void s50() = 0;
	virtual void s54() = 0; virtual void s58() = 0; virtual void s5c() = 0;
	virtual void s60() = 0; virtual void s64() = 0;
	virtual void slot68(Object *other) = 0;
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
	void rva001CC660(Object *other);

private:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x204 - 0x08];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x214 - 0x208];
	Object *m_container;
	unsigned char m_pad218[0x26c - 0x218];
	Weapon *m_weapons[4];
	UnsignedInt m_curWeapon;
	unsigned char m_pad280[4];
	void *m_weaponSet;
};

void Object::rva001CC660(Object *other)
{
	Object *container = m_container;
	if (container)
	{
		ThingTemplate *tmpl = container->m_template;
		if (tmpl != 0 && tmpl->m_nextOverride != 0)
			tmpl = (ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		if ((tmpl->m_kindOf[3] & 0x1000) == 0)
			return;
		AIUpdateInterface *ai = container->m_ai;
		if (!ai)
			return;
		BfmeSub1CC_EC3 *sub = ai->m_sub1cc;
		if (!sub)
			return;
		float v = sub->queryCached(this);
		sub->cache1B4980(v, 5);
		return;
	}

	if (getRelationship(other) != ENEMIES)
		return;

	if (m_weaponSet)
	{
		Weapon *weapon = m_weapons[m_curWeapon];
		if (weapon && weapon->m_template->get() &&
			weapon->isWithinAttackRange(this, other, 0))
			reinterpret_cast<BfmeObjectV68 *>(this)->slot68(other);
	}

	AIUpdateInterface *ai = m_ai;
	if (!ai)
		return;
	BfmeSub1CC_EC3 *sub = ai->m_sub1cc;
	if (!sub)
		return;
	float v = sub->queryCached(this);
	sub->cache1B4980(v, 5);
}
