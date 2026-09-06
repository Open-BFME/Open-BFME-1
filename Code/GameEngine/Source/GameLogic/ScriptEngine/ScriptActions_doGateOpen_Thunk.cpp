// cl: /DNDEBUG /MD /EHsc
//
// GATE_OPEN (script action 463) dispatches through 0x000123A5 to the retail
// body at 0x002F0B00.  The body resolves the named unit, looks up the
// GateOpenAndCloseBehavior module, and performs the state-0 transition only
// when the proven state-one predicate is false and the ready flag is set.

class AsciiString;
enum NameKeyType { };

class Object;
// ScriptEngine's BFME vtable has getUnitNamed at slot 26 (+0x68).  The full
// preceding slot run is retained so the call is to the proven BFME interface,
// not to a shortened helper vtable.
class ScriptEngine
{
public:
	virtual void _bfme_se_slot_00() = 0;
	virtual void _bfme_se_slot_01() = 0;
	virtual void _bfme_se_slot_02() = 0;
	virtual void _bfme_se_slot_03() = 0;
	virtual void _bfme_se_slot_04() = 0;
	virtual void _bfme_se_slot_05() = 0;
	virtual void _bfme_se_slot_06() = 0;
	virtual void _bfme_se_slot_07() = 0;
	virtual void _bfme_se_slot_08() = 0;
	virtual void _bfme_se_slot_09() = 0;
	virtual void _bfme_se_slot_10() = 0;
	virtual void _bfme_se_slot_11() = 0;
	virtual void _bfme_se_slot_12() = 0;
	virtual void _bfme_se_slot_13() = 0;
	virtual void _bfme_se_slot_14() = 0;
	virtual void _bfme_se_slot_15() = 0;
	virtual void _bfme_se_slot_16() = 0;
	virtual void _bfme_se_slot_17() = 0;
	virtual void _bfme_se_slot_18() = 0;
	virtual void _bfme_se_slot_19() = 0;
	virtual void _bfme_se_slot_20() = 0;
	virtual void _bfme_se_slot_21() = 0;
	virtual void _bfme_se_slot_22() = 0;
	virtual void _bfme_se_slot_23() = 0;
	virtual void _bfme_se_slot_24() = 0;
	virtual void _bfme_se_slot_25() = 0;
	virtual Object *getUnitNamed(const AsciiString& unitName) = 0;
};
extern ScriptEngine *TheScriptEngine;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
public:
	virtual void moduleSlot();
};

class Object
{
public:
	Module *findModule(NameKeyType key) const;
};

// The primary GateOpenAndCloseBehavior vtable is a complete 13-slot table at
// 0x010A41CC.  All slots are represented; the three slots used here are tied
// to the proven bodies at 0x001FC390, 0x001FD550, and 0x001FC3C0.
class GateOpenAndCloseBehaviorView
{
public:
	virtual void _bfme_gate_slot_00() = 0;
	virtual void _bfme_gate_slot_01() = 0;
	virtual void _bfme_gate_slot_02() = 0;
	virtual void _bfme_gate_slot_03() = 0;
	virtual void _bfme_gate_slot_04() = 0;
	virtual void _bfme_gate_slot_05() = 0;
	virtual bool stateIsOne() = 0; // +0x18, 0x001FC390: (+0x28 == 1)
	virtual void transitionStateZero() = 0; // +0x1c, 0x001FD550
	virtual void _bfme_gate_slot_08() = 0; // +0x20, 0x001FD5A0
	virtual void _bfme_gate_slot_09() = 0;
	virtual bool isReady() = 0; // +0x28, 0x001FC3C0
	virtual void _bfme_gate_slot_11() = 0;
	virtual void _bfme_gate_slot_12() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doGateOpen(const AsciiString& gateName);
};

// ?doGateOpen@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doGateOpen(const AsciiString& gateName)
{
	Object *object = TheScriptEngine->getUnitNamed(gateName);
	if (object == 0)
		return;

	static NameKeyType gateKey =
		TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
	Module *module = object->findModule(gateKey);
	if (module == 0)
		return;

	GateOpenAndCloseBehaviorView *gate =
		reinterpret_cast<GateOpenAndCloseBehaviorView *>(
			reinterpret_cast<unsigned char *>(module) - 4);
	if (gate == 0)
		return;

	if (!gate->stateIsOne() && gate->isReady())
		gate->transitionStateZero();
}
