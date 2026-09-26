// cl: /DNDEBUG /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

enum DisabledType
{
	DISABLED_HELD = 3
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_LASERED = 9
};

template<int Bits>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<Bits> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(bit) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (bit))

class Drawable
{
public:
	void setShadowsEnabled(Bool enable);
};

class Object
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Drawable *getDrawable();

	void setStatus(const ObjectStatusMaskType &status, Bool set);
	Bool clearDisabled(DisabledType type);
	void kill(DamageType damage, DeathType death);
};

class DockUpdate
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void getExitPosition(Object *docker, void *position);
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void onExitReached(Object *docker);
	void cancelDock(Object *docker);
};

class MonsterDockUpdate : public DockUpdate
{
public:
	virtual void onExitReached(Object *docker);
};

void MonsterDockUpdate::onExitReached(Object *docker)
{
	DockUpdate::cancelDock(docker);
	Object *owner = *(Object **)((char *)this - 0x18);
	getExitPosition(docker, 0);
	owner->setStatus(MAKE_OBJECT_STATUS_MASK(3), false);
	owner->clearDisabled(DISABLED_HELD);
	docker->setStatus(MAKE_OBJECT_STATUS_MASK(3), false);
	docker->setStatus(MAKE_OBJECT_STATUS_MASK(59), false);
	docker->getDrawable()->setShadowsEnabled(true);
	owner->kill(DAMAGE_UNRESISTABLE, DEATH_LASERED);
}
