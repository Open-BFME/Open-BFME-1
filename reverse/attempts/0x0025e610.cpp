// ?d_0025e610@@YAXXZ
// partial score=0.98 date=2026-09-10
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHs-c-
// GiveUpgradeUpdate::onObjectCreated, retail RVA 0x0025E610.
//
// The GiveUpgradeUpdate constructor installs primary vtable 0x010B5368.
// Slot 15 enters this body through ILT 0x0002E1D6. The body uses the module's
// upgrade lookup, the target checks, the object upgrade sink, and the shared
// selection cleanup in the same order as the retail call sequence.

typedef int ObjectID;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType
{
	KINDOF_UNRECONSTRUCTED_108 = 108
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

class UpgradeTemplate;
class Object;
class BfmeThingND;
extern void j_0001df16();
extern BfmeThingND *TheUpgradeCenter;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType source);
};

class AIUpdateInterface
{
public:
	unsigned char m_pad00[0x20];
};

class Drawable
{
public:
	void colorFlash(const RGBColor *color, UnsignedInt decayFrames,
		UnsignedInt attackFrames, UnsignedInt sustainAtPeak);
};

class Object
{
public:
	virtual void objectSlot00();
	virtual void objectSlot01();
	virtual void objectSlot02();
	virtual void objectSlot03();
	virtual void objectSlot04();
	virtual void objectSlot05();
	virtual void objectSlot06();
	virtual void objectSlot07();
	virtual void objectSlot08();
	virtual void objectSlot09();
	virtual Drawable *getDrawable();

	unsigned char m_pad04[0x200];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x1c];
	UnsignedInt m_upgradeMask;
	unsigned char m_pad228[0x11c];
	UnsignedInt m_deadFlags;

	Bool isKindOf(KindOfType kind) const;
	Bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	void giveUpgrade(const UpgradeTemplate *upgrade);
	void *unidentified_001BFE20(void) const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	void deselectObject(Object *object, unsigned short playerMask, Bool affectClient);
};

class BfmeThingND
{
public:
	void *bfmeFindND(const UnsignedInt *mask);
};

static __forceinline void *__fastcall findUpgrade(Object *object)
{
	typedef void *(BfmeThingND::*Call)(const UnsignedInt *);
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0001df16;
	return (TheUpgradeCenter->*call.member)(&object->m_upgradeMask);
}

class UpgradeSink
{
public:
#define UPGRADE_SINK_SLOT(n) virtual void slot##n();
	UPGRADE_SINK_SLOT(00) UPGRADE_SINK_SLOT(01) UPGRADE_SINK_SLOT(02)
	UPGRADE_SINK_SLOT(03) UPGRADE_SINK_SLOT(04) UPGRADE_SINK_SLOT(05)
	UPGRADE_SINK_SLOT(06) UPGRADE_SINK_SLOT(07) UPGRADE_SINK_SLOT(08)
	UPGRADE_SINK_SLOT(09) UPGRADE_SINK_SLOT(10) UPGRADE_SINK_SLOT(11)
	UPGRADE_SINK_SLOT(12) UPGRADE_SINK_SLOT(13) UPGRADE_SINK_SLOT(14)
	UPGRADE_SINK_SLOT(15) UPGRADE_SINK_SLOT(16) UPGRADE_SINK_SLOT(17)
	UPGRADE_SINK_SLOT(18) UPGRADE_SINK_SLOT(19) UPGRADE_SINK_SLOT(20)
	UPGRADE_SINK_SLOT(21) UPGRADE_SINK_SLOT(22) UPGRADE_SINK_SLOT(23)
	UPGRADE_SINK_SLOT(24) UPGRADE_SINK_SLOT(25) UPGRADE_SINK_SLOT(26)
	UPGRADE_SINK_SLOT(27) UPGRADE_SINK_SLOT(28) UPGRADE_SINK_SLOT(29)
	UPGRADE_SINK_SLOT(30) UPGRADE_SINK_SLOT(31) UPGRADE_SINK_SLOT(32)
	UPGRADE_SINK_SLOT(33) UPGRADE_SINK_SLOT(34) UPGRADE_SINK_SLOT(35)
	UPGRADE_SINK_SLOT(36) UPGRADE_SINK_SLOT(37) UPGRADE_SINK_SLOT(38)
	UPGRADE_SINK_SLOT(39) UPGRADE_SINK_SLOT(40) UPGRADE_SINK_SLOT(41)
	UPGRADE_SINK_SLOT(42)
	virtual void applyUpgrade(const UpgradeTemplate *upgrade);
#undef UPGRADE_SINK_SLOT
};

