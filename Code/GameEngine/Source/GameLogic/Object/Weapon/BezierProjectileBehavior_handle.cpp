// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport
// BezierProjectileBehavior secondary-iface handle, retail 0x001F08B0 size 135.
// Adjustor at 0x001F1360 does sub ecx,4 then jmp here, so this is the +0x20
// interface. Vector<12-byte> begin/end are this+0x24/+0x28 (= module +0x44/+0x48,
// the dtor-proven stride). this-0x18 is Object*. this+0x20 is the launcher
// pointer the dtor leaves unreconstructed at module+0x40.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int ObjectID;

enum KindOfType
{
	KINDOF_0x6C = 0x6C
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	Bool testStatus(int status) const;

	Bool isEffectivelyDead() const
	{
		return (m_deadFlags & 1) != 0;
	}

	char m_pad000[0x344];
	unsigned char m_deadFlags;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct BezierPathPod
{
	int a[3];
};

class BezierLaunchHelper
{
public:
	Bool fire(Object *found, Object *launcher, Object *victim, void *extra);
};

class BezierProjectileBehavior
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual ObjectID getLauncherID();

	Bool handle(Object *victim);

	char m_pad04[0x18 - 4];
	void *m_extra18;
	char m_pad1C[0x20 - 0x1C];
	BezierLaunchHelper *m_launcher;
	_STL::vector<BezierPathPod> m_path;
};

// ?handle@BezierProjectileBehavior@@QAE_NPAVObject@@@Z
Bool BezierProjectileBehavior::handle(Object *victim)
{
	if (m_path.size() == 0)
		return false;
	if (!m_launcher)
		return false;

	Object *v = victim;
	if (v)
	{
		if (v->isKindOf(KINDOF_0x6C))
			return false;
		if (v->isEffectivelyDead())
			return false;
		if (v->testStatus(4))
			return false;
	}

	Object *found = TheGameLogic->findObjectByID(getLauncherID());
	Object *owner = *(Object **)((char *)this - 0x18);
	void *extra = m_extra18;
	return m_launcher->fire(found, owner, v, extra);
}
