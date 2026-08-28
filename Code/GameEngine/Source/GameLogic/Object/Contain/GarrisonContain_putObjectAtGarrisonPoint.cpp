// cl: /DNDEBUG /MD /EHsc
// readable body of ?putObjectAtGarrisonPoint@GarrisonContain@@: Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp
// Open-BFME: GarrisonContain::putObjectAtGarrisonPoint, retail 0x0021D750,
// 161 bytes.
//
// The reference's body up to the point counter; BFME drops everything after it
// -- the GarrisonGun muzzle drawable and the shroud copy are gone.
//
// The point data entry is 20 bytes and the slot holds the object's ID, not the
// object: retail reads Object+0x74 and stores that.  The arrays are at +0xD8
// (40 entries) and +0x3FC (3 conditions of 40 positions), with the in-use count
// at +0x3F8 between them, and the two bounds are the reference's own 40 and 3.

typedef int Int;
typedef unsigned int UnsignedInt;
enum ObjectID { INVALID_ID = 0 };
typedef float Real;

struct Coord3D { Real x, y, z; };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setPosition(const Coord3D *pos);			// ILT 0x0003A1A7
	ObjectID getID(void) const { return m_id; }

private:
	unsigned char m_unmodelled_000[0x74];
	ObjectID m_id;						// Object+0x74
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) const { return m_frame; }

private:
	unsigned char m_unmodelled_000[0x3C];
	UnsignedInt m_frame;					// +0x3C
};

extern GameLogic *TheGameLogic;

enum { MAX_GARRISON_POINTS = 40 };
enum { MAX_GARRISON_POINT_CONDITIONS = 3 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
class GarrisonContain
{
protected:
	void putObjectAtGarrisonPoint( Object *obj, ObjectID targetID, Int conditionIndex, Int pointIndex );

private:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GarrisonContain.h
	struct GarrisonPointData
	{
		ObjectID object;				// +0x00
		ObjectID targetID;				// +0x04
		UnsignedInt placeFrame;				// +0x08
		unsigned char m_unmodelled_00c[8];		// +0x0C
	};

	unsigned char m_unmodelled_000[0xD8];
	GarrisonPointData m_garrisonPointData[MAX_GARRISON_POINTS];			// +0x0D8
	Int m_garrisonPointsInUse;							// +0x3F8
	Coord3D m_garrisonPoint[MAX_GARRISON_POINT_CONDITIONS][MAX_GARRISON_POINTS];	// +0x3FC
};

void GarrisonContain::putObjectAtGarrisonPoint( Object *obj,
																								ObjectID targetID,
																								Int conditionIndex,
																								Int pointIndex )
{

	// sanity
	if( obj == 0 || pointIndex < 0 || pointIndex >= MAX_GARRISON_POINTS ||
			conditionIndex < 0 || conditionIndex >= MAX_GARRISON_POINT_CONDITIONS )
	{

		return;

	}  // end if

	// make sure this point is empty
	if( m_garrisonPointData[ pointIndex ].object != INVALID_ID )
	{

		return;

	}  // end if

	// get the position we're going to use
	const Coord3D &pt = m_garrisonPoint[ conditionIndex ][ pointIndex ];
	Coord3D pos;
	pos = pt;

	// set the object position
	obj->setPosition( &pos );

	// save the data for being place at this point
	m_garrisonPointData[ pointIndex	].object = obj->getID();
	m_garrisonPointData[ pointIndex	].targetID = targetID;
	m_garrisonPointData[ pointIndex	].placeFrame = TheGameLogic->getFrame();
	++m_garrisonPointsInUse;

}
