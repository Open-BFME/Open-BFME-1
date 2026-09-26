// cl: /DNDEBUG /MD /EHsc
// SupplyWarehouseCripplingBehavior::update, retail 0x0020D7B0.
//
// The retail entry point is the UpdateModuleInterface subobject at primary
// +0x10.  This TU deliberately models that entry point as a standalone ABI
// shell: the surrounding object/module layout is already fixed by the other
// SupplyWarehouseCripplingBehavior bodies, while a C++ inheritance model here
// would make the compiler adjust this before entering the body.

typedef unsigned int UnsignedInt;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class BodyModule
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual Real getHealth() const = 0;
	virtual void slot14() = 0;
	virtual Real getMaxHealth() const = 0;
};

class Object
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
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void attemptHealing(Real amount, Object *source) = 0;
};

class GameLogic
{
public:
	unsigned char m_padding[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

struct SupplyWarehouseCripplingBehaviorModuleData
{
	unsigned char m_padding[0x0c];
	UnsignedInt m_selfHealDelay;
	Real m_selfHealAmount;
};

class SupplyWarehouseCripplingBehavior
{
public:
	virtual UpdateSleepTime update();
};

// ?update@SupplyWarehouseCripplingBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SupplyWarehouseCripplingBehavior::update()
{
	unsigned char *self = (unsigned char *)this;
	const SupplyWarehouseCripplingBehaviorModuleData *data =
		*(const SupplyWarehouseCripplingBehaviorModuleData **)(self - 0x0c);
	UnsignedInt now = TheGameLogic->m_frame;
	Object *object = *(Object **)(self - 0x08);
	*(UnsignedInt *)(self + 0x18) = now + data->m_selfHealDelay;
	object->attemptHealing(data->m_selfHealAmount, 0);

	BodyModule *body = *(BodyModule **)((unsigned char *)*(Object **)(self - 0x08) + 0x200);
	if (body->getHealth() == body->getMaxHealth())
		return UPDATE_SLEEP_FOREVER;

	return (UpdateSleepTime)(*(UnsignedInt *)(self + 0x18) - now);
}
