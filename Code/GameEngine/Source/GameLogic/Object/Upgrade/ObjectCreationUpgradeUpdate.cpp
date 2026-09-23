// ?update@ObjectCreationUpgrade@@UAE?AW4UpdateSleepTime@@XZ
// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib

// ObjectCreationUpgrade::update at retail 0x002D72F0, 552 bytes.
// The landed ObjectCreationUpgrade constructor (0x002D6D90) installs vtable
// 0x010CD54C at this+0x18. Its slot 0 is ILT 0x0002C07A -> this body and its
// slot 1 is ILT 0x0004985F -> UpdateModule::getDisabledTypesToProcess
// (0x0011A130), so +0x18 is the UpdateModuleInterface subobject and this is
// its update(). The two returns are UPDATE_SLEEP_NONE and UPDATE_SLEEP_FOREVER.
// The decoded extent ends with ret at 0x002D7517, before int3 padding.
// Native WWMath types preserve the retail x87 constructor/copy schedule.

#include "ascii_string.h"
#include "matrix3d.h"

extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);
#pragma intrinsic(memset)

enum NameKeyType
{
	NAME_KEY_NONE = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

typedef float Real;
typedef unsigned int UnsignedInt;

#define LOGICFRAMES_PER_MSEC_REAL (30.0f / 1000.0f)

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
	void set(Real ax, Real ay, Real az) { x = ax; y = ay; z = az; }
};

// WWLib's StringBase buffer header: an AsciiString holds one pointer to it.
struct AsciiStringBuffer
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
};

static inline bool isStringEmpty(const AsciiString &s)
{
	const AsciiStringBuffer *buffer = *(const AsciiStringBuffer *const *)&s;
	return buffer == 0 || buffer->length == 0;
}

template <int NUMBITS>
class BitFlags
{
public:
	BitFlags() { memset(m_bits, 0, sizeof(m_bits)); }

private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<86> ObjectStatusMaskType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_pad00[0x3c];
	UnsignedInt m_frame;
};

class Team;
class ThingTemplate;
class UpgradeTemplate;
class Module;
class Object;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team,
		const ObjectStatusMaskType &statusBits = ObjectStatusMaskType(),
		UnsignedInt flags = 0);
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

// Body 0x000C9530, called on the new object's controlling Player with the
// owner and the new object; the ledger holds it under an address-derived name
// with two word arguments.
class Rva000C9530
{
public:
	void wrap(int creator, int created);
};

class Player;

// Drawable body 0x00410D80, reached through ILT 0x00046A1F.
class Drawable
{
public:
	void bfmeDelayB(int frames);
};

// Body 0x00207450 on the module found by the "SlaveWatcherBehavior" name key:
// stores its argument at +0x20.
class BfmeThingBHA
{
public:
	void bfmeGoBHA(void *what);
};

class Thing
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1c();
	virtual void vslot20();
	virtual void vslot24();
	virtual Drawable *getDrawable() const;

	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);

	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
	const Matrix3D *getTransformMatrix() const { return &m_transform; }

private:
	unsigned int m_template;
	Matrix3D m_transform;
	Coord3D m_cachedPos;
	Real m_cachedAngle;
};

class Object : public Thing
{
public:
	int getID() const { return m_id; }
	Team *getTeam() const { return m_team; }
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
	void giveUpgrade(const UpgradeTemplate *upgrade);
	void removeUpgrade(const UpgradeTemplate *upgrade);

private:
	char m_pad48[0x74 - 0x48];
	int m_id;
	char m_pad78[0x23c - 0x78];
	Team *m_team;
};

extern GameLogic *TheBfmeGameLogic;
extern ThingFactory *TheThingFactory;
extern NameKeyGenerator *TheNameKeyGenerator;
extern UpgradeCenter *TheUpgradeCenter;

// Field offsets from the ObjectCreationUpgradeModuleData FieldParse table
// (see ObjectCreationUpgradeModuleDataConstructor.cpp).
struct ObjectCreationUpgradeModuleData
{
	char m_pad00[0x78];
	AsciiString m_removeUpgrade;
	AsciiString m_grantUpgrade;
	AsciiString m_thingToSpawn;
	Coord3D m_offset;
	char m_pad90[0xa0 - 0x90];
	UnsignedInt m_fadeInTime;
};

class OCU_GrandBase
{
public:
	virtual ~OCU_GrandBase();

private:
	unsigned int m_dword04;
};

class OCU_MidGrand
{
public:
	virtual ~OCU_MidGrand();

protected:
	const ObjectCreationUpgradeModuleData *m_moduleData;
	Object *m_object;
};

class OCU_Iface1
{
public:
	virtual ~OCU_Iface1();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ObjectCreationUpgrade : public OCU_GrandBase, public OCU_MidGrand,
	public OCU_Iface1, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();

protected:
	const ObjectCreationUpgradeModuleData *getObjectCreationUpgradeModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	unsigned int m_1C;
	int m_20;
	int m_24;
	UnsignedInt m_28;
	bool m_2C;
};

UpdateSleepTime ObjectCreationUpgrade::update()
{
	if (m_2C && TheBfmeGameLogic->getFrame() > m_28)
	{
		const ObjectCreationUpgradeModuleData *data = getObjectCreationUpgradeModuleData();
		if (data != 0 && !isStringEmpty(data->m_thingToSpawn))
		{
			const ThingTemplate *tmplate = TheThingFactory->findTemplate(data->m_thingToSpawn);
			Object *obj = TheThingFactory->newObject(tmplate, getObject()->getTeam());
			if (obj == 0)
				return UPDATE_SLEEP_FOREVER;

			((Rva000C9530 *)obj->getControllingPlayer())->wrap((int)getObject(), (int)obj);

			if (obj->getDrawable())
				obj->getDrawable()->bfmeDelayB((int)(data->m_fadeInTime * LOGICFRAMES_PER_MSEC_REAL));

			Object *owner = getObject();
			Coord3D pos;
			pos.set(owner->getPosition());
			Vector3 offset(data->m_offset.x, data->m_offset.y, data->m_offset.z);
			owner->getTransformMatrix()->mulVector3(offset);
			pos.x = offset.X;
			pos.y = offset.Y;
			pos.z = offset.Z;
			Real angle = owner->getOrientation();
			obj->setOrientation(angle);
			obj->setPosition(&pos);

			static NameKeyType slaveWatcherKey = TheNameKeyGenerator->nameToKey("SlaveWatcherBehavior");
			BfmeThingBHA *slaveWatcher = (BfmeThingBHA *)getObject()->findModule(slaveWatcherKey);
			if (slaveWatcher != 0)
				slaveWatcher->bfmeGoBHA((void *)obj->getID());
		}

		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_grantUpgrade);
		if (upgrade != 0)
			getObject()->giveUpgrade(upgrade);

		upgrade = TheUpgradeCenter->findUpgrade(data->m_removeUpgrade);
		if (upgrade != 0)
			getObject()->removeUpgrade(upgrade);

		return UPDATE_SLEEP_FOREVER;
	}
	return UPDATE_SLEEP_NONE;
}
