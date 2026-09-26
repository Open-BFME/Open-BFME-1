// cl: /DNDEBUG /MD /EHsc
// BFME retail 0x00108A90: Radar.cpp's file-static xferRadarObjectList.
//
// Identity: the Zero Hour twin (reference/.../Common/System/Radar.cpp) is the
// same body line for line -- version 1, count the list, xferUnsignedShort, save
// each node through xferSnapshot, and on load refuse a non-empty list unless
// every node's object is destroyed, then allocate each node and link it to
// the tail.  Its only caller, 0x00108BF0, is Radar::xfer: version 2, the two
// radar bools at +0x0C/+0x0D, this list helper on +0x14 (m_localObjectList)
// and then +0x10 (m_objectList) in the twin's order, then the
// MAX_RADAR_EVENTS (0x40) event count check.  The allocated node is the
// RadarObject: its inlined constructor installs vftable 0x01088838, whose
// slot 2 (ILT 0x000443BE -> 0x00106B70) returns the "RadarObject" literal,
// and stores m_object/m_next/m_color = 0/0/-1 as the twin's constructor does
// (GameMakeColor(255,255,255,255)).  BFME allocates it with plain operator
// new rather than the twin's memory pool.
//
// The helper is static, so MSVC 7.1 gives it a private convention (head in
// eax, xfer in edi); Radar::xfer (0x00108BF0) below is its only caller, as in
// retail.  BFME's Radar::xfer returns early for a light CRC xfer, writes
// version 2, and after the Zero Hour fields drops each event's reference-
// counted attachment on load and transfers the BFME-only fields that follow.

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef Int Color;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

class Snapshot
{
public:
	virtual ~Snapshot();
};

