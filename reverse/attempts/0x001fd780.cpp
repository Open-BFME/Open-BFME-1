// ?onObjectCreated@GateOpenAndCloseBehavior@@UAEXXZ
// partial score=0.47 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc

#include "../../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"

enum NameKeyType { };

class Module
{
public:
	virtual void moduleSlot();
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;

	unsigned char m_pad00[0x74];
	int m_id;
	unsigned char m_pad78[0x0c];
	AsciiString m_name;
	Object *m_next;
	unsigned char m_pad8c[0x344 - 0x8c];
	unsigned char m_privateStatus;
};

class ModuleData
{
};

class BehaviorModule
{
protected:
	virtual void loadPostProcess();

	ModuleData *m_moduleData;
	Object *m_object;
};

class Rva001FD6B0Owner
{
public:
	void update(bool enabled);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ScriptActionsDifficultyListManager
{
public:
	Object *getDifficultyListHead();
};

class GameLogic;
extern GameLogic *TheGameLogic;

struct BfmeAsciiHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

struct GateOpenAndCloseBehaviorModuleDataView
{
	void *m_vtable;
	unsigned char m_pad04[0x10];
	AsciiString m_name;
};

class GateOpenAndCloseBehavior : public BehaviorModule
{
public:
	virtual void onObjectCreated();

private:
	unsigned char m_pad0c[0x14];
	int m_gateObjectID;
};

// ?onObjectCreated@GateOpenAndCloseBehavior@@UAEXXZ
void GateOpenAndCloseBehavior::onObjectCreated()
{
	BehaviorModule::loadPostProcess();

	Object *object = m_object;
	if (object == 0)
		return;

	if ((object->m_privateStatus & 1) != 0)
	{
		reinterpret_cast<Rva001FD6B0Owner *>(
			reinterpret_cast<unsigned char *>(this) - 4)->update(true);
	}

	GateOpenAndCloseBehaviorModuleDataView *data =
		reinterpret_cast<GateOpenAndCloseBehaviorModuleDataView *>(m_moduleData);
	BfmeAsciiHeader *dataName =
		*reinterpret_cast<BfmeAsciiHeader **>(&data->m_name);
	if (dataName == 0 || dataName->m_length == 0)
		return;

	Object *candidate = reinterpret_cast<ScriptActionsDifficultyListManager *>(
		TheGameLogic)->getDifficultyListHead();
	if (candidate == 0)
		return;

	AsciiString candidateName;
	for (;;)
	{
		candidateName.set(candidate->m_name);
		if (candidateName.compare(data->m_name) == 0)
			break;
		candidate = candidate->m_next;
		if (candidate == 0)
			return;
	}

	static NameKeyType gateKey =
		TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	Module *module = candidate->findModule(gateKey);
	if (module != 0)
	{
		GateOpenAndCloseBehavior *gate =
			reinterpret_cast<GateOpenAndCloseBehavior *>(
				reinterpret_cast<unsigned char *>(module) - 4);
		gate->m_gateObjectID = object->m_id;
		m_gateObjectID = candidate->m_id;
	}
}
