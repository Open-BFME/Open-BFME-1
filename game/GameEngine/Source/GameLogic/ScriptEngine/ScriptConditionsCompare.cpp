// cl: /DNDEBUG /DWIN32 /MD
// The three ScriptConditions conditions that read one scalar out of the game
// and run the script's comparison operator over it:
//
//   0x00323B70  evaluateDistanceBetweenObjects   a named object's cached float
//   0x00324020  evaluateUnitHealth               a named object's body health
//   0x00324390  evaluateCompareNumPlayersInGame  the active player count
//
// All three end in the same six-way switch on the comparison Parameter's Int,
// and two of them open the same way as well, resolving the object through
// ScriptEngine's slot 26. They sat in three files, and the copies had drifted
// in the two ways separate files always drift.
//
// Parameter first. Two files spelled it as eight unnamed bytes and the Int at
// +0x08 and stopped there, hiding the Real at +0x0C that the third one reads
// as the value being compared against. One layout states both: the Int at
// +0x08, the Real at +0x0C.
//
// Then ScriptEngine. Two of the files declare the same virtual at +0x68 with
// the same Parameter argument but disagree about what it returns -- an Object
// in one, a "BfmeThingFBA" in the other. It is one slot and one call; the two
// return types are the same pointer, so the vtable states it once as Object
// and the cached-float body casts, which is also the honest reading: the owner
// of the 0x0000B816 thunk is not proven, only that it is what getUnitNamed
// hands back.
//
// The player counter keeps its address-derived name: PlayerList's body at
// 0x000DF510 is reached through a raw pointer-to-member, never by name.

typedef bool Bool;
typedef int Int;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	Int getInt(void) const { return m_int; }

	unsigned char m_beforeInt[8];
	Int m_int;						// this+0x08
	Real m_real;						// this+0x0C
};

// The cached-float reader at 0x0000B816. Its owner type is not proven; all the
// bodies show is that getUnitNamed returns something this can be called on.
class BfmeThingFBA
{
public:
	Real bfmeGoFBAThunk(void *context);
};

#pragma comment(linker, "/alternatename:?bfmeGoFBAThunk@BfmeThingFBA@@QAEMPAX@Z=?j_0000b816@@YAXXZ")

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BfmeBody
{
public:
	unsigned char m_beforeHealth[0x28];
	Int m_health;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_beforeBody[0x210];
	BfmeBody *m_body;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(Parameter *) = 0;		// slot 26, vtable+0x68
};

extern void b_000df510();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Int countPlayers(Bool includeObservers)		// address-derived: retail 0x000DF510
	{
		typedef Int (PlayerList::*CountFn)(Bool);
		union {
			Int (*raw)(void);
			CountFn member;
		} fn;
		fn.raw = (Int (*)(void))b_000df510;
		return (this->*fn.member)(includeObservers);
	}
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateDistanceBetweenObjects(Parameter *, Parameter *, Parameter *, Parameter *);
	Bool evaluateUnitHealth(Parameter *, Parameter *, Parameter *);
	Bool evaluateCompareNumPlayersInGame(Parameter *, Parameter *);
};

// ?evaluateDistanceBetweenObjects@ScriptConditions@@IAE_NPAVParameter@@000@Z
Bool ScriptConditions::evaluateDistanceBetweenObjects(
	Parameter *pObjectParm, Parameter *pComparisonParm,
	Parameter *pValueParm, Parameter *pContextParm)
{
	if (pObjectParm) {
		if (pContextParm) {
			if (pComparisonParm) {
				if (pValueParm) {
					BfmeThingFBA *object =
						(BfmeThingFBA *)TheScriptEngine->getUnitNamed(pObjectParm);
					if (object) {
						Real contextReal = pContextParm->m_real;
						void *context = *(void **)&contextReal;
						Real value = object->bfmeGoFBAThunk(context);
						switch (pComparisonParm->m_int) {
						case 0: return (value < pValueParm->m_real);
						case 1: return (value <= pValueParm->m_real);
						case 2: return (value == pValueParm->m_real);
						case 3: return (value >= pValueParm->m_real);
						case 4: return (value > pValueParm->m_real);
						case 5: return (value != pValueParm->m_real);
						}
					}
				}
			}
		}
	}

	return false;
}

// ?evaluateUnitHealth@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateUnitHealth(
	Parameter *pUnitParm, Parameter *pComparisonParm, Parameter *pHealthPercent)
{
	Object *theObj = TheScriptEngine->getUnitNamed(pUnitParm);
	if (theObj) {
		BfmeBody *body = theObj->m_body;
		if (body) {
			Int comparison = pComparisonParm->getInt();
			Int current = body->m_health;
			Bool result;
			switch (comparison) {
			case 0: result = current < pHealthPercent->getInt(); break;
			case 1: result = current <= pHealthPercent->getInt(); break;
			case 2: result = current == pHealthPercent->getInt(); break;
			case 3: result = current >= pHealthPercent->getInt(); break;
			case 4: result = current > pHealthPercent->getInt(); break;
			case 5: result = current != pHealthPercent->getInt(); break;
			default: result = false; break;
			}
			if (result)
				return true;
		}
	}

	return false;
}

// ?evaluateCompareNumPlayersInGame@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateCompareNumPlayersInGame(
	Parameter *pComparisonParm, Parameter *pCountParm)
{
	Int count = ThePlayerList->countPlayers(false);
	Bool result = false;

	switch (pComparisonParm->getInt()) {
	case 0: result = count < pCountParm->getInt(); break;
	case 1: result = count <= pCountParm->getInt(); break;
	case 2: result = count == pCountParm->getInt(); break;
	case 3: result = count >= pCountParm->getInt(); break;
	case 4: result = count > pCountParm->getInt(); break;
	case 5: result = count != pCountParm->getInt(); break;
	}

	return result;
}
