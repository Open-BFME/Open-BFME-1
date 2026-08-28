// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateNamedInsideArea@ScriptConditions@@IAE_NPAVParameter@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamInsideAreaEntirely@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamInsideAreaPartially@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// The ScriptConditions trigger-area conditions:
//
//   0x00324AC0  evaluateTeamInsideAreaEntirely   213 bytes
//   0x00324670  evaluateTeamInsideAreaPartially  239 bytes
//   0x003247A0  evaluateNamedInsideArea          248 bytes
//
// They share this translation unit because they share every model in it, down
// to the two ScriptEngine vtable slots and the delegating AsciiString.
//
// Both are the reference's bodies -- the first is the TeamInside condition
// despite its name -- with the one BFME change their sibling
// ScriptConditions_evaluateTeamCanPathToWaypoint.cpp already carries:
// getTeamNamed takes a second Bool the reference does not have.
//
// The two ScriptEngine slots are read off the call sites rather than guessed:
// getTeamNamed is vtable+0x44 (slot 17), which the sibling already pins, and
// getQualifiedTriggerAreaByName is vtable+0x58 (slot 22).
//
// Parameter::getString returns a const reference and getInt the Int at +0x08;
// both are inlined here, so the two by-value AsciiString arguments are built
// in the outgoing argument slots by StringBase<char>'s copy constructor. That
// is why AsciiString is the delegating slice the sibling uses -- a copy
// constructor that visibly forwards to StringBase<char> is what puts the
// __$SEHRec$ store ahead of `mov ecx, esp`.
//
// Two callees are pinned rather than owned, both calls these bodies make on
// the team they looked up: ?allInside@Team@@QBE_NPAVPolygonTrigger@@I@Z at
// 0x000F5A30 and ?someInsideSomeOutside@Team@@QBE_NPAVPolygonTrigger@@I@Z at
// 0x000F5CE0, which the partial condition tries first and falls back from.

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