class GiveUpgradeUpdate
{
public:
	virtual void onObjectCreated();

private:
	unsigned char m_pad04[0xe4];
	Bool m_created;
	Bool m_objectCreated;
};

extern GameLogic *TheGameLogic;
extern BfmeThingND *TheUpgradeCenter;
extern void j_0000557e();
extern void j_000077b6();
extern void j_00008995();
extern void j_0000d3b9();
extern void j_0001a97e();
extern void j_0001ec2c();
extern void j_0001f253();
extern void j_00024d70();
extern void j_0003251f();
extern void j_0003a2a1();
extern void j_0003fa30();
extern void j_0004347d();

static __forceinline void callBaseObjectCreated(GiveUpgradeUpdate *update)
{
	typedef void (GiveUpgradeUpdate::*Call)();
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0003fa30;
	(update->*call.member)();
}

static __forceinline UpgradeSink *findUpgradeSink(GiveUpgradeUpdate *update, Object *object)
{
	typedef void *(GiveUpgradeUpdate::*Call)(Object *);
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0004347d;
	return reinterpret_cast<UpgradeSink *>((update->*call.member)(object));
}

static __forceinline void finishObjectCreated(GiveUpgradeUpdate *update, Object *object)
{
	typedef void (GiveUpgradeUpdate::*Call)(Object *);
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0000557e;
	(update->*call.member)(object);
}

static __forceinline void flashDrawable(Drawable *drawable, const RGBColor *color)
{
	typedef void (Drawable::*Call)(const RGBColor *, UnsignedInt, UnsignedInt,
		UnsignedInt);
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_0003a2a1;
	(drawable->*call.member)(color, 4, 4, 15);
}

static __forceinline Bool checkTarget(GiveUpgradeUpdate *update, Object *object)
{
	typedef Bool (GiveUpgradeUpdate::*Call)(Object *);
	union
	{
		void (*raw)();
		Call member;
	} call;
	call.raw = j_00008995;
	return (update->*call.member)(object);
}

// ?onObjectCreated@GiveUpgradeUpdate@@UAEXXZ
void GiveUpgradeUpdate::onObjectCreated()
{
	if (m_created)
		return;

	callBaseObjectCreated(this);

	char *rawThis = reinterpret_cast<char *>(this);
	ObjectID objectID = *reinterpret_cast<ObjectID *>(rawThis + 0xac);
	Object *object = *reinterpret_cast<Object **>(rawThis + 8);
	Object *target = TheGameLogic->findObjectByID(objectID);
	if (target == 0 || (target->m_deadFlags & 1) != 0 ||
		!checkTarget(this, target))
		goto failure;

	m_objectCreated = false;
	UpgradeTemplate *upgrade = reinterpret_cast<UpgradeTemplate *>(
		findUpgrade(object));
	if (upgrade == 0)
	{
		finishObjectCreated(this, object);
		return;
	}
	UpgradeSink *sink;
	if (target->isKindOf(KINDOF_UNRECONSTRUCTED_108))
		sink = reinterpret_cast<UpgradeSink *>(target->unidentified_001BFE20());
	else
		sink = findUpgradeSink(this, target);

	if (sink != 0)
		sink->applyUpgrade(upgrade);
	else if (target->affectedByUpgrade(upgrade))
	{
		RGBColor white = { 0.99f, 0.99f, 0.99f };
		target->giveUpgrade(upgrade);
		Drawable *drawable = target->getDrawable();
		if (drawable != 0)
			flashDrawable(drawable, &white);
	}

	TheGameLogic->deselectObject(object, 0xffff, true);
	finishObjectCreated(this, object);
	return;

failure:
	AICommandInterface *commands = reinterpret_cast<AICommandInterface *>(
		reinterpret_cast<char *>(object->m_ai) + 0x20);
	commands->aiIdle(CMD_FROM_AI);
}
