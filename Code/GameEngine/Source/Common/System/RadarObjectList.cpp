// cl: /DNDEBUG /MD /EHsc
// readable body of ?deleteFromList@Radar@@IAE_NPAVObject@@PAPAVRadarObject@@@Z: Code/GameEngine/Source/Common/System/Radar.cpp
// readable body of ?deleteListResources@Radar@@IAEXXZ: Code/GameEngine/Source/Common/System/Radar.cpp
// readable body of ?isTemporarilyHidden@RadarObject@@QBE_NXZ: Code/GameEngine/Source/Common/System/Radar.cpp

// The radar's object lists and what hangs off a node.
//
//   deleteListResources 0x00106A90   tear both lists down
//   deleteFromList      0x00106BC0   unlink one object's node
//   isTemporarilyHidden 0x00106B90   whether a node's object draws right now
//
// One RadarObject layout serves all three, and each offset in it is something
// one of the bodies proves: the vftable at +0x00 whose slot 0 is the scalar
// deleting destructor both teardown paths call, the owning object at +0x04 that
// all three read, and the next link at +0x08 the two walks follow. The lists
// themselves hang off the radar at +0x10 and +0x14.
//
// Object is sliced the same way: the next-object link at +0x88 that the trailing
// walk in deleteListResources follows, the radar back-pointer at +0x20C that
// both teardown paths clear, and the vftable whose slot 10 is getDrawable.
// isTemporarilyHidden's identity is fixed by W3DRadar::renderObjectList, whose
// matched body calls it at the source loop's isTemporarilyHidden() test.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class RadarObject;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	bool isDrawableEffectivelyHidden() const;

	unsigned char m_pad[0x15c];
	int m_stealthLook;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual Drawable *getDrawable() const;

	void friend_setRadarData(RadarObject *radarData) { m_radarData = radarData; }
	Object *getNextObject(void) { return m_next; }

	char m_slice_padA[0x88 - 4];				// vftable at +0x00, then untouched to +0x87
	Object *m_next;						// this+0x88
	char m_slice_padB[0x20C - 0x8C];			// this+0x8C .. +0x20B, untouched
	RadarObject *m_radarData;				// this+0x20C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class RadarObject
{
public:
	virtual ~RadarObject();					// vftable slot 0

	Object *friend_getObject(void) { return m_object; }
	RadarObject *friend_getNext(void) { return m_next; }
	bool isTemporarilyHidden() const;

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
	Bool deleteFromList( Object *obj, RadarObject **listHead );

	char m_slice_pad[0x10];					// retail this+0x00 .. +0x0F, untouched
	RadarObject *m_objectList;				// this+0x10
	RadarObject *m_localObjectList;				// this+0x14
};

// ?deleteListResources@Radar@@IAEXXZ
// The reference's body unchanged, including the walk over every object at the
// end -- the reference's assertion loop, which survives with an empty body
// because getFirstObject is a call the compiler will not walk away from.
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

// ?deleteFromList@Radar@@IAE_NPAVObject@@PAPAVRadarObject@@@Z
// A singly-linked removal with the previous node carried in the register the
// return value later uses. On a hit the node is unlinked -- through the head
// pointer the caller passed when it is first, through the previous node
// otherwise -- the object's back-pointer is cleared, and the node is destroyed
// through its own vftable slot 0 with the deleting flag set. Walking off the
// end returns false without touching anything.
Bool Radar::deleteFromList( Object *obj, RadarObject **listHead )
{
	RadarObject *prev = 0;
	RadarObject *cur = *listHead;

	while( cur )
	{
		if( cur->m_object == obj )
		{
			if( prev == 0 )
				*listHead = cur->m_next;
			else
				prev->m_next = cur->m_next;

			obj->m_radarData = 0;

			delete cur;

			return true;
		}

		prev = cur;
		cur = cur->m_next;
	}

	return false;
}

// ?isTemporarilyHidden@RadarObject@@QBE_NXZ
bool RadarObject::isTemporarilyHidden() const
{
	Drawable *draw = m_object->getDrawable();
	if (draw->m_stealthLook == 5 || draw->isDrawableEffectivelyHidden())
		return true;

	return false;
}
