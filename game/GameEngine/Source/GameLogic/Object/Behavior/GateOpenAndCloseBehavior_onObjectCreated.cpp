// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib

// GateOpenAndCloseBehavior::onObjectCreated, retail 0x001FD780 (381 bytes).
// Constructor 0x001FC580 installs vtable 0x010A40C4 at object +4; its slot 1
// reaches this body (ILT 0x00019FC4), so `this` is the Module subobject at +4
// and update() is reached through lea ecx,[this-4].  After the base
// loadPostProcess, an effectively-dead owner updates at once; then the object
// whose name matches the module data's gate name at +0x14 is looked up and the
// two gates exchange object IDs through the GateOpenAndCloseBehavior module
// found by name key.

#include "ascii_string.h"

// Retail inlines the emptiness test at this site (null header, then a word
// compare of the length); the tree's out-of-line StringBase<char>::isEmpty
// serves the call sites, so this TU specializes it inline as other callers do.
template <> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

enum ObjectID
{
	INVALID_ID = 0
};
typedef int NameKeyType;

class ModuleData
{
};

class GateOpenAndCloseBehaviorModuleData : public ModuleData
{
public:
	unsigned char m_pad00[0x14];
	AsciiString m_gateName;
};

class Module
{
public:
	virtual void slot_000();
	virtual void onObjectCreated();

protected:
	const ModuleData *m_moduleData;
};

class Object;

class ObjectModule : public Module
{
protected:
	Object *m_object;
};

class BehaviorModule : public ObjectModule
{
protected:
	virtual void loadPostProcess();
};

// Object::isEffectivelyDead is Zero Hour's EFFECTIVELY_DEAD (bit 0) test of
// m_privateStatus at +0x344.
#define BFME_HAVE_OBJECTID
#define BFME_HAVE_ASCIISTRING
#define OBJECT_TU_MEMBERS \
	ObjectID getID() const { return m_id; } \
	const AsciiString &getName() const { return m_name; } \
	Object *getNextObject() const { return m_next; } \
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; } \
	Module *findModule(NameKeyType key) const;
#include "../object.h"
#undef OBJECT_TU_MEMBERS

class GameLogic
{
public:
	Object *getFirstObject();
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// The full object's primary base: the state update at 0x001FD6B0
// (Rva001FD6B0StateUpdate.cpp) takes the object at this-4.
class Rva001FD6B0Owner
{
public:
	virtual void slot_000();
	void update(bool enabled);
};

class GateOpenAndCloseBehavior : public Rva001FD6B0Owner, public BehaviorModule
{
public:
	virtual void onObjectCreated();

private:
	const GateOpenAndCloseBehaviorModuleData *getGateModuleData() const
	{
		return static_cast<const GateOpenAndCloseBehaviorModuleData *>(m_moduleData);
	}

	Object *getObject() const { return m_object; }

	unsigned char m_pad10[0x14];
	ObjectID m_linkedObjectId;
};

extern GameLogic *TheGameLogic;
extern NameKeyGenerator *TheNameKeyGenerator;

// ?onObjectCreated@GateOpenAndCloseBehavior@@UAEXXZ
void GateOpenAndCloseBehavior::onObjectCreated()
{
	BehaviorModule::loadPostProcess();

	if (m_object == 0)
		return;

	if (m_object->isEffectivelyDead())
		update(true);

	const GateOpenAndCloseBehaviorModuleData *data = getGateModuleData();
	if (data->m_gateName.isEmpty())
		return;

	Object *candidate = TheGameLogic->getFirstObject();
	AsciiString candidateName;
	while (candidate != 0)
	{
		candidateName = candidate->getName();
		if (candidateName.compare(data->m_gateName) == 0)
		{
			static NameKeyType gateKey =
				TheNameKeyGenerator->nameToKey("GateProxyBehavior");
			GateOpenAndCloseBehavior *other =
				static_cast<GateOpenAndCloseBehavior *>(candidate->findModule(gateKey));
			if (other != 0)
			{
				other->m_linkedObjectId = getObject()->getID();
				m_linkedObjectId = candidate->getID();
			}
			break;
		}
		candidate = candidate->getNextObject();
	}
}
