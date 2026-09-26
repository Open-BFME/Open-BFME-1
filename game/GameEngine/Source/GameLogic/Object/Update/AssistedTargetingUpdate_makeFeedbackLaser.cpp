// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AssistedTargetingUpdate::makeFeedbackLaser, retail 0x0027FD70.
// BFME passes the object positions to LaserUpdate's four-argument interface.

#define _STLP_NO_EXCEPTIONS 1
typedef bool Bool;
typedef int Int;
typedef int NameKeyType;

template<int NUMBITS>
class BitFlags
{
public:
	unsigned int m_bits[3];
};

typedef BitFlags<86> ObjectStatusMaskType;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Team
{
};

class Player
{
};

class Drawable;
class ClientUpdateModule
{
};

class Object
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual Drawable *getDrawable() const;

	Player *getControllingPlayer() const;
};

class ThingTemplate
{
};

class ThingFactory
{
};

extern ThingFactory *TheThingFactory;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Drawable
{
};

class GameLogic
{
};

extern GameLogic *TheGameLogic;

extern void j_0001d0de();
extern void j_00031d2c();
extern void j_0004494a();

typedef Object *(ThingFactory::*ThingFactoryNewObjectCall)(
	const ThingTemplate *, Team *, const volatile ObjectStatusMaskType &, void *);
typedef ClientUpdateModule *(Drawable::*DrawableFindClientUpdateCall)(NameKeyType);
typedef void (GameLogic::*GameLogicDestroyObjectCall)(Object *);

static __forceinline Object *newLaserObject(ThingFactory *factory,
	const ThingTemplate *laserTemplate, Team *laserTeam,
	const volatile ObjectStatusMaskType &statusBits = ObjectStatusMaskType(),
	void *extra = 0)
{
	union { void (*raw)(); ThingFactoryNewObjectCall member; } newObjectCall;
	newObjectCall.raw = j_0004494a;
	return (factory->*newObjectCall.member)(laserTemplate, laserTeam,
		statusBits, extra);
}

class LaserUpdate : public ClientUpdateModule
{
public:
	void initLaser(const Object *, const Coord3D *, const Coord3D *, Int);
};

class AssistedTargetingUpdate
{
private:
	__forceinline Object *getObject() const
	{
		return *(Object **)((const unsigned char *)this + 8);
	}

	void makeFeedbackLaser(const ThingTemplate *, const Object *, const Object *);
};

// ?makeFeedbackLaser@AssistedTargetingUpdate@@AAEXPBVThingTemplate@@PBVObject@@1@Z
void AssistedTargetingUpdate::makeFeedbackLaser(const ThingTemplate *laserTemplate,
	const Object *from, const Object *to)
{
	if (!getObject()->getControllingPlayer())
		return;

	Player *player = getObject()->getControllingPlayer();
	Team *laserTeam = *(Team **)((const unsigned char *)player + 0x230);
	Object *laser = newLaserObject(TheThingFactory, laserTemplate, laserTeam);
	if (!laser)
		return;

	Drawable *draw = laser->getDrawable();
	static NameKeyType key_LaserUpdate =
		TheNameKeyGenerator->nameToKey("LaserUpdate");
	union { void (*raw)(); DrawableFindClientUpdateCall member; } findCall;
	findCall.raw = j_00031d2c;
	LaserUpdate *update = (LaserUpdate *)
		(draw->*findCall.member)(key_LaserUpdate);
	if (!update)
	{
		union { void (*raw)(); GameLogicDestroyObjectCall member; } destroyCall;
		destroyCall.raw = j_0001d0de;
		(TheGameLogic->*destroyCall.member)(laser);
		return;
	}

	update->initLaser(
		getObject(),
		(const Coord3D *)((const unsigned char *)from + 0x38),
		(const Coord3D *)((const unsigned char *)to + 0x38), 0);
}
