// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// SpecialPowerModule::createViewObject. Retail 0x00269130, 422 bytes.
// Zero Hour twin: SpecialPowerModule.cpp createViewObject. BFME tests the
// location first, passes newObject a zeroed BitFlags<86> status mask and a
// trailing 0, and refreshes the view object's partition cells after setting
// its shroud clearing range.
#include "ascii_string.h"
#include <bitset>

struct Coord3D;
class ThingTemplate;
class Team;

template <unsigned N> class BitFlags
{
	std::bitset<N> m_bits;
public:
	BitFlags() {}
};

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_prefix000[0xc40];
	AsciiString m_specialPowerViewObjectName;			// +0xc40 field_names
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

	const Overridable *friend_getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;						// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	unsigned int getViewObjectDuration(void) const { return getFO()->m_viewObjectDuration; }
	float getViewObjectRange(void) const { return getFO()->m_viewObjectRange; }

private:
	const SpecialPowerTemplate *getFO(void) const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }

	unsigned char m_prefix008[0x108 - 8];
	unsigned int m_viewObjectDuration;					// +0x108 FieldParse ViewObjectDuration
	float m_viewObjectRange;							// +0x10c FieldParse ViewObjectRange
};

class SpecialPowerModuleData
{
public:
	unsigned char m_prefix000[8];
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x08 field_names
};

class Module
{
};

class DeletionUpdate : public Module
{
public:
	void setLifetimeRange(unsigned int minFrames, unsigned int maxFrames);
};

class Player
{
public:
	Team *getDefaultTeam(void) { return m_dword230; }	// ZH twin accessor
private:
	unsigned char m_prefix000[0x230];
	Team *m_dword230;									// +0x230 unwitnessed
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
};

class Object : public Thing
{
public:
	Player *getControllingPlayer(void) const;
	void setShroudClearingRange(float range);
	void bfmeRefreshPartitionCells(void);
	Module *findUpdateModule(NameKeyType key) const { return findModule(key); }	// ZH twin accessor

protected:
	Module *findModule(NameKeyType key) const;
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const BitFlags<86> &statusBits, unsigned int flags);
};
extern ThingFactory *TheThingFactory;

class SpecialPowerModule
{
protected:
	void createViewObject(const Coord3D *location);

	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const { return m_dword04; }
	Object *getObject(void) const { return m_dword08; }

private:
	void *m_dword00;
	const SpecialPowerModuleData *m_dword04;			// +0x04 unwitnessed
	Object *m_dword08;									// +0x08 unwitnessed
};

void SpecialPowerModule::createViewObject(const Coord3D *location)
{
	if (location == 0)
		return;

	const SpecialPowerModuleData *modData = getSpecialPowerModuleData();
	const SpecialPowerTemplate *powerTemplate = modData->m_specialPowerTemplate;
	if (powerTemplate == 0)
		return;

	float visionRange = powerTemplate->getViewObjectRange();
	unsigned int visionDuration = powerTemplate->getViewObjectDuration();

	if (visionRange == 0 || visionDuration == 0)
		return;

	AsciiString objectName = TheWritableGlobalData->m_specialPowerViewObjectName;
	if (objectName.isEmpty())
		return;

	const ThingTemplate *viewObjectTemplate = TheThingFactory->findTemplate(objectName);
	if (viewObjectTemplate == 0)
		return;

	Object *viewObject = TheThingFactory->newObject(viewObjectTemplate,
		getObject()->getControllingPlayer()->getDefaultTeam(), BitFlags<86>(), 0);
	if (viewObject == 0)
		return;

	viewObject->setPosition(location);
	viewObject->setShroudClearingRange(visionRange);
	viewObject->bfmeRefreshPartitionCells();

	static NameKeyType key_DeletionUpdate = TheNameKeyGenerator->nameToKey("DeletionUpdate");
	DeletionUpdate *dup = (DeletionUpdate *)viewObject->findUpdateModule(key_DeletionUpdate);
	if (dup)
		dup->setLifetimeRange(visionDuration, visionDuration);
}
