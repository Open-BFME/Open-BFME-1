// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: AIGroup::getMinMaxAndCenter, retail 0x00151F70, zh_sweep packet
// 00151f70.
//
// The Zero Hour body needed no logic change -- every branch, every x87 min/max
// ternary and the count/formation bookkeeping are already what retail runs.
// What it needed was the object layout, none of which the vendored headers
// agree with, so this is its own TU rather than a shared-header edit.
//
// The bytes pin all of it. m_memberList is AIGroup+0x04. On Object the
// position is +0x38, the disabled mask +0x1A4 (retail tests it a byte at a
// time, mask 0x08 for DISABLED_HELD), the AI update interface +0x204 and the
// formation ID +0x31C.
//
// One real source difference: retail divides once and multiplies three times
// -- fild count, fdivr 1.0f, then fmul into each of x, y and z -- where Zero
// Hour writes three /= count. MSVC will not turn division into a reciprocal
// on its own, so BFME hoisted it.
//
// The dead `if (id == NO_FORMATION_ID) id = NO_FORMATION_ID;` survives as a
// bare test and a jne over nothing (75 00) with the store optimised away.
// It is kept because dropping it removes those three bytes.

#include <list>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int FormationID;

enum { NO_FORMATION_ID = 0 };

enum { DISABLED_HELD = 0x00000008 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;														///< +0x00
	Real y;														///< +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;														///< +0x00
	Real y;														///< +0x04
	Real z;														///< +0x08
};

class AIUpdateInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	// Handed out raw, not as an isDisabledByType predicate: a bool return
	// normalises to shr 3 / test al,1, where retail tests the mask byte in
	// place. BFME's mask is a plain word, not Zero Hour's BitFlags bitset.
	Int getDisabledMask( void ) const { return m_disabledMask; }
	AIUpdateInterface *getAIUpdateInterface( void ) { return m_ai; }
	const Coord3D *getPosition( void ) const { return &m_position; }
	FormationID getFormationID( void ) const { return m_formationID; }

private:
	unsigned char m_unreconstructed_00[0x38];					///< +0x0000
	Coord3D m_position;											///< +0x0038
	unsigned char m_unreconstructed_44[0x1A4 - 0x44];			///< +0x0044
	Int m_disabledMask;											///< +0x01A4
	unsigned char m_unreconstructed_1a8[0x204 - 0x1A8];			///< +0x01A8
	AIUpdateInterface *m_ai;									///< +0x0204
	unsigned char m_unreconstructed_208[0x31C - 0x208];			///< +0x0208
	FormationID m_formationID;									///< +0x031C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	Bool getMinMaxAndCenter( Coord2D *min, Coord2D *max, Coord3D *center );

private:
	unsigned char m_unreconstructed_00[4];						///< +0x00
	std::list<Object *> m_memberList;							///< +0x04
};

// ?getMinMaxAndCenter@AIGroup@@QAE_NPAUCoord2D@@0PAUCoord3D@@@Z
Bool AIGroup::getMinMaxAndCenter( Coord2D *min, Coord2D *max, Coord3D *center )
{
	Int count = 0;
	min->x = 1e10f;
	max->x = -1e10f;
	min->y = 1e10f;
	max->y = -1e10f;
	center->x = 0.0f;
	center->y = 0.0f;
	center->z = 0.0f;

	std::list<Object *>::iterator i;
	FormationID id = NO_FORMATION_ID;
	for( i = m_memberList.begin(); i != m_memberList.end(); ++i )
	{
		if( (*i)->getDisabledMask() & DISABLED_HELD )
		{
			continue; // don't bother counting riders in the center calculation.
		}
		AIUpdateInterface *ai = (*i)->getAIUpdateInterface();
		if (ai)
		{
			const Coord3D *objPos = (*i)->getPosition();
			center->x += objPos->x;
			center->y += objPos->y;
			center->z += objPos->z;

			//Calculate the bounding coordinates of all units
			min->x = min->x > objPos->x ? objPos->x : min->x;
			max->x = max->x < objPos->x ? objPos->x : max->x;
			min->y = min->y > objPos->y ? objPos->y : min->y;
			max->y = max->y < objPos->y ? objPos->y : max->y;
			FormationID curID = (*i)->getFormationID() ;
			if (count==0) {
				id = curID;
			} else {
				if (id == NO_FORMATION_ID) {
					id = NO_FORMATION_ID;
				}
			}

			count++;
		}
	}

	Real oneOverCount = 1.0f / count;
	center->x *= oneOverCount;
	center->y *= oneOverCount;
	center->z *= oneOverCount;
	Bool isFormation = (id != NO_FORMATION_ID);
	if (count < 2) isFormation = false;
	return isFormation;
}