// The BFME Xfer interface is not layout-compatible with the reference ZH
// header; slot names follow TeamInQueueXfer.cpp: IsStoring at +0x08,
// xferVersion at +0x28, xferSnapshot at +0x30, xferUnsignedShort at +0x7C.
class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void xferRGBAColorInt(void *color);
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17(void *value);
	virtual void slot18();
	virtual void xferICoord2D(void *value);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(void *value);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27(void *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
// m_status at +0x90 per tools/name_oracle.py; bit 0 is OBJECT_STATUS_DESTROYED.
class Object
{
public:
	Bool isDestroyed() const { return (m_status & 1) != 0; }

	char m_slice_pad[0x90];
	UnsignedByte m_status;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
// m_object +0x04 and m_next +0x08 as in RadarObjectList.cpp.
class RadarObject : public Snapshot
{
public:
	RadarObject( void )
	{
		m_object = NULL;
		m_next = NULL;
		m_color = -1;
	}

	inline Object *friend_getObject( void ) { return m_object; }
	inline void friend_setNext( RadarObject *next ) { m_next = next; }
	inline RadarObject *friend_getNext( void ) { return m_next; }

protected:
	virtual ~RadarObject();

	Object *m_object;
	RadarObject *m_next;
	Color m_color;
};

struct RadarObjectListXferLocal
{
	union
	{
		XferVersion version;
		XferException error;
	};
};

// ?xferRadarObjectList@@YAXPAVXfer@@PAPAVRadarObject@@@Z
static void xferRadarObjectList( Xfer *xfer, RadarObject **head )
{
	RadarObject *radarObject;

	// version
	RadarObjectListXferLocal local;
	local.version.m_version = 1;
	local.version.m_currentVersion = 1;
	xfer->xferVersion( &local.version );

	// write could of objects in list
	UnsignedShort count = 0;
	for( radarObject = *head; radarObject; radarObject = radarObject->friend_getNext() )
		count++;
	xfer->xferUnsignedShort( &count );

	// xfer the list data
	if( xfer->IsStoring() )
	{

		// save each object
		for( radarObject = *head; radarObject; radarObject = radarObject->friend_getNext() )
		{

			// save this object
			xfer->xferSnapshot( radarObject );

		}  // end for, radarObject

	}  // end if, save
	else
	{

		// the list should be empty at this point as we are loading it as a whole
		if( *head != NULL )
		{
			for( radarObject = *head; radarObject; radarObject = radarObject->friend_getNext() )
			{
				if (!radarObject->friend_getObject()->isDestroyed())
				{
					bfmeFormatText( &local.error, 5, NULL );
					_CxxThrowException( &local.error, &g_rva005c5100ThrowInfo );
				}
			}
		}  // end if

		// read each element
		for( UnsignedShort i = 0; i < count; ++i )
		{

			// alloate a new radar object
			radarObject = new RadarObject;

			// link to the end of the list
			if( *head == NULL )
				*head = radarObject;
			else
			{

				RadarObject *other;
				for( other = *head; other->friend_getNext() != NULL; other = other->friend_getNext() )
				{
				}  // end for, other

				// set the end of the list to point to the new object
				other->friend_setNext( radarObject );

			}  // end else

			// load the data
			xfer->xferSnapshot( radarObject );

		}  // end for i

	}  // end else, load

}  // end xferRadarObjectList

class MidVirtualSlot90Receiver;

void Rva0010BF80(MidVirtualSlot90Receiver *xfer, void *value);

// An event's reference-counted attachment; the load path drops it.
class Rva00108BF0EventAttachment
{
public:
	virtual ~Rva00108BF0EventAttachment();

	void releaseRef()
	{
		if (--m_refCount <= 0)
			delete this;
	}

	Int m_refCount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
struct RadarEvent
{
	Int type;
	Bool active;
	UnsignedInt createFrame;
	UnsignedInt dieFrame;
	UnsignedInt fadeFrame;
	Int color1[4];
	Int color2[4];
	float worldLoc[3];
	Int radarLoc[2];
	Bool soundPlayed;
	Rva00108BF0EventAttachment *m_attachment;
};

enum
{
	MAX_RADAR_EVENTS = 64
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar : public Snapshot
{
protected:
	virtual void xfer(Xfer *xfer);

	unsigned char m_pad04[0x0c - 0x04];
	Bool m_radarHidden;
	Bool m_radarForceOn;
	RadarObject *m_objectList;
	RadarObject *m_localObjectList;
	float m_field18;
	float m_field1C;
	float m_xSample;
	float m_ySample;
	RadarEvent m_event[MAX_RADAR_EVENTS];
	Int m_nextFreeRadarEvent;
	Int m_lastRadarEvent;
	Int m_field1430;
	UnsignedInt m_field1434;
	unsigned char m_pad1438[0x1454 - 0x1438];
	unsigned char m_field1454[0x10];
	Bool m_field1464;
	UnsignedInt m_queueTerrainRefreshFrame;
};

struct RadarXferVersion : public XferVersion
{
	RadarXferVersion(UnsignedByte version, UnsignedByte currentVersion)
	{
		m_version = version;
		m_currentVersion = currentVersion;
	}
};

// ?xfer@Radar@@MAEXPAVXfer@@@Z
void Radar::xfer( Xfer *xfer )
{
	if( xfer->IsLightCRC() )
		return;

	// version
	RadarXferVersion version(1, 2);
	xfer->xferVersion( &version );

	xfer->xferBool( &m_radarHidden );
	xfer->xferBool( &m_radarForceOn );

	xferRadarObjectList( xfer, &m_localObjectList );
	xferRadarObjectList( xfer, &m_objectList );

	// save the radar event count and data
	UnsignedShort eventCountVerify = MAX_RADAR_EVENTS;
	UnsignedShort eventCount = eventCountVerify;
	xfer->xferUnsignedShort( &eventCount );
	if( eventCount != eventCountVerify )
	{
		XferException error;
		bfmeFormatText( &error, 5, NULL );
		_CxxThrowException( &error, &g_rva005c5100ThrowInfo );
	}

	for( UnsignedShort i = 0; i < eventCount; ++i )
	{
		Rva0010BF80( (MidVirtualSlot90Receiver *)xfer, &m_event[ i ].type );
		xfer->xferBool( &m_event[ i ].active );
		xfer->xferUnsignedInt( &m_event[ i ].createFrame );
		xfer->xferUnsignedInt( &m_event[ i ].dieFrame );
		xfer->xferUnsignedInt( &m_event[ i ].fadeFrame );
		xfer->xferRGBAColorInt( m_event[ i ].color1 );
		xfer->xferRGBAColorInt( m_event[ i ].color2 );
		xfer->xferCoord3D( m_event[ i ].worldLoc );
		xfer->xferICoord2D( m_event[ i ].radarLoc );
		xfer->xferBool( &m_event[ i ].soundPlayed );

		if( !xfer->IsStoring() && m_event[ i ].m_attachment )
		{
			m_event[ i ].m_attachment->releaseRef();
			m_event[ i ].m_attachment = NULL;
		}
	}

	xfer->xferInt( &m_nextFreeRadarEvent );
	xfer->xferInt( &m_lastRadarEvent );

	xfer->slot27( &m_field18 );
	xfer->slot27( &m_field1C );
	xfer->slot27( &m_xSample );
	xfer->slot27( &m_ySample );

	xfer->slot17( m_field1454 );
	xfer->xferBool( &m_field1464 );
	xfer->slot17( m_field1454 );
	xfer->xferUnsignedInt( &m_queueTerrainRefreshFrame );

	if( version.m_currentVersion >= 2 )
	{
		xfer->xferInt( &m_field1430 );
		xfer->xferUnsignedInt( &m_field1434 );
	}
}
