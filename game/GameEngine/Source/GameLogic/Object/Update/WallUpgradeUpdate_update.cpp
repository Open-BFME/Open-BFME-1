// cl: /DNDEBUG /MD /EHsc
// WallUpgradeUpdate::update, retail 0x002B25E0.
//
// The entry point is the third update interface at complete-object offset
// +0x10.  The primary WallUpgradeUpdate subobject therefore starts at this-0x10.

typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_UNREADY = 5,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum BodyDamageType
{
	BODY_DAMAGE_PRISTINE = 0
};

class BodyModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void setDamageState(BodyDamageType state) = 0;
};

class Object
{
public:
	unsigned char m_pad000[0x114];
	UnsignedInt m_conditionFlags;
	UnsignedInt m_modelCondition;
	unsigned char m_pad11c[0x200 - 0x11c];
	BodyModuleInterface *m_body;
	unsigned char m_pad204[0x344 - 0x204];
	unsigned char m_privateStatus;

	void notifyModelConditionChanged();
};

class BfmeOwnerBUD
{
public:
	void bfmeTwoBUD();
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class WallUpgradeUpdate
{
public:
	virtual UpdateSleepTime update();
};

extern GameLogic *TheGameLogic;
extern void j_0000fbaa();

#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")

typedef void (WallUpgradeUpdate::*WallUpgradeInitPartner)();

static __forceinline bool wallUpgradePartnerReady(const Object *partner)
{
	if ((partner->m_privateStatus & 1) == 0)
		return (~(partner->m_modelCondition >> 4)) & 1;
	return false;
}

// ?update@WallUpgradeUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime WallUpgradeUpdate::update()
{
	unsigned char *self = (unsigned char *)this;
	UpdateSleepTime result = UPDATE_SLEEP_FOREVER;

	if (self[0x20] != 0)
	{
		self[0x20] = 0;
		union
		{
			void (*raw)();
			WallUpgradeInitPartner member;
		} initPartner;
		initPartner.raw = j_0000fbaa;
		(reinterpret_cast<WallUpgradeUpdate *>(self - 0x10)->*
			initPartner.member)();
	}

	int frames = *(int *)(self + 0x1c);
	if (frames > 0)
	{
		--frames;
		*(int *)(self + 0x1c) = frames;
		if (frames == 0)
			self[0x21] = 1;
		else
			result = UPDATE_SLEEP_NONE;
	}

	if (self[0x21] != 0)
	{
		Object *partner = TheGameLogic->findObjectByID(*(int *)(self + 0x18));
		if (partner == 0 || !wallUpgradePartnerReady(partner))
			goto unready;

		Object *owner = *(Object **)(self - 8);
		reinterpret_cast<BfmeOwnerBUD *>(owner)->bfmeTwoBUD();
		owner->m_body->setDamageState(BODY_DAMAGE_PRISTINE);
		if ((owner->m_conditionFlags & 0x20000000) != 0)
		{
			owner->m_conditionFlags &= 0xdfffffff;
			owner->notifyModelConditionChanged();
		}
		self[0x21] = 0;
	}
	return result;

unready:
	return UPDATE_SLEEP_UNREADY;
}
