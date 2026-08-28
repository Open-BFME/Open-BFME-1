// cl: /DNDEBUG /MD /EHsc
// readable body of ?deleteFromList@Radar@@IAE_NPAVObject@@PAPAVRadarObject@@@Z: Code/GameEngine/Source/Common/System/Radar.cpp

// Radar::deleteFromList, retail 0x00106BC0. A singly-linked removal with the
// previous node carried in the register the return value later uses.
//
// Each node holds its object at +0x04 and its next at +0x08. On a hit the node
// is unlinked - through the head pointer the caller passed when it is first,
// through the previous node otherwise - the object's back-pointer at +0x20C is
// cleared, and the node is destroyed through its own vftable slot 0 with the
// deleting flag set. Walking off the end returns false without touching
// anything.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class RadarObject
{
public:
	virtual void deleteInstance( int deleting ) = 0;	// slot 0

	class Object *m_object;					// +0x04
	RadarObject *m_next;					// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_unmodelled_00[ 0x20C ];
	RadarObject *m_radarObject;				// +0x20C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar
{
protected:
	Bool deleteFromList( Object *obj, RadarObject **listHead );
};

// ?deleteFromList@Radar@@IAE_NPAVObject@@PAPAVRadarObject@@@Z
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

			obj->m_radarObject = 0;

			cur->deleteInstance( 1 );

			return true;
		}

		prev = cur;
		cur = cur->m_next;
	}

	return false;
}
