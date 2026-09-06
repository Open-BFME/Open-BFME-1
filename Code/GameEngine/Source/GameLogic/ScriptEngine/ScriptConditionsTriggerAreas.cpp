// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateNamedInsideArea@ScriptConditions@@IAE_NPAVParameter@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamInsideAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamInsideAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamEnteredAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamEnteredAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamExitedAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamExitedAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateNamedExitedArea@ScriptConditions@@IAE_NPAVParameter@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateSkirmishNamedAreaExists@ScriptConditions@@IAE_NPAVParameter@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// Every ScriptConditions condition that asks where something is relative to a
// trigger area:
//
//   0x00324670  evaluateTeamInsideAreaPartially   someInsideSomeOutside || allInside
//   0x003247A0  evaluateNamedInsideArea           pointInTrigger on the object
//   0x00324AC0  evaluateTeamInsideAreaEntirely    allInside
//   0x00324E40  evaluateTeamEnteredAreaEntirely   didAllEnter       0x000F5580
//   0x00324ED0  evaluateTeamEnteredAreaPartially  didPartialEnter   0x000F56D0
//   0x00324F60  evaluateTeamExitedAreaEntirely    didAllExit        0x000F58B0
//   0x00324FF0  evaluateTeamExitedAreaPartially   didPartialExit    0x000F57C0
//   evaluateNamedExitedArea                       didExit
//   evaluateSkirmishNamedAreaExists               the lookup alone
//
// All nine look the area up the same way and differ only in what they ask of
// it, so they share every model here. They sat in four files that each carried
// a private copy of Parameter, AsciiString, StringBase and the ScriptEngine
// vtable, and those copies had already drifted: two spelled Parameter as a
// 0x10-byte run to the string, hiding the Int at +0x08 that the other two
// read, and each file cut the vtable off after the last slot it happened to
// need (17, 22 or 26).
//
// The Team callees are the Team.cpp cluster in that file's order, ending at
// allInside (0x000F5A30) and someInsideSomeOutside (0x000F5CE0). BFME's
// getTeamNamed takes a second Bool the reference does not have.
//
// Parameter::getString returns a const reference and getInt the Int at +0x08;
// both are inlined here, so the by-value AsciiString arguments are built in
// the outgoing argument slots by StringBase<char>'s copy constructor. That is
// why AsciiString is a delegating slice: a copy constructor that visibly
// forwards to StringBase<char> is what puts the __$SEHRec$ store ahead of
// `mov ecx, esp`.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

typedef float Real;

// Member-wise, because retail's copy is: the position's y and z go through
// general registers into the local while x is fld'd straight out of the object
// for the first __ftol, which a block copy of the three would not do.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D(void) {}
	Coord3D(const Coord3D &other) { x = other.x; y = other.y; z = other.z; }

	Real x, y, z;
};
struct ICoord3D { Int x, y, z; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	Bool pointInTrigger(ICoord3D &point) const;		// retail 0x0004AB6F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition(void) const { return &m_position; }
	Bool didExit(const PolygonTrigger *pTrigger) const;

private:
	unsigned char m_bfmeHead[0x38];
	Coord3D m_position;					// this+0x38
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	Int getInt(void) const { return m_int; }
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;						// this+0x08
	unsigned char m_beforeString[0x10 - 0x0C];
	AsciiString m_string;					// this+0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool allInside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;			// retail 0x000F5A30
	Bool someInsideSomeOutside(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;	// retail 0x000F5CE0
	Bool didAllEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didPartialEnter(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didPartialExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
	Bool didAllExit(PolygonTrigger *pTrigger, UnsignedInt whichToConsider) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;		// slot 17, vtable+0x44
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString) = 0;	// slot 22, vtable+0x58
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;	// slot 26, vtable+0x68
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateTeamInsideAreaEntirely(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *);
	Bool evaluateNamedInsideArea(Parameter *, Parameter *);
	Bool evaluateTeamEnteredAreaEntirely(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamEnteredAreaPartially(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamExitedAreaEntirely(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamExitedAreaPartially(Parameter *, Parameter *, Parameter *);
	Bool evaluateNamedExitedArea(Parameter *, Parameter *);
	Bool evaluateSkirmishNamedAreaExists(Parameter *, Parameter *);
};

// ?evaluateTeamInsideAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamInsideAreaEntirely(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{// This is actually TeamInside(...)
	Team *theTeam = TheScriptEngine->getTeamNamed( pTeamParm->getString(), false );
	AsciiString triggerName = pTriggerParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (pTrig == 0)
		return false;

	if (theTeam) {
		return theTeam->allInside(pTrig, (UnsignedInt)pTypeParm->getInt());
	}
	return false; // Non existent team isn't in trigger area. :)
}

// ?evaluateTeamInsideAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamInsideAreaPartially(Parameter *pTeamParm, Parameter *pTriggerAreaParm, Parameter *pTypeParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed( pTeamParm->getString(), false );
	AsciiString triggerName = pTriggerAreaParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerAreaParm->getString());

	if (pTrig == 0) return false;
	if (theTeam) {
		return (theTeam->someInsideSomeOutside(pTrig, (UnsignedInt) pTypeParm->getInt()) ||
						theTeam->allInside(pTrig, (UnsignedInt) pTypeParm->getInt()));
	}
	return false; // Non existent team isn't in trigger area. :)
}

// ?evaluateNamedInsideArea@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedInsideArea(Parameter *pUnitParm, Parameter *pTriggerAreaParm )
{
	Object *theObj = TheScriptEngine->getUnitNamed( *(const AsciiString *)pUnitParm );

	if (!theObj) {
		return false;
	}

	AsciiString triggerName = pTriggerAreaParm->getString();
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerAreaParm->getString());
	if (pTrig == 0) return false;
	if (theObj) {
		Coord3D pCoord = *theObj->getPosition();
		ICoord3D iCoord;
		iCoord.x = pCoord.x; iCoord.y = pCoord.y; iCoord.z = pCoord.z;
		return pTrig->pointInTrigger(iCoord);
	}
	return false; // Non existent team isn't in trigger area. :)
}

// ?evaluateTeamEnteredAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamEnteredAreaEntirely(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (pTrig) {
		return pTeam->didAllEnter(pTrig, (UnsignedInt)pTypeParm->getInt());
	}

	return false;
}

// ?evaluateTeamEnteredAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamEnteredAreaPartially(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (pTrig) {
		return pTeam->didPartialEnter(pTrig, (UnsignedInt)pTypeParm->getInt());
	}

	return false;
}

// ?evaluateTeamExitedAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamExitedAreaEntirely(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (!pTrig) {
		return false;
	}

	return (pTeam->didAllExit(pTrig, (UnsignedInt)pTypeParm->getInt()));
}

// ?evaluateTeamExitedAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamExitedAreaPartially(Parameter *pTeamParm, Parameter *pTriggerParm, Parameter *pTypeParm)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (!pTrig) {
		return false;
	}

	return (pTeam->didPartialExit(pTrig, (UnsignedInt)pTypeParm->getInt()));
}

// ?evaluateNamedExitedArea@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedExitedArea(Parameter *pUnitParm, Parameter *pTriggerParm)
{
	Object *pUnit = TheScriptEngine->getUnitNamed(*(const AsciiString *)pUnitParm);
	if (!pUnit) {
		return false;
	}

	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());

	if (!pTrig) {
		return false;
	}

	return (pUnit->didExit(pTrig));
}

// ?evaluateSkirmishNamedAreaExists@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateSkirmishNamedAreaExists(Parameter *, Parameter *pTriggerParm)
{
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	return (pTrig != 0);
}
