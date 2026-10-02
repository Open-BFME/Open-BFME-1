// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// UnitCrateCollide::executeCrateBehavior (retail 0x00218A00, 381 B): slot 10 of UnitCrateCollide's table
// 0x010AAB8C through ILT 0x000189BC. Zero Hour's UnitCrateCollide.cpp body on BFME types: 4-argument
// newObject, free findPositionAround, 0x70-byte AudioEventRTS, audio slots +0x124/+0x44.

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum ObjectID { INVALID_ID = 0 };

struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	// Retail copies member by member straight from Object+0x38.
	Coord3D( const Coord3D &o ) : x( o.x ), y( o.y ), z( o.z ) {}
};

class Team;
class ThingTemplate;

// A plain aggregate: ObjectStatusMaskType() value-initializes it with one zero register.
template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[3];
};

typedef BitFlags<86> ObjectStatusMaskType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Team *bfmeTeam230() const { return m_bfmeTeam230; }	///< Zero Hour's getDefaultTeam() here
private:
	char m_unmodelled000[0x230];
	Team *m_bfmeTeam230;								///< this+0x230
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void setOrientation( Real angle );
	void setPosition( const Coord3D *pos );
	const Coord3D *getPosition() const { return &m_cachedPos; }
	Real getOrientation() const { return m_cachedAngle; }
private:
	char m_unmodelled000[0x38];
	Coord3D m_cachedPos;								///< this+0x38
	Real m_cachedAngle;									///< this+0x44
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	ObjectID getID() const { return m_id; }
private:
	char m_unmodelled048[0x74 - 0x48];
	ObjectID m_id;										///< this+0x74
};

// Only the entry points this body calls, under their ledger names.
class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};

class ThingFactory
{
public:
	Object *newObject( const ThingTemplate *tmplate, Team *team, const ObjectStatusMaskType &statusBits, UnsignedInt bfmeFlags );
};

