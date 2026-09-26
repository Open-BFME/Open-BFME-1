// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// SpawnUnitBehavior::update, retail 0x0020D310 (361 bytes).
// Identity: the constructor at 0x0020D0F0 installs vtable 0x010A6EC4 at +0x10
// and that vtable's slot 0 reaches this body through ILT 0x00043798.
// Module data fields come from the FieldParse table at 0x010A6FE8 that
// friend_newModuleData (0x00125D70) registers through 0x0020D260:
// UnitName +0x08, UnitCommand +0x0C, SpawnOnce +0x1C.

#include "string_base.h"

// Retail's StringBase<char> equality (ILT 0x000259B9 -> 0x0007FFF0), declared
// before ascii_string.h so its inline AsciiString operator== binds to it.
// Nothrow, as LANGameSlot::isUser's compareNoCase is: the conditional
// AsciiString temporary below gets no unwind state, and its destruction flag
// is set just before the comparison call, as retail sets it.
bool operator==(const StringBase<char> &left, const StringBase<char> &right) throw();

#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_5 = 5
};

class Player;
class CommandButton;
class ThingTemplate;

class SpawnUnitBehaviorModuleData
{
public:
	unsigned char m_pad00[0x08];
	AsciiString m_unitName;
	AsciiString m_unitCommand;
	unsigned char m_pad10[0x0c];
	Bool m_spawnOnce;
};

// The entry vslot18 returns; this body reads only +0x08 and +0x10.
class ProductionEntryRva0020D310
{
public:
	unsigned char m_pad00[0x08];
	const unsigned char *m_08;
	unsigned char m_pad0c[0x04];
	int m_10;
};

class ProductionUpdateInterface
{
public:
	virtual void vslot00();
	virtual void vslot01();
	virtual void vslot02();
	virtual void vslot03();
	virtual void vslot04();
	virtual void vslot05();
	virtual void vslot06();
	virtual void vslot07();
	virtual void vslot08(int value);
	virtual void vslot09();
	virtual void vslot10();
	virtual void vslot11();
	virtual void vslot12();
	virtual void vslot13();
	virtual UnsignedInt vslot14();
	virtual void vslot15();
	virtual void vslot16();
	virtual void vslot17();
	virtual ProductionEntryRva0020D310 *vslot18();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	ProductionUpdateInterface *getProductionUpdateInterface();
	void doCommandButton(const CommandButton *button, int source, int extra);
};

class GameLogicFrameSlice
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_3c;
};
extern GameLogicFrameSlice *TheGameLogic;

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactory *TheThingFactory;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

struct Rva000C7CD0Obj;

class Rva000C7CD0
{
public:
	unsigned char ok(Rva000C7CD0Obj *object, int flags);
};

// Base and interface layout as in SpawnUnitBehaviorConstructor.cpp.
class SpawnUnitBehaviorGrandBase
{
public:
	virtual ~SpawnUnitBehaviorGrandBase();

protected:
	const SpawnUnitBehaviorModuleData *m_moduleData;
	Object *m_08;
};

class SpawnUnitBehaviorIface1
{
public:
	virtual ~SpawnUnitBehaviorIface1();
};

class SpawnUnitBehaviorIface2
{
public:
	virtual UpdateSleepTime update() = 0;
};

class SpawnUnitBehaviorBase : public SpawnUnitBehaviorGrandBase, public SpawnUnitBehaviorIface1, public SpawnUnitBehaviorIface2
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

// Vtable 0x010A6EC0 at +0x20; its slot 0 (ILT 0x0003D474) is the body at
// 0x0020D280, which returns a copy of the module data's UnitName.
class SpawnUnitBehaviorIface3
{
public:
	virtual AsciiString rva0020D280() const = 0;
};

class SpawnUnitBehavior : public SpawnUnitBehaviorBase, public SpawnUnitBehaviorIface3
{
public:
	virtual UpdateSleepTime update();
	virtual AsciiString rva0020D280() const;

private:
	unsigned char m_24;
};

// ?update@SpawnUnitBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SpawnUnitBehavior::update()
{
	Object *object = m_08;
	const SpawnUnitBehaviorModuleData *data = m_moduleData;
	Player *player = object->getControllingPlayer();
	if (player == 0)
		return UPDATE_SLEEP_5;
	if (TheGameLogic->m_3c < 5)
		return UPDATE_SLEEP_5;
	if (*((const unsigned char *)player + 0x681) == 0)
		return UPDATE_SLEEP_5;
	if ((*((const unsigned char *)object + 0x118) & 0x14) != 0)
		return UPDATE_SLEEP_5;

	ProductionUpdateInterface *production = object->getProductionUpdateInterface();
	if (production != 0 && production->vslot14() > 0)
	{
		if (production->vslot14() > 1)
		{
			ProductionEntryRva0020D310 *entry = production->vslot18();
			const unsigned char *item = entry->m_08;
			if (item != 0 && *(const AsciiString *)(item + 0x20) == rva0020D280())
				production->vslot08(entry->m_10);
		}
		return UPDATE_SLEEP_5;
	}

	Rva000C7CD0 *availability = (Rva000C7CD0 *)((unsigned char *)player + 0x30);
	if (availability == 0)
		return UPDATE_SLEEP_5;
	const ThingTemplate *unit = TheThingFactory->findTemplate(data->m_unitName);
	if (unit == 0 || !availability->ok((Rva000C7CD0Obj *)unit, 0))
		return UPDATE_SLEEP_5;
	const CommandButton *button = TheControlBar->findCommandButton(data->m_unitCommand);
	if (data->m_spawnOnce && m_24 == 0)
		return UPDATE_SLEEP_5;
	if (button != 0)
		object->doCommandButton(button, 2, 0);
	m_24 = 0;
	return UPDATE_SLEEP_5;
}
