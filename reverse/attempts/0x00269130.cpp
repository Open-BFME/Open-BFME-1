// ?createViewObject@SpecialPowerModule@@IAEXPBUCoord3D@@@Z
// partial score=0.94 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ de-lift of the __emit MASM thunk.
//
// BFME1 adds an early return when location is NULL (retail tests it before
// even touching modData), and its newObject() call has grown extra
// parameters (a zeroed Coord3D "starting position" and a trailing flag)
// beyond the two Zero Hour passes. The template's view-object range/duration
// getters still walk the Overridable chain the same way isSharedNSync does
// elsewhere in this class. Positions below are read directly off
// tools/dis_retail.py 0x00269130 422.

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

struct Coord3D
{
	float x, y, z;
};

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	bool isEmpty(void) const;			///< pinned at 0x0005E4C0

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	using StringBase<char>::isEmpty;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xc40];
	AsciiString m_specialPowerViewObjectName;			///< retail +0xc40
};

extern GlobalData *TheWritableGlobalData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	Overridable *m_nextOverride;						// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	float getViewObjectRange(void) const { return getFO()->m_viewObjectRange; }
	UnsignedInt getViewObjectDuration(void) const { return getFO()->m_viewObjectDuration; }

private:
	const SpecialPowerTemplate *getFO(void) const
	{
		SpecialPowerTemplate *self = (SpecialPowerTemplate *)this;
		return (const SpecialPowerTemplate *)(self->m_nextOverride
			? self->m_nextOverride->friend_getFinalOverride()
			: (Overridable *)self);
	}

	unsigned char m_unreconstructed_08[0x108 - 8];
	UnsignedInt m_viewObjectDuration;					///< +0x108
	float m_viewObjectRange;							///< +0x10c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	unsigned char m_unreconstructed_00[8];
	SpecialPowerTemplate *m_specialPowerTemplate;		///< retail +0x08
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);			///< pinned at 0x0008FFC0
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module.h
class Module
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdate : public Module
{
public:
	void setLifetimeRange(UnsignedInt minFrames, UnsignedInt maxFrames);	///< pinned at 0x0028C6E0
};

class ThingTemplate;
class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Team *getDefaultTeam(void) const { return *(Team *const *)((const char *)this + 0x230); }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Thing.h
class Thing
{
public:
	void setPosition(const Coord3D *pos);				///< pinned at 0x00132CE0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
	friend class SpecialPowerModule;

public:
	Player *getControllingPlayer(void) const;			///< pinned at 0x001BE3F0
	void setShroudClearingRange(float range);			///< pinned at 0x001BF3B0

protected:
	Module *findModule(NameKeyType key) const;			///< pinned at 0x001BEE60
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	///< pinned at 0x00137E80

	// Not-yet-converted retail helper (Code/gen_asm/d_0012bdd0.asm, still a
	// naked dump under the placeholder name ?d_00138520@@YAXXZ). BFME grew
	// newObject() by a starting-position pointer and a trailing flag beyond
	// Zero Hour's two-argument form; pinned separately in reverse/symbols.csv
	// under this method's own mangled name so this call resolves without
	// claiming that placeholder row's identity.
	Object *createViewObjectHelper(const ThingTemplate *tmpl, Team *team, const Coord3D *startingPos, int flag);
};

extern BfmeThingFactory *TheThingFactory;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule
{
protected:
	void createViewObject(const Coord3D *);

private:
	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const
	{
		return *(const SpecialPowerModuleData *const *)((const char *)this + 4);
	}

	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this + 8);
	}
};

// ?createViewObject@SpecialPowerModule@@IAEXPBUCoord3D@@@Z
void SpecialPowerModule::createViewObject(const Coord3D *location)
{
	if (!location)
		return;

	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();
	const SpecialPowerTemplate *powerTemplate = modData->m_specialPowerTemplate;

	if (powerTemplate == 0)
		return;

	float visionRange = powerTemplate->getViewObjectRange();
	UnsignedInt visionDuration = powerTemplate->getViewObjectDuration();

	if (visionRange == 0 || visionDuration == 0)
		return;

	AsciiString objectName = TheWritableGlobalData->m_specialPowerViewObjectName;
	if (objectName.isEmpty())
		return;

	const ThingTemplate *viewObjectTemplate = TheThingFactory->findTemplate(objectName);
	if (viewObjectTemplate == 0)
		return;

	Coord3D startingPos = { 0.0f, 0.0f, 0.0f };
	Object *viewObject = TheThingFactory->createViewObjectHelper(
		viewObjectTemplate, getObject()->getControllingPlayer()->getDefaultTeam(), &startingPos, 0);

	if (viewObject == 0)
		return;

	viewObject->setPosition(location);
	viewObject->setShroudClearingRange(visionRange);

	static NameKeyType key_DeletionUpdate = TheNameKeyGenerator->nameToKey("DeletionUpdate");
	Module *dup = viewObject->findModule(key_DeletionUpdate);
	if (dup)
	{
		((DeletionUpdate *)dup)->setLifetimeRange(visionDuration, visionDuration);
	}
}
