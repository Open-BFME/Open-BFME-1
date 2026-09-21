// ?d_00327a00@@YAXXZ
// partial score=0.20 date=2026-09-21
// (carved, no named caller -- "callers (2 sites, 2 via ILT thunk):" resolved no names)
//
// This candidate should be spliced into
// Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp right
// after ScriptConditions::evaluateBuiltByPlayer() -- it needs that TU's real
// ScriptConditions/Condition/Parameter/ObjectTypesTemp/PlayerMaskType/
// g_bfmeP1087/ThePlayerList/TheThingFactory/TheScriptEngine declarations
// (all already present there); written standalone below only for the stash.
//
// IDENTITY (high confidence, semantics only -- see residue below for the
// unresolved mechanical problem):
//   Disassembly matches ScriptConditions::evaluateBuiltByPlayer's shape
//   (Code/.../ScriptConditions.cpp:1103) almost line for line -- same
//   TheThingFactory->findTemplate, same pCondition->getCustomData()/
//   getCustomFrame()/setCustomData()/setCustomFrame() cache dance (reads
//   TheScriptEngine+0x170d8 inline, matching Scripts.h's
//   getFrameObjectCountChanged()), same ObjectTypesTemp/objectTypesFromParam/
//   prepForPlayerCounting/rts::sum(counts) tail -- but two concrete
//   differences from the existing evaluateBuiltByPlayer source:
//     1. the findTemplate/pTemplate==NULL check happens BEFORE the
//        getCustomData() cache check (evaluateBuiltByPlayer has it after);
//     2. the player comes from a player-mask parameter through
//        g_bfmeP1087->bfmeNext1087(pPlayerParm) then (once, not a while loop
//        -- no backward branch to the getEachPlayerFromMask call site)
//        ThePlayerList->getEachPlayerFromMask(playerMask), the exact idiom
//        the already-landed ScriptConditions::evaluateRva003231E0 sibling
//        uses (same file, ~line 2195) -- instead of playerFromParam(). The
//        "numTemplates > 0" guard is also "numTemplates != 0" here (a plain
//        cmp/jne in the disassembly, not a signed jg/jle).
//   Params: (Condition *pCondition, Parameter *pTypeParm, Parameter
//   *pPlayerParm) -- ret 0xc (3 stack args), and 'this'/ecx is read from the
//   incoming register at NO point in the body: retail's very first non-EH
//   instruction loads TheThingFactory (aliased elsewhere in this campaign as
//   Rva0020AA00TheRegistry, same VA 0x012EF1D8 -- confirmed via
//   reverse/symbols.csv) directly into ecx to use as findTemplate's `this`,
//   hoisted above the SEH prologue since it is a fault-free global load.
//
// MECHANICAL PROBLEM (why this only scores 0.20, 523/653 non-reloc bytes
// differ despite the semantic match above): objectTypesFromParam() is a
// PROTECTED ScriptConditions member (real header,
// reference/.../GameLogic/ScriptConditions.h:86), so a plain free function
// or unrelated class cannot call it, and the file has no spare same-shaped
// ZH declaration left to alias the way evaluateRva003231E0 aliases
// evaluatePlayerHasComparisonValueExcessPower (the #define-before-include
// trick, ScriptConditions.cpp:90-91) -- evaluateBuiltByPlayer already owns
// the only (Condition*, Parameter*, Parameter*) slot in the real header.
// The workaround used here, a NEW address-derived class PUBLICLY DERIVING
// from ScriptConditions solely to reach the protected member, compiles and
// reaches the retail SIZE almost exactly (643 vs 653, 10 bytes) but throws
// off MSVC 7.1's register allocation from the very first instruction: ours
// never hoists the TheThingFactory load, and the divergence cascades through
// the whole body (register-mirror family per shape_family_levers.py; an
// eh_levers.py pass found nothing, consistent with this not being an EH
// residue). t=45min model=claude-sonnet-5
//
// NEXT: either find a way to reach the protected objectTypesFromParam()
// without introducing a derived class (a friend shim? a different owning
// class already in this TU with access?), or confirm the derived-class
// approach is unavoidable and chase the register-mirror cascade the way
// 0x007B4940's bank note describes for its own (unrelated) register-mirror
// residue in this same campaign.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt PlayerMaskType;

class AsciiString { public: };
class ThingTemplate { public: };
class ObjectTypes
{
public:
	Int prepForPlayerCounting(void *templates, void *counts);
	void addObjectType(const AsciiString &name);
};
class Parameter
{
public:
	const AsciiString &getString(void) const;
	Int getInt(void) const;
};
class Condition
{
public:
	Int getCustomData(void) const;
	void setCustomData(Int val);
	Int getCustomFrame(void) const;
	void setCustomFrame(Int val);
};
class Player
{
public:
	void countObjectsByThingTemplate(Int count, const ThingTemplate **templates, Bool ignoreDead, Int *counts);
};
class PlayerListStub
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType mask);
};
extern PlayerListStub *ThePlayerList;

class BfmeThingFactoryStub
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern BfmeThingFactoryStub *TheThingFactory;

class ScriptEngineStub
{
public:
	Int getFrameObjectCountChanged(void);
	ObjectTypes *getObjectTypes(const AsciiString &name);
};
extern ScriptEngineStub *TheScriptEngine;

class BfmeP1087
{
public:
	PlayerMaskType bfmeNext1087(Parameter *parameter);
};
extern BfmeP1087 *g_bfmeP1087;

class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;
	ObjectTypesTemp() : m_types(0) {}
	~ObjectTypesTemp() {}
};

// Real ScriptConditions declares objectTypesFromParam() protected; deriving
// is the only way found so far to reach it without a shared-header edit.
class ScriptConditions
{
protected:
	void objectTypesFromParam(Parameter *pTypeParm, ObjectTypes *outObjectTypes);
};

namespace rts { template<typename T> T sum(T &vecOfValues); }

class ScriptConditionsRva00327A00 : public ScriptConditions
{
public:
	Bool evaluateRva00327A00(Condition *pCondition, Parameter* pTypeParm, Parameter* pPlayerParm);
};

Bool ScriptConditionsRva00327A00::evaluateRva00327A00(Condition *pCondition, Parameter* pTypeParm, Parameter* pPlayerParm)
{
	const ThingTemplate* pTemplate = TheThingFactory->findTemplate(pTypeParm->getString());
	if (!pTemplate) {
		return false;
	}

	if (pCondition->getCustomData()!=0) {
		if (TheScriptEngine->getFrameObjectCountChanged() == pCondition->getCustomFrame()) {
			if (pCondition->getCustomData()==1) return true;
			if (pCondition->getCustomData()==-1) return false;
		}
	}

	ObjectTypesTemp types;
	objectTypesFromParam(pTypeParm, types.m_types);

	Int counts[1];
	const ThingTemplate *templates[1];

	Int numTemplates = types.m_types->prepForPlayerCounting(templates, counts);
	if (numTemplates != 0) {
		PlayerMaskType playerMask = g_bfmeP1087->bfmeNext1087(pPlayerParm);
		if (playerMask) {
			Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);
			pPlayer->countObjectsByThingTemplate(numTemplates, templates, false, counts);
		}
	} else {
		return 0;
	}

	Int sumOfObjs = 0; // rts::sum(counts) in the real TU
	pCondition->setCustomData(-1);
	if (sumOfObjs != 0) {
		pCondition->setCustomData(1);
	}
	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	return (sumOfObjs != 0);
}
