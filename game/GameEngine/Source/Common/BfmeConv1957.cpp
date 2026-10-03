// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/namekeygenerator /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include "Common/NameKeyGenerator.h"

class Module;
#define OBJECT_TU_MEMBERS \
	friend char __stdcall bfmeCheckERM(void *handle); \
protected: \
	Module *findModule(NameKeyType key) const;
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

class BfmeThingERM;

class BfmeGlobalERM
{
public:
	virtual void bfmeSlot00ERM();
	virtual void bfmeSlot01ERM();
	virtual void bfmeSlot02ERM();
	virtual void bfmeSlot03ERM();
	virtual void bfmeSlot04ERM();
	virtual void bfmeSlot05ERM();
	virtual void bfmeSlot06ERM();
	virtual void bfmeSlot07ERM();
	virtual void bfmeSlot08ERM();
	virtual void bfmeSlot09ERM();
	virtual void bfmeSlot10ERM();
	virtual void bfmeSlot11ERM();
	virtual void bfmeSlot12ERM();
	virtual void bfmeSlot13ERM();
	virtual void bfmeSlot14ERM();
	virtual void bfmeSlot15ERM();
	virtual void bfmeSlot16ERM();
	virtual void bfmeSlot17ERM();
	virtual void bfmeSlot18ERM();
	virtual void bfmeSlot19ERM();
	virtual void bfmeSlot20ERM();
	virtual void bfmeSlot21ERM();
	virtual void bfmeSlot22ERM();
	virtual void bfmeSlot23ERM();
	virtual void bfmeSlot24ERM();
	virtual void bfmeSlot25ERM();
	virtual BfmeThingERM *bfmeSlot26ERM(void *handle);
};

// retail 0x012F076C: EA's ScriptEngine *TheScriptEngine, defined once in
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp. BfmeGlobalERM
// is this TU's local view of the pointee; cast at the use.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class BfmeIfaceERM
{
public:
	virtual void bfmeIface00ERM();
	virtual void bfmeIface01ERM();
	virtual void bfmeIface02ERM();
	virtual void bfmeIface03ERM();
	virtual void bfmeIface04ERM();
	virtual void bfmeIface05ERM();
	virtual char bfmeIface06ERM();
	virtual void bfmeIface07ERM();
	virtual void bfmeIface08ERM();
	virtual void bfmeIface09ERM();
	virtual char bfmeIface10ERM();

	unsigned char m_bfmeHeadERM[0x3c];
	int m_bfmeCountERM;
};

class BfmeModERM;

char __stdcall bfmeCheckERM(void *handle)
{
	BfmeThingERM *thing =
		((BfmeGlobalERM *)TheScriptEngine)->bfmeSlot26ERM(handle);

	if (thing == 0)
		return 0;

	static int s_bfmeKeyERM =
		TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");

	BfmeModERM *mod = (BfmeModERM *)((const Object *)thing)->findModule(
		(NameKeyType)s_bfmeKeyERM);

	if (mod == 0)
		return 0;

	BfmeIfaceERM *iface = (BfmeIfaceERM *)((char *)mod - 4);

	if (iface == 0)
		return 0;

	if (iface->bfmeIface10ERM() == 0)
		return 0;

	if (iface->m_bfmeCountERM > 0 && iface->bfmeIface06ERM() == 0)
		return 0;

	return 1;
}