extern ThingFactory *TheThingFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
struct FindPositionOptions
{
	FindPositionOptions()
	{
		flags = 0;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;							// RANDOM_START_ANGLE
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}
	UnsignedInt flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

Bool findPositionAround( const Coord3D *center, const FindPositionOptions *options, Coord3D *result );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioEventRTS
{
public:
	AudioEventRTS( const AudioEventRTS &right );
	~AudioEventRTS();
	void setObjectID( ObjectID objID );
private:
	char m_unmodelled000[0x70];
};

struct MiscAudio
{
	char m_unmodelled000[0x9a0];
	AudioEventRTS m_crateFreeUnit;						///< this+0x9A0
};

#define BFME_AUDIO_SLOT(n) virtual void bfmeAudioSlot##n() = 0;

class AudioManager
{
public:
	BFME_AUDIO_SLOT(0) BFME_AUDIO_SLOT(1) BFME_AUDIO_SLOT(2) BFME_AUDIO_SLOT(3)
	BFME_AUDIO_SLOT(4) BFME_AUDIO_SLOT(5) BFME_AUDIO_SLOT(6) BFME_AUDIO_SLOT(7)
	BFME_AUDIO_SLOT(8) BFME_AUDIO_SLOT(9) BFME_AUDIO_SLOT(10) BFME_AUDIO_SLOT(11)
	BFME_AUDIO_SLOT(12) BFME_AUDIO_SLOT(13) BFME_AUDIO_SLOT(14) BFME_AUDIO_SLOT(15)
	BFME_AUDIO_SLOT(16)
	virtual void addAudioEvent( const AudioEventRTS *eventToAdd ) = 0;	///< vtable +0x44
	BFME_AUDIO_SLOT(18) BFME_AUDIO_SLOT(19) BFME_AUDIO_SLOT(20) BFME_AUDIO_SLOT(21)
	BFME_AUDIO_SLOT(22) BFME_AUDIO_SLOT(23) BFME_AUDIO_SLOT(24) BFME_AUDIO_SLOT(25)
	BFME_AUDIO_SLOT(26) BFME_AUDIO_SLOT(27) BFME_AUDIO_SLOT(28) BFME_AUDIO_SLOT(29)
	BFME_AUDIO_SLOT(30) BFME_AUDIO_SLOT(31) BFME_AUDIO_SLOT(32) BFME_AUDIO_SLOT(33)
	BFME_AUDIO_SLOT(34) BFME_AUDIO_SLOT(35) BFME_AUDIO_SLOT(36) BFME_AUDIO_SLOT(37)
	BFME_AUDIO_SLOT(38) BFME_AUDIO_SLOT(39) BFME_AUDIO_SLOT(40) BFME_AUDIO_SLOT(41)
	BFME_AUDIO_SLOT(42) BFME_AUDIO_SLOT(43) BFME_AUDIO_SLOT(44) BFME_AUDIO_SLOT(45)
	BFME_AUDIO_SLOT(46) BFME_AUDIO_SLOT(47) BFME_AUDIO_SLOT(48) BFME_AUDIO_SLOT(49)
	BFME_AUDIO_SLOT(50) BFME_AUDIO_SLOT(51) BFME_AUDIO_SLOT(52) BFME_AUDIO_SLOT(53)
	BFME_AUDIO_SLOT(54) BFME_AUDIO_SLOT(55) BFME_AUDIO_SLOT(56) BFME_AUDIO_SLOT(57)
	BFME_AUDIO_SLOT(58) BFME_AUDIO_SLOT(59) BFME_AUDIO_SLOT(60) BFME_AUDIO_SLOT(61)
	BFME_AUDIO_SLOT(62) BFME_AUDIO_SLOT(63) BFME_AUDIO_SLOT(64) BFME_AUDIO_SLOT(65)
	BFME_AUDIO_SLOT(66) BFME_AUDIO_SLOT(67) BFME_AUDIO_SLOT(68) BFME_AUDIO_SLOT(69)
	BFME_AUDIO_SLOT(70) BFME_AUDIO_SLOT(71) BFME_AUDIO_SLOT(72)
	virtual MiscAudio *getMiscAudio() = 0;				///< vtable +0x124
};

#undef BFME_AUDIO_SLOT

class ClientSubsystem;
extern ClientSubsystem *TheAudioClientUpdate;

struct UnitCrateCollideModuleData
{
	char m_unmodelled000[0x54];
	UnsignedInt m_unitCount;							///< this+0x54
	AsciiString m_unitType;								///< this+0x58
};

class UnitCrateCollide
{
public:
	virtual Bool executeCrateBehavior( Object *other );

	const UnitCrateCollideModuleData *getUnitCrateCollideModuleData() const { return m_moduleData; }

private:
	const UnitCrateCollideModuleData *m_moduleData;		///< this+0x04
};

// ?executeCrateBehavior@UnitCrateCollide@@UAE_NPAVObject@@@Z
Bool UnitCrateCollide::executeCrateBehavior( Object *other )
{
	UnsignedInt unitCount = getUnitCrateCollideModuleData()->m_unitCount;
	ThingTemplate const *unitType = ((BfmeThingFactory *)TheThingFactory)->findTemplate( getUnitCrateCollideModuleData()->m_unitType );

	if( unitType == 0 )
	{
		return false;
	}

	for( UnsignedInt unitIndex = 0; unitIndex < unitCount; unitIndex++ )
	{
		Team *creationTeam = other->getControllingPlayer()->bfmeTeam230();
		Object *newObj = TheThingFactory->newObject( unitType, creationTeam, ObjectStatusMaskType(), 0 );
		if( newObj )
		{
			Coord3D creationPoint = *other->getPosition();
			FindPositionOptions fpOptions;
			fpOptions.minRadius = 0.0f;
			fpOptions.maxRadius = 20.0f;
			findPositionAround( &creationPoint, &fpOptions, &creationPoint );

			newObj->setOrientation( other->getOrientation() );
			newObj->setPosition( &creationPoint );
		} 
	}

	//Play a crate pickup sound.
	AudioEventRTS soundToPlay = ((AudioManager *)TheAudioClientUpdate)->getMiscAudio()->m_crateFreeUnit;
	soundToPlay.setObjectID( other->getID() );
	((AudioManager *)TheAudioClientUpdate)->addAudioEvent(&soundToPlay);

	return true;
}
