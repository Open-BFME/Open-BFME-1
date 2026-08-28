// cl: /DNDEBUG /MD /EHsc
// readable body of ?deleteListResources@Radar@@IAEXXZ: Code/GameEngine/Source/Common/System/Radar.cpp
// Open-BFME: Radar::deleteListResources, retail 0x00106A90, 130 bytes.
//
// The reference's body unchanged, including the walk over every object at the
// end -- the reference's assertion loop, which survives with an empty body
// because getFirstObject is a call the compiler will not walk away from.
//
// The layout comes out of it: the regular object list at this+0x10 and the
// local one at +0x14, a radar object's owner at its +0x04 and its next link at
// +0x08, the object's radar-data pointer at +0x20C and its next-object link at
// +0x88. deleteInstance is the scalar deleting destructor at vtable slot 0.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class RadarObject;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void friend_setRadarData(RadarObject *radarData) { m_radarData = radarData; }
	Object *getNextObject(void) { return m_next; }

private:
	char m_slice_padA[0x88];				// retail this+0x00 .. +0x87, untouched
	Object *m_next;						// this+0x88
	char m_slice_padB[0x20C - 0x8C];			// this+0x8C .. +0x20B, untouched
	RadarObject *m_radarData;				// this+0x20C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class RadarObject
{
public:
	virtual ~RadarObject();					// vtable slot 0

	Object *friend_getObject(void) { return m_object; }
	RadarObject *friend_getNext(void) { return m_next; }

private:
	Object *m_object;					// this+0x04
	RadarObject *m_next;					// this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *getFirstObject(void);				// ILT 0x000358BE
};

extern GameLogic *TheGameLogic;					// 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar
{
protected:
	void deleteListResources(void);

	char m_slice_pad[0x10];					// retail this+0x00 .. +0x0F, untouched
	RadarObject *m_objectList;				// this+0x10
	RadarObject *m_localObjectList;				// this+0x14
};

void Radar::deleteListResources( void )
{
	RadarObject *nextObject;

	// delete entries from the local object list
	while( m_localObjectList )
	{

		// get next object
		nextObject = m_localObjectList->friend_getNext();

		// remove radar data from object
		m_localObjectList->friend_getObject()->friend_setRadarData( 0 );

		// delete the head of the list
		delete m_localObjectList;

		// set head of the list to the next object
		m_localObjectList = nextObject;

	}  // end while

	// delete entries from the regular object list
	while( m_objectList )
	{

		// get next object
		nextObject = m_objectList->friend_getNext();

		// remove radar data from object
		m_objectList->friend_getObject()->friend_setRadarData( 0 );

		// delete the head of the list
		delete m_objectList;

		// set head of the list to the next object
		m_objectList = nextObject;

	}  // end while

	Object *obj;
	for( obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject() )
	{

	}

}  // end deleteListResources
